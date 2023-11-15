#include "functions.cpp"

int main() {
    srand(time(nullptr));
    output_array(); //displaying interface with a 2
    printf(BWHT"Score: %i\n", score); // prints score at the start
    printf(RESET);
    userInput(); // takes user input

    return 0;
}