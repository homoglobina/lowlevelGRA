#include "game.h"
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdio.h>






void enemy(struct enemyStruct* enemy)
{
    sfTexture* texture = sfTexture_createFromFile("coding/textures/plane.png", NULL);
    if (!texture)
    {
        printf("Error loading texture\n");
        return;
    }

    sfTexture_setSmooth(texture, 1);

    // Create the sprite and set its texture
    enemy->sprite = sfSprite_create();
    sfSprite_setTexture(enemy->sprite, texture, sfTrue);
    sfSprite_setColor(enemy->sprite, sfRed);

    // Set the sprite's scale
    sfVector2f scale = {0.4f, 0.4f};
    sfSprite_setScale(enemy->sprite, scale);


    enemy->x = 100.0f;
    enemy->y = 100.0f;
    // Set the sprite's position
    sfVector2f position = {enemy->x, enemy->y};
    sfSprite_setPosition(enemy->sprite, position);
    sfSprite_setRotation(enemy->sprite,90.f); // absolute angle
}





void drawEnemy(sfRenderWindow* window, struct enemyStruct* enemy)
{

    enemy->x += 0.5f;

    // Sterowanie
    sfVector2f position = {enemy->x, enemy->y};
    sfSprite_setPosition(enemy->sprite, position);



    // Draw the sprite onto the window
    sfRenderWindow_drawSprite(window, enemy->sprite, NULL);




}