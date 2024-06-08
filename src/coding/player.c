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
    sfTexture* texture = sfTexture_createFromFile("coding/textures/plane.png", NULL);
    if (!texture)
    {
        printf("Error loading texture\n");
        return;
    }

    sfTexture_setSmooth(texture, 1);

    // Create the sprite and set its texture
    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);

    // Set the sprite's scale
    sfVector2f scale = {0.5f, 0.5f};
    sfSprite_setScale(sprite, scale);

    // Set the sprite's position
    sfVector2f position = {100.0f, 100.0f};
    sfSprite_setPosition(sprite, position);



}




void drawPlayer(sfRenderWindow* window)
{
    double tempx = x;
    double tempy = y;
    double angle;



    // Sterowanie
    if (sfKeyboard_isKeyPressed(0) ){        // A
        --x;
        }
    if (sfKeyboard_isKeyPressed(3)){          // D
        ++x;
        }
    if (sfKeyboard_isKeyPressed(18)){        // S
        ++y;
        }
    if (sfKeyboard_isKeyPressed(22)){      // W
        --y;
        }


    if (x < tempx){
        if (y > tempy){
            angle = 225.f;
        }
        else if (y < tempy){
            angle = 315.f;
        }
        else {
            angle = 270.f;
        }
    }
    else if (x > tempx){
        if (y > tempy){
            angle = 135.f;
        }
        else if (y < tempy){
            angle = 45.f;
        }
        else {
            angle = 90.f;
        }
    }
    else {
        if (y > tempy){
            angle = 180.f;
        }
        else if (y < tempy){
            angle = 0.f;
        }
    }
    


    sfSprite_setRotation(sprite,angle);



    sfVector2f position = {x,y};
    sfSprite_setPosition(sprite, position);

    
    // Get the size of the texture
    sfVector2u textureSize = sfTexture_getSize(sfSprite_getTexture(sprite));

    // Set the origin to the center of the texture
    sfVector2f origin = {textureSize.x / 2.0f, textureSize.y / 2.0f};
    sfSprite_setOrigin(sprite, origin);
    
    
    // Draw the sprite onto the window
    sfRenderWindow_drawSprite(window, sprite, NULL);

}