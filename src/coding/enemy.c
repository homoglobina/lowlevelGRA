#include "game.h"
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float randomFloat(float min, float max) {
    return ((max - min) * ((float)rand() / RAND_MAX)) + min;
}

int randomInteger(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void enemy(struct enemyStruct* enemy) {
    sfTexture* texture = sfTexture_createFromFile("coding/textures/plane.png", NULL);
    if (!texture) {
        printf("Error loading texture\n");
        return;
    }

    sfTexture_setSmooth(texture, 1);
    enemy->sprite = sfSprite_create();
    sfSprite_setTexture(enemy->sprite, texture, sfTrue);
    sfSprite_setColor(enemy->sprite, sfRed);

    sfVector2f scale = {0.15f, 0.15f};
    sfSprite_setScale(enemy->sprite, scale);

    enemy->x = randomFloat(30, WIDTH-30);
    enemy->y = randomFloat(30, HEIGHT-30);
    enemy->axis = randomInteger(0,1);
    enemy->active = 1;
    enemy->hp = 5; // Initialize hp

    sfVector2f position = {enemy->x, enemy->y};
    sfSprite_setPosition(enemy->sprite, position);
    sfSprite_setRotation(enemy->sprite, 90.f);
}

void drawEnemy(sfRenderWindow* window, struct enemyStruct* enemy, int level) {
    if (enemy->axis == 1) enemy->x += 2.5f * level;
    else {
        enemy->y += 2.5f * level;
        sfSprite_setRotation(enemy->sprite, 180.f);
    }

    if (enemy->hp <= 0) {
        enemy->active = 0;
        enemy->y = -20;
        enemy->x = -20;
    }

    sfVector2f position = {enemy->x, enemy->y};
    position = checkPosition(enemy->x, enemy->y, WIDTH, HEIGHT);
    enemy->x = position.x;
    enemy->y = position.y;

    // Get the size of the texture
    sfVector2u textureSize = sfTexture_getSize(sfSprite_getTexture(enemy->sprite));

    // Set the origin to the center of the texture
    sfVector2f origin = {textureSize.x / 2.0f, textureSize.y / 2.0f};
    sfSprite_setOrigin(enemy->sprite, origin);

    
    sfSprite_setPosition(enemy->sprite, position);
    sfRenderWindow_drawSprite(window, enemy->sprite, NULL);
}
