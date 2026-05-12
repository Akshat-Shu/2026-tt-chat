# tt-chat-2026

A C++ networking course that builds up from a single-file TCP echo client/server to a multi-client chat application, culminating in a group project that benchmarks TCP against UDP multicast.

Each exercise is self-contained in its own directory with a `README.md` of tasks and questions, source code under `src/`, and (from exercise-5 onward) a `Makefile`.

## Prerequisites

You need:

- **`g++` with C++20 support** (gcc 10+, ideally 13+; or clang 15+).
  - **macOS:** `brew install gcc`, then make sure `g++` resolves to the Homebrew version, not Apple's `clang` alias.
  - **Linux (Debian/Ubuntu):** `sudo apt-get install g++ make`.
  - **Windows:** install the [MinGW-w64 toolchain](https://code.visualstudio.com/docs/cpp/config-mingw).
- **`make`** (Linux/macOS have it; on Windows it ships with MinGW-w64).
- **`git`** — install from <https://git-scm.com/downloads> if `git --version` doesn't work.
- An editor. VSCode with the C/C++ extension works well, but anything will do.

Later exercises additionally require a Linux environment with `epoll` (exercise-7 onward), `spdlog` (exercise-6), and `perf` + FlameGraphs (group exercise).

## How to Use This Repo

- Work through `exercise-1` through `exercise-8` in order.
- Answer the questions in each exercise's `README.md` by editing it directly.
- Commit and push after each task. Keep commits scoped to a single task or question.
- Bonus sections are optional and harder.
- The `group-exercise/` directory is the capstone, done as a team.

## Exercises

### exercise-1 — Tooling Fundamentals
Compile a TCP echo client and server with `g++`. Write a `Makefile` that builds `build/client` and `build/server` and supports `make clean`. Learn the essential git commands. First look at sockets, headers, and the difference between pointers and references, `std::string` vs. C-style strings.

### exercise-2 — Sources, Refactoring, and Debugging
Identify authoritative sources for sockets, TCP/IP, and C++ (man pages, RFCs, ISO). Practice the "extract function" refactor. Start thinking about performance. Learn IDE debugging and memory inspection in debug mode.

### exercise-3 — Reuse, Compiler Explorer, Memory
Reduce duplication between client and server. Use Compiler Explorer (godbolt) to inspect generated assembly. Go deeper on memory management and performance reasoning.

### exercise-4 — Multi-File C++ Projects
Split the code across multiple translation units. Understand the distinction between compiling and linking. Run performance experiments.

### exercise-5 — Classes, Namespaces, Abstraction
Reorganize into `client-main.cc`, `server-main.cc`, a `net/` module, and `utils.h`. Introduce classes and namespaces. Compare file changes between versions.

### exercise-6 — Third-Party Libraries
Add `spdlog` as a dependency. Cover static vs. dynamic linking, building libraries from source, and C++ package managers.

### exercise-7 — `epoll`
Replace the blocking I/O loop with `epoll`. Build a chat client and server that can handle many connections. Add a third-party library from source.

### exercise-8 — Chat Server with `epoll` (partial scaffold)
Two weeks of tasks built on the partial epoll echo server in this directory. Includes a hard bonus section.

### group-exercise — Capstone: TCP vs. UDP Multicast Chat
Design and build a chat application as a team. Define a timeline, divide tasks, and agree on a branching and PR review workflow. Build a test framework that opens many client connections and measures throughput. Profile with `perf` and FlameGraphs. Compare TCP fan-out against UDP multicast.

Relevant topics: network vs. host byte order (`htons`/`ntohs`, `htonl`/`ntohl`), `inet_pton`/`inet_ntop`, struct padding and `__attribute__((packed))` / `#pragma pack`, type punning and zero-copy techniques used in HFT, and scaling considerations for millions of clients.

References: [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/), [RFC 768 (UDP)](https://datatracker.ietf.org/doc/html/rfc0768), [RFC 1112 (IP Multicasting)](https://www.rfc-editor.org/rfc/rfc1112), [RFC 8085 (UDP Usage Guidelines)](https://datatracker.ietf.org/doc/html/rfc8085), [TLDP Multicast HOWTO](https://tldp.org/HOWTO/Multicast-HOWTO.html).

## Recurring Themes

- Prefer authoritative sources (man pages, RFCs, ISO standard) over secondhand summaries.
- Measure performance; do not guess.
- Keep commits small and focused on a single task.
- Learn how to evaluate whether a source of information is trustworthy.
