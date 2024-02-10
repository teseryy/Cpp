The task is to create a calculator for working with matrices. Separate matrices and results of operations can be stored in variables and these variables can be used in further calculations.

The calculator implements the following functionalities:

    1.Work with matrices of any size (loading and enumeration of variables).

    2.Basic operations: addition, subtraction, multiplication and transpose.

    3.Merging and trimming of matrices.

    4.Computation of inverse matrix for square matrices.

    5.Functions for calculating determinant, determining rank and performing Gauss elimination method.

    6.The state of the calculator (i.e. its variables) can be saved in a text file. It is also possible to restore this state from the file.

    7.Storing in variables (and in a file) saves memory. When a variable is stored in memory, the type of matrix is determined. The calculator distinguishes between sparse matrices and 
      dense matrices.

The application handles expressions in postfix notation, such as A = B C ADD.

The following commands are used to work with the calculator :
<filename> IMPORT - imports a matrix (or list of expressions) from the <filename> file, 
<Matrix> SCAN - inputs a <Matrix> matrix from the user, 
<PName> = <list of operations (or matrix value)> - writes the result of operations to a variable, 
<fMatrix> <sMatrix> ADD - returns the result of adding two matrices <fMatrix> and <sMatrix>, 
<fMatrix> <sMatrix> SUB - returns the result of the difference of two matrices <fMatrix> and <sMatrix>, 
<fMatrix> <sMatrix> MULM - returns the result of the product of <fMatrix> and <sMatrix>,
<fMatrix> <number(or numeric variable)> MULN - returns the result of the product of <fMatrix> and <number>,
<fMatrix> TRANSP - returns the transposed matrix <fMatrix>, 
<fMatrix> <sMatrix> ROWS(COLS) CONC - combines matrices <fMatrix> and <sMatrix> by rows (columns), 
<Matrix> (<startRow>, <endRow>, <startColumn>, <endColumn>) SLICE - trims the <Matrix> matrix to the specified parameters, 
<Matrix> INVERSE - returns the inverse matrix for a square matrix <Matrix>, 
<Matrix> DET - returns the determinant of the <Matrix> matrix, 
<Matrix> RANK - returns the rank of the matrix <Matrix>, 
<Matrix> GAUSS - returns the matrix <Matrix> written in upper triangular form, 
<Matrix> PRINT - outputs the <Matrix> matrix to the console, 
<filename> EXPORT - writes variables to the <filename> file. 

Example of using the CONC command:
A = B C ROWS CONC //- (3x3 and 3x3 -> 6x3) 
X = Y Z COLS CONC //- (3x3 and 3x3 -> 3x6)

A variable name can only be a string starting with a letter. The string can contain characters such as letters, numbers and '_'.

The format of the input matrix must be strictly as follows [[num1, num2, ...], [num3, num4, ...], ...], where "num" is a number of double(integer) type and "..." represents a sequence of numbers (strings). 
sequence of numbers (strings). 

Each input string represents a sequence of operations to be performed, the result of these operations is stored in a temporary stack, which is cleared after the string is processed, unless the result is stored in a variable using the "=" operation. If such a variable already exists, it will be overwritten. 

Inputs must be executed exactly as described above. Otherwise, the command will not be processed and an error message will be displayed to the user.

If the file is not in the same folder as the executable, the path must be specified when importing.

Running the program may look as follows:
memory IMPORT
X = [[1, 7], [3, 2]]  DET 
Y SCAN 
// input from user ...
Z = Y [[1, 0], [0, 1]] ADD X MUL
A = Z GAUSS
A PRINT
EXPORT memory

Polymorphism is mainly used to store matrices efficiently. Two types of matrices (sparse and dense) are used, for which some algorithms are 
are implemented differently. Polymorphism is also used to represent matrix operations using the Command design pattern.
