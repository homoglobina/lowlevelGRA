#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.h>

struct enemyStruct
{
    sfSprite* sprite;
    double x;
    double y;
};


void player();
void drawPlayer(sfRenderWindow* window);
void enemy(struct enemyStruct* enemy);
void drawEnemy(sfRenderWindow* window, struct enemyStruct* enemy);

#endif // GAME_H
