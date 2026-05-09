#include <iostream>
using namespace std;

int *fuc(int * &obj_arr, int &obj_number) {
    obj_number++;
    static int *temp_arr = new int[obj_number];
    for(int i = 0; i < obj_number-1; i++) {
        temp_arr[i] = obj_arr[i];
    }
    delete[] obj_arr;
    obj_arr = temp_arr;
    return &obj_arr[obj_number-1];
}

int main() {
    int num = 2;
    int *a = new int[num];
    a[0] = 2;
    a[1] = 4;
    fuc(a, num);
    //a[2] = 7;
    cout << a[0] << a[1] << a[2] << a[3];
}