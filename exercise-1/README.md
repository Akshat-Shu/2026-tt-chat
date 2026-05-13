# Exercise 1

**Update this README with your answers to the questions below.**

## How to Approach This Exercise

Before you scroll down to the questions, try this:

1. **Don't peek at the questions yet.** Pretend you've just been handed a brief
   that says: *"Learn these topics as deeply as you can — g++ CLI, Make, Git,
   sockets, and memory management in C++."* That's the whole assignment.
   How would you go about it? What would you read, what would you try, in what
   order, and how would you know when you've understood something well enough?
   Write that plan down in this README, then actually follow it.

### Answer

- I feel that there are two ways to go around learning things. One is to just go ahead with trying complete the task and learn things as you go experimenting with the different features, the other is to first read up on documentation and try to understand the concepts before trying to implement them.

- When time is limited, it is often better to go with the second approach.

- If the thing I'm learning about is a linux command, the man page is often enough to get me started and then I can experiment with the particular use case that I have in mind.

- Otherwise, googling for examples and documentation is wnat works for me. Often, I find official documentation where I can find quickstart guides and examples, but when that is not the case, I look for Stack Overflow and blog posts from reputable sources or just look through the most relevant topics in the documentation.

- Googling also reveals good YouTube videos that explain the concepts in a more intuitive way. For example, watching CppCon videos on a particular concept is often a better than starting with the CppReference documentation.

- For me, what classifies as well enough understanding is when I feel confident enough to explain the concept to someone else and I can apply it to solve a problem that I have in mind.

- After I have a well enough understanding of the tool, I should be able to explain the usefulness of the tool and how it works at a high level, as well as some of the details of how to modify it with flags and arguments to achieve a particular goal.

- After I have a good understanding of the concepts, in order to know about some specific syntax, it is better to ask ChatGPT as compared to finding it in the documentation.


1. **Now go through the questions below and answer them like you're an LLM.**
   No live Googling, no Stack Overflow, no asking ChatGPT mid-question. You may
   refer to notes *you* took during step 1 — that's your context window. Answer
   from what you've internalised.

2. **Reflect on how it went.** Honestly:
   - Did your self-directed learning actually prepare you for the questions, or
     did you over-study things that never came up?
   - Which questions blindsided you? Why — was the topic missing from your
     plan, or did you skim past it?
   - Map your experience onto the *known knowns / known unknowns / unknown
     unknowns* idea. The interesting category is usually the last one: things
     you didn't even realise you should have learned. What were yours, and how
     could a better learning plan have surfaced them earlier?

The point of this exercise isn't to get the questions "right" — it's to notice
the gap between how you *think* you learn and how you actually do, so you can
close it.

## Learning How to Learn

- Answer the following questions in this file and commit and push your changes.
- Bonus sections are more difficult and optional.
- How can you find the information required to complete these tasks?
- How can you tell if the source of your information is good?
- How would you define "good" in this situation?

## Learn Basics of g++ CLI

- Compile the TCP client and server using `g++` from command line.
- What are the most important command line arguments to learn for `g++`?
- What is the difference between debug vs release versions?
- What are the tradeoffs between debug and release versions?
- What arguments would you use in a debug build?
- What about for release?
- What other kinds of build types are useful?

### Answers
- Compile using
```bash
g++ src/tcp_echo_client.cc -o tcp_echo_client
g++ src/tcp_echo_server.cc -o tcp_echo_server
```
- Most important flags for g++ are -o for specifying the output file, -g for including debug symbols, -O for optimization level, -I for specifying inclusion path, and -W... for enabling warnings. Most often, unless we are doing something very specific, these flags are enough for most use cases.

- Debug builds of executables include debug symbols and they are not optimized, commands in the executable are not rearranged for performance. Release builds are optimized for performance and they do not include debug symbols.

- Debug symbols allow us to use gdb to debug the executable line by line but they also make the executable larger and slower. Optimization makes the executable faster but it also makes debugging harder because the commands are rearranged and some of them might be removed if they are not used.

- For debug builds, I would use -g flag to include debug symbols and I would avoid using -O flag to disable optimization. For release builds, I would use -O2 or -O3 for optimization.

- I didn't know this up-front after reading about g++, but I looked into it, the other common build types that I found were the Minimum Size Release (-Os) which optimizes for size and the Release with Debug Info (-Og) which is a compromise between debug and release builds, it includes debug symbols and it also does some optimization but not as much as the release build.


## Learn Basics of Make

- Create a Makefile that will speed up the process.
- [Quickstart tutorial to make](https://makefiletutorial.com/) - Learn make 
  fundamentals with practical examples and common patterns.
- How else can you learn about make?
- How can you tell if the resource you are using is correct?
- Create a makefile such that when you run `make` with no arguments, it will:
  - Create `build/` directory if it does not exist
  - Create executables **client** and **server** in `build/`, if needed
  - How does make know when it needs to rebuild the executables?
  - Change your Makefile such that `make clean` will remove `build/` and all
    its contents
- What are the most important command line arguments to learn for make?
- What are the most important directives to learn about in Makefile?
- What are the most important commands to implement in your Makefile?
- Which ones are essential, which ones are nice to haves?

### Answers
- Besides this quickstart tutorial, the official [GNU Make manual](https://www.gnu.org/software/make/manual/make.html) is a good resource to look at all of the features of Make.
- The official documentation always provides correct information, it is the most authoritative source of information about a tool. Besides the official documentation, to verify credibility of a resource, it might be helpful to check the author's credentials as well as to verify if the information is up-to-date and if it is consistent with other reputable sources.
- Make uses the latest modification timestamp of targets and their dependencies to determine if a target needs to be rebuilt. If any of the dependencies of a target have been modified more recently than the target itself, then make will rebuild that target.
- Some of the important command line arguments for make are -f for specifying which file to use, -n for a Dry Run which just prints the commands that would be executed without actually executing them, -i for ignoring errors during execution and -s for silent mode which suppresses the output of the commands being executed.
- I only knew about the include directive in Makefiles. After looking into it, I found out that there are also other important directives such as define for defining variables which may be multi-line, ifeq/ifdef for conditional statements dependent on variables, and foreach for iterating over lists of items.

- The most important targets in any makefile are the `all` target which is usually placed at the top of the Makefile and it is the default target that gets executed when you run `make` with no arguments, and the `clean` target which is used to remove any files that were generated during the build process. Besides these two targets, it is also common to have a `test` target for running tests and a `install` target for installing the built executables.
- The `all` and `clean` targets are essential for any Makefile, while the `test` and `install` targets are nice to have but they are not necessary for every project.

## Learn Basics of Git

- Read through the code in `src/`
- Answer any `#Questions` as a comment
- Commit and push your changes to git
- Each commit should be responding to a single task or question
- Why is it important to keep your commit to a single task or question?
- Is it better to have a lot of very small commits, or one big commit when 
  everything is working?
- What are the most important commands to know in git?

## Introduction to Sockets

- Read the code in `src/tcp-echo-client.cc` and add a way to change the 
  message sent using command line arguments
- **Example**: `./client "hello message from the command prompt"` should send
  `"hello message from the command prompt"` to the server
- Commit your changes into git
- What do all these headers do?
- How do you find out which part of the below code comes from which header?
- How do you change the code so that you are sending messages to servers
  other than localhost?
- How do you change the code to send to a IPv6 address instead of IPv4?
- **Bonus**: How do you change the client code to connect by hostname instead
  of IP address?

### Answers
- <arpa/inet.h> provides definitions for useful functions for transforming IP addresses, such as inet_pton which converts an IP address in string format to binary format.
- <netinet/in.h> provides definitions for internet protocol, like sockaddr_in which is a structure that contains information about an internet address. It also has definitions for functions like htons which converts a port number from host byte order to network byte order.
- <sys/socket.h> is the Unix header that provides definitions for socket functions and structures, such as the socket function which creates a new socket, the connect function which connects a socket to a remote address, the send and recv functions for sending and receiving data through a socket, the accept function for accepting incoming connections on a server socket, and the bind function for binding a socket to a local address and port.
- <sys/types.h> is just used for defining some data types that are used in the other headers, such as ssize_t which is used for representing the number of bytes sent or received through a socket.
- <unistd.h> provides access to the POSIX operating system API, it includes definitions for functions like close which is used to close a socket file descriptor.
- To find out which functions comes from which header, I usually just use CTRL + Click on the function name in my IDE and it takes me to the header file where that function is defined.
- To send messages to servers other than localhost, we can change the IP address in the code (`kServerAddress`) to the IP address of the server we want to connect to. We can also modify the code to take the server address as a command line argument.
- To change the code to send to an IPv6 address, we need to change the socket family from `AF_INET` to `AF_INET6`, and we also need to change the `sockaddr_in` structure to `sockaddr_in6` which is used for IPv6 addresses.
- I didn't know this off the top of my head after reading about sockets, but I looked into it, I found that in order to connect by hostname instead of by raw IP address, `getaddrinfo()` can be used instead of `inet_pton()`. `getaddrinfo()` resolves a hostname like `example.com` into one or more socket addresses, so the client can work with whichever address family the hostname supports. **Example**:
```cpp
struct addrinfo hints{}, *res;
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;

int err = getaddrinfo(kServerAddress.c_str(),
                      std::to_string(kPort).c_str(),
                      &hints,
                      &res);

if (err != 0)
    return -1; // ERROR

int my_sock = socket(res->ai_family,
                     res->ai_socktype,
                     res->ai_protocol);
```
  
## Introduction to Memory Management

- What is happening in line 26 of `tcp-echo-client.cc`? 
  `if (inet_pton(AF_INET, kServerAddress.c_str(), &address.sin_addr) <= 0) {`
- What is happening in line 31 of `tcp-echo-client.cc`?
  `if (connect(my_sock, (sockaddr *)&address, sizeof(address)) < 0) {`
- What is the difference between a pointer and a reference?
- When is it better to use a pointer?
- When is it better to use a reference?
- What is the difference between `std::string` and a C-style string?
- What type is a C-style string?
- What happens when you iterate a pointer?
- What are the most important safety tips to know when using pointers?

### Answers
- `inet_pton` is being called to convert the server address from string format to binary format. The first argument `AF_INET` specifies that the address is an IPv4 address, the second argument is the server address in string format, and the third argument is a pointer to a buffer where the converted address will be stored. If the conversion is successful, positive value is returned.
- `connect` is being called to connect the socket to the server. The first argument is the socket file descriptor of the client, the rest of the arguments are for specifying the address of the server to connect to.
- A pointer is a variable that holds the memory address of another variable, while a reference is an alias for another variable. A pointer can be reassigned to point to different variables, while a reference cannot be changed after it is initialized. Also, references must be always initialized when they are declared, while pointers can be declared without being initialized.
- It is better to use a pointer when we need to have the ability to reassign it to point to different variables, of when we need to represent the absence of a value (using a null pointer). It is also better to use pointers when we are working with arrays or when we need to perform pointer arithmetic.
- It is better to use a reference when we want to create an alias for another variable and we don't need to reassign it to point to different variables. References are also generally safer and easier to use than pointers, because they cannot be null and they cannot be accidentally dereferenced.
- `std::string` provides a convenient and safe way to work with strings. It manages memory automatically and also provides us with some common methods for string manipulation. A C-style string is just an array of characters that are null-terminated. Memory is not managed automatically and size is not adjusted automatically, so we need to be careful with memory issues.
- A C-style string is of type `const char*`, it is a pointer to the first character of the string. The string ends with a null character (`'\0'`).
- When we iterate a pointer, we point to the next memory location which is determined by the size of the type that the pointer is pointing to. It is not guaranteed that the next memory location is valid or that it contains the data we are expecting, so we need to be careful to avoid accessing invalid memory.
- When dereferencing pointers, we need to make sure that the pointer is not null. We also need to be careful with pointer arithmetic to avoid accessing memory that is out of bounds. Most often, iterators are a safer alternative to pointers. When working with pointers for memory that is dynamically allocated, we need to make sure to free the memory to avoid memory leaks.

## Learn Basics of Creating a C++ Project in Your IDE

- How do you compile and run your project in your IDE?

### Answers
- In VS Code, the C++ Extension Pack provides a convenient way to compile and run a single file.
- VS Code also provides a way to create a `tasks.json` file which can be used to define custom build tasks, and a `launch.json` file which can be used to define custom debug configurations. The tasks can be accessed by using `Ctrl + Shift + B` and `F5` for debug configurations. We can also use Makefiles to build the project by defining a task that runs `make` command.

## Improving Interactions with LLMs

- What is the most authoritative source of information about `socket()`
  from `<sys/socket.h>`?
- What is the most authoritative source of information about the TCP and IP
  protocols?
- What is the most authoritative source of information about the C++
  programming language?
- What information can you find about using Markdown when structuring prompts 
  to LLMs?
- What is the difference between LLM and AI?
- Is it grammatically correct in English to say "a LLM" or "an LLM"? Why?

### Answers
- for most system calls, the `man` pages are the most authoritative source of information. For `socket()`, we can run `man socket` to get it's manual page.
- I didn't know this off the top of my head, but after looking into it, I found that IETF (Internet Engineering Task Force) is the organization that develops Internet standards, the most authorative sources of information about the protocols are their RFCs (Request for Comments) which are the documents that describe the specifications and standards for the protocols. We can look at RFC 793 for TCP and RFC 791 for IP. After a quick Google Search, the first result that comes up is the [GeeksforGeeks page](https://www.geeksforgeeks.org/computer-networks/tcp-ip-model/) which gives a good starting point for understanding as compared to the actual RFCs which are enormous and not very beginner-friendly.
- The most authoritative source about the C++ according to me is [CppReference](https://www.cppreference.com), it provides documentation and examples about all the features of C++ and it's standard library. The official C++ standard documents are also authoritative but they are not very beginner-friendly.
- LLMs are often trained on structured text data, so using Markdown can help to structure the prompt in a way that is more easily understood by the model. For example, using headings to specify the Role, Task, Context, Examples and Instructions can guide the model to produce the desired output. Using bullet points can also help to break down the information into smaller chunks which are easier to process. Also, using code blocks can help the model differentiate between code and regular text, which can be useful when asking for code generation or explanations of code.
- LLM stands for Large Language Model, it is a type of AI model that is trained on a large corpus of text data to understand and generate human-like text based on the context of text that has been input to it. AI stands for Artificial Intelligence, it is a much broader term that stands of techniques using which machines can perform tasks that require intelligence such as understanding natural language, language translation, recognizing images, writing mathematical proofs, etc.
- `an` is used before Vowel sounds and `a` is used before Consonant sounds. I pronounce LLM as `el-el-em` which starts with a vowel sound, so it is grammatically correct to say `an LLM`. Considering a similar example, is it correct to say `an LCD Monitor`, not `a LCD Monitor`.