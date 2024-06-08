#include "game.h"
#include <SFML/Graphics.h>
#include <SFML/Window.h>

#include <stdio.h>

// Declare a global variable to hold the sprite
sfSprite* sprite;
double x = 0.0f; 
double y = 0.0f;

void player()
{
    sfTexture* texture = sfTexture_createFromFile("coding/textures/test.png", NULL);
    if (!texture)
    {
        printf("Error loading texture\n");
        return;
    }

    // Create the sprite and set its texture
    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);

    // Set the sprite's scale
    sfVector2f scale = {0.02f, 0.02f};
    sfSprite_setScale(sprite, scale);

    // Set the sprite's position
    sfVector2f position = {100.0f, 100.0f};
    sfSprite_setPosition(sprite, position);


    // Clean up the texture (it's now managed by the sprite)
    //sfTexture_destroy(texture);
}

void draw(sfRenderWindow* window)
{

    // Sterowanie
    if (sfKeyboard_isKeyPressed(0)){        // A
        sfVector2f position = {--x, --y};
        sfSprite_setPosition(sprite, position);
        }
    if (sfKeyboard_isKeyPressed(3)){          // D
        sfVector2f position = {++x, ++y};
        sfSprite_setPosition(sprite, position);
        }
    if (sfKeyboard_isKeyPressed(18)){        // S
        sfVector2f position = {--x, ++y};
        sfSprite_setPosition(sprite, position);
        }
    if (sfKeyboard_isKeyPressed(22)){      // W
        sfVector2f position = {++x, --y};
        sfSprite_setPosition(sprite, position);
        }


    sfRenderWindow_clear(window, sfBlack);

    // Draw the sprite onto the window
    sfRenderWindow_drawSprite(window, sprite, NULL);

    // Display the contents of the window
    sfRenderWindow_display(window);
}