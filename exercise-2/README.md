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
- According to the man page, `SOCK_RAW` provides raw network protocol access. We may use it when we want to send over some data without any protocol-specific formatting, like when we want to send a custom packet for pinging.

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


## Refactoring: Extract Function

- What is different in this code compared to exercise-1?
- Is this code better or worse than exercise-1?
- What are the tradeoffs compared to exercise-1?
- Are you able to spot any mistakes or inconsistencies in the changes?
  
## Thinking About Performance

- Does writing code this way have any impact on performance?
- What do we mean when we say performance?
- How do we measure performance in a program?

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

## Learn Basics of Debugging in Your IDE

- How do you enable debug mode in your IDE?
- In debug mode, how do you add a watch?
- In debug mode, how do you add a breakpoint?
- In debug mode, how do you step through code?

### Memory Management and Debug Mode in Your IDE

- How do you see the memory layout of a `std::string` from your IDE debug mode?
- How do you see the memory layout of a struct from your IDE debug mode?