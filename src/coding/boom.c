#include "game.h"
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdio.h>


void intiliazieExplosion(struct explosionStruct* boom) {
    sfTexture* texture = sfTexture_createFromFile("coding/textures/explosion.png", NULL);
    if (!texture) {
        printf("Error loading texture\n");
        return;
    }

    boom->sprite = sfSprite_create();
    sfSprite_setTexture(boom->sprite, texture, sfTrue);
    sfVector2f scale = {1.f, 1.f};
    sfSprite_setScale(boom->sprite, scale);

    // Initialize other members of struct explosionStruct if needed
    boom->x = 0.0f;
    boom->y = 0.0f;
    boom->liveFrames = 0;
}

void setExplosion(float x, float y, struct explosionStruct* boom) {
    boom->x = x;
    boom->y = y;
    boom->liveFrames = 10;
}

void drawExplosion(struct explosionStruct* boom, sfRenderWindow* window) {
    
    if (boom->liveFrames > 0) {
        sfVector2f position = {boom->x, boom->y};
        sfSprite_setPosition(boom->sprite, position);
        sfRenderWindow_drawSprite(window, boom->sprite, NULL);
        boom->liveFrames--;
    }



}