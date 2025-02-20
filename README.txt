CS5600 Project 1 - README

Overview
This project consists of three parts, part-1 focusing on reading and printing using system call wrappers, part-2 focusing on ELF file execution, and part-3 focusing on context switching.

Part 1 - Basic System Call Wrappers
In part-1.c, the following functions were implemented:

- System Call Wrappers:
  - read(int fd, void *ptr, int len): Reads data from the given file descriptor.
  - write(int fd, void *ptr, int len): Writes data to the given file descriptor.
  - exit(int err): Terminates the program with the given error code.

- Utility Functions:
  - readline(char *buf, int len): Reads input from stdin character by character.
  - print(char *buf): Prints a string to stdout.

- Main Function:
  - Continuously reads input from the user and echoes it back.
  - Exits when the user types "quit".

Part 2 - Extended System Calls & ELF Execution
In part-2.c, additional system call wrappers and ELF execution functions were implemented:

- Additional System Call Wrappers:
  - open(char *path, int flags): Opens a file.
  - close(int fd): Closes a file descriptor.
  - lseek(int fd, int offset, int flag): Seeks to a position in a file.
  - mmap(void *addr, int len, int prot, int flags, int fd, int offset): Maps a file to memory.
  - munmap(void *addr, int len): Unmaps memory.

- Input and Argument Handling:
  - do_readline(char *buf, int len): Reads a line from input.
  - do_print(char *buf): Prints a string to stdout.
  - do_getarg(int i): Retrieves command-line arguments.

- ELF File Execution:
  - exec_file(char *filename): 
    - Opens the ELF file and reads the header.
    - Iterates through program headers to find PT_LOAD sections.
    - Maps memory regions and loads the ELF segments into memory.
    - Calls the entry point of the ELF binary to execute it.
    - After execution, unmaps the allocated memory to prevent leaks.

- Main Function:
  - Reads user input and splits it into arguments.
  - Executes ELF files using exec_file(char *filename).

Part 3 - Process Execution and Context Switching
In part-3.c, process execution and thread switching were implemented:

- Additional System Call Wrappers:
  - Used the same system call wrappers from Part 1 and Part 2.

- ELF File Execution:
  - exec_file(char *filename, unsigned long offset): 
    - Opens the ELF file and reads the ELF header.
    - Iterates through the program headers, mapping PT_LOAD sections to memory.
    - Maps memory pages at a fixed offset to avoid address conflicts.
    - Loads executable sections into the allocated memory.
    - Returns the entry point address for execution.

- Thread Switching Functions:
  - do_yield12(): Switches from thread 1 to thread 2.
  - do_yield21(): Switches from thread 2 to thread 1.
  - do_uexit(): Exits a user-mode thread and returns to the original context.

- Main Function:
  - Sets up two process stacks.
  - Loads and executes process1 and process2 using exec_file().
  - Uses switch_to() to switch between user threads, simulating cooperative multitasking.

Conclusion
Each part of this project progressively builds on system programming concepts, from basic system calls to ELF execution and user-level threading. This work demonstrates an understanding of low-level operations in UNIX-like systems, including system calls, memory mapping, and context switching.

