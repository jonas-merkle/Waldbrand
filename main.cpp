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
            cout << forest->area[y][x] << "  ";
        }
        cout << endl;
    }
    cout << endl;

}

/*
 * Function which generates a random forest.
 */
void generateForest(forest_t *forest, float randFact) {

}

/*
 * Function to start the forest fires at one point.
 */
void setFirePoint(forest_t *forest) {

}

/*
 * Function to start the forest fires at the howl first row.
 */
void setFireRow(forest_t *forest) {

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
    cout << "Hello, World!" << endl;

    return 0;
}