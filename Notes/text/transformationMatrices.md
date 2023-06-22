# Transformation Matrices
* It's more efficient to write transformation matrices rather than functions 
that take in and output vectors
* This way matrix multiplication can be used to generate matrices that 
represent the composition of multiple transformations
* 4 by 4 matrices are used for transformations of 3d vectors, the vector is
treated as having a fourth component to make matrix multiplication possible
* This is necessary to include information about translation

# Scaling Matrices
* To scale a given vector, the matrix will be of the form
$$
\begin{bmatrix}
sx & 0  & 0  & 0\cr
0  & sy & 0  & 0\cr
0  & 0  & sz & 0\cr
0  & 0  & 0  & 0\cr
\end{bmatrix}
\begin{bmatrix}
x \cr
y \cr
z \cr
1 \cr
\end{bmatrix}
$$
* This makes sense when we think of matrix multiplication as encoding information
about transformations, where each column in the left matrix represents the new
location of a basis vector
    * In this sense the matrix is essentially stating that i hat is replaced
    with some scale of i hat, and the same for the other basis vectors
