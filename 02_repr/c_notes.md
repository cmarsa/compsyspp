# Notes on C-language

## `typedef`
The `typedef` declaration in C provides a way of giving a name to a data type.
This can be a great help in improving code readability, since deeply nested type
declarations can be difficult to decipher.
The syntax for typedef is exactly like that of declaring a variable, except that it uses a type name
rather than a variable name. Thus, the declaration of `byte_pointer` has the same form as
the declaration of a variable of type `unsigned char *`.
For example, the declaration
```
typedef int *int_pointer;
int_pointer ip;
```
defines type int_pointer to be a pointer to an int, and declares a variable ip of this type.
Alternatively,
we could declare this variable directly as
```
int *ip;
```