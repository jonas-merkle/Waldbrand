#include <iostream>

#define FOREST_WIDTH 30
#define FOREST_HIGHT 20

#define EMPTY ' '
#define TREE 'T'
#define FIRE 'F'
#define BURNED '_'

/*
 * Text-snippets for the user interface
 */
 //@TODO: UI-Texte
 char germanUIText[3][256] {
    "\nHallo und herzlich Willkommen beim Waldbrand Simulator!\n\n",
    "Bevor es los geht gib bitte die von dir gewünschte Dichte des Waldes ein (Zahl zwischen 0 und 1): ",
    "Dein Wald wurde erfolgreich generiert und sieht wie folgt aus:\n"
};

char englishUIText[3][256];

/*
 * New datatype to store the data of a forest.
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
            printf(" %c ", forest->area[y][x]);
        }
        printf("\n");
    }
    printf("\n");
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
}

/*
 * Function to start the forest fires at one point.
 */
void setFirePoint(forest_t *forest) {
    forest->is_buring = true;
    forest->area[0][0] = FIRE;
}

/*
 * Function to start the forest fires at the howl first row.
 */
void setFireRow(forest_t *forest) {
    forest->is_buring = true;
    for (int x = 0; x < FOREST_WIDTH; ++x) {
        forest->area[0][x] = FIRE;
    }
}

/*
 * Function to simulate a step of the forest fires.
 */
void makeItBurn(forest_t *forest) {
    //@TODO: Brandsimulation
}

/*
 * Function to print out the user interface text-snippets in the selected language.
 */
void printUI(char language, int textNumber) {

    // switch to the selected language
    switch (language) {
        default:
        case 'D':
            printf("%s", germanUIText[textNumber]);
        break;

        case 'E':
            printf("%s", englishUIText[textNumber]);
        break;
    }
}

/*
 * Main-Function...
 */
int main() {

    // init the seed for rand()
    srand(time(NULL));


    //@TODO: Game-Routine (evtl. mit zusätzlichem exception handling)
    printUI('D', 0);
    printUI('D', 1);

    forest_t wald;
    float density;
    scanf("%f", &density);
    generateForest(&wald, density);
    printUI('D', 2);
    printForest(&wald);




    setFirePoint(&wald);
    printForest(&wald);

    return 0;
}