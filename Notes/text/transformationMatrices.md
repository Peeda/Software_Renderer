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

# Translation Matrices
* To translate a Vector3 we need the fourth column of the matrix

$$
\begin{bmatrix}
1 & 0 & 0 & tx\cr
0 & 1 & 0 & ty\cr
0 & 0 & 1 & tz\cr
0 & 0 & 0 & 1 \cr
\end{bmatrix}
\begin{bmatrix}
x \cr
y \cr
z \cr
1 \cr
\end{bmatrix}
$$
* Because the fourth entry of the vector will be one,
this will add the three translations to x y and z
* The diagonal ones function similarly to the identity matrix, maintaining the values of x y and z
# Rotation Matrices
* To rotate about an axis, the vector component for that axis remains locked
* In two dimensions a rotation matrix looks like
$$
\begin{bmatrix}
\cos(\alpha) & -\sin(\alpha) \cr
\sin(\alpha) & \cos(\alpha) \cr
\end{bmatrix}
$$
* This makes a lot of sense when we interpret matrices as encoding the new, transformed locations of the basis vectors
* Reading the matrix this way, the first column states that after rotating by alpha, i hat lands at cos(alpha) in x, and sin(alpha) in y
    * Kinda like the unit circle
* And j hat lands at -sin(alpha) in x, and cos(alpha) in y
* Which follows from the fact that the two should be perpendicular