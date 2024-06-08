#ifndef GAME_H
#define GAME_H



#define WIDTH 1920
#define HEIGHT 1080

#include <SFML/Graphics.h>

struct enemyStruct
{
    sfSprite* sprite;
    double x;
    double y;
};

sfVector2f checkPosition(float x, float y, int width,int height);

sfVector2f trigPosition(float x, float y, float angle, float distance);

void player();
void drawPlayer(sfRenderWindow* window);
void enemy(struct enemyStruct* enemy);
void drawEnemy(sfRenderWindow* window, struct enemyStruct* enemy);

#endif // GAME_H
