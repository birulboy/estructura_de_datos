#include <iostream>
#include <vector>

using namespace std;

using Matrix = vector<vector<int>>;

// Transpuesta de una matriz
Matrix transpose(const Matrix &A) {
    int rows = A.size(), cols = A[0].size(); // Sacamos filas y columnas ( Asumimos que todas las filas tienen la misma longitud )
    Matrix T(cols, vector<int>(rows)); // Inicializamos la matriz transpuesta
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            T[j][i] = A[i][j]; // Asignamos el valor de la matriz original ( invertida ) a la transpuesta
    return T;
}

// Multiplicación estándar (int) de matrices
Matrix multiply(const Matrix &A, const Matrix &B) {
    int n = A.size(), m = B[0].size(), p = B.size(); // Sacamos filas y columnas de A y B
    Matrix R(n, vector<int>(m, 0)); // Inicializamos la matriz resultado
    for (int i = 0; i < n; ++i) // Recorremos filas de A
        for (int j = 0; j < m; ++j)// Recorremos columnas de B
            for (int k = 0; k < p; ++k) // Recorremos las filas de B
                R[i][j] += A[i][k] * B[k][j]; // Multiplicamos la fila i de A por la columna j de B
    return R;
}

// Imprimir matriz
void print_matrix(const Matrix &M, const string &label) {
    cout << "\nMatriz " << label << ":\n";
    for (const auto& row : M) { // Recorremos cada fila
        for (int val : row) // Recorremos cada valor de la fila
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
