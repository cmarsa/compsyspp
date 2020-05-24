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