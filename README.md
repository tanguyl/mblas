### BLAS implementation for Erlang, targeted for the GRISP platform.

The goal is to obtain large Matrix*Matrix operations, coded in erlang,
and relying on NIF Vector*Vector operations.
The Erlang/NIF interactions shold allow other processus to execute while
the matrices computations are running.

##Early stage: experimentations, nothing really usable now!

##Current API

NAME            DESCRIPTION  
vector(L)       Input: L, list of doubles.
                Returns a Vector defined as {vector, {size, values}}.
                Size is an int, values is a Binary type.

to_list(V)      Input: V, Vector.
                Returns a list, containing the elements of V.

dot(V1, V2)     Input: Vectors.
                Returns the element-wise product between the two numbers.



##Roadmap
The following functions are expected to be done by 01/10/2020:

Level 1
    xSCAL
    xAXPY

Level 2
    xGEMV

Level 3
    xGEMM

For reference,
http://www.netlib.org/blas/
