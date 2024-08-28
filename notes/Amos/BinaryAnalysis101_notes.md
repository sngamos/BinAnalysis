
# Amos' notes for Binary analysis  

## From Uni Idaho notes  

## Introduction  

### Steps in Binary Analysis methodology  
1. Perform Binary Discovery
2. Information gathering
3. Static Analysis
4. Iterating each step
5. Automatic methodolgy task
6. Adopting methodology steps  
 
### Binary Discovery  


Slide 6 outputs:
> `file` command in Unix OS is used to determine the type of file by examining its contents rather than relying on the extensions.  

`# file -i /bin/cat`  

> output:  
> `/bin/cat: application/x-pie-executable; charset=binary`  

>Explanation:  
>> `-i` option is used to output the `MIME` type of the file, in this case the MIME type is: `application/x-pie-executable`.  
>> This indicates `/bin/cat` is a Position Independant Executable (PIE) binary.
>>> `MIME` types are the standard way of describing the content type of files.  
>> The `charset=binary` indicates the files is a binary file **NOT** text file.

`# file /bin/cat`  

> output:  
> `/bin/cat: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1=f2ca4d18037c2be160ba882ffbe2fbed56d60f83, for GNU/Linux 3.2.0, stripped`  

>Explanation: 
>> Without the `-i` option, the output is more detailed.  
>> From the output, `/bin/cat` is a Executable and  Linkable Format (ELF) file, specifically a 64-bit least significant bit (LSB) first executable that is also PIE.
>> Breakdown of output:  
>>> **Architecture:** x86-64  
>>> **ABI version:** SYSV  
>>> **Linking:** dynamically linked (meaning that the file depends on shared libraries)  
>>> **Interpreter:** /lib64/ld-linux-x86-64.so.2 (the dynamic linker/loader)  
>>> **BuildID:** the unique identifier for the binary  
>>> **Compatibility:** built for GNU/Linux 3.2.0 or later  
>>> **Stripped:** binary is stripped of debug information and symbols  

`# ls -alt /bin/`

> `-a` includes **all** files, including hidden files.  
> `-l` shows detailed information about each file, (permissions, number of links, owner, group, size, time of last modification, and the file/directory name).  
> `-t` sorts the files by time of last modication, with most recently modified first.  
> output: a detailed list of files in /bin sorted in chronological of modication (newest to oldest).  


### Examining Binaries  

`$ file 64bit/ch04-example`  

output:  
`ch04-example: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=be0fc51d5fa6803f3d477cd8eda1e41ecddab29a, not stripped`

`$ file 32bit/ch04-example`  

output:  
`ch04-example: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=791f8775cdeafe85055931846e75d1b84fee5257, not stripped`  

Notice the 32-bit is built for Intel 80386 architecture, 64-bit is built for x86-64 architecture  

`strings ch04-example`  
> `strings` scans files provided for sequences of printable characters (letters, numbers, puntuation, etc) that are typically longer than 4 characters (can be adjusted with a flag).
> typically used to scanned binary files like executable/object file.  

output:  
A list of elements with type `string`.  

`readlef -h ch04-example`  
> displays header information of ELF file.
>> output: 
>> **Magic number**: identifies the file as an ELF file  
>> **Class**: 32-bit or 64-bit file  
>> **Data**: Encoding type, if the file uses big or little endian byte order  
>> **Version**: ELF version  
>> **OS/ABI**: OS and ABI for whcih the file is intended  
>> **Type**: if the file is executable, share library, object file, etc  
>> **Machine**: Architecture for which the file is intended for  
>> **Entry point access**: The memory address at which the execution starts when the file is run  
>> **Program header offset**: Offset of the program header table in the file  
>> **Section header offset**: Offset for suction header table in the file  
>> **Flags**: Processor-specific flags  
>> **Header size**: Size of the ELF header  
>> **Program header size**: Size of each entry in program header table  
>> **Number of program headers**: number of entries in program header table  
>> **Section header size**: Size of each entry in the section header table  
>> **Number of section headers**: number of entries in section header table  
>> **Section header string table index**: The index of the section header string table, which contrains the names of the sections.  

`readlef -l -W ch04-example`  
> `-l` displays program headers  
> `-W` enable the display of the full width of the output  
>> output:  
>> **Type**: Type of segement. `LOAD`: a segment that should be loaded into memory. `DYNAMIC`: dynamic linking information. `INTERP`: Interpretor information   
>> **Offset**: the offset of the segment in the file image  
>> **VirtAddr**: Virtual address at which the segment is loaded into memory  
>> **PhysAddr**: Physical address for systems where physical addressing is used (however it is often the same as virtual address)  
>> **FileSiz**: Size of the segment in the file  
>> **MemSiz**: Size of the segment in the memory (often larger than FileSiz if the segment contains unintialized data)  
>> **Flags**: Permissions of the segment, R/W/X  
>> **Align**: Aligment of the segment in the memory  

`readlef -S -W ch04-example`  
> `-S` displays section headers, which describe the sections of the ELF file.  
>> output:  
>> **[NR]**: section index number  
>> **Name**: name of the section (.text, .data, .bss, etc)  
>> **Type**: type of section (PROGBITS, SYMTAB, STRTAB, NOBITS, etc)  
>> **Addr**: address at which the section's first byte should reside in memory  
>> **Off**: Offset of the section in the file image  
>> **Size**: Size of the section in bytes  
>> **ES**: Entry Size if the section holds a table of fixed-size entries  
>> **Flg**: **A** for allocatable, **W** for writable, **X** for executable
>> **Lk**: section table index link, such as to a related section (like a symbol table)  
>> **Inf**: Extra info or section-dependent data  
>> **Al**: Alignment requirement of the section

`readelf -s -W ch04-example`  
> `-s` displays symbol table, which includes information about fucntions, and other symbols used in ELF file.
>> output (of interests):  
>> **Bind**: binding attribute, such as 'GLOBAL' or 'LOCAL' or "WEAK'  
>> **Vis**: visibility of the symbol, such as 'DEFAULT', 'HIDDEN', 'PROTECTED'
>> **Ndx**: section index where the symbol resides, such as '.text', '.data', '.bss', if undefined: 'UND'  

`readelf –p .text ch04-example`  
Gets the string dump of section '.text'






# Appendix  

#### Executable Linkable Format: 
Common standard file format for executables, object code, shared libraries, and core dumps in Unix OS.  
> Components:  
>> **Header** --> Contains metadata about the file, including the type of ELF file (e.g executable, shared library), the architecture & other important info.  
>> **Program Header Table** --> Describes sections of the file that needs to be loaded into memory.  
>> **Section Header Table** --> Describes sections of the file which are used for linking and relocation.  
>> **Sections and Segments** --> Contain actual data, code and other information necessary for execution or linking.  

#### 64-bit LSB Executable
refers to a executable file designed to run on a 64 bit architecture, where the system is capable of processing data in 64-bit chunks.  

#### ABI Version (Application Binary Interface Version)  
A set of rules or convenions that dictate how different pieces of binary code can interact with each other at low level, i.e how functions are called, how parameters are passed, how system calls are made, how data types are represented in memory.  
> In the example above, the ABI version is `SYSV` which refers to `System V ABI`, a common standard for UNIX system.

#### Binding attribute  
GLOBAL, LOCAL, WEAK, which determines the visibility and linkage behaviour of symbols (such as functions for variables) in a program.  
##### GLOBAL symbols  
Visibility: 
> Visible across the entire program, including all object files and shared libraries that are lionked together.

Purpose:  
> Used for functions or variables that need to be accessible from multiple translation units (source files) or even from other shared libraries.  

Linkage Behaviour:  
> When linker encounters a global symbol, it tries to resolve it to a single definition across all linked files. If there are multiple definations of the same global symbol, linker may raise error unless special attribute like `weak` is used.  

#### Local symbols  
Visibility:  
> Only visible within the file in which they are defined. Note accessible or visible to other object files or shared libraries.  

Purpose:  
> Used for internal functions or variables that should not be exposed to other parts of the program or other modules.  

Linkage Behaviour:  
>Linker doesn't try to resolve local symbols across different files. Each file can have its own local symbols with the same name, and won't conflict with each other.  

#### Weak Symbols
Visibility:  
> Lower precedence than global symbols. Can be overwritten by a global symbol of the same name if one exists.

Purpose:  
> Used when you want to provide a default implementation of a function or variable that can be optionally overwritten by another definition elsewhere in the program.  

Linkage Behaviour:  
> If linker finds weak and global symbol with same name, it will link to the global symbol and ignore the weak one. If no global symbol is found, weak on is linked.  



 