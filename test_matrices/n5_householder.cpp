#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void householder(
    vector<vector<double>> &right_matrix, 
    vector<vector<double>> &holder_matrix,
    int rows, int columns) {
    int iter_count = min(rows, columns);
    for(int k = 0; k < iter_count; k++) {
        vector<double> x(rows - k);
        for(int i = k; i < rows; i++) {
            x[i - k] = right_matrix[i][k];
        }

        double norm = 0.0;
        for(double value : x) {
            norm += value * value;
        }
        norm = sqrt(norm);
        if (norm < 1e-5) {
            continue;
        }

        vector<double> u(x.size());
        u[0] = x[0] - norm;
        for(int i = 1; i < u.size(); i++) {
            u[i] = x[i];
        }
        double u_norm = 0.0;
        for(double value : u) {
            u_norm += value * value;
        }
        if(u_norm < 1e-5) {
            continue;
        }
        double beta = 2.0 / u_norm;

        for(int i = 0; i < rows; i++) {
            double elem_summ = 0.0;
            for(int j = k; j < rows; j++) {
                elem_summ += holder_matrix[i][j] * u[j - k];
            }
            double factor = beta * elem_summ;
            for(int j = k; j < rows; j++) {
                holder_matrix[i][j] -= factor * u[j - k];
            }
        }
        for(int j = k; j < columns; j++) {
            double elem_summ = 0.0;
            for(int i = k; i < rows; i++) {
                elem_summ += u[i - k] * right_matrix[i][j];
            }
            double factor = beta * elem_summ;
            for(int i = k; i < rows; i++) {
                right_matrix[i][j] -= factor * u[i - k];
            }
        }
    }
}

vector<vector<double>> multiplyMatrix(
    const vector<vector<double>> &a,
    const vector<vector<double>> &b,
    int rows,
    int common,
    int columns) {
    vector<vector<double>> result(rows, vector<double>(columns, 0.0));
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            for(int k = 0; k < common; ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

bool equalMatrix(
    const vector<vector<double>> &a,
    const vector<vector<double>> &b,
    int rows,
    int columns,
    double eps = 1e-6) {
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            if(fabs(a[i][j] - b[i][j]) > eps) {
                return false;
            }
        }
    }
    return true;
}

void printMatrix(const vector<vector<double>> &m, int rows, int columns) {
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<double>> A = {
        {4, 1, 2, 0},
        {3, 4, 1, 1},
        {0, 2, 3, 4},
        {1, 0, 0, 2}
    };
    int rows = (int)A.size();
    int cols = (int)A[0].size();

    vector<vector<double>> originalA = A;
    vector<vector<double>> Q(rows, vector<double>(rows, 0.0));
    for(int i = 0; i < rows; ++i) Q[i][i] = 1.0;

    cout << "A (original):" << endl;
    printMatrix(A, rows, cols);
    cout << endl;

    householder(A, Q, rows, cols);

    cout << "R (after Householder, stored in right_matrix):" << endl;
    printMatrix(A, rows, cols);
    cout << endl;

    cout << "Q (accumulated Householder transformations):" << endl;
    printMatrix(Q, rows, rows);
    cout << endl;

    vector<vector<double>> QR = multiplyMatrix(Q, A, rows, rows, cols);
    cout << "Q * R:" << endl;
    printMatrix(QR, rows, cols);
    cout << endl;

    cout << "Q * R equals original A? ";
    cout << (equalMatrix(QR, originalA, rows, cols) ? "yes" : "no") << endl;
    cout << endl;

    return 0;
}