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
the number 0x7AF, we compute its decimal equivalent as
`7 * 16 2 + 10 * 16 + 15 = 7 * 256 + 10 * 16 + 15 = 1,792 + 160 + 15 = 1,967.`

## Data Sizes
