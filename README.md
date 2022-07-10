# Project 2 - Matrix Processing Library C++

This project is a tool to perform matrix operations (i.e adding, subtracting, multiplication, and transpose) based on a given input matrix. 


## To build using clang++ and makefile in this project:

run the following command in the terminal: 

```sh
make run
```
then to run the program:
```sh
./main
```

This project could be further developed into a matrix image processing library. All images can be represented as a matrix of single-byte values, where a pixel at matrix location (i, j) is represented by a number between 0 and 255. A color image consists of three channels: a red channel (R), a green channel (G), and a blue channel (B), and the corresponding matrix for an image includes three matrices, each with the same number of rows (height) and columns (width), one for each of the three channels. Together, these are passed to an image-writing library for outputting to a file and displaying.
