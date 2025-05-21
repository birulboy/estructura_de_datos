#include <vector>
#include <iostream>
#include <iomanip>
#include <limits>
#include <random>
using namespace std;

class Graph
{
private:
    vector<vector<int>> adj_matrix;

public:
    Graph(int n) : adj_matrix(n, vector<int>(n, -1)) {}

    void add_edge(int u, int v, int weight)
    {
        if (u == v || adj_matrix[u][v] != -1)
            return;
        adj_matrix[u][v] = weight;
    }

    void print()
    {
        cout << "Matriz de adyacencia ponderada:\n";
        int n = adj_matrix.size();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (adj_matrix[i][j] == -1)
                    cout << setw(4) << ".";
                else
                    cout << setw(4) << adj_matrix[i][j];
            }
            cout << endl;
        }
    }

    void transponer()
    {
        int n = adj_matrix.size();
        vector<vector<int>> transpuesta(n, vector<int>(n, -1));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                transpuesta[j][i] = adj_matrix[i][j];
            }
        }

        adj_matrix = transpuesta;
    }

    vector<int> producto(const vector<int> &v)
    {
        int n = adj_matrix.size();
        vector<int> res(n, 0);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (adj_matrix[i][j] != -1)
                    res[j] += adj_matrix[i][j] * v[i];
            }
        }

        return res;
    }
};

int main()
{
    int n = 5;
    Graph g(n);

    g.add_edge(0, 1, 1);
    g.add_edge(0, 2, 1);
    g.add_edge(1, 3, 1);
    g.add_edge(2, 3, 1);
    g.add_edge(3, 4, 1);

    g.print();
    int target = 4;
    g.transponer();
    cout << "Matriz Transpuesta: \n";
    g.print();
    vector<int> v(n, 0);
    v[target] = 1;

    vector<int> resultado = g.producto(v);

    for (int i = 0; i < n; i++)
    {
        if (resultado[i] != 0)
        {
            cout << "Nodo " << i << " apunta a " << target << endl;
        }
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> r_nums(0, 100);
    vector<int> producto_punto(10);

    for (int i = 0; i < producto_punto.size(); i++)
    {
        producto_punto.at(i) = r_nums(gen);
    }

    for (int i = 0; i < producto_punto.size(); i++)
    {
        cout << producto_punto.at(i) << " ";
    }

    cout << endl;

    int escalar = 2;
    vector<int> result(producto_punto.size());
    for (int i = 0; i < producto_punto.size(); i++)
    {
        result[i] = producto_punto[i] * escalar;
    }

    producto_punto = result;

    for (int i = 0; i < producto_punto.size(); i++)
    {
        cout << producto_punto.at(i) << " ";
    }

    cout << endl;
}
