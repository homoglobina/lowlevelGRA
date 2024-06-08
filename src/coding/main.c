#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "game.h"

int main() {
    // Create the window
    sfVideoMode mode = {WIDTH, HEIGHT, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "TOP GUN\t THE GAME", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    sfVector2i position = {0, 0};
    sfRenderWindow_setPosition(window, position);

    // Call the functions to load the texture and create the sprites
    player();
    int n = 0;

    struct enemyStruct adam;
    enemy(&adam);

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

        // Exit
        if (sfKeyboard_isKeyPressed(sfKeyEscape)){
            int choice = menu();
            if (choice == 1) {
                sfRenderWindow_close(window);
            }
            else if (choice == 2) {
                // sfRenderWindow_close(window);
            }
            else if (choice == 3) {
                sfRenderWindow_close(window);
            }
        }


        // Clear the window
        sfRenderWindow_clear(window, sfBlue);

        // Draw the sprites onto the window
        drawEnemy(window, &adam);

        if (n == NUM_BULLETS) n = 0;
        drawPlayer(window, bullets);

        for (int j = 0; j < NUM_BULLETS; j++) {
            if (bullets[j].active) drawBullet(&bullets[j], window);
        }

        // Display the window contents
        sfRenderWindow_display(window);
    }

    sfRenderWindow_destroy(window);
    return 0;
}
