# Exercise 2

**Update this README with your answers to the questions below.**

## Sources of Information for Questions from Before

### Socket 
- https://man7.org/linux/man-pages/man2/socket.2.html - System call reference
  for creating communication endpoints
- Or type `man socket` in terminal
- https://man7.org/linux/man-pages/man7/socket.7.html - Socket interface 
  overview and protocol families
- Or type `man 7 socket` in terminal
- When would you want to use a `SOCK_RAW` stream?
#### Answer
- According to the man page, `SOCK_RAW` provides raw network protocol access. We may use it when we want to transmit data without any protocol-specific formatting, like when we want to send a custom packet for pinging.

### TCP and IP Protocols
- [IPv4](https://www.rfc-editor.org/info/rfc791) - Internet Protocol 
  specification defining packet structure and routing
- [IPv6](https://www.rfc-editor.org/info/rfc8200) - Next-generation Internet 
  Protocol with expanded address space
- [TCP](https://datatracker.ietf.org/doc/html/rfc9293) - Transmission Control 
  Protocol providing reliable, ordered data delivery
    
### C++
- [C++23 ISO standard draft](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4950.pdf) - 
  Working draft of the C++ language specification
- Is the above the official C++23 spec? 
- Where is the official C++23 spec?
- Why was this link chosen instead?
- Is this a helpful reference for learning C++?
- Can the various implementations of C++ compilers be different from the
  C++ standard?
- What are the most widely used and most significant C++ compilers?
- Where is the equivalent spec for C++26?

- Where do you find the spec for the HTTP protocol?
- What about HTTPS? Is there a spec for that protocol?

#### Answers
- The link above is not the official C++23 spec, The actual C++23 spec is 2104 pages long and is not freely available. I found a purchase link [Here](https://www.iso.org/standard/83626.html)
- This link is a public working draft of the C++23 specification, it is not the final version but it is the most up-to-date version that is freely available. It is the draft version of what became the final C++23 standard.
- The standard is one of the most authoritative references for learning C++, but it is not easy for beginners to go through the entire standard, If someone has a specific question about a particular feature, it is easy to look it up in the standard, but CppReference is a more user-friendly reference for learning C++ as it provides explanations and examples for each feature.
- All of the C++ compilers implement the C++ standard, but none of them are identical. The C++ standard defines the rules and the compiler is the implementation of those rules. Compilers may differ because of incomplete implementation of the standard, or because of extensions that they provide beyond the standard. They may also differ in terms of implementation-defined behaviour, which is behaviour that is not standard-defined.
- The most widely used and significant C++ compilers are:
  - GCC (GNU Compiler Collection)
  - Clang (LLVM-based compiler)
  - MSVC (Microsoft Visual C++)
- I found the Equivalent spec for C++26 [Here](https://isocpp.org/files/papers/N5032.pdf)
- [Here](https://datatracker.ietf.org/doc/html/rfc9110) is the spec for HTTP Protocol. 
- HTTPS is HTTP over TLS, [Here](https://datatracker.ietf.org/doc/html/rfc2818) is a spec I found for HTTPS.


## Introduction to C++ and Sockets Programming

- Read the code in `src/`
- Are there any bugs in this code? 
- What can you do to identify if there are bugs in the code?

### Answers
- One bug I noticed is that when reading the message from server, if we read exactly `kBufferSize` bytes, we won't have space for the null terminator, which can lead to undefined behaviour when we try to print the message. To fix this, we can read at most `kBufferSize - 1` bytes and then add a null terminator at the end of the buffer.
- Another issue I notice is that the functions call exit when an error occurs, which is not ideal as it doesn't allow the caller of the function to handle the error in a way that makes sense for their use case. Instead of calling exit, we can throw a runtime error with a descriptive message, which allows the caller to catch the exception and decide how to handle it.
- In order to identify bugs, we can write Unit tests for the functions, we can also use a debugger to step through the code and inspect the values of variables at runtime to see if they are what we expect. We can also use static analysis tools to analyze the code for potential bugs and issues.
- We can also use profiling tools and memory analysis tools like Valgrind and Gprof to identify performance issues and memory leaks/illegal memory access in our code.

## Refactoring: Extract Function

- What is different in this code compared to exercise-1?
- Is this code better or worse than exercise-1?
- What are the tradeoffs compared to exercise-1?
- Are you able to spot any mistakes or inconsistencies in the changes?
### Answers
- By using a lot of functions with descriptive names, the code is more modular. This also makes it easier to read and understand the code. Moreover, by using functions, we can abstract away the actual implementation details of how the function acomplishes its task, If we need to change the implementation of a function, we can do so without affecting the rest of the code that uses that function. For example, in `set_binary_address` function in `tcp_echo_client.cpp`, we can instead use `getaddrinfo()` to set the address using the hostname.
- The code is definitely organized in a better fashion as compared to exercise-1 in terms of readability and maintainability. The intent of each part of the code is much more clearer. Each function has a single responsibility, and the main function is much more concise and easier to understand.
- When using functions, there is some overhead associated with function calls, which can impact performance. However, the benefits of improved readability and maintainability often outweigh the performance costs. Additionally, modern compilers are very good at optimizing function calls, so the performance impact may be negligible in many cases.
- We also have to type more code to define the functions and call them, which can make the code longer. However, this is often an acceptable tradeoff for the improved readability and maintainability of the code.
- One of the issues is in the function `read_args`, if the user does not provide any arguments, the function does not use the default initialized value of message, It instead prints the usage message and exits the program.
- Another change that I noticed was that in the function `handle_accept`, the code has been modified to handle all cases based on sign of the return value of `read()`, which eliminates the implicit conversion issue that we faced earlier.
- In Exercise-1, the same buffer was being used for every read operation, However, in Exercise-2, we are using a new buffer for each read operation and initializing it to zero before each read, which can help prevent issues with leftover data from previous reads.
- Exercise-2 handles file descriptors in a better manner by closing them whenever an error occurs or when they are no longer needed, which can help prevent resource leaks.
  
## Thinking About Performance

- Does writing code this way have any impact on performance?
- What do we mean when we say performance?
- How do we measure performance in a program?

### Answers
- Writing code in a more modular way using functions can have some impact on performance due to the overhead of function calls. But, some modern compilers can optimize function calls and make the performance impact negligible in many cases. Additionally, we can also `inline` small functions to reduce the overhead of function calls.
- When we say performance, we usually consider factors such as execution time and memory usage. We say that the performance of a program is better as compared to another if it uses less resources to accomplish the same task. Performance can also include considering factors like responsiveness and scalability.
- We can measure performance in a program using various tools and techniques. For execution time, we can use profiling tools like Gprof. For memory usage, we can use tools like Valgrind. We can also use built-in functions like `std::chrono` in C++ to measure the execution time of specific sections of code. Additionally, we can also use benchmarking frameworks to compare the performance of different implementations of a function or algorithm.

## Play with Git

- There isn't necessarily a single correct answer for how to abstract the 
  code from exercise-1 into functions
- Try different ways to refactor the code from exercise-1 to make it more
  readable.
- Make sure to commit each change as small and self-contained commit
- This will make it easier to revert your code if you need to
- What is `git tag`? How is `git tag` different from `git branch`?
- How can you use `git tag` and `git branch` to make programming easier and
  more fun?

### Answers
- `git tag` is a reference to a specific commit, it is often used to mark release versions or important milestones in a project but a tag does not move forward with new commits. On the other hand, `git branch` creates a branch which is a seperate line of active development, it moves forward with new commits.
- When working in a team, it becomes increasingly important to use branches so that everyone can work on their own features without affecting the main codebase. We can use branches to develop new features, fix bugs, or experiment with new ideas without affecting the main codebase. Once the work on a branch is complete and tested, we can merge it back into the main branch. Tags can be used to mark specific commits as release versions, which can be helpful for tracking changes and rolling back to previous versions if necessary.
- You can view the refactored code inside the `refactor/` directory.

## Learn Basics of Debugging in Your IDE

- How do you enable debug mode in your IDE?
- In debug mode, how do you add a watch?
- In debug mode, how do you add a breakpoint?
- In debug mode, how do you step through code?

### Answers
- I am using VS Code. I found this helpful [Youtube Video](https://www.youtube.com/watch?v=G9gnSGKYIg4) that explains how to use the debugger for C++ in VS Code. To enable debug mode, we need to create a launch configuration in the `launch.json` file. We can do this by going to the Debug view and clicking on the gear icon to open the `launch.json` file. Then we can add a new configuration for C++ debugging.
- To start debugging, we can go to the Run and Debug view and select the configuration we need. Then, we can press `F5` to start debugging.
- Once we are in debug mode, to add a watch to a variable, we can right click on the variable in the `Locals` tab and select `Add to Watch`. This will add the variable to the `Watch` tab where we can see its value and how it changes as we step through the code.
- To add a breakpoint at a line, we can just click on the red dot on the left side of the line number in the editor. So the execution will pause when it reaches that line.
- To step through code, we can use the following commands:
  - `F5` to continue running the code until the next breakpoint is hit or the program finishes execution
  - `F10` to step over a line of code (execute the line without stepping into any function calls)
  - `F11` to step into a function call (if the line contains a function call, it will step into that function)
  - `Shift + F11` to step out of the current function (if we are inside a function, it will execute the rest of the function and return to the caller)
- These are also available as buttons in the debug toolbar in the IDE.

### Memory Management and Debug Mode in Your IDE

- How do you see the memory layout of a `std::string` from your IDE debug mode?
- How do you see the memory layout of a struct from your IDE debug mode?

### Answers
- In VS Code, when we are in debug mode, we can run gdb commands by opening the Debug Console and using `-exec <command>`. To view the memory layout of a particular variable, we can use the command `x/32xb &variable_name` to view the memory layout in hexadecimal byte format. Here, `32` is the number of bytes we want to view, `x` is for hexadecimal format, and `b` is for byte size.
- For Example, here is some of my output when debugging the file `testing.cpp`:
```
-exec x/32xb &message
0x7fffffffce70:	0x80	0xce	0xff	0xff	0xff	0x7f	0x00	0x00
0x7fffffffce78:	0x0d	0x00	0x00	0x00	0x00	0x00	0x00	0x00
0x7fffffffce80:	0x48	0x65	0x6c	0x6c	0x6f	0x2c	0x20	0x57
0x7fffffffce88:	0x6f	0x72	0x6c	0x64	0x21	0x00	0x00	0x00
-exec x/32xb &point
0x7fffffffceb0:	0x0a	0x00	0x00	0x00	0x14	0x00	0x00	0x00
0x7fffffffceb8:	0xc8	0xce	0xff	0xff	0xff	0x7f	0x00	0x00
0x7fffffffcec0:	0x08	0x00	0x00	0x00	0x00	0x00	0x00	0x00
0x7fffffffcec8:	0x4d	0x79	0x20	0x50	0x6f	0x69	0x6e	0x74
```