#ifndef GAME_H
#define GAME_H

#define NUM_ENEMIES 5
#define NUM_BULLETS 80
#define WIDTH 1000
#define HEIGHT 800

#include <SFML/Graphics.h>

struct enemyStruct {
    int hp;
    sfSprite* sprite;
    double x;
    double y;
    int active;
};

struct bulletStruct {
    sfSprite* sprite;
    double x;
    double y;
    double angle;
    double speed;
    int active;
};

sfVector2f checkPosition(float x, float y, int width, int height);
sfVector2f trigPosition(float x, float y, float angle, float distance);

void player();
void drawPlayer(sfRenderWindow* window, struct bulletStruct* bullets);

void enemy(struct enemyStruct* enemy);
void drawEnemy(sfRenderWindow* window, struct enemyStruct* enemy);

void initializeBullet(struct bulletStruct* bullet);
void activateBullet(struct bulletStruct* bullet, float startAngle, float dx, float dy);
void drawBullet(struct bulletStruct* bullet, sfRenderWindow* window);

int menu();

#endif // GAME_H
