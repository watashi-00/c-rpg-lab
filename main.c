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

typedef struct  EntryHash   EntryHash;
typedef struct  Type        Type;
typedef enum    TypeKind    TypeKind;

enum TypeKind {
    TYPE_VOID,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_PTR
};

struct Type {
    TypeKind    kind;
    size_t      size;
    const char *name;
};

struct EntryHash {
    const char  *name;
    void        *function;

    size_t      argument_count;
    Type        *arguments;

    Type        return_type;

    EntryHash   *next;
};

static Player   rPlayer;
static Enemy    *gEnemy;

#define HASH_CAPACITY 8

static EntryHash **functions;

static bool player_defined;
static bool menu_defined;

static void function_insert(EntryHash *entry);
static EntryHash *function_get(const char *name);

#define TYPE_DEFINE(type_kind, c_type) \
    (Type) {                                \
        .kind = type_kind,                  \
        .size = sizeof(c_type),             \
        .name = #c_type                     \
    }

#define FUNCTION_REGISTER_VOID(fn, ret_type) \
    static EntryHash fn##_entry = {                 \
        .name = #fn,                                \
        .function = fn,                             \
        .argument_count = 0,                        \
        .arguments = NULL,                          \
        .return_type = ret_type,                    \
        .next = NULL                                \
    };                                              \
    function_insert(&fn##_entry);

#define FUNCTION_REGISTER(fn, ret_type, ...)                \
    static Type fn##_args[] = { __VA_ARGS__ };                     \
    static EntryHash fn##_entry = {                                \
        .name = #fn,                                               \
        .function = fn,                                            \
        .argument_count = sizeof(fn##_args) / sizeof(fn##_args[0]),\
        .arguments = fn##_args,                                    \
        .return_type = ret_type,                                   \
        .next = NULL                                               \
    };                                                             \
    function_insert(&fn##_entry);

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

    functions = calloc(HASH_CAPACITY, sizeof(EntryHash *));

    FUNCTION_REGISTER_VOID(
        changeName,
        TYPE_DEFINE(TYPE_VOID, void)
    )

    menu_defined = true;
}

static void menu() {

    config();

    for (int i = 0; i < 8; i++) {
        if (functions[i] != NULL) {
            printf("%s\n", functions[i]->name);
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


static size_t hash_string(const char *str) {
    size_t hash = 5381;

    while (*str) {
        hash = ((hash << 5) + hash) + (unsigned char)*str;
        str++;
    }

    return hash;
}

static void function_insert(EntryHash *entry) {
    size_t index = hash_string(entry->name) & HASH_CAPACITY - 1;

    entry->next = functions[index];
    functions[index] = entry;
}

static EntryHash *function_get(const char *name) {
    size_t index = hash_string(name) & HASH_CAPACITY - 1;

    EntryHash *entry = functions[index];

    while (entry != NULL) {
        if (strcmp(entry->name, name) == 0) {
            return entry;
        }

        entry = entry->next;
    }

    return NULL;
}