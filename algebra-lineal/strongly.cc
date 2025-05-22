#include <iostream>
#include <vector>

using namespace std;

const int N = 8; // Tamaño máximo del grafo

using Matrix = vector<vector<bool>>;

Matrix identity(int n) {
    Matrix I(n, vector<bool>(n, false));// Inicializamos la matriz identidad
    for (int i = 0; i < n; ++i) I[i][i] = true; //Ponemos la diagonal principal a true
    return I;
}

Matrix boolean_or(const Matrix &A, const Matrix &B) {
    int n = A.size(); // Tamaño de la matriz
    Matrix R(n, vector<bool>(n));// Inicializamos la matriz resultado
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) 
            R[i][j] = A[i][j] || B[i][j]; // Recorremos la matriz y hacemos la suma booleana
    return R;
}

Matrix boolean_and(const Matrix &A, const Matrix &B) {
    int n = A.size(); // Tamaño de la matriz
    Matrix R(n, vector<bool>(n)); // Inicializamos la matriz resultado
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            R[i][j] = A[i][j] && B[i][j]; // Recorremos la matriz y hacemos la multiplicación booleana
    return R;
}

Matrix transpose(const Matrix &A) {
int n = A.size(); // Tamaño de la matriz
    Matrix T(n, vector<bool>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            T[j][i] = A[i][j]; // Asignamos el valor de la matriz original ( invertida ) a la transpuesta
    return T;
}

Matrix boolean_multiply(const Matrix &A, const Matrix &B) {
    int n = A.size(); // Tamaño de la matriz
    Matrix R(n, vector<bool>(n, false)); // Inicializamos la matriz resultado
    for (int i = 0; i < n; ++i) // Recorremos filas de A
        for (int j = 0; j < n; ++j) // Recorremos columnas de B
            for (int k = 0; k < n; ++k) // K es el índice de la multiplicación
                R[i][j] = R[i][j] || (A[i][k] && B[k][j]); // El operador || acumula el resultado para R[i][j], sumando lógicamente (OR) cada producto A[i][k] && B[k][j] en la multiplicación booleana.

    return R;
}

// C = I ∨ A ∨ A^2 ∨ ... ∨ A^(n-1)
Matrix compute_reachability(const Matrix &A) {
    int n = A.size(); // Tamaño de la matriz
    Matrix C = identity(n); // Inicializamos la matriz de conectividad
    Matrix P = A; // Inicializamos la matriz de potencia
    for (int i = 0; i < n; ++i) { // Hacemos el ciclo el numero de filas ( nodos ) en la matriz A
        C = boolean_or(C, P); // C = I ∨ A ∨ A^2 ∨ ... ∨ A^(i-1)
        P = boolean_multiply(P, A); // P = A^i 
    }
    return C;
}

void print_components(const Matrix &SCC) {
    int n = SCC.size(); // Tamaño de la matriz
    vector<bool> visited(n, false);// Inicializamos el vector de visitados
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) { // Si no ha sido visitado
            cout << "Componente: ";
            for (int j = 0; j < n; ++j) {
                if (SCC[i][j]) { // Si hay una conexión entre i y j
                    cout << j << " "; // Imprimimos el nodo
                    visited[j] = true; // Marcamos como visitado
                }
            }
            cout << endl;
        }
    }
}

void print_matrix(const Matrix &M, const string &name) {
    cout << "\nMatriz " << name << ":\n";
    for (const auto& row : M) { // Recorremos cada fila
        for (bool val : row) // Recorremos cada valor de la fila
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
