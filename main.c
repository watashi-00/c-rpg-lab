#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "includes/entity.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#else
    #include <unistd.h>
#endif

static Player rPlayer;
static Enemy *gEnemy;

static void **functions;

static bool player_defined;
static bool menu_defined;

static void changeName() {
    char player_name[8];

    printf("Enter player name: ");
    scanf("%7s", player_name);

    if (player_defined) {
        char temp_name[8];

        strcpy(temp_name, rPlayer.name);
        strcpy(rPlayer.name, player_name);

        printf("Changed player name: %s -> %s\n", temp_name, player_name);

        return;
    }

    Player *pPlayer = createPlayer(player_name);
    rPlayer = *pPlayer;

    free(pPlayer);
    player_defined = true;

    printf("Player name: %s\n", rPlayer.name);

}

static void cls(int delay) {
#if defined(_WIN32) || defined(_WIN64)
    Sleep(delay * 1000);
    system("cls");
#else
    sleep(delay);
    system("clear");
#endif
}

void config() {
    if (menu_defined) {
        return;
    }

    functions = calloc(8, 8);
    functions[0] = &changeName;

    menu_defined = true;
}
void menu() {

    config();

    for (int i = 0; i < 8; i++) {
        if (functions[i] != NULL) {
            printf("%p\n", &functions[i]);
        }
    }
}

int main(void) {


    while (true) { // core loop
        menu();
        cls(5);
    }
    return 0;
}