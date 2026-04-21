#include "Mesh.h"
#include <QFile>
#include <QTextStream>

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

}

// getnormal