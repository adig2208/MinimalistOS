/*
 * file:        part-3.c
 * description: part 3, CS5600 Project 1, 2025 SP
 */

/* NO OTHER INCLUDE FILES */
#include "elf64.h"
#include "sysdefs.h"

#define STACK_SIZE 4096

void *stack1;
void *stack2;

void *s1, *s2, *s;

extern void *vector[];
extern void switch_to(void **location_for_old_sp, void *new_value);
extern void *setup_stack0(void *_stack, void *func);

/* ---------- */

/* write these 
*/
int read(int fd, void *ptr, int len);
int write(int fd, void *ptr, int len);
void exit(int err);
int open(char *path, int flags);
int close(int fd);
int lseek(int fd, int offset, int flag);
void *mmap(void *addr, int len, int prot, int flags, int fd, int offset);
int munmap(void *addr, int len);

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

/* copy from Part 2 */
void do_print(char *buf);

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

/* ---------- */



void *exec_file(char *filename, unsigned long offset);

void *exec_file(char *filename, unsigned long offset) {
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

    for (int i = 0; i < n; i++) {
        if (phdrs[i].p_type == PT_LOAD) {
            int len = ROUND_UP(phdrs[i].p_memsz, 4096);

            unsigned long request_addr = offset + (unsigned long)phdrs[i].p_vaddr;
            unsigned long desired_addr = ROUND_DOWN(request_addr, 4096UL);
            
            void *buf = mmap((void *)desired_addr, len, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
            
            if (buf == MAP_FAILED) { 
                do_print("mmap failed\n"); 
                exit(1); 
            }
            
            lseek(fd, phdrs[i].p_offset, SEEK_SET);
            read(fd, (void *)(offset + phdrs[i].p_vaddr), phdrs[i].p_filesz);
        }
    }
    close(fd);

    return (void *)(hdr.e_entry + offset);
}


/* write these new functions */
void do_yield12(void);
void do_yield21(void);
void do_uexit(void);

void do_yield12(void) {
	switch_to(&s1,s2);
}

void do_yield21(void) {
	switch_to(&s2,s1);
}

void do_uexit(void) {
	switch_to(&s1,s);
	exit(0);
}
/* ---------- */

void main(void)
{
	vector[1] = do_print;

	vector[3] = do_yield12;
	vector[4] = do_yield21;
	vector[5] = do_uexit;

	/* your code here */
	stack1 = mmap(0, STACK_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	stack2 = mmap(0, STACK_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if ((stack1 == MAP_FAILED) || (stack2 == MAP_FAILED)) { 
            do_print("stack mmap failed\n"); 
            exit(1); 
        }

	void *entry1 = exec_file("process1", 0x90000000);
	void *entry2 = exec_file("process2", 0x80000000);

	s1 = setup_stack0(stack1 + STACK_SIZE, entry1);
	s2 = setup_stack0(stack2 + STACK_SIZE, entry2);

	switch_to(&s, s1);

	do_print("done\n");
	exit(0);
}
