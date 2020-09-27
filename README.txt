This is a first homebrew BLAS implementation, based on C.
Target implementation:


NAME            DESCRIPTION  
vector(L)       Input: L, list of doubles.
                Returns a Vector defined as {vector, {size, values}}.
                Size is an int, values is a Binary type.

to_list(V)      Input: V, Vector.
                Returns a list, containing the elements of V.

dot(V1, V2)     Input: Vectors.
                Returns the element-wise product between the two numbers.

DOTO:
Select functions required to perform higher level 
vector/matrix multiplication,
matrix/matrix multiplication.

BLAS source:
http://www.netlib.org/blas/

Interesting functions, to implement by thursday:

Level 1
    xSCAL
    xAXPY

Level 2
    xGEMV

Level 3
    xGEMM

CYA, HAVE FUN
