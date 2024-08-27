
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
>>>>See Appendix for explanations on `ELF`, `64-LSB executable` and `ABI version`.  
>> Breakdown of output:  
>>> **Architecture:** x86-64  
>>> **ABI version:** SYSV  
>>> **Linking:** dynamically linked (meaning that the file depends on shared libraries)  
>>> **Interpreter:** /lib64/ld-linux-x86-64.so.2 (the dynamic linker/loader)  
>>> **BuildID:** the unique identifier for the binary  
>>> **Compatibility:** built for GNU/Linux 3.2.0 or later  
>>> **Stripped:** binary is stripped of debug information and symbols  






#Appendix