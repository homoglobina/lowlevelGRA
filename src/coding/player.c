#include "game.h"
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

sfSprite* sprite;
double x = 420.0f; 
double y = 120.0f;
double angle = 0.0f;
float speed = 4.0f;
int n = 0;
time_t lastSpacePressTime = 0;
double spaceCooldown = 0.5; 

time_t lastHitPressTime = 0;
double hitCooldown = 2.0; 


void player() {
    sfTexture* texture = sfTexture_createFromFile("coding/textures/plane.png", NULL);
    if (!texture) {
        printf("Error loading texture\n");
        return;
    }

    sfTexture_setSmooth(texture, 1);

    // Create the sprite and set its texture
    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);

    // Set the sprite's scale
    sfVector2f scale = {0.2f, 0.2f};
    sfSprite_setScale(sprite, scale);
    sfSprite_setColor(sprite, sfWhite);

    // Set the sprite's position
    sfVector2f position = {x, y};
    sfSprite_setPosition(sprite, position);
}

void drawPlayer(sfRenderWindow* window, struct bulletStruct* bullets) {
    int i = 0;
    int j = 0;

    // Rotacja
    if (sfKeyboard_isKeyPressed(sfKeyW)) --j;
    if (sfKeyboard_isKeyPressed(sfKeyA)) --i;
    if (sfKeyboard_isKeyPressed(sfKeyS)) ++j;
    if (sfKeyboard_isKeyPressed(sfKeyD)) ++i;

    if (speed > 20.0f) speed = 20.0f;
    if ((speed < 2.5f && j != 0) || (speed < 2.5f && i != 0)) speed += 4.0f;
    if (speed > 1.5f && j == 0 && i == 0) speed -= 0.25f;

    if (i == 0 && j == 0) {
        // no rotation
    } else if (i < 0) {
        if (j > 0) {
            angle = 225.f;
        } else if (j < 0) {
            angle = 315.f;
        } else {
            angle = 270.f;
        }
    } else if (i > 0) {
        if (j > 0) {
            angle = 135.f;
        } else if (j < 0) {
            angle = 45.f;
        } else {
            angle = 90.f;
        }
    } else {
        if (j > 0) {
            angle = 180.f;
        } else if (j < 0) {
            angle = 0.f;
            sfSprite_setRotation(sprite, angle);
        }
    }

    if (angle) {
        sfSprite_setRotation(sprite, angle);
    }

    sfVector2f position = trigPosition(x, y, angle, speed);
    x = position.x;
    y = position.y;

    position = checkPosition(x, y, WIDTH, HEIGHT); // out of bounds
    x = position.x;
    y = position.y;

    sfSprite_setPosition(sprite, position);

    // Get the size of the texture
    sfVector2u textureSize = sfTexture_getSize(sfSprite_getTexture(sprite));

    // Set the origin to the center of the texture
    sfVector2f origin = {textureSize.x / 2.0f, textureSize.y / 2.0f};
    sfSprite_setOrigin(sprite, origin);



    if (sfKeyboard_isKeyPressed(sfKeySpace)) {
        time_t currentTime = time(NULL);
        if (currentTime - lastSpacePressTime >= spaceCooldown) {
            if (n == NUM_BULLETS) n = 0;
            activateBullet(&bullets[n], angle, x, y);
            n++;
            lastSpacePressTime = currentTime;
        }
    }

    // Draw the sprite onto the window
    sfRenderWindow_drawSprite(window, sprite, NULL);
}

int checkPlayerCollision(struct enemyStruct* enemy) {
    
    



    if (abs(enemy->x - x) < 50 && abs(enemy->y - y) < 50) {
        time_t currentTime = time(NULL);
        if (currentTime - lastHitPressTime >= hitCooldown) {
            lastHitPressTime = currentTime;
            return 1;  // collision
        }
    }
    return 0;  // no collision
}