#include <vector>
#include <iostream>

using namespace std;

void gepp(vector<vector<double>> &matrix, int rows, int columns) {
    for(int k = 0; k < rows - 1; k++) {
        int max_row = k;
        double max_val = std::abs(matrix[k][k]);
        for(int i = k + 1; i < rows; i++) {
            if(std::abs(matrix[i][k]) > max_val) {
                max_val = std::abs(matrix[i][k]);
                max_row = i;
            }
        }

        if(max_row != k) {
            for(int j = 0; j < columns; j++) {
                double temp = matrix[k][j];
                matrix[k][j] = matrix[max_row][j];
                matrix[max_row][j] = temp;
            }
        }

        for(int i = k + 1; i < rows; i++) {
            matrix[i][k] = matrix[i][k] / matrix[k][k];
        }
        for(int i = k + 1; i < rows; i++) {
            for(int j = k + 1; j < columns; j++) {
                matrix[i][j] -= matrix[i][k] * matrix[k][j];
            }
        }

    }
}

int main() {
    vector<vector<double>> matrix = { 
        {25, 76, 12, 34, 0}, 
        {15, 75, 23, 52, 1}, 
        {52, 52, 18, 0, 4}, 
        {35, 5, 6, 7, 2}};
    //vector<vector<double>> matrix = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 5; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    gepp(matrix, 4, 5);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 5; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }


}