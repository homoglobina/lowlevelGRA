#include "game.h"
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float randomFloat(float min, float max) {
    return ((max - min) * ((float)rand() / RAND_MAX)) + min;
}

void enemy(struct enemyStruct* enemy) {
    sfTexture* texture = sfTexture_createFromFile("coding/textures/plane.png", NULL);
    if (!texture) {
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

    enemy->x = randomFloat(30, WIDTH-30);
    enemy->y = randomFloat(30, HEIGHT-30);
    
    // Set the sprite's position
    sfVector2f position = {enemy->x, enemy->y};
    sfSprite_setPosition(enemy->sprite, position);
    sfSprite_setRotation(enemy->sprite, 90.f); // absolute angle
}

void drawEnemy(sfRenderWindow* window, struct enemyStruct* enemy) {
    enemy->x += randomFloat(2.0f, 7.0f);

    // Update position
    sfVector2f position = {enemy->x, enemy->y};

    position = checkPosition(enemy->x, enemy->y, WIDTH, HEIGHT); // out of bounds
    enemy->x = position.x;
    enemy->y = position.y;
    
    sfSprite_setPosition(enemy->sprite, position);

    // Draw the sprite onto the window
    sfRenderWindow_drawSprite(window, enemy->sprite, NULL);
}
