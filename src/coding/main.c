#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "game.h"

int score = 0;
int playerHP = 100;
int level = 1;
int repetitions = 0;


int main() {
    srand((unsigned int)time(NULL));

    sfVideoMode mode = {WIDTH, HEIGHT, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "TOP GUN THE GAME", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    sfVector2i position = {0, 0};
    sfRenderWindow_setPosition(window, position);

    player();

    int numEnemies = NUM_ENEMIES + level * 2;
    struct enemyStruct *ships = malloc(numEnemies * sizeof(struct enemyStruct));
    if (!ships) {
        return 1; // Memory allocation failed
    }

    for (int i = 0; i < numEnemies; i++) {
        enemy(&ships[i]);
    }

    struct bulletStruct bullets[NUM_BULLETS];
    for (int i = 0; i < NUM_BULLETS; i++) {
        initializeBullet(&bullets[i]);
    }
    
    struct explosionStruct *boom = malloc(5 * sizeof(struct explosionStruct));
    if (!boom) {
        return 1; // Memory allocation failed
    }

    for (int i = 0; i < 5; i++) {
        intiliazieExplosion(&boom[i]);
    }



    sfRenderWindow_setVerticalSyncEnabled(window, sfTrue); // Enable VSync


    initializeTextObjects();

    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
            int choice = menu();
            if (choice == 1) {
                // sfRenderWindow_close(window);
            } else if (choice == 2) {
                // sfRenderWindow_close(window);
            } else if (choice == 3) {
                sfRenderWindow_close(window);
            }
        }

        sfRenderWindow_clear(window, sfBlue);

        printLevel(level, playerHP, score, window);

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
                return 1; // Memory allocation failed
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
                        if (repetitions == 4){
                            repetitions = 0;
                            boom = realloc(boom, 5 * sizeof(struct explosionStruct));
                        }
                        break; // Bullet has hit, move to the next enemy
                    }
                }
                if (checkPlayerCollision(&ships[j])) {
                    playerHP -= 10;
                    if (playerHP <= 0) {
                        sfRenderWindow_close(window);
                    }
                }
            }
        }

        for (int i = 0; i < 5; i++) {
            drawExplosion(&boom[i], window);
        }

        drawPlayer(window, bullets);

        sfRenderWindow_display(window);
    }

    free(boom); // Free allocated memory
    free(ships); // Free allocated memory
    sfRenderWindow_destroy(window);
    return 0;
}
