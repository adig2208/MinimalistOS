/*
 * file:        part-1.c
 * description: Part 1, CS5600 Project 1, 2025 SP
 */

/* THE ONLY INCLUDE FILE */
#include "sysdefs.h"

#define BUFFER_SIZE 200

/* write these functions */
int read(int fd, void *ptr, int len);
int write(int fd, void *ptr, int len);
void exit(int err);

/* System call wrappers */
int read(int fd, void *ptr, int len) {
    return syscall(__NR_read, fd, ptr, len);
}

int write(int fd, void *ptr, int len) {
    return syscall(__NR_write, fd, ptr, len);
}

void exit(int err) {
    syscall(__NR_exit, err);
}

/* ---------- */

/* Factor, factor! Don't put all your code in main()! 
*/

void readline(char *buf, int len);
void print(char *buf);

/* Reads one line from stdin (file descriptor 0) into a buffer */
void readline(char *buf, int len) {
    int i = 0;
    char ch;
    long input;

    while (i < len - 1) {
        input = read(0, &ch, 1);

        if (input == -1) {
            write(1, "Error reading input\n", 19);
            break;
        }
        if (input == 0) {
            break;
        }
        if (ch == '\n') {
            break;
        }

        buf[i] = ch;
        i++;
    }
    buf[i] = '\0';

    while (ch != '\n' && read(0, &ch, 1) > 0);
}

/* Prints a string to stdout (file descriptor 1) */
void print(char *buf) {
    int len = 0;

    while (buf[len] != '\0') {
        len++;
    }

    char temp[len];

    for (int i = 0; i < len; i++) {
        temp[i] = buf[i];
    }

    write(1, temp, len);
}

/* Main function */
void main(void) {
    char buffer[BUFFER_SIZE];

    while (1) {
        print("Enter String: ");
        readline(buffer, BUFFER_SIZE);

        if (buffer[0] == 'q' && buffer[1] == 'u' && buffer[2] == 'i' &&
            buffer[3] == 't' && buffer[4] == '\0') {
            exit(0);
        }

        print("Output: ");
        print(buffer);
        print("\n");
    }
}
