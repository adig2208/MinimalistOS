/*
 * file:        sysdefs.h
 * description: system definitions for "bare metal" homework
 */
#ifndef __SYSDEFS_H__
#define __SYSDEFS_H__

/* found in syscall.S 
 */
extern long int syscall(int, ...);

/* system call numbers 
 */
#define __NR_read 0
#define __NR_write 1
#define __NR_exit 60
#define __NR_open 2
#define __NR_close 3
#define __NR_lseek 8
#define __NR_munmap 11
#define __NR_mmap 9

/* flags for mmap, lseek 
 */
#define O_RDONLY 0
#define PROT_READ 1
#define PROT_WRITE 2
#define PROT_EXEC 4
#define MAP_PRIVATE 2
#define MAP_ANONYMOUS 0x20
#define MAP_FAILED (void*)-1
#define SEEK_SET 0
#define NULL 0

/* round 'a' up to the next multiple of 'b'
 */
#define ROUND_UP(a, b) (((a + b - 1) / b) * b)
#define ROUND_DOWN(a, b) ((a / b) * b)

#endif
