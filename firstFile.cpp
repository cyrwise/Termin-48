#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void output_array(double interface[][4]);
void generate_rand(int& a, int& b);

int main() {
    bool isGameActive = true; // Could potentially use this to declare whether the game is active or not. For example if the player has lost yet or not

    srand(time(nullptr));

    //initializing array of zeros
    double interface[4][4] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
    };

    //displaying interface with a 2
    output_array(interface);

    int turns = 0; // TEMPORARY VARIABLE JUST TO MAKE THE PROGRAM STOP ASKING FOR A DIRECTION AFTER 3 OCCURANCES
    // temporary solution for the player to move in a certain direction
    do {
        char direction;
        cout << "Direction (W, A, S, D): ";
        cin >> direction;

        // these cout statements can be replaced with other things such as running a funciton that actually executes moves
        switch(tolower(direction)) {
        case 'w':
            cout << "up" << endl;
            break;
        case 'a':
            cout << "left" << endl;
            break;
        case 's':
            cout << "down" << endl;
            break;
        case 'd':
            cout << "right" << endl;
            break;
        // if the user inputs an invalid direction / does not input a character
        default:
            cout << "please choose a valid direction" << endl;
            break;
        }
        turns++;
        if(turns >= 3) {
            isGameActive = false;
        }
    }
    while(isGameActive == true);

    return 0;
}

void generate_rand(int& a, int& b){
    //generating random x and y coordinates
    a = rand() % 4;
    b = rand() % 4;
}

void output_array(double interface[][4]){
    //calling generating-random#-function
    int a;
    int b;
    generate_rand(a, b);

    //assigning generated random coordanates with 2
    interface[a][b] = 2;

    //printing score
    int score;
    for (int i = 0; i<=3; i++){
        for (int j = 0; j<=3; j++){
            score = score + interface[i][j];
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
    
    //displaying interface
    for (int i = 0; i<=3; i++){
        for (int j = 0; j<=3; j++){
            printf("%.f\t", interface[i][j]);
        }
        cout << endl;
    }


}


