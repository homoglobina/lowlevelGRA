#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "game.h"

#define MAX_EXPLOSIONS 5

int score = 0;
int playerHP = 100;
int level = 1;
int repetitions = 0;
int isHit = 0;

void startGame(sfRenderWindow* window);

int main() {
    srand((unsigned int)time(NULL));

    sfVideoMode mode = {WIDTH, HEIGHT, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "TOP GUN THE GAME", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    sfVector2i position = {0, 0};
    sfRenderWindow_setPosition(window, position);

    while (sfRenderWindow_isOpen(window)) {
        startGame(window);
    }

    sfRenderWindow_destroy(window);
    return 0;
}

void startGame(sfRenderWindow* window) {
    score = 0;
    playerHP = 100;
    level = 1;
    repetitions = 0;
    isHit = 0;

    player();

    int numEnemies = NUM_ENEMIES + level * 2;
    struct enemyStruct *ships = malloc(numEnemies * sizeof(struct enemyStruct));
    if (!ships) {
        printf("Memory allocation failed\n");
        return;
    }

    for (int i = 0; i < numEnemies; i++) {
        enemy(&ships[i]);
    }

    struct bulletStruct bullets[NUM_BULLETS];
    for (int i = 0; i < NUM_BULLETS; i++) {
        initializeBullet(&bullets[i]);
    }

    struct explosionStruct *boom = malloc(MAX_EXPLOSIONS * sizeof(struct explosionStruct));
    if (!boom) {
        printf("Memory allocation failed\n");
        free(ships);
        return;
    }

    for (int i = 0; i < MAX_EXPLOSIONS; i++) {
        initializeExplosion(&boom[i]);
    }

    initializeTextObjects();

    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
            int choice = menu();
            if (choice == 3) sfRenderWindow_close(window);
        }

        if (isHit == 1){
            sfRenderWindow_clear(window, sfRed);
            isHit = 0;
        } else {
            sfRenderWindow_clear(window, sfBlue);
        }

        int deadEnemies = 0;
        for (int j = 0; j < numEnemies; j++) {
            if (ships[j].active) drawEnemy(window, &ships[j], level);
            else deadEnemies++;
        }

        if (deadEnemies == numEnemies) {
            level++;
            numEnemies = NUM_ENEMIES + level * 2;
            ships = realloc(ships, numEnemies * sizeof(struct enemyStruct));
            if (!ships) {
                printf("Memory allocation failed\n");
                free(boom);
                return;
            }

            for (int i = 0; i < numEnemies; i++) {
                enemy(&ships[i]);
            }
        }

        for (int j = 0; j < NUM_BULLETS; j++) {
            if (bullets[j].active) drawBullet(&bullets[j], window);
        }

        for (int j = 0; j < numEnemies; j++) {
            if (ships[j].active) {
                for (int i = 0; i < NUM_BULLETS; i++) {
                    if (checkShot(&bullets[i], &ships[j])) {
                        score += 25 * level;
                        setExplosion(ships[j].x, ships[j].y, &boom[repetitions]);
                        repetitions++;
                        if (repetitions == 4) {
                            repetitions = 0;
                            boom = realloc(boom, MAX_EXPLOSIONS * sizeof(struct explosionStruct));
                        }
                        break;
                    }
                }
                if (checkPlayerCollision(&ships[j])) {
                    playerHP -= 10;
                    isHit = 1;
                    if (playerHP <= 0) {
                        int choice = deadScreen(score);
                        if (choice == 4) {
                            sfRenderWindow_close(window);
                        } else if (choice == 1) {
                            free(boom);
                            free(ships);
                            return; // Restart the game
                        }
                    }
                }
            }
        }

        for (int i = 0; i < MAX_EXPLOSIONS; i++) {
            drawExplosion(&boom[i], window);
        }

        drawPlayer(window, bullets);

        printLevel(level, playerHP, score, window);

        sfRenderWindow_display(window);
    }

    free(boom);
    free(ships);
}
