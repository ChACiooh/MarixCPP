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
    printf("D:\n");
    d.PrintMatrix();

    vector<int> col = c.col(1);
    for (auto e : col) {
        printf("%d ", e);
    }
    printf("\n");
    return 0;
}