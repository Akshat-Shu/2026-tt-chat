# Exercise 5

**Update this README with your answers to the questions below.**

## Comparing File Changes

- What's an easy way to identify the changes in source code from one exercise to another?
  - **Answer**: we can use the `diff` command to compare the source code files from one exercise to another. For example,
```bash
diff exercise-4/src/tcp_echo_client.cpp exercise-5/src/client-main.cc 
```
  - This command will show the differences between the two files, highlighting the lines that have been added, removed, or changed. We can also use graphical tools like `meld`.
    
## Using Classes

- Here is one way to separate out code into multiple files
- Is this the best way to do it? 
  - **Answer**: One suggestion I would make is to have a seperate class for handling socket operations, maybe a `Socket` class that can be used by both the client and server. Further, we can also have a `Message` class that supports sending and receiving messages. Both of them can be used in `Client` and `Server` classes.
- What are the advantages and disadvantages?
  - **Answer**: The advantage of this approach is that it promotes code reusability and separation of concerns. By having a `Socket` class, we can encapsulate all socket-related operations, making the code cleaner and easier to maintain. The `Message` class can handle message formatting and parsing, which can also improve code organization. However, the disadvantage is that it may introduce additional complexity, especially for smaller projects where such abstraction may not be necessary. It can also lead to more files and classes to manage and having to put more thought into the design of the classes and their interactions.

## Introduction to Namespace

- There are different ways namespace is being used in this exercise
- Which way is better? What are the advantages and disadvantages?
  - The two ways `namespace` is being used in the exercise are:
    - Namespace aliasing using `namespace ttc = tt::chat`
    - Using directive `using namespace tt::chat` which brings all the definitions of a namespace into the current scope.
  - Between these two ways, the one being better depends on the context where the namespace is being used and the size of the codebase. If definitions inside the namespace would not end up conflicting with other definitions in the current scope, then using directive can be more convenient and can make the code cleaner. However, if there are potential naming conflicts or if the namespace contains a large number of definitions, then namespace aliasing can be a better choice as it provides better readability and avoids potential naming conflicts or ambiguity.

## Abstracting Code into Classes

- Abstract the client and server logic into a `Client` and `Server` class
- **Note**: You don't have to use the code in this exercise as a starting point
- You can use the code you wrote from previous exercises instead
- How should you divide the code into files?
- What namespace and directory structure should you use? Why?
  - **Answer**: I have divided the code into three files: `client-main.cc`, `server-main.cc`, and `chat-sockets.cc`. The `client-main.cc` file contains the main function for the client, while the `server-main.cc` file contains the main function for the server. The `chat-sockets.cc` file contains the implementation of the `Socket` and `Address` classes that are used by both the client and server. I have also created a `net` directory to hold the `chat-sockets` files,. `Client` comes under the `tt::chat::client` namespace, `Server` comes under the `tt::chat::server` namespace, and the `Socket` and `Address` classes come under the `tt::chat::net` namespace. This structure allows for better organization of the code and promotes separation of concerns.

## Programming Sense of Taste

- How do you judge what makes a particular choice of namespace and directory
  structure?
  - **Answer**: For a namespace and directory structure, I judge it by how easy it is to understand and maintain. A good structure groups related code together, keeps dependencies obvious, and avoids making imports or includes awkward. If the layout mirrors the real design of the program and makes it easy to find where something belongs, that is usually a good sign. If it feels like files are scattered or namespaces are doing too much work, that is usually a sign of not so good structure. 
- How do you judge what makes a good naming convention or programming style?
  - **Answer**: A good convention or style is one that helps the next person understand the code quickly without guessing. I usually look for names that are clear, consistent, and specific enough to show intent. Good style also keeps the code easy to scan, avoids unnecessary surprises, and fits the rest of the project.



## "Senses" in Programming

- Have you ever heard of programmers referring to "code smells"? How can code
  smell?
  - **Answer**: Yes. Code can smell when something feels off even if it still works, like duplicated logic, vague names, overly long functions, or confusing structure. A smell is usually a warning sign that the code may be harder to understand, change, or trust later.
- What does it mean to have a sense of taste in programming? How can code
  taste?
  - **Answer**: Having taste in programming means being able to choose solutions that are not just correct, but clean, simple, and appropriate for the problem. Code can "taste good" when it feels clear, well-fitted, and balanced, like the design matches the job without extra noise.
- Is there an analogue for every sense?
  - **Answer**: Not always one-to-one, but many senses have a rough analogue in programming. For example, readability is like sight, code smell is like smell, and the feeling of a design being clunky or smooth is close to touch. Some analogies are only partial, though, because code is an abstraction and not a physical thing.
- What other code senses can you think of?
  - **Answer**: I can think of a sense of rhythm for repeated patterns, a sense of balance for how responsibilities are split, a sense of scale for whether a solution will still work when the project grows, and a sense of risk for spotting fragile parts of the code.
- How many senses do humans have?
  - **Answer**: People usually talk about five senses in everyday conversation, but biologically humans have more than that, including balance, body position, and internal senses like hunger or pain.
- When would you want to see something before you touch it?
  - **Answer**: You would want to see first when you need to judge safety or shape before acting, like checking whether something is fragile, dangerous, or worth picking up.
- When would you want to touch something before you see it?
  - **Answer**: You would want to touch first when feel gives you the important information, like finding something in the dark, checking texture, or knowing whether a surface is hot before looking closely.