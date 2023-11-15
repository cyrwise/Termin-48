#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void output_array(); // generate a new integer at a random position - print board
void generate_rand(int& a, int& b); // generate random coordinates for new integer
void userInput(); // takes user input 
void moveUp();
void moveLeft();
void moveDown();
void moveRight();
void turnDone(); // counts the score on the board and calls output_array()

#define UWHT "\e[4;37m" // white underline
#define RESET "\e[0;39m" // reset font changes
#define BWHT "\e[1;37m" // white bold
#define BLKB "\e[40m" // black highlight
#define YELB "\e[43m" // yellow highlight



bool isGameActive = true; // Could potentially use this to declare whether the game is active or not. For example if the player has lost yet or not
double positions[16]; // just making this a global variable
double interface[4][4] = { //initializing array of zeros
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
    };
int score = 2;

void generate_rand(int& a, int& b) {
    a = rand() % 4;
    b = rand() % 4;
}

void output_array() {
    int a;
    int b;
    generate_rand(a, b);

    if (interface[a][b] == 0) { // if spot is vacant, place the new number, if not, generate a different spot and restart function
        interface[a][b] = 2; //assigning generated random coordanates with 2
        for (int i = 0; i < 4; i++) { //display interface
            for (int j = 0; j < 4; j++) {
                if (interface[i][j] != 0) {
                    printf(YELB"%.f\t", interface[i][j]); // make numbers that aren't 0 highlight yellow
                    printf(RESET);
                }
                else {
                    printf(BLKB"%.f\t", interface[i][j]); // otherwise highlight black
                    printf(RESET);
                }
            }
            printf("\n");
        }
    }
    else {
        output_array();
    }

}



void userInput() {
    int turns = 0; // TEMPORARY VARIABLE JUST TO MAKE THE PROGRAM STOP ASKING FOR A DIRECTION AFTER 5 OCCURANCES

    do { // temporary solution for the player to move in a certain direction
        char direction;
        cout << UWHT"Direction (W, A, S, D): ";
        cin >> direction;
        cout << RESET;
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); // just makes it so that the board is more visible, less messy from turn to turn

        // these cout statements can be replaced with other things such as running a funciton that actually executes moves
        switch(tolower(direction)) {
        case 'w':
            moveUp();
            break;
        case 'a':
           moveLeft();
            break;
        case 's':
            moveDown();
            break;
        case 'd':
            moveRight();
            break;
        // if the user inputs an invalid direction / does not input a character
        default:
            printf("please choose a valid direction\n");
            break;
        }
        turns++;
        if(turns >= 10) {
            isGameActive = false;
        }
    }
    while(isGameActive == true);

}

void moveUp() { 
    // key:
    // a, b, c, d = numbers/positions that haven't been checked yet
    // *  = any number that would happen to be in that position
    // 0 = self-explanatory
    // if 0 0 0 *, do nothing
    // if 0 0 * *, do nothing
    // if 0 * * *, do nothing
    // if * * * *, do nothing

    for (int i = 0; i < 4; i++) { // do this for 4 rows
        if (interface[0][i] == 0) { // if a b c 0
            if (interface[1][i] == 0) { // if a b 0 0 
                if (interface[2][i] == 0) { // if a 0 0 0
                    swap(interface[3][i], interface[0][i]); // case: * 0 0 0 
                }
                else { // if a * 0 0
                    if (interface[3][i] == 0) { // if 0 * 0 0
                        swap(interface[2][i], interface[0][i]); // case: 0 * 0 0
                    }
                    else { // if * * 0 0
                        swap(interface[2][i], interface[0][i]);
                        swap(interface[3][i], interface[1][i]);
                    }
                }
            }
            else { // if a b * 0
                if (interface[2][i] == 0) { // if a 0 * 0
                    if (interface[3][i] == 0) { // if 0 0 * 0
                        swap(interface[1][i], interface[0][i]); // case: 0 0 * 0
                    }
                    else { // if * 0 * 0
                        swap(interface[2][i], interface[0][i]);
                        swap(interface[3][i], interface[1][i]); // case * 0 * 0
                    }
                }
                else { // if a * * 0
                    if (interface[0][i] == 0) { // if 0 * * 0
                        swap(interface[1][i], interface[0][i]);
                        swap(interface[2][i], interface[1][i]); // case: 0 * * 0
                    }
                    else { // if * * * 0
                        swap(interface[1][i], interface[0][i]);
                        swap(interface[2][i], interface[1][i]);
                        swap(interface[3][i], interface[2][i]); // case: * * * 0
                    }
                }
            }
        }
        else {
            if (interface[1][i] == 0) { // if a b 0 *
                if (interface[2][i] == 0) { // if a 0 0 *
                    if (interface[3][i] != 0) { // if NOT 0 0 0 * 
                        swap(interface[3][i], interface[1][i]); // case: * 0 0 * 
                    }
                }
                else {
                    if (interface[3][i] == 0) { // if 0 * 0 *
                        swap(interface[2][i], interface[1][i]); // case: 0 * 0 *
                    }
                    else { 
                        if (interface[3][i] != 0) { // if 2 2 0 2
                            swap(interface[2][i], interface[1][i]); 
                            swap(interface[3][i], interface[2][i]); // case: * * 0 *
                        }
                    }
                }
            }
            else {
                if (interface[2][i] == 0) { // a 0 * *
                    if (interface[3][i] != 0) { // if NOT 0 0 * *
                        swap(interface[3][i], interface[2][i]); // case: * 0 * *
                    }
                }
            }
        }
    } 

    output_array(); // calls function to generate a new random integer and place it on the board - also reprints board
    turnDone();
}

void moveLeft() { 
    // key:
    // a, b, c, d = numbers/positions that haven't been checked yet
    // *  = any number that would happen to be in that position
    // 0 = self-explanatory
    // if 0 0 0 *, do nothing
    // if 0 0 * *, do nothing
    // if 0 * * *, do nothing
    // if * * * *, do nothing

    for (int i = 0; i < 4; i++) { // do this for 4 rows
        if (interface[i][0] == 0) { // if a b c 0
            if (interface[i][1] == 0) { // if a b 0 0 
                if (interface[i][2] == 0) { // if a 0 0 0
                    swap(interface[i][3], interface[i][0]); // case: * 0 0 0 
                }
                else { // if a * 0 0
                    if (interface[i][3] == 0) { // if 0 * 0 0
                        swap(interface[i][2], interface[i][0]); // case: 0 * 0 0
                    }
                    else { // if * * 0 0
                        swap(interface[i][2], interface[i][0]);
                        swap(interface[i][3], interface[i][1]);
                    }
                }
            }
            else { // if a b * 0
                if (interface[i][2] == 0) { // if a 0 * 0
                    if (interface[i][3] == 0) { // if 0 0 * 0
                        swap(interface[i][1], interface[i][0]); // case: 0 0 * 0
                    }
                    else { // if * 0 * 0
                        swap(interface[i][2], interface[i][0]);
                        swap(interface[i][3], interface[i][1]); // case * 0 * 0
                    }
                }
                else { // if a * * 0
                    if (interface[i][0] == 0) { // if 0 * * 0
                        swap(interface[i][1], interface[i][0]);
                        swap(interface[i][2], interface[i][1]); // case: 0 * * 0
                    }
                    else { // if * * * 0
                        swap(interface[i][1], interface[i][0]);
                        swap(interface[i][2], interface[i][1]);
                        swap(interface[i][3], interface[i][2]); // case: * * * 0
                    }
                }
            }
        }
        else {
            if (interface[i][1] == 0) { // if a b 0 *
                if (interface[i][2] == 0) { // if a 0 0 *
                    if (interface[i][3] != 0) { // if NOT 0 0 0 * 
                        swap(interface[i][3], interface[i][1]); // case: * 0 0 * 
                    }
                }
                else {
                    if (interface[i][3] == 0) { // if 0 * 0 *
                        swap(interface[i][2], interface[i][1]); // case: 0 * 0 *
                    }
                    else { 
                        if (interface[i][3] != 0) { // if 2 2 0 2
                            swap(interface[i][2], interface[i][1]); 
                            swap(interface[i][3], interface[i][2]); // case: * * 0 *
                        }
                    }
                }
            }
            else {
                if (interface[i][2] == 0) { // a 0 * *
                    if (interface[i][3] != 0) { // if NOT 0 0 * *
                        swap(interface[i][3], interface[i][2]); // case: * 0 * *
                    }
                }
            }
        }
    } 

    output_array(); // calls function to generate a new random integer and place it on the board - also reprints board
    turnDone();
}

void moveRight() { 
    // key:
    // a, b, c, d = numbers/positions that haven't been checked yet
    // *  = any number that would happen to be in that position
    // 0 = self-explanatory
    // if 0 0 0 *, do nothing
    // if 0 0 * *, do nothing
    // if 0 * * *, do nothing
    // if * * * *, do nothing

    for (int i = 0; i < 4; i++) { // do this for 4 rows
        if (interface[i][3] == 0) { // if a b c 0
            if (interface[i][2] == 0) { // if a b 0 0 
                if (interface[i][1] == 0) { // if a 0 0 0
                    swap(interface[i][0], interface[i][3]); // case: * 0 0 0 
                }
                else { // if a * 0 0
                    if (interface[i][0] == 0) { // if 0 * 0 0
                        swap(interface[i][1], interface[i][3]); // case: 0 * 0 0
                    }
                    else { // if * * 0 0
                        swap(interface[i][1], interface[i][3]);
                        swap(interface[i][0], interface[i][2]);
                    }
                }
            }
            else { // if a b * 0
                if (interface[i][1] == 0) { // if a 0 * 0
                    if (interface[i][0] == 0) { // if 0 0 * 0
                        swap(interface[i][2], interface[i][3]); // case: 0 0 * 0
                    }
                    else { // if * 0 * 0
                        swap(interface[i][1], interface[i][3]);
                        swap(interface[i][0], interface[i][2]); // case * 0 * 0
                    }
                }
                else { // if a * * 0
                    if (interface[i][0] == 0) { // if 0 * * 0
                        swap(interface[i][2], interface[i][3]);
                        swap(interface[i][1], interface[i][2]); // case: 0 * * 0
                    }
                    else { // if * * * 0
                        swap(interface[i][2], interface[i][3]);
                        swap(interface[i][1], interface[i][2]);
                        swap(interface[i][0], interface[i][1]); // case: * * * 0
                    }
                }
            }
        }
        else {
            if (interface[i][2] == 0) { // if a b 0 *
                if (interface[i][1] == 0) { // if a 0 0 *
                    if (interface[i][0] != 0) { // if NOT 0 0 0 * 
                        swap(interface[i][0], interface[i][2]); // case: * 0 0 * 
                    }
                }
                else {
                    if (interface[i][0] == 0) { // if 0 * 0 *
                        swap(interface[i][1], interface[i][2]); // case: 0 * 0 *
                    }
                    else { 
                        if (interface[i][0] != 0) { // if 2 2 0 2
                            swap(interface[i][1], interface[i][2]); 
                            swap(interface[i][0], interface[i][1]); // case: * * 0 *
                        }
                    }
                }
            }
            else {
                if (interface[i][1] == 0) { // a 0 * *
                    if (interface[i][0] != 0) { // if NOT 0 0 * *
                        swap(interface[i][0], interface[i][1]); // case: * 0 * *
                    }
                }
            }
        }
    } 

    output_array(); // calls function to generate a new random integer and place it on the board - also reprints board
    turnDone();
}

void moveDown() { 
    // key:
    // a, b, c, d = numbers/positions that haven't been checked yet
    // *  = any number that would happen to be in that position
    // 0 = self-explanatory
    // if 0 0 0 *, do nothing
    // if 0 0 * *, do nothing
    // if 0 * * *, do nothing
    // if * * * *, do nothing

    for (int i = 0; i < 4; i++) { // do this for 4 rows
        if (interface[3][i] == 0) { // if a b c 0
            if (interface[2][i] == 0) { // if a b 0 0 
                if (interface[1][i] == 0) { // if a 0 0 0
                    swap(interface[0][i], interface[3][i]); // case: * 0 0 0 
                }
                else { // if a * 0 0
                    if (interface[0][i] == 0) { // if 0 * 0 0
                        swap(interface[1][i], interface[3][i]); // case: 0 * 0 0
                    }
                    else { // if * * 0 0
                        swap(interface[1][i], interface[3][i]);
                        swap(interface[0][i], interface[2][i]);
                    }
                }
            }
            else { // if a b * 0
                if (interface[1][i] == 0) { // if a 0 * 0
                    if (interface[0][i] == 0) { // if 0 0 * 0
                        swap(interface[2][i], interface[3][i]); // case: 0 0 * 0
                    }
                    else { // if * 0 * 0
                        swap(interface[1][i], interface[3][i]);
                        swap(interface[0][i], interface[2][i]); // case * 0 * 0
                    }
                }
                else { // if a * * 0
                    if (interface[0][i] == 0) { // if 0 * * 0
                        swap(interface[2][i], interface[3][i]);
                        swap(interface[1][i], interface[2][i]); // case: 0 * * 0
                    }
                    else { // if * * * 0
                        swap(interface[2][i], interface[3][i]);
                        swap(interface[1][i], interface[2][i]);
                        swap(interface[0][i], interface[1][i]); // case: * * * 0
                    }
                }
            }
        }
        else {
            if (interface[2][i] == 0) { // if a b 0 *
                if (interface[1][i] == 0) { // if a 0 0 *
                    if (interface[0][i] != 0) { // if NOT 0 0 0 * 
                        swap(interface[0][i], interface[2][i]); // case: * 0 0 * 
                    }
                }
                else {
                    if (interface[0][i] == 0) { // if 0 * 0 *
                        swap(interface[1][i], interface[2][i]); // case: 0 * 0 *
                    }
                    else { 
                        if (interface[0][i] != 0) { // if 2 2 0 2
                            swap(interface[1][i], interface[2][i]); 
                            swap(interface[0][i], interface[1][i]); // case: * * 0 *
                        }
                    }
                }
            }
            else {
                if (interface[1][i] == 0) { // a 0 * *
                    if (interface[0][i] != 0) { // if NOT 0 0 * *
                        swap(interface[0][i], interface[1][i]); // case: * 0 * *
                    }
                }
            }
        }
    } 

    output_array(); // calls function to generate a new random integer and place it on the board - also reprints board
    turnDone();
}

void turnDone() {
    score = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            score += interface[i][j];
        }
    }
    printf(BWHT"Score: %i\n", score);
    printf(RESET);
}