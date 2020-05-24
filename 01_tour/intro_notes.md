# A Tour of computer systems: notes
Files such as hello.c that consist exclusively
of ASCII characters are known as text files. All other files are known as binary
files.

The representation of hello.c illustrates a fundamental idea: All information
in a system—including disk files, programs stored in memory, user data stored in
memory, and data transferred across a network—is represented as a bunch of bits.
The only thing that distinguishes different data objects is the context in which
we view them. For example, in different contexts, the same sequence of bytes
might represent an integer, floating-point number, character string, or machine
instruction.

The `hello` program begins life as a high-level C program because it can be read
and understood by human beings in that form. However, in order to run hello.c
on the system, the individual C statements must be translated by other programs
into a sequence of low-level machine-language instructions. These instructions are
then packaged in a form called an executable object program and stored as a binary
disk file. Object programs are also referred to as executable object files.

On a Unix system, the translation from source file to object file is performed
by a compiler driver:
```bash
linux> gcc -o hello hello.c
```

Here the `GCC` compiler driver redas the source file `hello.c` and translates it into
an executable object file `hello`. The translation is performed in the squence 
of four phases. The programs that perform the four phases:
1. preprocessor
2. compiler
3. assembler
4. linker
are known collectively as the __compilation system__.

 + _Preprocessing phase_: The preprocessor (`cpp`) modifies the original C program
   according to directives that begin with the `#` character. For eaxmple, the
   `#include <stdio.h>` command in line 1 of `hello.c` tells the preprocessor
   to read the contents of the system header file `stdio.h` and isnert it directly
   into the program text. The result is another C program, typically with the `.i`
   suffix.
   ```
   * hello.c   -> [preprocessor] ->   hello.i
   ```

 + _Compilation phase_: The compiler (`cc1`) translates the   text file `hello.i` into
    the text `hello.s`, which contains an _assembly-language program_. This program includes the following definition
    of function main:
    ```assembly
    main:
        subq    $8, %rsp
        movl    $.LCO, %edi
        call    puts
        movl    $0, %eax
        addq    $8, %rsp
        ret
    ```
    Each of lines 2–7 in this definition describes one low-level machine-
    language instruction in a textual form. Assembly language is useful because
    it provides a common output language for different compilers for different
    high-level languages. For example, C compilers and Fortran compilers both
    generate output files in the same assembly language.
    ```
    hello.i   -> [compiler] ->   hello.s
    ```

 + _Assembly phase_: Next, the assembler (`as`) translates
 the `hello.s` into mchine language instructions,
   packages them in a form known as a _relocable object program_,
   and stores the result int he object file `hello.o`.
   This file is a binary file containin 17 bytes to encode
   the isntructions for function main. If we were to
   view `hello.o` with a text editor, it would
   appear to be gibberish.
   ```
   hello.s   -> [assembler] ->   hello.o
   ```

 + _Linking phase_: Notice that our `hello` program calls
   the `printf` function, which is part of the _standard C library_ provided by every C compiler. The `printf`
   function resides in a separate precompiled object file 
   called `printf.o` which must somehow be merged with
   out `hello.o` program. The linker (`ld`) handles this
   merging. The result is the `hello` file, which is an
   executable object file that is ready to be loaded into 
   memory and executed by the system.
   ```
   printf.o + hello.o   -> [linker] ->   hello
   ```