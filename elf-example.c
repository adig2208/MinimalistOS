/*
 * file:        elf-example.c
 * description: project-1-part-2 CS5600
 */

/* this code uses the real include files and standard library */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "elf64.h"

/* round A up to the next multiple of B
*/
#define ROUND_UP(a,b) (((a+b-1)/b)*b)

/* usage: elf-example <exe_file>
 *    reads ELF header and printfs useful info on loadable sections
 */
int main(int argc, char **argv)
{
	char *filename = argv[1];	/* I should really check argc first... */
	int fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return 1;		/* failure code */

	/* read the main header (offset 0) */
	struct elf64_ehdr hdr;
	read(fd, &hdr, sizeof(hdr));
	printf("entry point address: %p\n", hdr.e_entry);

	/* read program headers (offset 'hdr.e_phoff') */
	int i, n = hdr.e_phnum;
	struct elf64_phdr phdrs[n];
	lseek(fd, hdr.e_phoff, SEEK_SET);
	read(fd, phdrs, sizeof(phdrs));

	/* look at each section in program headers */
	for (i = 0; i < hdr.e_phnum; i++) {
		if (phdrs[i].p_type == PT_LOAD) {
			int len = ROUND_UP(phdrs[i].p_memsz, 4096);
			printf("section %d: need to allocate %d bytes at %p\n", 
				i, len, phdrs[i].p_vaddr);
			printf("   and read %d bytes from offset %d into that memory\n",
				(int)phdrs[i].p_filesz, (int)phdrs[i].p_offset);
		}
	}

	close(fd);
	exit(0); 			/* success */
}
