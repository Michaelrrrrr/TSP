#pragma once
#include "Points.h"

class Walls
{
private:
    int pointsIndexes[3];
public:
    void setWall(int p1, int p2, int p3) {
        pointsIndexes[0] = p1;
        pointsIndexes[1] = p2;
        pointsIndexes[2] = p3;
    };
    int getPoint1Index() { return pointsIndexes[0]; };
    int getPoint2Index() { return pointsIndexes[1]; };
    int getPoint3Index() { return pointsIndexes[2]; };

    Points Normal(Points p1, Points p2, Points p3); 
};
