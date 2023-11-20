void moveRight();
void shiftRight();



void moveRight() {

if (interface[0][3] == interface[0][2]) { // 2 4 2 2 
    double newVal = interface[0][3] + interface[0][2];
    interface[0][3] = newVal;
    interface[0][2] = 0; // 2 4 0 4
}

shiftRight(); // 0 2 4 4

if (interface[0][1] == interface[0][2]) { 
    double newVal = interface[0][1] + interface[0][2];
    interface[0][2] = newVal;
    interface[0][1] = 0; 
}

shiftRight();

if (interface[0][0] == interface[0][1]) { 
    double newVal = interface[0][0] + interface[0][1];
    interface[0][1] = newVal;
    interface[0][0] = 0; 
}

    output_array(); // calls function to generate a new random integer and place it on the board - also reprints board
    turnDone();
]


void shiftRight() { 
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
}