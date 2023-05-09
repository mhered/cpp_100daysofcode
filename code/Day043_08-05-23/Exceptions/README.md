#link: https://www.learncpp.com/cpp-tutorial/the-need-for-exceptions/

# Exceptions
Follow along sections 20.1-20.4 of the Exceptions chapter in the great course `learncpp.com` 

## Need for exceptions
A common way to handle potential errors in the code is via return codes. Return codes are simple but mix your control flow and error flow, constraining both: 1) return codes can be criptic, 2) can get ugly (e.g. having to return by reference in functions that also need to return a result, or needing to check constantly if many things can go wrong), 3) doesn't mix well with constructors and 4) sometimes the caller cannot handle the error.

Exception handling decouples handling of errors or other exceptional circumstances from the typical control flow of your code. This allows more freedom to handle errors when and how ever is most useful for a given situation, alleviating most (if not all) of the messiness that return codes cause.

## Basic exception handling

* throwing exceptions: `throw` statements (raising an exception) signal an error case has ocurred

* `try` blocks look for exceptions raised inside and route them to the appropriate `catch` block for handling  

* catching exceptions: exceptions raised in statemetns inside a `try` block are detected and routed to a matching`catch` block where they are handled. A `try` block must have at least one or more `catch` blocks immediately following it. 

```c++
try
{
    // Statements that may throw exceptions tht need handling

    throw -1; // a  throw statement raises an integer exception
}

catch (int x) // catch block for integer exceptions
{
    // Handle an exception of type int here
    std::cerr << "Caught int exception with value" << x << '\n';
}
```

Principles:

- When an exception is raised (using `throw`), the compiler looks in the nearest enclosing `try` block (propagating up the stack if necessary to find an enclosing `try` block) to see if any of the `catch` handlers attached to the `try` block can handle that type of exception. If so, execution jumps to the top of the `catch` block, and the exception is considered handled.

- If no appropriate `catch` handlers exist in the nearest enclosing `try` block, the compiler continues to look at subsequent enclosing `try` blocks for a `catch` handler. If no appropriate `catch` handlers can be found before the end of the program, the program will fail with an exception error.

- Note that the compiler will not perform implicit conversions or promotions when matching exceptions with `catch` blocks. 

Typically `catch` blocks will do one of 4 things:

1. print an error to the console or a log file and proceed.
2. return a value or error code back to the caller.
3. throw another exception (because the `catch` block is outside of the preceding `try` block, the new exception is handled by the next enclosing `try` block.
4. a `catch` block in `main()` may be used to catch fatal errors and terminate the program in a clean way.

## Throwing exceptions from a called function
Note: `try` blocks catch exceptions from statements within, but also from functions that are called within the `try` block.

A common pattern is that functions may throw an exception, but delegate the responsibility for handling it to the caller (different applications may want to handle errors in different ways depending on context)

## Exception handling and stack unwinding
When an exception is thrown, the program first tries to handle it immediately inside the current function. If no handler is found, it tries the next function up the call stack -- if the call to the current function was inside a `try` block, and there is a matching `catch` block associated. The process of checking each function up the call stack continues until either a handler is found, or all of the functions on the call stack have been checked and no handler can be found.

If a matching exception handler is found, then execution jumps from the point where the exception is thrown to the top of the matching catch block. This requires unwinding the stack (removing the current function from the call stack) as many times as necessary to make the function handling the exception the top function on the call stack.

If no matching exception handler is found, the stack may or may not be unwound. When the current function is removed from the call stack, all local variables are destroyed as usual, but no value is returned. Unwinding the stack destroys local variables in the functions that are unwound (which is good, because it ensures their destructors execute).

## Uncaught exceptions and catch-all handlers

When a function throws an exception that it does not handle itself, it is making the assumption that a function up the call stack will handle the exception. When no exception handler for a function can be found, `std::terminate()` is called, and the application is terminated. In such cases, the call stack may or may not be unwound! If the stack is not unwound, local variables will not be destroyed, and any cleanup expected upon destruction of said variables will not happen!

The catch-all handler `catch (...)` is a mechanism to catch all types of exceptions. It must be placed last in the `catch` block chain, to ensure that exceptions can be caught by exception handlers tailored to specific data types if those handlers exist.

```c++

int main()
{
	try
	{
		throw 5; // throw an int exception
	}
	catch (double x)
	{
		std::cout << "We caught an exception of type double: " << x << '\n';
	}
	catch (...) // catch-all handler
	{
		std::cout << "We caught an exception of an undetermined type\n";
	}
}
```

This will catch any unanticipated exceptions, ensuring that stack unwinding occurs up to this point and preventing the program from terminating.

Best practice: If your program uses exceptions, consider using a catch-all handler in `main()`, to help ensure orderly behavior when an unhandled exception occurs. Also consider disabling the catch-all handler for debug builds, to make it easier to identify how unhandled exceptions are occurring.
e.g.

```c++
#include <iostream>

int main()
{

    try
    {
        runGame();
    }
    catch(...)
    {
        std::cerr << "Abnormal termination\n";
    }

    saveState(); // Save user's game
    return 1;
}
```

# Tags
#tags: 

- [ ] basics
- [ ] algorithms
- [ ] data_structures: trees, graphs
- [ ] strings: regex
- [ ] dates_times: timezones
- [ ] file_management: input, output, folders and files
- [ ] testing
- [x] exceptions
- [ ] logging
- [ ] object_oriented_programming
- [ ] GUI
- [ ] plotting_data
- [ ] CLI
- [ ] arduino
- [ ] ROS
- [ ] chatGPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [ ] OpenCV