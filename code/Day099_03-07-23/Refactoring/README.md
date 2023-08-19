#link:

# Refactoring

I recently started reading the book [Refactoring: Improving the Design of Existing Code](https://martinfowler.com/books/refactoring.html) 2nd Ed. by Martin Fowler

Fowler defines refactoring as a controlled technique for improving the design of an existing code base by applying a series of small behavior-preserving transformations.

Chapter 1 of the book demonstrates the technique by applying it step by step to a relatively simple example. The book uses Javascript language for the examples, and I thought it would be a good idea to translate the example to C++ as literally as possible and then follow along the steps proposed by Fowler in the book.

## The problem

We are going to refactor the billing software for a theatre company.

Today the billing rules are as follows:

For tragedy: $400 base, if audience > 30: + $10 per each attendee above 30
For comedy: $300 base + $3 per seat, if audience > 20: +$100 bonus + $5 per each attendee above 20

Additionally the company runs a loyalty program that awards credits: 1 credit per seat above the first 30, and for comedies +1 credit per each 5 attendees (Note that the comment in the original code incorrectly states +1 credit per 10 attendees but this is inconsistent with the provided example)

Therefore a step by step calculation for the example provided in the book would look like this:

| Play Type | Attendees | Price | Credits |
|------|-----------|-------|---------|
| tragedy | 55 | $400 + $10 * 25 = $650 | 25 |
| comedy | 35 | $300 + $3 * 35 + $100 + $5 * 15 = $580 | 5 + 7 = 12 |
| tragedy | 40 | $400 + $10 * 10 = $500 | 10 |

Total: $1730 and 47 credits

The customer has requested two changes:
- HTML-formatted statements in addition to the plain text ones
- The company is looking at expanding their repertoire to many more - yet undefined - kinds of play, each with its own charging and credit calculation schemes

## Translating to C++

The original code from Fowler's book is in the following files:

* [statement.js](./statement.js) : javascript code implementing the function `statement(invoice, plays)`
* [plays.json](./plays.json): input data in JSON format listing the repertoire of the theatre company
* [invoices.json](./invoices.json): input data in JSON format listing the plays performed for each customer including the attendance for each play. 

The C++ translation is the following two files:

* [statement.h](./statement.h): definition of the C++ function `std::string statement(Invoice invoice, std::map<std::string, Play> plays)` translated as closely as possible from the original Javascript with some help from ChatGPT. The code defines also simple `Performance`, `Play` and `Invoice` objects and an auxiliary function `formatCurrency()`
* [main.cpp](./main.cpp): a C++ wrapper that reads the input data from the JSON files and calls the function `statement()` with it.

## Building Tests

The First step in refactoring is always building a solid test suite using a testing framework that reports self-checking results and makes it really easy to run the tests often and debug any errors

With [some help from ChatGPT](https://chat.openai.com/share/e87e0468-583b-41b7-95eb-3dea5699b917) I installed  `gtest`and `gmock` and wrote with them  [tests.cpp](./tests.cpp), a test suite that checks some invalid inputs as well as a few additional examples calculated by hand:

| Play Type | Attendees | Price | Credits |
|------|-----------|-------|---------|
| tragedy | 20 | $400 | 0 |
| comedy | 40 | $300 + $3 * 40 + $100 + $5 * 20 = $620 | 10 + 8 = 18 |
| tragedy | 15 | $400 | 0 |
| tragedy | 60 | $400 + $10 * 30 = $700| 30 |

The original code passes the tests:

```bash
[==========] Running 7 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 6 tests from StatementTest
[ RUN      ] StatementTest.OriginalStatement
[       OK ] StatementTest.OriginalStatement (0 ms)
[ RUN      ] StatementTest.SingleTragedyStatement
[       OK ] StatementTest.SingleTragedyStatement (1 ms)
[ RUN      ] StatementTest.SingleComedyStatement
[       OK ] StatementTest.SingleComedyStatement (0 ms)
[ RUN      ] StatementTest.MultiplePerformancesStatement
[       OK ] StatementTest.MultiplePerformancesStatement (0 ms)
[ RUN      ] StatementTest.SingleUnknownPlayTypeStatement
[       OK ] StatementTest.SingleUnknownPlayTypeStatement (0 ms)
[ RUN      ] StatementTest.EmptyInvoiceStatement
[       OK ] StatementTest.EmptyInvoiceStatement (0 ms)
[----------] 6 tests from StatementTest (1 ms total)

[----------] 1 test from FormatCurrencyTest
[ RUN      ] FormatCurrencyTest.Formatting
[       OK ] FormatCurrencyTest.Formatting (0 ms)
[----------] 1 test from FormatCurrencyTest (0 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 2 test suites ran. (1 ms total)
[  PASSED  ] 7 tests.
```

Note: because I add a second C++ source file to the project folder I had to modify the `tasks.json` for vscode to compile only one file at a time. Note I also link to the `gtest` and `gmock` dynamic libraries:

```json
"tasks": [
        {
			...
            "args": [
                "-fdiagnostics-color=always",
                "-I${fileDirname}",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}/bin/${fileBasenameNoExtension}",
                "-lgtest",
                "-lgtest_main",
                "-lgmock",
                "-lgmock_main",
                "-pthread"
                ],
            ... 
```

## The refactoring loop

1. Make a small behavior-preserving transformation in `statement.h`
2. Compile and execute `tests.cpp` to run the tests
3. When tests are green:
   1. (Optionally save a copy of current status in `./steps/statement_[N+1].h`. This is to save intermediate steps and only applies to this tutorial)
   2. Commit changes

### Extracting `amountFor()`

The first actual refactoring step consists of extracting the chunk of code that calculates the charge per one performance to a function `amountFor()` and then renaming parameters and local variables for clarity. 

The author proposes also to remove the  `play` parameter by replacing it with a query. I did it but this seems to make more sense in original Javascript than in the C++ version for two reasons:

- Due to the way scope works in JS the variable `plays` is available inside nested functions such such as `playFor()` or `amountFor()`, but in C++ you need to be pass it explicitly as a parameter, therefore removing the parameter `play`  from `amountFor()`does not result in less parameters being passed
- Additionally, the `switch` statement in C++ works only with integers, so replacing `play.type` with a query `playFor(aPerformance, plays).type` in each if statement results in multiple calls to `playFor()` in each step of the loop which is not very efficient. The author recommends not to worry about this. In JS  there are 3 calls to `playFor()` per loop. However in C++ there are 4 calls (and there will be more when we add more kinds of play...)

I saved the intermediate result as [./steps/statement_01.h](./steps/statement_01.h) 

### Extracting `volumeCreditsFor()`

Next we extract the chunk of code that calculates the credits to a function `volumeCreditsFor()` and rename local variables and parameters.

I saved the intermediate result as [./steps/statement_02.h](./steps/statement_02.h) 

### Change function declaration for `formatCurrency()`

In the original JS code the `format` variable is an instance of type number formatter object. The next refactoring step is replacing this variable with a formatting function, but the C++ translation already created a function for that: `formatCurrency()`. we will rename to `usd()` and move to`/100` inside it.

I used the migration approach. I first defined:

```c++ 
std::string usd(int numberCents) {
    return formatCurrency(numberCents / 100.0);
}
```

And then proceeded to replace all calls to `formatCurrency()` by calls to `usd()` This is cool because it allows both versions to coexist which is good to allow migrating slowly, e.g. to save and test in every replacement and/or to mark the old function as deprecated and allow time for API users to adapt.

Note that I changed the type of the parameter to `int`. This had further implications, for consistency I also changed the declarations of `int totalAmount` and  `int amountFor()` and even the implementation of `amountFor()` so it would return an `int`. Probably should have taken small steps but I did it all in one go.

I added some tests to the test suite to check `usd()` because for amounts < $1 it makes a difference between writing `/100.0` or `/100`.

On a second step I can inline the function `formatCurrency()` and delete it:

```c++
std::string usd(int numberCents) {
    return formatCurrency(numberCents / 100.0);
}
```





I am not too happy with the name and would have preferred something like`formatCentsAsUSD()`

# Tags
#tags: 

- [x] basics
- [ ] algorithms
- [ ] data_structures: trees, graphs
- [ ] strings: regex
- [ ] dates_times: timezones
- [x] file_management: input, output, folders and files
- [x] testing
- [ ] exceptions
- [ ] logging
- [ ] object_oriented_programming
- [ ] GUI
- [ ] plotting_data
- [ ] CLI
- [ ] arduino
- [ ] ROS
- [x] AI_tools: chat GPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [ ] OpenCV