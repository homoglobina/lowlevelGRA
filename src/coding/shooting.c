#include "game.h"
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdio.h>


void initializeBullet(struct bulletStruct* bullet)
{
    sfTexture* texture = sfTexture_createFromFile("coding/textures/star.png", NULL);
    if (!texture)
    {
        printf("Error loading texture\n");
        return;
    }

    sfTexture_setSmooth(texture, 1);

    // Create the sprite and set its texture
    bullet->sprite = sfSprite_create();
    sfSprite_setTexture(bullet->sprite, texture, sfTrue);
    sfSprite_setColor(bullet->sprite, sfRed);

    // Set the sprite's scale
    sfVector2f scale = {0.1f, 0.1f};
    sfSprite_setScale(bullet->sprite, scale);

    bullet->active = 0;
    bullet->x = 0.0f;
    bullet->y = 0.0f;
    bullet->angle = 0.0f;
    bullet->speed = 0.0f;
    sfVector2f position = {bullet->x, bullet->y};
    sfSprite_setPosition(bullet->sprite, position);
    sfSprite_setRotation(bullet->sprite,90.f); 

}

void activateBullet(struct bulletStruct* bullet, float startAngle, float dx, float dy)
{
    bullet->active = 1;
    bullet->x = dx;
    bullet->y = dy;
    bullet->angle = startAngle;

}


void drawBullet(struct bulletStruct* bullet, sfRenderWindow* window) {
    float x = bullet->x;
    float y = bullet->y;
    float angle = bullet->angle;
    float speed = bullet->speed;

    speed = 10.0f;
    sfVector2f position = trigPosition(x, y, angle, speed);
    bullet->x = position.x;
    bullet->y = position.y;

    // Get the size of the texture
    sfVector2u textureSize = sfTexture_getSize(sfSprite_getTexture(bullet->sprite));

    // Set the origin to the center of the texture
    sfVector2f origin = {textureSize.x / 2.0f, textureSize.y / 2.0f};
    sfSprite_setOrigin(bullet->sprite, origin);
    sfSprite_setPosition(bullet->sprite, position);
    sfSprite_setRotation(bullet->sprite, bullet->angle);
    sfRenderWindow_drawSprite(window, bullet->sprite, NULL);
}


    
    
    
    



