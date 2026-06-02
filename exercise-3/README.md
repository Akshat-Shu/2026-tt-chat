# Exercise 3

**Update this README with your answers to the questions below.**

## Re-using Code

- Read the code in `src/tcp_echo_client.cc`
- A new function `check_error()` has been created and `create_socket()` from 
  exercise-2 has been refactored to make use of it
- What are the benefits of writing code in this way?
  - **Answer**: Having a seperate check_error() function is much like making a Logger which can be reused across codebase. It allows us to write code in a more modular way and we can change the implementation of a single function to change the behaviour of all code that uses it. Supposed we wanted to make the function asynchronous instead, we would just need to change a single function.
- Are there any costs to writing code like this?
  - **Answer**: The main cost is the function call overhead. However, in this case, the benefits of code reuse and modularity likely outweigh the costs of the additional function call. The cost can also be minimized by inling the function. Inside the check_error() function, error_message is being passed by value, which means that a copy of the string is being made each time the function is called. This can be inefficient, especially if the error messages are long. To improve performance, we can pass the error_message by reference instead.
- Apply `check_error` to all the code in `src/`

## Introduction to Compiler Explorer

- Try out the old `create_socket()` and the new `check_error()` and 
  `create_socket()` in [Compiler Explorer](https://godbolt.org) - Interactive 
  tool for exploring how C++ code compiles to assembly
```bash
create_socket2():
        sub     rsp, 8
        mov     edx, 0
        mov     esi, 1
        mov     edi, 2
        call    socket
        test    eax, eax
        js      .L10
        add     rsp, 8
        ret
.L10:
        mov     esi, OFFSET FLAT:.LC1
        mov     edi, OFFSET FLAT:std::cerr
        call    std::basic_ostream<char, std::char_traits<char>>& std::operator<<<std::char_traits<char>>(std::basic_ostream<char, std::char_traits<char>>&, char const*)
        mov     edi, 1
        call    exit
```

```bash
create_socket1():
        push    rbx
        sub     rsp, 48
        mov     edx, 0
        mov     esi, 1
        mov     edi, 2
        call    socket
        mov     ebx, eax
        lea     rdx, [rsp+47]
        mov     esi, OFFSET FLAT:.LC1
        mov     rdi, rsp
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>::basic_string<std::allocator<char>>(char const*, std::allocator<char> const&)
        mov     edi, ebx
        shr     edi, 31
        mov     rsi, rsp
        call    check_error(bool, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>)
        jmp     .L52
        mov     rbx, rax
        mov     rdi, rsp
        call    std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>::_M_dispose()
        mov     rdi, rbx
        call    _Unwind_Resume

check_error(bool, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char>>):
        test    dil, dil
        jne     .L6
        ret
```
- What is happening here?
  - **Answer**: The first code snippet is the assembly generated for the old `create_socket()` function, while the second code snippet is the assembly generated for the new `check_error()` and `create_socket()` functions. The new code has more instructions due to the additional function call and the handling of the error message string. The old code directly calls the `socket` function and checks the return value, while the new code calls `socket`, checks the return value, and then calls `check_error` if there is an error, which involves additional instructions for handling the error message.
- Can you think of any different approaches to this problem?
  - **Answer**: One alternative approach could be to use exceptions instead of a separate error-checking function. This would allow us to throw an exception when an error occurs and catch it at a higher level in the code, which can simplify error handling and reduce the number of function calls. However, this approach may have its own performance implications due to the overhead of exception handling.
- How can you modify your Makefile to generate assembly code instead of
  compiled code?
  - **Answer**: We can use the `-S` flag in our `CXXFLAGS` to generate assembly code instead of compiled code. 
- **Note**: You can save the generated assembly from Compiler Explorer
- **Bonus**: Can you view assembly code using your IDE?
  - **Answer**: In VSCode, while in debug mode, we can right click on the source code and select "Open Disassembly View" to view the assembly code corresponding to the source code.
- **Bonus**: How do you see the assembly when you step through each line in
  debugging mode from your IDE?
  - **Answer**: In VSCode, Disassembly View allows us to do this. We can set breakpoints in our source code and when we hit a breakpoint, we can step through the assembly instructions in the Disassembly View.
- [x86 assembly reference](http://ref.x86asm.net/) - Comprehensive reference 
  for x86 assembly language instructions and syntax

## More About Memory Management

- Make sure you have `-fsanitize=address` in both your `CXX_FLAGS` and 
  `LD_FLAGS` in your Makefile
- What do `-fsanitize=address`, `CXX_FLAGS` and `LD_FLAGS` mean?
- With the new tool of the Compiler Explorer, and keeping in mind what you 
  have learned about how to use debug mode
- What happens when you look at a `std::string` using the above methods?
- **Answer**: A std::string object is created from the string literal. For "Socket creation error\n" (22 chars), it does a heap allocation because the string is too large for the small-string optimization buffer. The constructor visible in the assembly is `std::__cxx11::basic_string<char>::basic_string(char const*)` since `std::string` is just an alias for this template specialization.
- Where is the text in your `std::string`?
  - **Answer**: 
  - For short strings (<=15 chars on this compiler explorer): inside the `std::string` object itself (SSO).
  - For `"Socket creation error\n"`: on the heap, with the `std::string` storing a pointer to it.
- What is `std::optional`?
  - **Answer**: `std::optional` objects may or may not contain a value. It is a wrapper that can hold either a value of a specified type or no value at all (i.e., it can be "empty"). It provides a way to express optional values without using pointers or dynamic memory allocation.
- How do you find out the memory layout of a `std::optional`?
  - **Answer**: We can look at the implementation of `std::optional` in the C++ standard library or use tools like Compiler Explorer to inspect the generated assembly code and see how `std::optional` is implemented. Generally, `std::optional` will contain a boolean flag to indicate whether it contains a value and a storage area for the value itself.
- Read https://en.cppreference.com/w/cpp/memory#Smart_pointers - Guide to 
  modern C++ memory management using smart pointers
- Which pointer types are the most important to know about?
  - **Answer**: The most important smart pointer types to know about are `std::unique_ptr`, `std::shared_ptr`, and `std::weak_ptr`.
- Which smart pointer should you use by default if you can?
  - **Answer**: `std::unique_ptr` should be used by default if you can, as it provides exclusive ownership of the resource and has no overhead of reference counting. It is also safer to use as it prevents accidental copying and ensures proper cleanup of resources.
- Does changing your optimization level in `CXXFLAGS` from `-O0` to `-O3` have
  any impact on the answers to any of the above questions?
  - **Answer**: Changing the optimization level can impact the generated assembly code and how certain constructs are implemented. For example, with higher optimization levels, the compiler may inline functions, eliminate unused code, or optimize memory access patterns, which can affect how `std::string` and `std::optional` are implemented in the assembly. But, the fundamental concepts of where data is stored (SSO vs heap) and the behavior of smart pointers will remain the same regardless of optimization level.

## More Thinking About Performance

- After your experiments with Compiler Explorer, do you have any updates for
  your answers in exercise-2?
  - **Answer**: The major difference between the approaches is that before doing any meaningful work, the compiler has to create a string object and call the function if we use `check_error()`. But in the original code, we can directly check the return value of `socket()` without the overhead of creating a string object and calling an additional function.

### Bonus: Do Not Watch Now 

- [More about Compiler Explorer](https://www.youtube.com/watch?v=bSkpMdDe4g4) - 
  Deep dive into compiler optimization and assembly analysis
  - Create a struct which contain many different data types
  - Look at the memory layout in the debugger
  - Create a `char` or `uint8_t` pointer to the beginning of the struct, 
    iterate to the end of the struct, printing out the value of each byte in 
    hexadecimal
  - Try accessing different parts of the struct and see in compiler explorer
    what the assembly looks like
    - **Tip**: I found that inside VSCode, you can inspect memory layout while debugging by installing a `Hex Editor` extension.
  - What happens if you iterate the pointer to outside the bounds of your
    array?
    - **Answer**: It just causes undefined behaviour, for me it it printing `20` right now but it may be different as that is just a garbage value
  - Let's say your struct is called `Foo`
  - What is the difference between `std::vector<Foo>` and `std::vector<Foo*>`?
    - **Answer**: `std::vector<Foo>` is a vector of `Foo` objects, where each element is an actual `Foo` object stored contiguously in memory. On the other hand, `std::vector<Foo*>` is a vector of pointers to `Foo` objects, where each element is a pointer that can point to a `Foo` object stored elsewhere in memory. The main difference is that with `std::vector<Foo>`, the objects are stored directly in the vector, while with `std::vector<Foo*>`, the vector only stores pointers and the actual objects can be allocated dynamically on the heap or elsewhere.
  - What are the tradeoffs between using `std::vector<Foo>` vs 
    `std::vector<Foo*>`? 
    - **Answer**: 
      - Pros of `std::vector<Foo>`: 
        - Better cache locality since the objects are stored contiguously in memory, which can lead to better performance when iterating over the vector.
        - Simpler memory management since the vector will automatically handle the construction and destruction of the `Foo` objects.
        - Less overhead since there are no pointers involved, which can reduce memory usage and improve performance.
      - Pros of `std::vector<Foo*>`: 
        - More flexible since you can have pointers to objects that are allocated dynamically or shared across different parts of the code.
        - Can be useful when you need polymorphism, as you can store pointers to derived classes in a vector of base class pointers.
        - Can allow for more efficient copying (while `push_back`) and assignment since only pointers are copied instead of entire objects, which can be beneficial if `Foo` is a large object.
  - Give an example where `std::vector<Foo>` is a better choice than 
    `std::vector<Foo*>`
    - **Answer**: If `Foo` is a small, simple struct that does not require dynamic memory allocation or polymorphism, then using `std::vector<Foo>` would be a better choice. For example, if `Foo` is defined as follows:
      ```cpp
      struct Foo {
          int x;
          float y;
      };
      ```
      In this case, using `std::vector<Foo>` would be more efficient and simpler to manage than using `std::vector<Foo*>`, since the objects are small and can be stored contiguously in memory without the need for dynamic allocation or polymorphism.
  - Give another example where the opposite is true
    - **Answer**: If `Foo` is a large class that manages its own resources (e.g., it has a lot of member variables or it manages dynamic memory), then using `std::vector<Foo*>` might be a better choice. For example, if `Foo` is defined as follows:
      ```cpp
      class Foo {
      public:
          std::array<int, 1000> data;
      };
      ```
      In this case, using `std::vector<Foo*>` would allow us to store pointers to `Foo` objects that are allocated dynamically on the heap, which need not be copied while copying the vector. It may also be useful if we need runtime polymorphism, as we can store pointers to derived classes in a vector of base class pointers. 
  - Can you create `std::vector<Foo&>`?
    - **Answer**: No, you cannot create `std::vector<Foo&>` because C++ does not allow containers of references. References in C++ must be bound to an object at the time of their creation and cannot be reseated to refer to another object. Instead, you can use `std::vector<std::reference_wrapper<Foo>>` if you want to store references in a vector-like structure.
  - Can you create `std::vector<std::optional<Foo>>`?
    - **Answer**: Yes, you can create `std::vector<std::optional<Foo>>`. This allows you to have a vector where each element can either contain a `Foo` object or be empty (i.e., it does not contain a value).
  - What happens if your struct contains another struct?
    - **Answer**: The inner struct will be a member of the outer struct, the size of the outer struct will include the size of the inner struct (maybe along with some padding). Also, the alignment of the outer struct will also take the alignment of the inner struct into account while calculating the maximum of all alignments.
  - What is the difference between a struct and a class?
    - **Answer**: In C++, the only difference between a struct and a class is the default access specifier. In a struct, members are public by default, while in a class, members are private by default. Other than that, structs and classes are essentially the same and can have member functions, constructors, destructors, and so on.