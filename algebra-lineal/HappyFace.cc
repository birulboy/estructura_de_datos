#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>

using namespace std;

typedef vector<vector<double>> Matrix;
const double m = numeric_limits<double>::max(); // Representación de infinito

// Imprimir matriz
void printMatrix(const Matrix& mat) {
    for (const auto& row : mat) {
        for (double val : row) {
            if (val == m)
                cout << "∞\t"; // Mostrar infinito de forma clara
            else
                cout << val << "\t";
        }
        cout << endl;
    }
}

// Multiplicación de matrices en el semianillo (min, +)
Matrix multiplyMatrices(const Matrix& A, const Matrix& B) {
    if (A.empty() || B.empty() || A[0].empty() || B[0].empty())
        throw invalid_argument("Las matrices no pueden estar vacías.");

    int rowsA = A.size();
    int colsA = A[0].size();
    int rowsB = B.size();
    int colsB = B[0].size();

    if (colsA != rowsB)
        throw invalid_argument("Dimensiones incompatibles para multiplicación.");

    Matrix C(rowsA, vector<double>(colsB, m));

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                if (A[i][k] != m && B[k][j] != m) {
                    C[i][j] = min(C[i][j], A[i][k] + B[k][j]);
                }
            }
        }
    }

    return C;
}

int main() {
    // Matriz de adyacencia del grafo
    Matrix A = {
        {m, 2, 1, m, 3},
        {m, m, m, 4, m},
        {m, 1, m, m, 1},
        {1, m, 3, m, 5},
        {m, m, m, m, m}
    };

    cout << "Matriz original A:" << endl;
    printMatrix(A);

    Matrix power = A;
    Matrix result = A;

    int maxPower = 4; // Máxima longitud de camino a considerar

    for (int i = 1; i < maxPower; ++i) {
        power = multiplyMatrices(power, A);
        for (int r = 0; r < result.size(); ++r) {
            for (int c = 0; c < result[0].size(); ++c) {
                result[r][c] = min(result[r][c], power[r][c]);
            }
        }
    }

    cout << "\nCaminos mínimos acumulados (hasta longitud " << maxPower << "):" << endl;
    printMatrix(result);

    return 0;
}
