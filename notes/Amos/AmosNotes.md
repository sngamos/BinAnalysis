
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

`# file -i /bin/cat`  

> output:  
> `/bin/cat: application/x-pie-executable; charset=binary`  
  

`# file /bin/cat`  

> output:  
> `/bin/cat: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1=f2ca4d18037c2be160ba882ffbe2fbed56d60f83, for GNU/Linux 3.2.0, stripped`
