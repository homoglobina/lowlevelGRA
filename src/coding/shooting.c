#include "game.h"
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdio.h>
#include <math.h>

void initializeBullet(struct bulletStruct* bullet) {
    sfTexture* texture = sfTexture_createFromFile("coding/textures/star.png", NULL);
    if (!texture) {
        printf("Error loading texture\n");
        return;
    }

    sfTexture_setSmooth(texture, 1);

    bullet->sprite = sfSprite_create();
    sfSprite_setTexture(bullet->sprite, texture, sfTrue);
    sfSprite_setColor(bullet->sprite, sfRed);

    sfVector2f scale = {0.01f, 0.01f};
    sfSprite_setScale(bullet->sprite, scale);

    bullet->active = 0;
    bullet->x = 0.0f;
    bullet->y = 0.0f;
    bullet->angle = 0.0f;
    bullet->speed = 0.0f;
    sfVector2f position = {bullet->x, bullet->y};
    sfSprite_setPosition(bullet->sprite, position);
    sfSprite_setRotation(bullet->sprite, 90.f);
}

void activateBullet(struct bulletStruct* bullet, float startAngle, float dx, float dy) {
    bullet->active = 1;
    bullet->x = dx;
    bullet->y = dy;
    bullet->angle = startAngle;
    bullet->speed = 14.f;
}

void drawBullet(struct bulletStruct* bullet, sfRenderWindow* window) {
    if (!bullet->active) return;

    sfVector2f position = trigPosition(bullet->x, bullet->y, bullet->angle, bullet->speed);
    bullet->x = position.x;
    bullet->y = position.y;

    if (bullet->x < 0 || bullet->x > WIDTH || bullet->y < 0 || bullet->y > HEIGHT) {
        bullet->active = 0;
        return;
    }

    sfVector2u textureSize = sfTexture_getSize(sfSprite_getTexture(bullet->sprite));
    sfVector2f origin = {textureSize.x / 2.0f, textureSize.y / 2.0f};
    sfSprite_setOrigin(bullet->sprite, origin);
    sfSprite_setPosition(bullet->sprite, position);
    sfSprite_setRotation(bullet->sprite, bullet->angle);
    sfRenderWindow_drawSprite(window, bullet->sprite, NULL);
}

int checkShot(struct bulletStruct* bullet, struct enemyStruct* enemy) {
    if (bullet->active && enemy->active) {
        // Calculate the distance between bullet and enemy
        float dx = bullet->x - enemy->x;
        float dy = bullet->y - enemy->y;
        float distanceSquared = dx * dx + dy * dy;
        if (distanceSquared < 250.f) { 
            enemy->hp -= 5;
            if (enemy->hp <= 0) {
                enemy->active = 0;
            }
            bullet->active = 0;
            return 1; // Return 1 to indicate a hit
        }
    }
    return 0; // Return 0 to indicate no hit
}
