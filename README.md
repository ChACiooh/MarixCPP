# MatrixCPP
Matrix operation for C++

# Installation
```bash
cd Matrix
sudo bash install.sh
make
```

# Usage
See main.cpp
- scalar scaling
- instantiate with constants
- instantiate with vector of vector
- matrix addition
- matrix subtraction
- unary operation (-)
- matrix multiplication
- transpose
- get column space
```c++
A:
1 2 3 
3 4 5 
B:
2 4 6 
6 8 10 
A - B:
-1 -2 -3 
-3 -4 -5 
A + B
3 6 9 
9 12 15 
C:
1 2 
3 4 
5 6 
D = A * C:
22 28 
40 52 
scaling:
2.2 4.4 6.6 
6.6 8.8 11 
Transpose:
2.2 6.6 
4.4 8.8 
6.6 11
```
