/*
 * ###########################
 * ### Waldbrand-Simulator ###
 * ### Autor: Jonas Merkle ###
 * ###########################
 * source-code form: https://github.com/jonas-merkle/Waldbrand
 */
#include <iostream>

#define FOREST_WIDTH 30
#define FOREST_HIGHT 20

#define EMPTY ' '
#define TREE 'T'
#define FIRE 'F'
#define BURNED '_'

using namespace std;

/*
 * Text-snippets for the user interface
 */
 char germanUIText[8][256] = {
    "\nHallo und herzlich Willkommen beim Waldbrand Simulator!\n\n",
    "Bevor es los geht gib bitte die von dir gewünschte Dichte des Waldes ein (Zahl zwischen 0 und 1): ",
    "Dein Wald wurde erfolgreich generiert und sieht wie folgt aus:\n",
    "Wähle wo das Feuer beginnen soll (r = 1. Reihe, p = 1. Baum von links):",
    "Um die Simulation zu beenden drücke x + enter, um den nächsten Schritt durchzuführen einen beliebige Taste + enter: ",
    "Der Wald ist in ",
    " Simulationsschritten abgebrannt.\n",
    "Danke für's benutzen dieser Software!\n"
};
//@TODO: UI-text english
char englishUIText[8][256] = {
        "\nHallo und herzlich Willkommen beim Waldbrand Simulator!\n\n",
        "Bevor es los geht gib bitte die von dir gewünschte Dichte des Waldes ein (Zahl zwischen 0 und 1): ",
        "Dein Wald wurde erfolgreich generiert und sieht wie folgt aus:\n",
        "Wähle wo das Feuer beginnen soll (r = 1. Reihe, p = 1. Baum von links):",
        "Um die Simulation zu beenden drücke x + enter, um den nächsten Schritt durchzuführen einen beliebige Taste + enter: ",
        "Der Wald ist in ",
        " Simulationsschritten abgebrannt.\n",
        "Danke für's benutzen dieser Software!\n"
};

/*
 * New data type to store the data of a forest.
 */
typedef struct forest_t {
    char area[FOREST_HIGHT][FOREST_WIDTH];
    int burned_cycles;
    bool is_buring;
};

/*
 * Function to print the forest to the command line.
 */
void printForest(forest_t *forest) {

    for (int y = 0; y < FOREST_HIGHT; y++) {
        for (int x = 0; x < FOREST_WIDTH; x ++) {
            cout << forest->area[y][x] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/*
 * Function which generates a random forest.
 */
void generateForest(forest_t *forest, float density) {

    for (int y = 0; y < FOREST_HIGHT; y++) {
        for (int x = 0; x < FOREST_WIDTH; x ++) {
            if (((density * 10) - 1) < (rand() % 10)) {
                forest->area[y][x] = EMPTY;
            }
            else {
                forest->area[y][x] = TREE;
            }
        }
    }

    forest->is_buring = false;
    forest->burned_cycles = 0;
}

/*
 * Function to start the forest fires at one point.
 */
void setFirePoint(forest_t *forest) {

    forest->is_buring = true;
    forest->burned_cycles++;
    // searching for the leftmost tree
    int x;
    for (x  = 0; x < FOREST_WIDTH && forest->area[0][1] != TREE; x++);
    forest->area[0][x] = FIRE;
}

/*
 * Function to start the forest fires at the howl first row.
 */
void setFireRow(forest_t *forest) {

    forest->is_buring = true;
    forest->burned_cycles++;
    for (int x = 0; x < FOREST_WIDTH; ++x) {
        if (forest->area[0][x] == TREE) {
            forest->area[0][x] = FIRE;
        }
    }
}

/*
 * Function to simulate a step of the forest fires.
 */
void makeItBurn(forest_t *forest) {

    // generating a buffer for the state of the trees in the forest at the start of the simulation step
    forest_t buf;
    for (int y = 0; y < FOREST_HIGHT; y++) {
        for (int x = 0; x < FOREST_WIDTH; x ++) {
            buf.area[y][x] = forest->area[y][x];
        }
    }

    // check all trees
    bool noBurningtrees = true;
    for (int y = 0; y < FOREST_HIGHT; y++) {
        for (int x = 0; x < FOREST_WIDTH; x ++) {
            // pick burning trees
            if (buf.area[y][x] == FIRE){
                // set upper neighbor on fire if possible
                if (y-1 >= 0 && buf.area[y-1][x] == TREE){
                    forest->area[y-1][x] = FIRE;
                }
                // set lower neighbor on fire if possible
                if (y+1 < FOREST_HIGHT && buf.area[y+1][x] == TREE){
                    forest->area[y+1][x] = FIRE;
                }
                // set left neighbor on fire if possible
                if (x-1 >= 0 && buf.area[y][x-1] == TREE){
                    forest->area[y][x-1] = FIRE;
                }
                // set right neighbor on fire if possible
                if (x+1 < FOREST_WIDTH && buf.area[y][x+1] == TREE){
                    forest->area[y][x+1] = FIRE;
                }
                // burn down the burning tree
                forest->area[y][x] = BURNED;
                noBurningtrees = false;
            }
        }
    }

    if (noBurningtrees){
        forest->is_buring = false;
    }
    else {
        forest->burned_cycles++;
    }

}

/*
 * Function to print out the user interface text-snippets in the selected language.
 */
void printUI(char language, int textNumber) {

    // switch to the selected language
    switch (language) {
        default:
        case 'd':
            cout << germanUIText[textNumber];
        break;

        case 'e':
            cout << englishUIText[textNumber];
        break;
    }
}

/*
 * Main-Function...
 */
int main() {

    // init the seed for rand()
    srand(time(NULL));

    // choose a language dialog
    char language;
    do {
       cout << "[INFO]: Please choose a language (d = german, e = english): ";
        cin >> language;
    } while (language != 'd' && language != 'e');

    // some ui messages
    printUI(language, 0);

    // generate the forest
    forest_t wald;
    float density;
    do {
        printUI(language, 1);
        cin >> density;
    } while (density > 1 || density < 0);
    generateForest(&wald, density);
    printUI(language, 2);
    printForest(&wald);

    // choose where to set the fire
    char c;
    do {
        printUI(language, 3);
        cin >> c;
    } while (c != 'p' && c != 'r');
    switch (c) {
        default:
        case 'p':
            setFirePoint(&wald);
        break;

        case 'r':
            setFireRow(&wald);
        break;
    }
    cout << endl;
    printForest(&wald);

    // Simulation of the forest fires
    while(wald.is_buring) {
        printUI(language, 4);
        cin >> c;
        if (c == 'x') {
            exit(0);
        }
        cout << endl;

        makeItBurn(&wald);
        printForest(&wald);
    }

    // output a statistic
    printUI(language, 5);
    cout << wald.burned_cycles;
    printUI(language, 6);

    // som ui messages
    printUI(language, 7);

    return 0;
}