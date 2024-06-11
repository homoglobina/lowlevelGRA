#ifndef GAME_H
#define GAME_H

#define NUM_ENEMIES 2
#define NUM_BULLETS 12
#define WIDTH 1920
#define HEIGHT 1080

#include <SFML/Graphics.h>

struct enemyStruct {
    int hp;
    sfSprite* sprite;
    double x;
    double y;
    int active;
    int axis;
};

struct explosionStruct
{
    sfSprite* sprite;
    double x;
    double y;
    int liveFrames;

};


struct bulletStruct {
    sfSprite* sprite;
    double x;
    double y;
    double angle;
    double speed;
    int active;
};

int checkShot(struct bulletStruct* bullet, struct enemyStruct* enemy);

sfVector2f checkPosition(float x, float y, int width, int height);
sfVector2f trigPosition(float x, float y, float angle, float distance);

void player();
void drawPlayer(sfRenderWindow* window, struct bulletStruct* bullets);
int checkPlayerCollision(struct enemyStruct* enemy);

void enemy(struct enemyStruct* enemy);
void drawEnemy(sfRenderWindow* window, struct enemyStruct* enemy, int level);

void intiliazieExplosion(struct explosionStruct* boom);
void drawExplosion(struct explosionStruct* boom, sfRenderWindow* window);
void setExplosion(float x, float y, struct explosionStruct* boom);

void initializeBullet(struct bulletStruct* bullet);
void activateBullet(struct bulletStruct* bullet, float startAngle, float dx, float dy);
void drawBullet(struct bulletStruct* bullet, sfRenderWindow* window);

void initializeTextObjects();
int menu();
int deadScreen(int level);
void printLevel(int level, int hp, int score, sfRenderWindow* window);

void addScore(const char *name, int score);
void getPlayerName(char *playerName, int maxLen, sfRenderWindow *window);

#endif // GAME_H
