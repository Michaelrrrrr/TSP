#pragma once
#include <QVector>
#include <Points.h>
#include <Walls.h>
#include <QString>

using namespace std;

struct Vec3
{
    double x, y, z;
};

class Mesh
{
private:
    QVector<Points> points;
    QVector<Walls> walls;

    QVector<int> pointMeighbour;
    QVector<int> pointWalls;

    int** neighb = nullptr;
    int* count_neighb = nullptr;

public:
    
    void clear();
    bool loadFromVTK(QString filename);
    bool saveToVTK(QString filename);

    int getPointsCount() const { return points.size(); }
    int getWallsCount() const { return walls.size(); }
/*
    void addWall(int p1, int p2, int p3) {
        Walls wall;
        wall.setWall(p1, p2, p3);
        walls.push_back(wall);
    }
    void addPoint(int x1, int y1, int z1) {
        Points point;
        point.setPoint(x1, y1, z1);
        points.push_back(point);

    }*/
    void addWall(int p1, int p2, int p3);

    QVector<Points> getPoints() { return points; };
    QVector<Walls> getWalls() { return walls; };

    void addPoint(double x, double y, double z);
  
    void Neighbours();
    void SearchNeighbours();

    Vec3 getAB(int p1, int p2);
    Vec3 getAC(int p1, int p3);
    double CalculateSurface();
    void CalculateNormals();
    void SearchNeighboursOrdered();

    void moveMesh(double dx, double dy, double dz);
    void scaleMesh(double factor);
    void rotateMesh(QString axis, double angle);
};
