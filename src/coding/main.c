#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

int main() {
    srand((unsigned int)time(NULL));

    sfVideoMode mode = {WIDTH, HEIGHT, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "TOP GUN THE GAME", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    sfVector2i position = {200, 200};
    sfRenderWindow_setPosition(window, position);

    player();

    struct enemyStruct ships[NUM_ENEMIES];
    for (int i = 0; i < NUM_ENEMIES; i++) {
        enemy(&ships[i]);
    }

    struct bulletStruct bullets[NUM_BULLETS];
    for (int i = 0; i < NUM_BULLETS; i++) {
        initializeBullet(&bullets[i]);
    }

    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        if (sfKeyboard_isKeyPressed(sfKeyEscape)){
            int choice = menu();
            if (choice == 1) {
                // sfRenderWindow_close(window);
            }
            else if (choice == 2) {
                // sfRenderWindow_close(window);
            }
            else if (choice == 3) {
                sfRenderWindow_close(window);
            }
        }

        sfRenderWindow_clear(window, sfBlue);

        for (int j = 0; j < NUM_ENEMIES; j++) {
            if (ships[j].active) drawEnemy(window, &ships[j]);
        }

        for (int j = 0; j < NUM_BULLETS; j++) {
            if (bullets[j].active) drawBullet(&bullets[j], window);
        }

        for (int j = 0; j < NUM_ENEMIES; j++) {
            if (ships[j].active) {
                for (int i = 0; i < NUM_BULLETS; i++) {
                    if (checkShot(&bullets[i], &ships[j])) {
                        break; // Bullet has hit, move to the next enemy
                    }
                }
            }
        }

        drawPlayer(window, bullets);

        sfRenderWindow_display(window);
    }

    sfRenderWindow_destroy(window);
    return 0;
}
