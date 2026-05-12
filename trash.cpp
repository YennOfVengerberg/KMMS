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

void change_speed(int &speed, int dx) {
    speed += dx;
}

class temp {
    private:
        int x;
        int y;
    public:
        void set_coordinates(int x_pos, int y_pos) {
            x = x_pos;
            y = y_pos;
        }

        // void set_coordinates(int x_pos = x, int y_pos = y) {
        //     x = x_pos;
        //     y = y_pos;
        // }

        void show_coordinates() {
            cout << x << " " << y << endl;
        }
};

int main() {
    temp t;
    t.set_coordinates(5, 10);
    t.show_coordinates();
    t.set_coordinates(6, 20);
    t.show_coordinates();
}