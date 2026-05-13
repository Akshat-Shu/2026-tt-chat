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

- I didn't know this up-front after reading about g++, but I looked into it, the other common build types that I found were the Minimum Size Relese (-Os) which optimizes for size and the Release with Debug Info (-Og) which is a compromise between debug and release builds, it includes debug symbols and it also does some optimization but not as much as the release build.


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

## Learn Basics of Creating a C++ Project in Your IDE

- How do you compile and run your project in your IDE?

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