#include <iostream>
#include <vector>

using namespace std;

const int N = 8; // Tamaño máximo del grafo

using Matrix = vector<vector<bool>>;

Matrix identity(int n) {
    Matrix I(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i) I[i][i] = true;
    return I;
}

Matrix boolean_or(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix R(n, vector<bool>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            R[i][j] = A[i][j] || B[i][j];
    return R;
}

Matrix boolean_and(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix R(n, vector<bool>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            R[i][j] = A[i][j] && B[i][j];
    return R;
}

Matrix transpose(const Matrix &A) {
    int n = A.size();
    Matrix T(n, vector<bool>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            T[j][i] = A[i][j];
    return T;
}

Matrix boolean_multiply(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix R(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                R[i][j] = R[i][j] || (A[i][k] && B[k][j]);
    return R;
}

// C = I ∨ A ∨ A^2 ∨ ... ∨ A^(n-1)
Matrix compute_reachability(const Matrix &A) {
    int n = A.size();
    Matrix C = identity(n);
    Matrix P = A;
    for (int i = 0; i < n; ++i) {
        C = boolean_or(C, P);
        P = boolean_multiply(P, A); // P = A^i
    }
    return C;
}

void print_components(const Matrix &SCC) {
    int n = SCC.size();
    vector<bool> visited(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            cout << "Componente: ";
            for (int j = 0; j < n; ++j) {
                if (SCC[i][j]) {
                    cout << j << " ";
                    visited[j] = true;
                }
            }
            cout << endl;
        }
    }
}

void print_matrix(const Matrix &M, const string &name) {
    cout << "\nMatriz " << name << ":\n";
    for (const auto& row : M) {
        for (bool val : row)
            cout << val << " ";
        cout << endl;
    }
}

int main() {
    // Ejemplo: grafo dirigido con 6 nodos
   Matrix A = {
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 1, 1, 0, 0},
    {0, 0, 0, 1, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 1}
};


    Matrix C = compute_reachability(A);
    Matrix Ct = transpose(C);
    Matrix SCC = boolean_and(C, Ct); // SCC = C ∧ Cᵗ
    print_matrix(SCC, "SCC (Componentes Fuertemente Conexas)");

    print_components(SCC);


    return 0;
}
