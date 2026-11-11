#include <iostream> 
int main() {
    int arr[5] = {3, 6, 5, 9, 10};
    int min = 100000;
    int max = -1;
    for (int i = 0; i < 5; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    for(int a: arr) {
        std::cout << a << " ";
    }
}