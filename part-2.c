/*
 * file:        part-2.c
 * description: Part 2, CS5600 Project 1, 2025 SP
 */

/* NO OTHER INCLUDE FILES */
#include "elf64.h"
#include "sysdefs.h"

extern void *vector[];

#define BUFFER_SIZE 200
#define MAX_ARGS 10

char *argv[10];
int argc = 0;

/* ---------- */

/* write these functions 
*/
int read(int fd, void *ptr, int len);
int write(int fd, void *ptr, int len);
void exit(int err);
int open(char *path, int flags);
int close(int fd);
int lseek(int fd, int offset, int flag);
void *mmap(void *addr, int len, int prot, int flags, int fd, int offset);
int munmap(void *addr, int len);

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

int open(char *path, int flags) {
	return syscall(__NR_open, path, flags);
}

int close(int fd) {
	return syscall(__NR_close, fd);
}

int lseek(int fd, int offset, int flag) {
	return syscall(__NR_lseek, fd, offset, flag);
}

void *mmap(void *addr, int len, int prot, int flags, int fd, int offset) { 
	return (void *)syscall(__NR_mmap, addr, len, prot, flags, fd, offset);
}

int munmap(void *addr, int len) {
	return syscall(__NR_munmap, addr, len);
}

/* ---------- */

/* the three 'system call' functions - readline, print, getarg 
 * hints: 
 *  - read() or write() one byte at a time. It's OK to be slow.
 *  - stdin is file desc. 0, stdout is file descriptor 1
 *  - use global variables for getarg
 */

void do_readline(char *buf, int len);
void do_print(char *buf);
char *do_getarg(int i);         

void do_readline(char *buf, int len) {
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

void do_print(char *buf) {
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

char *do_getarg(int i) {
	if(i >= argc) {
		return NULL;
	}
	return argv[i];
}
/* ---------- */

/* the guts of part 2
 *   read the ELF header
 *   for each section, if b_type == PT_LOAD:
 *     create mmap region
 *     read from file into region
 *   function call to hdr.e_entry
 *   munmap each mmap'ed region so we don't crash the 2nd time
 */

/* your code here */
void exec_file(char *filename);

void exec_file(char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        do_print("Error opening file\n");
        exit(1);
    }

	struct elf64_ehdr hdr;
	read(fd, &hdr, sizeof(hdr));

    int n = hdr.e_phnum;
	struct elf64_phdr phdrs[n];
	lseek(fd, hdr.e_phoff, SEEK_SET);
	read(fd, phdrs, sizeof(phdrs));

    void *allocated_mem_addr[n];
    int allocated_mem_size[n];
    int allocated_mem_count = 0;

    for (int i = 0; i < n; i++) {
		if (phdrs[i].p_type == PT_LOAD) {
            int len = ROUND_UP(phdrs[i].p_memsz, 4096UL);

            unsigned long request_addr = 0x80000000UL + (unsigned long)phdrs[i].p_vaddr;
            unsigned long desired_addr = ROUND_DOWN(request_addr, 4096UL);
            
            void *buf = mmap((void *)desired_addr, len, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
            
            if (buf == MAP_FAILED) { 
                do_print("mmap failed\n"); 
                exit(1); 
            }

            allocated_mem_addr[allocated_mem_count] = (void *)desired_addr;
            allocated_mem_size[allocated_mem_count] = len;
            allocated_mem_count++;

            lseek(fd, phdrs[i].p_offset, SEEK_SET);
            read(fd,(void *)(0x80000000 + phdrs[i].p_vaddr), phdrs[i].p_filesz);
		}
	}
    close(fd);
    void (*f)() = hdr.e_entry + 0x80000000;
    f();

    for(int j=0; j<allocated_mem_count; j++) {
        munmap(allocated_mem_addr[j], allocated_mem_size[j]);
    }
}
/* ---------- */

/* simple function to split a line:
 *   char buffer[200];
 *   <read line into 'buffer'>
 *   char *argv[10];
 *   int argc = split(argv, 10, buffer);
 *   ... pointers to words are in argv[0], ... argv[argc-1]
 */
int split(char **argv, int max_argc, char *line)
{
	int i = 0;
	char *p = line;

	while (i < max_argc) {
		while (*p != 0 && (*p == ' ' || *p == '\t' || *p == '\n'))
			*p++ = 0;
		if (*p == 0)
			return i;
		argv[i++] = p;
		while (*p != 0 && *p != ' ' && *p != '\t' && *p != '\n')
			p++;
	}
	return i;
}

/* ---------- */

void main(void)
{
    char buffer[BUFFER_SIZE];

	vector[0] = do_readline;
	vector[1] = do_print;
	vector[2] = do_getarg;

	/* YOUR CODE HERE */
    while(1) {
        do_print("Input: ");
        do_readline(buffer, BUFFER_SIZE);

        if(buffer[0] == '\0') {
            continue;
        }

        if (buffer[0] == 'q' && buffer[1] == 'u' && buffer[2] == 'i' &&
            buffer[3] == 't' && buffer[4] == '\0') {
            exit(0);
        }

        argc = split(argv, MAX_ARGS, buffer);

        if(argc == 0) {
            continue;
        }

        exec_file(argv[0]);
    }
}

