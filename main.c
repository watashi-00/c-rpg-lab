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

typedef struct EntryHash EntryHash;
typedef struct Type Type;
typedef enum TypeKind TypeKind;

enum TypeKind {
    TYPE_VOID,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_PTR
};

struct Type {
    TypeKind kind;
    size_t size;
    const char *name;
};

struct EntryHash {
    const char *name;
    void *function;

    size_t argument_count;
    Type *arguments;

    Type return_type;

    EntryHash *next;
};


static Player rPlayer;
static Enemy *gEnemy;

static EntryHash **functions;

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


static void config() {
    if (menu_defined) {
        return;
    }

    functions = calloc(8, sizeof(EntryHash));
    functions[0] = &(EntryHash) {
        .name = "changeName",
        .function = changeName,
        .next = NULL,
    };

    menu_defined = true;
}
static void menu() {

    config();

    for (int i = 0; i < 8; i++) {
        if (functions[i] != NULL) {
            printf("%s\n", &functions[i]->name);
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