/*
 * file:        elf32.h
 * description: easier-to-use version of the 32-bit parts of elf.h
 * license:     GPL 2.1 or higher, derived from the GNU C Library
 */
#ifndef __ELF64_H__
#define __ELF64_H__

/* file type
*/
enum ftype {
	ET_NONE = 0,
	ET_REL = 1,
	ET_EXEC = 2,
	ET_DYN = 3,
	ET_CORE = 4,
	ET_16 = 0xFFFF
} __attribute__((__packed__));

/* machine type - ignore all the others
*/
enum mtype {
	EM_386 = 3,
	EM_16 = 0xFFFF
} __attribute__((__packed__)) ;

/* ELF only has one version
*/
enum vrsion {
	EV_CURRENT = 1
};

/* class and data encoding are bytes 4 and 5 of e_ident
*/
enum ei {
	EI_CLASS =      4,          /* File class byte index */
	EI_DATA =       5,          /* Data encoding byte index */
};

enum eiclass {
	ELFCLASSNONE =  0,          /* Invalid class */
	ELFCLASS32 =    1,          /* 32-bit objects */
	ELFCLASS64 =    2,          /* 64-bit objects */
	ELFCLASSNUM =   3,
};

enum eidata {
	ELFDATANONE =   0,          /* Invalid data encoding */
	ELFDATA2LSB =   1,          /* 2's complement, little endian */
	ELFDATA2MSB =   2,          /* 2's complement, big endian */
};

/* so we don't need <stdint.h> 
*/
typedef unsigned long long uint64_t;
typedef unsigned int       uint32_t;
typedef unsigned short     uint16_t;
typedef unsigned char      uint8_t;

/* the ELF header itself
*/
struct elf64_ehdr {
	unsigned char e_ident[16];            /* Magic number and other info */
	enum ftype    e_type;                 /* Object file type */
	enum mtype    e_machine;              /* Architecture */
	uint32_t      e_version;              /* Object file version */
	void *        e_entry;                /* Entry point virtual address */
	uint64_t      e_phoff;                /* Program header table file offset */
	uint64_t      e_shoff;                /* Section header table file offset */
	uint32_t      e_flags;                /* Processor-specific flags */
	uint16_t      e_ehsize;               /* ELF header size in bytes */
	uint16_t      e_phentsize;            /* Program header table entry size */
	uint16_t      e_phnum;                /* Program header table entry count */
	uint16_t      e_shentsize;            /* Section header table entry size */
	uint16_t      e_shnum;                /* Section header table entry count */
	uint16_t      e_shstrndx;             /* Section header string table index */
} __attribute__((__packed__));

/* program header table
*/
enum ptype {
	PT_NULL =       0,               /* Program header table entry unused */
	PT_LOAD =       1,               /* Loadable program segment */
	PT_DYNAMIC =    2,               /* Dynamic linking information */
	PT_INTERP =     3,               /* Program interpreter */
	PT_NOTE =       4,               /* Auxiliary information */
	PT_SHLIB =      5,               /* Reserved */
	PT_PHDR =       6,               /* Entry for header table itself */
	PT_TLS =        7,               /* Thread-local storage segment */
	PT_NUM =        8,               /* Number of defined types */
	PT_LOOS =       0x60000000,      /* Start of OS-specific */
	PT_GNU_EH_FRAME = 0x6474e550,    /* GCC .eh_frame_hdr segment */
	PT_GNU_STACK =  0x6474e551,      /* Indicates stack executability */
	PT_GNU_RELRO =  0x6474e552,      /* Read-only after relocation */
	PT_LOSUNW =     0x6ffffffa,
	PT_SUNWBSS =    0x6ffffffa,      /* Sun Specific segment */
	PT_SUNWSTACK =  0x6ffffffb,      /* Stack segment */
	PT_HISUNW =     0x6fffffff,
	PT_HIOS =       0x6fffffff,      /* End of OS-specific */
	PT_LOPROC =     0x70000000,      /* Start of processor-specific */
	PT_HIPROC =     0x7fffffff       /* End of processor-specific */
} __attribute__((__packed__));

enum pflag {
	PF_X =          (1 << 0),        /* Segment is executable */
	PF_W =          (1 << 1),        /* Segment is writable */
	PF_R =          (1 << 2)         /* Segment is readable */
};

struct elf64_phdr {
	enum ptype  p_type;                 /* Segment type */
	uint32_t    p_flags;                /* Segment flags */
	uint64_t    p_offset;               /* Segment file offset */
	void *      p_vaddr;                /* Segment virtual address */
	void *      p_paddr;                /* Segment physical address */
	uint64_t    p_filesz;               /* Segment size in file */
	uint64_t    p_memsz;                /* Segment size in memory */
	uint64_t    p_align;                /* Segment alignment */
} __attribute__((__packed__));

/* section header table
*/
enum shtype {
	SHT_NULL = 0,             /* Section header table entry unused */
	SHT_PROGBITS = 1,
	SHT_SYMTAB = 2, 
	SHT_STRTAB = 3,
	SHT_RELA = 4,
	SHT_HASH = 5,
	SHT_DYNAMIC = 6,
	SHT_NOTE = 7,
	SHT_NOBITS = 8,
	SHT_REL = 9,
	SHT_SHLIB = 10,
	SHT_DYNSYM = 11,
	SHT_INIT_ARRAY = 14,
	SHT_FINI_ARRAY = 15,
	SHT_PREINIT_ARRAY = 16,
	SHT_GROUP = 17,
	SHT_SYMTAB_SHNDX = 18,
	SHT_32 = 0xFFFFFFFF
} __attribute__((__packed__));

enum shflag {
	SHF_WRITE = (1 << 0),
	SHF_ALLOC = (1 << 1),
	SHF_EXECINSTR = (1 << 2),
	SHF_MERGE = (1 << 4),
	SHF_STRINGS = (1 << 5),
	SHF_INFO_LINK = (1 << 6),
	SHF_LINK_ORDER = (1 << 7),
	SHF_GROUP = (1 << 9),
	SHF_TLS = (1 << 10)
};

struct elf64_section {
	uint32_t    sh_name;                /* Section name (string tbl index) */
	enum shtype sh_type;                /* Section type */
	uint64_t    sh_flags;               /* Section flags */
	void *      sh_addr;                /* Section virtual addr at execution */
	uint64_t    sh_offset;              /* Section file offset */
	uint64_t    sh_size;                /* Section size in bytes */
	uint32_t    sh_link;                /* Link to another section */
	uint32_t    sh_info;                /* Additional section information */
	uint64_t    sh_addralign;           /* Section alignment */
	uint64_t    sh_entsize;             /* Entry size if section holds table */
} __attribute__((__packed__));

/* symbol table structure. This isn't completely converted yet
*/
struct elf64_sym {
	uint32_t    st_name;                /* Symbol name (string tbl index) */
	uint8_t     st_info;                /* Symbol type and binding */
	uint8_t     st_other;               /* Symbol visibility */
	uint16_t    st_shndx;               /* Section index */
	void *      st_value;               /* Symbol value */
	uint64_t    st_size;                /* Symbol size */
} __attribute__((__packed__));

enum dtag {
	DT_NULL =       0,               /* Marks end of dynamic section */
	DT_NEEDED =     1,               /* Name of needed library */
	DT_PLTRELSZ =   2,               /* Size in bytes of PLT relocs */
	DT_PLTGOT =     3,               /* Processor defined value */
	DT_HASH =       4,               /* Address of symbol hash table */
	DT_STRTAB =     5,               /* Address of string table */
	DT_SYMTAB =     6,               /* Address of symbol table */
	DT_RELA =       7,               /* Address of Rela relocs */
	DT_RELASZ =     8,               /* Total size of Rela relocs */
	DT_RELAENT =    9,               /* Size of one Rela reloc */
	DT_STRSZ =      10,              /* Size of string table */
	DT_SYMENT =     11,              /* Size of one symbol table entry */
	DT_INIT =       12,              /* Address of init function */
	DT_FINI =       13,              /* Address of termination function */
	DT_SONAME =     14,              /* Name of shared object */
	DT_RPATH =      15,              /* Library search path (deprecated) */
	DT_SYMBOLIC =   16,              /* Start symbol search here */
	DT_REL =        17,              /* Address of Rel relocs */
	DT_RELSZ =      18,              /* Total size of Rel relocs */
	DT_RELENT =     19,              /* Size of one Rel reloc */
	DT_PLTREL =     20,              /* Type of reloc in PLT */
	DT_DEBUG =      21,              /* For debugging; unspecified */
	DT_TEXTREL =    22,              /* Reloc might modify .text */
	DT_JMPREL =     23,              /* Address of PLT relocs */
	DT_BIND_NOW =   24,              /* Process relocations of object */
	DT_INIT_ARRAY = 25,              /* Array with addresses of init fct */
	DT_FINI_ARRAY = 26,              /* Array with addresses of fini fct */
	DT_INIT_ARRAYSZ =7,              /* Size in bytes of DT_INIT_ARRAY */
	DT_FINI_ARRAYSZ =8,              /* Size in bytes of DT_FINI_ARRAY */
	DT_RUNPATH =    29,              /* Library search path */
	DT_FLAGS =      30,              /* Flags for the object being loaded */
	DT_ENCODING =   32,              /* Start of encoded range */
	DT_PREINIT_ARRAY = 32,           /* Array with addresses of preinit fct*/
	DT_PREINIT_ARRAYSZ = 33          /* size in bytes of DT_PREINIT_ARRAY */
} __enum_64__;

struct elf32_dyn {
	enum dtag   d_tag;                  /* Dynamic entry type */
	union
	{
		uint64_t d_val;                 /* Integer value */
		void *   d_ptr;                 /* Address value */
	} d_un;
};

/* AMD x86-64 relocations. many comments elided 
*/
enum relo {
	R_X86_64_NONE =             0, /* No reloc */
	R_X86_64_64 =               1, /* Direct 64 bit  */
	R_X86_64_PC32 =             2, /* PC relative 32 bit signed */
	R_X86_64_GOT32 =            3, /* 32 bit GOT entry */
	R_X86_64_PLT32 =            4, /* 32 bit PLT address */
	R_X86_64_COPY =             5, /* Copy symbol at runtime */
	R_X86_64_GLOB_DAT =         6, /* Create GOT entry */
	R_X86_64_JUMP_SLOT =        7, /* Create PLT entry */
	R_X86_64_RELATIVE =         8, /* Adjust by program base */
	R_X86_64_GOTPCREL =         9,    
	R_X86_64_32 =               10, /* Direct 32 bit zero extended */
	R_X86_64_32S =              11, /* Direct 32 bit sign extended */
	R_X86_64_16 =               12, /* Direct 16 bit zero extended */
	R_X86_64_PC16 =             13, /* 16 bit sign extended pc relative */
	R_X86_64_8 =                14, /* Direct 8 bit sign extended  */
	R_X86_64_PC8 =              15, /* 8 bit sign extended pc relative */
	R_X86_64_DTPMOD64 =         16, /* ID of module containing symbol */
	R_X86_64_DTPOFF64 =         17,   
	R_X86_64_TPOFF64 =          18,   
	R_X86_64_TLSGD =            19,   
	R_X86_64_TLSLD =            20,    
	R_X86_64_DTPOFF32 =         21, /* Offset in TLS block */
	R_X86_64_GOTTPOFF =         22,    
	R_X86_64_TPOFF32 =          23, /* Offset in initial TLS block */
	R_X86_64_PC64 =             24, 
	R_X86_64_GOTOFF64 =         25, 
	R_X86_64_GOTPC32 =          26, 
	R_X86_64_GOT64 =            27, 
	R_X86_64_GOTPCREL64 =       28, 
	R_X86_64_GOTPC64 =          29, 
	R_X86_64_GOTPLT64 =         30, 
	R_X86_64_PLTOFF64 =         31, 
	R_X86_64_SIZE32 =           32, /* Size of symbol plus 32-bit addend */
	R_X86_64_SIZE64 =           33, /* Size of symbol plus 64-bit addend */
	R_X86_64_GOTPC32_TLSDESC =  34, 
	R_X86_64_TLSDESC_CALL =     35,  
	R_X86_64_TLSDESC =          36,   
	R_X86_64_IRELATIVE =        37, /* Adjust indirectly by program base */
	R_X86_64_RELATIVE64 =       38, /* 64-bit adjust by program base */
	R_X86_64_GOTPCRELX =        41, 
	R_X86_64_REX_GOTPCRELX =    42, 
	R_X86_64_NUM =              43
};

#endif  /* __ELF64_H__ */
