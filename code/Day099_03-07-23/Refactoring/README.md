#link:

# Refactoring

I recently started reading the book [Refactoring: Improving the Design of Existing Code](https://martinfowler.com/books/refactoring.html) 2nd Ed. by Martin Fowler

Fowler defines refactoring as a controlled technique for improving the design of an existing code base by applying a series of small behavior-preserving transformations.

Chapter 1 of the book demonstrates the technique by applying it step by step to a relatively simple example. The book uses Javascript language for the examples, and I thought it would be a good idea to translate the example to C++ as literally as possible and then follow along the steps proposed by Fowler in the book.

By the way it seems that I am not the first person who had the same idea: https://www.eficode.com/blog/turning-an-example-by-martin-fowler-into-a-refactoring-kata

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

The author proposes also to remove the  `play` parameter by replacing it with a query. I did it, but this seems to make more sense in the original Javascript than in the C++ version for two reasons:

- Due to the way scope works in JS the variable `plays` is available inside nested functions such as `playFor()` or `amountFor()`, but in C++ you need to pass it explicitly as a parameter. Therefore in order to replace the parameter `play`  in `amountFor()` by a query, you need to pass `plays` as a parameter, so the whole exercise does not result in less parameters being passed.
- Additionally, the `switch` statement in C++ works only with integers, so replacing `play.type` with the query `playFor(aPerformance, plays).type` in each of the `if` statements results in multiple calls to `playFor()` in each step of the loop which is not very efficient. In JS there are 3 calls to `playFor()` per loop, but in C++ there are 4 calls (and there will be more when we add more kinds of play...). The author recommends not to worry about this. 

I saved the intermediate result as [./steps/statement_01.h](./steps/statement_01.h) 

### Extracting `volumeCreditsFor()`

Next we extract the chunk of code that calculates the credits to a function `volumeCreditsFor()` and rename local variables and parameters.

I saved the intermediate result as [./steps/statement_02.h](./steps/statement_02.h) 

### Deprecating `formatCurrency()`

In the original JS code the `format` variable is an instance of a number formatter object. The next refactoring step is replacing this variable with a formatting function, but the C++ translation already expressed this with a function `formatCurrency()`. In this step we will rename it to `usd()` and move the`/100` inside it.

I used the migration approach. I first defined:

```c++ 
std::string usd(int numberCents) {
    return formatCurrency(numberCents / 100.0);
}
```

And then proceeded to replace all calls to `formatCurrency()` by calls to `usd()` This migration approach is cool because it allows both versions to coexist which is good e.g. to save and test after every replacement and/or to mark the old function as deprecated and allow time for API users to adapt.

Note that I also changed the type of the parameter to `int`. This had further implications, for consistency I also changed the declarations of `int totalAmount` and  `int amountFor()` and even the implementation of `amountFor()` so it would return an `int`. Probably should have taken small steps, but I did it all in one go.

I added some tests to the test suite to check `usd()` because for amounts < $1 it makes a difference between writing `/100.0` or `/100`.

In a second step I can inline the function `formatCurrency()` and delete it (updating also the tests accordingly). The resulting `usd()` looks like this:

```c++
std::string usd(int numberCents)
{
    std::ostringstream formatted;
    formatted.imbue(std::locale("en_US.UTF-8"));
    formatted << "$" << std::fixed << std::setprecision(2) << numberCents / 100.0;
    return formatted.str();
}
```

Note: I am not too happy with the name and would have preferred something like`formatCentsAsUSD()`

I saved the intermediate result as [./steps/statement_03.h](./steps/statement_03.h) 

### Removing `volumeCredits` and `totalAmount`

Four small steps for` volumeCredits`: 

1. split the `for` loop to separate the `volumeCredits`calculation

2. slide the statement the initializes `volumeCredits` to move it next to the loop

3. extract the chunk of code to a function `totalVolumeCredits()`

4. inline the variable `volumeCredits` 

Five small steps for` totalAmount`: 

1. split the `for` loop to separate the `totalAmount`calculation

2. slide the statement the initializes `totalAmount` to move it next to the loop

3. extract the chunk of code to a function. We temporarily name it `appleSauce()`because we want to name it `totalAmount()` but we cannot while we still have a variable with the same name.

4. inline the variable `totalAmount` 
5. rename `appleSauce()` to `totalAmount()`, and while we are at it we rename the local variables `totalAmount` and `volumeCredits` to `result`

I saved the intermediate result as [./steps/statement_04.h](./steps/statement_04.h) 

### Splitting calculation and formatting phases

1. extract formatting into its own function `renderPlainText()` - actually this is all the code of `statement()`
2. introduce an intermediate data structure `Statement` as additional argument of `renderPlainText()`
3. move one by one to the `Statement` data structure the parameters used in the calculation: `customer`,  `performances` 
4. Remove the  `invoice` parameter

I saved the intermediate result as [./steps/statement_05.h](./steps/statement_05.h) 

Next I need to add in sequence `play`, `amount`, and `volumeCredits` to the intermediate data structure. The goal is to extract the calculation to its own function that returns the data structure.

I must admit I struggled implementing `enrichPerformance()` because there is no direct equivalent to JS `.map()` in C++. It seems unlike C++, JS is happy with altering a data structure e.g. adding fields to it - without declaring it anywhere. 

So I created an `EnrichedPerformance` data structure and slowly added fields to it while making some of the functions e.g. `amountFor()`, `volumeCreditsFor()` polymorphic to work both with `Performance` and `EnrichedPerformance` parameters in order to preserve functionality through the migration.

In the process I put everything upside down, and although in the end I somehow arrived somewhere close to where I wanted, it was not really through small behavior preserving changes...  

I saved the intermediate result as [./steps/statement_06.h](./steps/statement_06.h) 

1. Replace in `totalVolumeCredits()` and `totalAmount()` the for loop with a pipeline using  `std::accumulate()`

2. Extract the chunk of code that prepares the `Statement` data structure to its own function `createStatementData()`. In the process I realized I had forgotten to add `int total` and `int volumeCredits` to `Statement`.
3. Move `createStatementData()` and related functions and data structures to a separate file `createStatementData.h`

### Writing `htmlStatement()`

> "For each desired change, make the change easy (warning: this may be hard), 
> then make the easy change" -  Kent Beck

Now it is trivial to implement a `htmlStatement()` function that instead of calling `renderPlainText()` calls a  `renderHtml()` function where the HTML is generated. 

The result for the original input in [output.html](./output.html)

I saved the intermediate status as [./steps/statement_07.h](./steps/statement_07.h) and  [./steps/createStatementData_07.h](./steps/createStatementData_07.h) 

### Using polymorphism to organize calculations by type

I want to get rid of the conditionals in `amountFor()`and `volumeCreditFor()` to make it easier to support more categories of plays.

1. set up an inheritance hierarchy with subclasses for each type of play 

2. move the calculation logic to the subclasses using replace conditional with polymorphism refactoring.

To create a performance calculator:

1. create a `PerformanceCalculator` class with a `performance` member and a constructor
2. add a `play` member
3. add an `amount()` method to the class with the logic of `amountFor()`, modify `amountFor()` to delegate to the new method and inline `amountFor()`
4. In the process I realized I was unnecesarily calling `amountFor()` in `totalAmount()` and `volumeCreditFor()` in `totalVolumeCredits(`). I corrected it.
5. add an `volumeCredits()` method to the class with the logic of `volumeCreditFor()`, modify `volumeCrfeditFor()` to delegate to the new method, inline `volumeCreditFor()` then delete it

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