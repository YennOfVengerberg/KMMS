#include <vector> 
#include <iostream>

using namespace std;

void doolittle(vector<vector<double>> &matrix, int rows, int columns) {
    for(int i = 0; i < rows; i++) {
        for(int j = i; j < columns; j++) {
            double sum = 0.0;
            for(int k = 0; k < i; k++) {
                sum += matrix[i][k] * matrix[k][j];

            }
            matrix[i][j] = matrix[i][j] - sum;

        }
        for(int j = i+1; j < rows; j++) {
            double sum = 0.0;
            for(int k = 0; k < i; k++) {
                sum += matrix[j][k] * matrix[k][i];
            }
            matrix[j][i] = (matrix[j][i] - sum) / matrix[i][i];
        }
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++)
                cout << matrix[i][j] << " ";
            cout << endl;
        }
        cout << i << endl;
    }
}

int main() {
    //vector<vector<double>> matrix = { {25, 76, 12, 34}, 
    //                                   {15, 75, 23, 52},
    //                                   {52, 52, 18, 0},
    //                                   {35, 5, 6, 7}};
    vector<vector<double>> matrix = { {1, 1, 1, 0},
                                      {13, 12, 11, 10},
                                      {7, 3, 2, 11},
                                      {1, 2, 3, 4}};
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    doolittle(matrix, 4, 4);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}