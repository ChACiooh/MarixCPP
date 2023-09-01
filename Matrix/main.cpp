#include "matrix.h"
#include <cstdio>

using namespace std;

int main() {
    Matrix<int> a({{1,2,3},
                   {3,4,5}});
    Matrix<int> b = 2 * a;

    printf("A:\n");
    a.PrintMatrix();
    printf("B:\n");
    b.PrintMatrix();

    Matrix<int> c = Matrix<int>({{1, 2},
                                 {3, 4},
                                 {5, 6}});

    printf("C:\n");
    c.PrintMatrix();

    Matrix<int> d = a * c;
    printf("D = A * C:\n");
    d.PrintMatrix();

    printf("scaling:\n");
    Matrix<double> e = 2.2 * Matrix<double>(a);
    e.PrintMatrix();

    printf("Transpose:\n");
    Matrix<double> f = e.Transpose();
    f.PrintMatrix();

    printf("(2, 1) elem:\n");
    printf("%lf\n", f[1][0]);
    return 0;
}