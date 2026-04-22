#include "Mesh.h"
#include <QFile>
#include <QTextStream>
#include <iostream>

bool Mesh::loadFromVTK(QString filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;

    points.clear();
    walls.clear();

    QTextStream in(&file);
    QString word;

    while (!in.atEnd()) {
        in >> word;
        if (word == "POINTS") {
            int count;
            QString type;
            in >> count >> type;
            for (int i = 0; i < count; ++i) {
                double x, y, z;
                in >> x >> y >> z;
                addPoint(x, y, z);
            }
        }
        else if (word == "POLYGONS") {
            int count, total;
            in >> count >> total;
            for (int i = 0; i < count; ++i) {
                int n, p1, p2, p3;
                in >> n >> p1 >> p2 >> p3;
                if (n == 3) addWall(p1, p2, p3);
            }
        }
    }
    file.close();

    Neighbours();
    SearchNeighbours();

    return true;
}

bool Mesh::saveToVTK(QString filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return false;

    QTextStream out(&file);
    out << "# vtk DataFile Version 3.0\nVTK\nASCII\nDATASET POLYDATA\n";

    out << "POINTS " << points.size() << " double\n";
    for (auto& p : points) {
        out << p.getX() << " " << p.getY() << " " << p.getZ() << "\n";
    }

    out << "POLYGONS " << walls.size() << " " << walls.size() * 4 << "\n";
    for (auto& w : walls) {
        out << "3 " << w.getPoint1Index() << " " << w.getPoint2Index() << " " << w.getPoint3Index() << "\n";
    }
    file.close();
    return true;
}

// vytvaranie bodu s suradnicami zo suboru a uchovanie do listu points 
void Mesh::addPoint(double x, double y, double z)
{
    points.push_back(Points(x, y, z));
}

// vytvaranie stien s trougolnikov a ich uchovanie
void Mesh::addWall(int p1, int p2, int p3)
{
    Walls wall;                
    wall.setWall(p1, p2, p3);
    walls.push_back(wall);
}

void Mesh::Neighbours()
{
    int size = points.size();

    if (neighb != nullptr || count_neighb != nullptr)
    {
        for (int i = 0; i < size; i++)
        {
            delete[] neighb[i];
        }
        delete[] neighb;
        delete[] count_neighb;
    }

    neighb = new int*[size];
    count_neighb = new int[size];

    for (int i = 0; i < size; i++)
    {
        neighb[i] = new int[size];
        count_neighb[i] = 0;
    }
}

void Mesh::SearchNeighbours()
{
    int size = walls.size();

    //prechod po vsetkym trojuholnikam
    for (int i = 0; i < size; i++)
    {
        //suradnici
        int p1 = walls[i].getPoint1Index();
        int p2 = walls[i].getPoint2Index();
        int p3 = walls[i].getPoint3Index();

        int arr[3] = { p1, p2, p3 };

        for (int j = 0; j < 3; j++)
        {
            int current = arr[j];
            
            // hladame ostatne body ako susiedov
            for (int k = 0; k < 3; k++)
            {
                if (j != k)
                {
                    int neighbour = arr[k];
                    bool exists = false;

                    //overenie ci uz existuje 
                    for (int m = 0; m < count_neighb[current]; m++)
                    {
                        if (neighb[current][m] == neighbour)
                        {
                            exists = true;
                            break;
                        }
                    }

                    if (!exists)
                    {
                        // zapis noveho susieda podla current bodu
                        int index = count_neighb[current];
                        neighb[current][index] = neighbour;
                        count_neighb[current]++;
                    }
                }
            }
        }
    }
}

// getnormal