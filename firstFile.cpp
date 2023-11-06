#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void output_array(double interface[][4]);
void generate_rand(int& a, int& b);

int main() {
    srand(time(nullptr));

    //initializing array of zeros
    double interface[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    
    //displaying interface with a 2
    output_array(interface);
    
    return 0;
}

void generate_rand(int& a, int& b){
    //generating random x and y coordinates
    a = rand() % 4;
    b = rand() % 4;
}

void output_array(double interface[][4]){
    //calling generating random# function
    int a;
    int b;
    generate_rand(a, b);
    interface[a][b] = 2;
    for (int i = 0; i<=3; i++){
        for (int j = 0; j<=3; j++){
            printf("%.2f\t", interface[i][j]);
        }
        cout << endl;
    }

}


