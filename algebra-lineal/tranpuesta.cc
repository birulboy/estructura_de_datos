#include <iostream>
#include <vector>

using namespace std;

using Matrix = vector<vector<int>>;

// Transpuesta de una matriz
Matrix transpose(const Matrix &A) {
    int rows = A.size(), cols = A[0].size();
    Matrix T(cols, vector<int>(rows));
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            T[j][i] = A[i][j];
    return T;
}

// Multiplicación estándar (entera) de matrices
Matrix multiply(const Matrix &A, const Matrix &B) {
    int n = A.size(), m = B[0].size(), p = B.size();
    Matrix R(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < p; ++k)
                R[i][j] += A[i][k] * B[k][j];
    return R;
}

// Imprimir matriz
void print_matrix(const Matrix &M, const string &label) {
    cout << "\nMatriz " << label << ":\n";
    for (const auto& row : M) {
        for (int val : row)
            cout << val << " ";
        cout << endl;
    }
}

int main() {
    // Ejemplo
    Matrix A = {
        {0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 0},
        {0, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0}
    };

    Matrix B = {
        {0},
        {0},
        {0},
        {1},
        {0},
        {0}
    };

    Matrix T = transpose(A);
    Matrix TB = multiply(T, B);

    print_matrix(A, "A");
    print_matrix(T, "A Transpuesta");
    print_matrix(B, "B");
    print_matrix(TB, "T * B");
    
    return 0;
}
