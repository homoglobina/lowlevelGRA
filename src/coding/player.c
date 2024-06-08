#include "game.h"
#include <SFML/Graphics.h>
#include <stdio.h>

// Declare a global variable to hold the sprite
sfSprite* sprite;

void player()
{
    sfTexture* texture = sfTexture_createFromFile("star.png", NULL);
    if (!texture)
    {
        printf("Error loading texture\n");
        return;
    }

    // Create the sprite and set its texture
    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);

    // Set the sprite's scale
    sfVector2f scale = {0.5f, 0.5f};
    sfSprite_setScale(sprite, scale);

    // Set the sprite's position
    sfVector2f position = {100.0f, 100.0f};
    sfSprite_setPosition(sprite, position);


    // Clean up the texture (it's now managed by the sprite)
    //sfTexture_destroy(texture);
}

void draw(sfRenderWindow* window)
{
    // Clear the window with a suitable color (e.g., black)
    sfRenderWindow_clear(window, sfBlack);

    // Draw the sprite onto the window
    sfRenderWindow_drawSprite(window, sprite, NULL);

    // Display the contents of the window
    sfRenderWindow_display(window);
}