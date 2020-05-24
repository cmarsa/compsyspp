# Representing and Manipulating Information
We consider the three most important representations of numbers. Unsigned
encodings are based on traditional binary notation, representing numbers greater
than or equal to 0. Two’s-complement encodings are the most common way to
represent signed integers, that is, numbers that may be either positive or negative.
Floating-point encodings are a base-2 version of scientific notation for represent-
ing real numbers. Computers implement arithmetic operations, such as addition
and multiplication, with these different representations, similar to the correspond-
ing operations on integers and real numbers.
Computer representations use a limited number of bits to encode a number,
and hence some operations can overflow when the results are too large to be rep-
resented. This can lead to some surprising results. For example, on most of today’s
computers (those using a 32-bit representation for data type int), computing the
expression

```
200 * 300 * 400 * 500
```

yields −884,901,888. This runs counter to the properties of integer arithmetic—
computing the product of a set of positive numbers has yielded a negative result.

Floating-point arithmetic has altogether different mathematical properties.
The product of a set of positive numbers will always be positive, although over-
flow will yield the special value +∞. Floating-point arithmetic is not associative
due to the finite precision of the representation. For example, the C expression
(3.14+1e20)-1e20 will evaluate to 0.0 on most machines, while 3.14+(1e20-
1e20) will evaluate to 3.14. The different mathematical properties of integer
versus floating-point arithmetic stem from the difference in how they handle the
finiteness of their representations—integer representations can encode a compar-
atively small range of values, but do so precisely, while floating-point representa-
tions can encode a wide range of values, but only approximately.

## Information Storage
Rather than accessing individual bits in memory, most computers use blocks of
8 bits, or bytes, as the smallest addressable unit of memory. A machine-level
program views memory as a very large array of bytes, referred to as virtual
memory. Every byte of memory is identified by a unique number, known as its
address, and the set of all possible addresses is known as the virtual address space.
As indicated by its name, this virtual address space is just a conceptual image
presented to the machine-level program. The actual implementation
uses a combination of dynamic random access memory (DRAM),
flash memory, disk storage, special hardware, and operating system software to
provide the program with what appears to be a monolithic byte array.

Various mechanisms are used to allocate and manage the storage for different
parts of the program. This management is all performed within the virtual address
space. For example, the value of a pointer in C—whether it points to an integer,
a structure, or some other program object—is the virtual address of the first byte
of some block of storage. The C compiler also associates type information with
each pointer, so that it can generate different machine-level code to access the
value stored at the location designated by the pointer depending on the type of
that value. Although the C compiler maintains this type information, the actual
machine-level program it generates has no information about data types. It simply
treats each program object as a block of bytes and the program itself as a sequence
of bytes.

## Hexadecimal Notation
A single byte consists of 8 bits. In binary notation, its value ranges from 00000000 2
to 11111111 2 . When viewed as a decimal integer, its value ranges from 0 10 to 255 10 .
Neither notation is very convenient for describing bit patterns. Binary notation
is too verbose, while with decimal notation it is tedious to convert to and from
bit patterns. Instead, we write bit patterns as base-16, or hexadecimal numbers.
Hexadecimal (or simply “hex”) uses digits ‘0’ through ‘9’ along with characters
‘A’ through ‘F’ to represent 16 possible values.
In C, numeric constants starting with 0x or 0X are interpreted as being in
hexadecimal. The characters ‘A’ through ‘F’ may be written in either upper- or
lowercase. For example, we could write the number `FA1D37B_16` as `0xFA1D37B`,
as `0xfa1d37b`, or even mixing upper- and lowercase (e.g., `0xFa1D37b`).

Converting between binary and hexadecimal is straightforward, since it can be
performed one hexadecimal digit at a time.
For example, suppose you are given the number 0x173A4C. You can convert
this to binary format by expanding each hexadecimal digit, as follows:

```
HEXA:       1       7       3       A       4       C
BINARY   0001    0111    0011    1010    0100    1100
```
This gives the binary representation 000101110011101001001100.

Conversely, given a binary number 1111001010110110110011, you convert it
to hexadecimal by first splitting it into groups of 4 bits each.

Note, however, that if
the total number of bits is not a multiple of 4, you should make the leftmost group
be the one with fewer than 4 bits, effectively padding the number with leading
zeros. Then you translate each group of bits into the corresponding hexadecimal
digit:

```
BINARY:     11  1100    1010    1101    1011    0011
HEXA:        3     C       A       D       B       3
```

When a value `x` is a power of 2, that is, `x = 2^n` for some non negative integer `n`,
we can readily write x in hexadecimal form by remembering that the binary
representation of x is simply 1 followed by `n` zeros. The hexadecimal digit 0
represents 4 binary zeros. So, for `n` written in the form
`i + 4j`, where `0 <= i <=3`, we can write _x_ with a leading hex digit of 1
`(i = 0)`, 2 `(i = 1)`, 4 `(i = 2)`, or 8 `(i = 3)`, followed by `j` hexadecimal 0s.
As an example, `x = 2048 = 2^11`, we have `n = 11 = 3 + 4*2`, giving
hexadecimal representation `0x800`.

Converting between decimal and hexadecimal representations requires using
multiplication or division to handle the general case. To convert a decimal num-
ber x to hexadecimal, we can repeatedly divide `x` by 16, giving a quotient `q` and a
remainder `r`, such that `x = q * 16 + r`. We then use the hexadecimal digit represent-
ing `r` as the least significant digit and generate the remaining digits by repeating
the process on `q`.

Conversely, to convert a hexadecimal number to decimal, we can multiply
each of the hexadecimal digits by the appropriate power of 16. For example, given
the number 0x7AF, swe compute its decimal equivalent as
`7 * 16 2 + 10 * 16 + 15 = 7 * 256 + 10 * 16 + 15 = 1,792 + 160 + 15 = 1,967.`

## Data Sizes
Every computer has a __word size__, indicating the nominal size of pointer data.
Since a virtual address is encoded by such a word the most important system parameter
determiend by the word size is the maxium size of the virtual address space.
That is, for a machine with a _w_-bit word size, the virtual addresses can range
from 0 to `2^w - 1`, giving the program access toat most `2^w` bytes.

In recent years, there has been a widespread shift from machines with 32-
bit word sizes to those with word sizes of 64 bits. This occurred first for high-end
machines designed for large-scale scientific and database applications, followed
by desktop and laptop machines, and most recently for the processors found in
smartphones. A 32-bit word size limits the virtual address space to 4 gigabytes
(written 4 GB), that is, just over 4 × 10 9 bytes. Scaling up to a 64-bit word size
leads to a virtual address space of 16 exabytes, or around 1.84 × 10 19 bytes.

To avoid the vagaries of relying on “typical” sizes and different compiler set-
tings, ISO C99 introduced a class of data types where the data sizes are fixed
regardless of compiler and machine settings. Among these are data types `int32_t`
and `int64_t`, having exactly 4 and 8 bytes, respectively. Using fixed-size integer
types is the best way for programmers to have close control over data represen-
tations.

### Addressing and Byte Ordering
For program objects that span multiple bytes, we must establish two conventions:
what the address of the object will be, and how we will order the bytes in memory.
In virtually all machines, a multi-byte object is stored as a contiguous sequence
of bytes, with the address of the object given by the smallest address of the bytes
used. For example, suppose a variable `x` of type int has address `0x100`; that is, the
value of the address expression &`x` is `0x100`. Then (assuming data type int has a
32-bit representation) the 4 bytes of `x` would be stored in memory locations `0x100`,
`0x101`, `0x102`, and `0x103`.

For ordering the bytes representing an object, there are two common conven-
tions. Consider a w-bit integer having a bit representation `[x_w−1 , x_w−2 , . . . , x_1 , x_0 ]`,
where `x_w−1` is the most significant bit and `x_0` is the least. Assuming `w` is a multiple
of 8, these bits can be grouped as bytes, with the most significant byte having bits
`[x_w−1 , x_w−2 , . . . , x_w−8 ]`, the least significant byte having bits `[x_7 , x_6 , . . . , x_0 ]`, and
the other bytes having bits from the middle. Some machines choose to store the ob-
ject in memory ordered from least significant byte to most, while other machines
store them from most to least. The former convention—where the least significant
byte comes first—is referred to as _little endian_. The latter convention—where the
most significant byte comes first—is referred to as _big endian_.

Suppose the variable x of type int and at address 0x100 has a hexadecimal
value of 0x01234567. The ordering of the bytes within the address range 0x100
through 0x103 depends on the type of machine:

```
Big endian:
            | 0x100 | 0x101 | 0x102 | 0x103 |
__ . . . ___|   01  |   23  |   45  |   67  |____ . . . __

Little endian:
            | 0x100 | 0x101 | 0x102 | 0x103 |
__ . . . ___|   67  |   45  |   23  |   01  |____ . . . __
```

Note that in the word `0x01234567` the high-order byte has hexadecimal value
`0x01`, while the low-order byte has value `0x67`.
Most Intel-compatible machines operate exclusively in little-endian mode. On
the other hand, most machines from IBM and Oracle (arising from their acquisition
tion of Sun Microsystems in 2010) operate in big-endian mode.Note that we said
“most.” The conventions do not split precisely along corporate boundaries. For
example, both IBM and Oracle manufacture machines that use Intel-compatible
processors and hence are little endian. Many recent microprocessor chips are
bi-endian, meaning that they can be configured to operate as either little- or
big-endian machines. In practice, however, byte ordering becomes fixed once a
particular operating system is chosen.
For example, ARM microprocessors, used
in many cell phones, have hardware that can operate in either little- or big-endian
mode, but the two most common operating systems for these chips—Android
(from Google) and IOS (from Apple)—operate only in little-endian mode.
People get surprisingly emotional about which byte ordering is the proper one.
In fact, the terms “little endian” and “big endian” come from the book Gulliver’s
Travels by Jonathan Swift, where two warring factions could not agree as to how a
soft-boiled egg should be opened—by the little end or by the big. Just like the egg
issue, there is no technological reason to choose one byte ordering convention over
the other, and hence the arguments degenerate into bickering about sociopolitical
issues. As long as one of the conventions is selected and adhered to consistently,
the choice is arbitrary

Different machine types
use different and incompatible instructions and encodings. Even identical proces-
sors running different operating systems have differences in their coding conven-
tions and hence are not binary compatible. Binary code is seldom portable across
different combinations of machine and operating system.
A fundamental concept of computer systems is that a program, from the
perspective of the machine, is simply a sequence of bytes. The machine has no
information about the original source program, except perhaps some auxiliary
tables maintained to aid in debugging.

### Introduction to Boolean algebra
