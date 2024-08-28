
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

#### Following the lecture notes walkthroughs  
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



# Appendix  

Executable Linkable Format: 
> Common standard file format for executables, object code, shared libraries, and core dumps in Unix OS.  
> Components:  
>> **Header** --> Contains metadata about the file, including the type of ELF file (e.g executable, shared library), the architecture & other important info.  
>> **Program Header Table** --> Describes sections of the file that needs to be loaded into memory.  
>> **Section Header Table** --> Describes sections of the file which are used for linking and relocation.  
>> **Sections and Segments** --> Contain actual data, code and other information necessary for execution or linking.  

64-bit LSB Executable
> refers to a executable file designed to run on a 64 bit architecture, where the system is capable of processing data in 64-bit chunks.  

ABI Version (Application Binary Interface Version)  
> set of rules or convenions that dictate how different pieces of binary code can interact with each other at low level, i.e how functions are called, how parameters are passed, how system calls are made, how data types are represented in memory.  
> In the example above, the ABI version is `SYSV` which refers to `System V ABI`, a common standard for UNIX system.


 