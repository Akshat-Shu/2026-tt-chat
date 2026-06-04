# Exercise 4

**Update this README with your answers to the questions below.**

## Learning Multi-File C++ Projects

- Move code that can be shared between `tcp_echo_server.cc` and 
  `tcp_echo_client.cc` to separate `.h` and `.cc` files
- How would you compile from the command line?
  - **Answer**: You can compile from the command line using the `g++` command. For example, if you have a shared utility file called `tcp_echo_utils.cpp` and its corresponding header file `tcp_echo_utils.h`, you can compile both the server and client like this:

  ```bash
  g++ -o tcp_echo_server tcp_echo_server.cpp tcp_echo_utils.cpp
  g++ -o tcp_echo_client tcp_echo_client.cpp tcp_echo_utils.cpp
  ```
- How would you compile using make?
  - **Answer**: While using make, we should have seperate targets for compiling the utilities object and then linking it with the server and client.
- How would you compile using VS Code?
  - **Answer**: In VS Code, we can create a `tasks.json` file to define custom build tasks. We can set up tasks for compiling the server and client, and we can also create a task for compiling the shared utilities. Then, we can run these tasks from the command palette or by using keyboard shortcuts.

### Compiling vs Linking

- What is the difference between compiling and linking in C++?
  - **Answer**: Compiling is converting source code files (`.cpp`) into assembly instructions, while linking is the process of combining these object files into a final executable or library. During linking, the linker resolves references between object files and includes necessary libraries. The Compiler creates executables in a 4 step process, Compiling and Linking are just two of those steps.
- What is the difference between creating an executable and creating a library?
  - **Answer**: An executable is a standalone program that can be run directly, while a library is a collection of pre-compiled code that can be reused by other programs. Libraries can be either static (linked at compile time) or dynamic (linked at runtime). An executable typically contains a `main` function, while a library does not.
- How do you compile a library, and then use that library to compile an executable?
  - **Answer**: There are two types of libraries: static and dynamic.
    - To compile a static library, you can use the `ar` command to create an archive of object files. For example:
    ```bash
    g++ -c tcp_echo_utils.cpp -o tcp_echo_utils.o
    ar rcs libtcp_echo_utils.a tcp_echo_utils.o
    ```
    - To compile a dynamic library, you can use the `-shared` flag with `g++`. For example:
    ```bash
    g++ -fPIC -shared tcp_echo_utils.cpp -o libtcp_echo_utils.so
    ```
    - To use the library when compiling an executable, you can specify the library path and name. For example, if you have a static library:
    ```bash
    g++ -o tcp_echo_server tcp_echo_server.cpp -L. -ltcp_echo_utils
    g++ -o tcp_echo_client tcp_echo_client.cpp -L. -ltcp_echo_utils
    ```
    - If you have a dynamic library, you would also need to set the `LD_LIBRARY_PATH` environment variable to include the directory where the `.so` file is located.

### Reminder 
[Quickstart tutorial to make](https://makefiletutorial.com/) - Learn make 
fundamentals with practical examples and common patterns.

## Experiments in Performance

- Is it better to have many small files spread across many directories, or a few large files across fewer directories?
  - **Answer**: It depends on the size and complexity of the project. Generally, having many small files can improve maintability. Another advantage would be that if only a few files are changed, the compile time is largely reduced since only the changed files need to be recompiled.
- Is there a difference in compilation time between the two?
  - **Answer**: It depends on how we are compiling the project and how the files are included. But in general, if seperate object files are being created, then the compilation time can be reduced since only the changed files need to be recompiled. However, if all files are being compiled together, then the compilation time may not differ significantly. 
- How can you assess performance other than compilation speed?
  - **Answer**: Other than compilation speed, we can assess performance by looking at the runtime performance of the executable, memory usage, and the efficiency of the code. Another factor that we should also consider for performance is the size of executable. Usually, using static libraries/multiple template instantiations can bloat the executable. Using Dynamic libraries can help reduce the size of the executable, but it may introduce some overhead at runtime due to dynamic linking.