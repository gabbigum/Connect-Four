#include "game_engine.h"

int main() {
    int option;
    printf("Choose an option \n"
           "1. Default game.\n"
           "2. Game with features.\n"
           "3. Play game from saved file.\n");

    scanf("%d", &option);

    switch (option) {
        case 1:
            playDefaultGame();
            break;
        case 2:
            playGameWithFeatures();
            break;
        case 3:
            playGameFromSavedFile();
            break;
        default:
            printf("No such option exist.");
    }

    return 0;
}
