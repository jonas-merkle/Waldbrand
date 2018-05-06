#include <iostream>

#define FOREST_WIDTH 30
#define FOREST_HIGHT 20

#define EMPTY ' '
#define TREE 'T'
#define FIRE 'F'
#define BURNED '_'

using namespace std;

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
void generateForest(forest_t *forest, float dencity) {
    for (int y = 0; y < FOREST_HIGHT; y++) {
        for (int x = 0; x < FOREST_WIDTH; x ++) {
            if (((dencity * 10) - 1) < (rand() % 10)) {
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

}

/*
 * Main-Function...
 */
int main() {

    // init the seed for rand()
    srand(time(NULL));


    forest_t wald;
    generateForest(&wald, 0.9);
    printForest(&wald);
    setFirePoint(&wald);
    printForest(&wald);

    return 0;
}