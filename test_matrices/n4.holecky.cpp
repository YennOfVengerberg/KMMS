#include <vector>
#include <cmath>
#include <iostream>
using namespace std; 

void holecky(vector<vector<double>> &matrix) {
    int size = matrix.size();
    for(int i = 0; i < size; i++) {
        double sum = 0.0;
        for(int k = 0; k < i; k++) {
            sum += matrix[i][k] * matrix[i][k];
        }
        double diag = matrix[i][i] - sum;
        matrix[i][i] = sqrt(diag);

        for(int j = i + 1; j < size; j++) {
            sum = 0.0;
            for(int k = 0; k < i; k++) {
                sum += matrix[i][k] * matrix[j][k];
            }
            matrix [i][j] = (matrix[i][j] - sum) / matrix[i][i];
            matrix[j][i] = (matrix[j][i] - sum) / matrix[i][i];
        }
    }
}

int main() {
    //vector<vector<double>> matrix = { {25, 76, 12, 34}, 
    //                                   {15, 75, 23, 52},
    //                                   {52, 52, 18, 0},
    //                                   {35, 5, 6, 7}};
    vector<vector<double>> matrix = { {5, 2, 1 , 2},
                                      {2, 5, 2, 1},
                                      {1, 2, 5, 2},
                                      {2, 1, 2, 5}};
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    holecky(matrix);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}