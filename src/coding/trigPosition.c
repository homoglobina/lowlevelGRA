#include "game.h"
#include <math.h>



sfVector2f checkPosition(float x, float y, int width,int height){
    if (x > width ) x = 0;
    else if (x < 0) x = width;
    if (y > height) y = 0;
    else if (y < 0) y = height;
    return (sfVector2f){x,y};
}



sfVector2f trigPosition(float x, float y, float angle, float distance)
{

    angle -= 90.f; // boskie 90 stopni 

    float radianAngle = angle * (M_PI / 180.0f);

    if (angle == 0.f) x += distance; 
    else if (angle == 45.f){
        x += distance * cos(radianAngle);
        y += distance * sin(radianAngle);
    }
    else if (angle == 90.f) y += distance; 
    else if (angle == 135.f){
        x += distance * cos(radianAngle);
        y += distance * sin(radianAngle);
    }
    else if (angle == 180.f) x -= distance; 
    else if (angle == 225.f){
        x += distance * cos(radianAngle);
        y += distance * sin(radianAngle);
    }
    else if (angle == 270.f) y -= distance; 
    else if (angle == 315.f){
        x += distance * cos(radianAngle);
        y += distance * sin(radianAngle);
    }
    else {
        x += distance * cos(radianAngle);
        y += distance * sin(radianAngle);
    }

    return (sfVector2f){x, y};
}
