#include <iostream>
using namespace std;

int main() {
    int *a = new int[2];
    a[0] = 2;
    a[1] = 4;
    a = new int[4];
    a[2] = 8;
    a[3] = 10;
    cout << a[0] << a[1] << a[2] << a[3];
}