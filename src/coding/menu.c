#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "game.h"
#include <stdio.h>

sfFont* font;
sfText* levelText;
sfText* statsText;
sfText* lostText;
sfText* deadText;

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

    sfVector2i position = {900, 200};
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
                //return choice = 2;
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


int deadScreen(int score) {
    sfFont* font = sfFont_createFromFile("coding/textures/zerovelo.ttf");
    
    if (!font){
        printf("Error loading font\n");
        return 0;
    }


    sfText* lostText = sfText_create();
    sfText_setString(lostText, "You LOST\n");
    sfText_setFont(lostText, font);
    sfText_setCharacterSize(lostText, 35);
    sfText_setPosition(lostText, (sfVector2f){35, 35});
    sfText_setColor(lostText, sfBlack);

    sfText* deadText = sfText_create();
    sfText_setString(deadText, "1. Retry\n2.Save Score\n3infern. Highscores\n4. Quit\n");
    sfText_setFont(deadText, font);
    sfText_setCharacterSize(deadText, 20);
    sfText_setPosition(deadText, (sfVector2f){40, 100});
    sfText_setColor(deadText, sfBlack);


    sfRenderWindow* window;
    sfVideoMode mode = {300, 200, 32};
    window = sfRenderWindow_create(mode, "You Lost", sfResize | sfClose, NULL);
    if (!window)
        return 0;

    sfVector2i position = {750, 300};
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
                sfRenderWindow_close(window);
                return choice = 2;
            }
            else if (sfKeyboard_isKeyPressed(29)){
                sfRenderWindow_close(window);
                return choice = 3;
            }
        }

        // Clear the window
        sfRenderWindow_clear(window, sfRed);

        sfRenderWindow_drawText(window, lostText, NULL);
        sfRenderWindow_drawText(window, deadText, NULL);
        


        // Display the window contents
        sfRenderWindow_display(window);
    }

    sfRenderWindow_destroy(window);
}






void initializeTextObjects() {
    font = sfFont_createFromFile("coding/textures/zerovelo.ttf");
    if (!font){
        printf("Error loading font\n");
        return;
    }

    levelText = sfText_create();
    statsText = sfText_create();

    sfText_setFont(levelText, font);
    sfText_setCharacterSize(levelText, 60);
    sfText_setPosition(levelText, (sfVector2f){40, 50});
    sfText_setColor(levelText, sfBlack);

    sfText_setFont(statsText, font);
    sfText_setCharacterSize(statsText, 35);
    sfText_setPosition(statsText, (sfVector2f){40, 135});
    sfText_setColor(statsText, sfWhite);
    

}

void printLevel(int level, int hp,int score, sfRenderWindow* window) {


    sfText* text = sfText_create();

    char levelString[50];
    sprintf(levelString, "LEVEL %d\n", level);
    sfText_setString(levelText, levelString);
    sfRenderWindow_drawText(window, levelText, NULL);


    char hpString[50];
    sprintf(hpString, "score: %d\n hp: %d\n", score, hp);
    sfText_setString(statsText, hpString);
    sfRenderWindow_drawText(window, statsText, NULL);
}