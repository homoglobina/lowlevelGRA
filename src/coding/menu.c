#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "game.h"
#include <stdio.h>

int menu() {

    sfFont* font = sfFont_createFromFile("coding/textures/zerovelo.ttf");
    if (!font){
        printf("Error loading font\n");
        return 1;
    }


    /// TEKST

    sfText* text = sfText_create();

    sfText_setString(text, "MENU\n");
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 50);
    sfText_setPosition(text, (sfVector2f){40, 50});
    sfText_setColor(text, sfWhite);

    sfText* text2 = sfText_create();

    sfText_setString(text2, "1. Play\n2. Highscores\n3. Quit\n4. xxxxxx \n5. xxxxxx \n6. xxxxxx\n7. xxxxxx\n8. xxxxxx\n9. xxxxxx\n");
    sfText_setFont(text2, font);
    sfText_setCharacterSize(text2, 20);
    sfText_setPosition(text2, (sfVector2f){40, 120});
    sfText_setColor(text2, sfWhite);


    sfRenderWindow* window;
    sfVideoMode mode = {300, 420, 32};
    window = sfRenderWindow_create(mode, "Menu", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    sfVector2i position = {0, 0};
    sfRenderWindow_setPosition(window, position);

    int choice;
    sfEvent event;
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
            else if (sfKeyboard_isKeyPressed(27)){
                sfRenderWindow_close(window);
                return choice = 1;

            }
            else if (sfKeyboard_isKeyPressed(28)){
                return choice = 2;
                //sfRenderWindow_close(window);
            }
            else if (sfKeyboard_isKeyPressed(29)){
                sfRenderWindow_close(window);
                return choice = 3;
            }
        }

        // Clear the window
        sfRenderWindow_clear(window, sfBlack);

        sfRenderWindow_drawText(window, text, NULL);
        sfRenderWindow_drawText(window, text2, NULL);
        


        // Display the window contents
        sfRenderWindow_display(window);
    }

    sfRenderWindow_destroy(window);
}
