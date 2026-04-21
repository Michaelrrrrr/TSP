#pragma once
#include "Mesh.h"

#include <QtWidgets/QMainWindow>
#include "ui_TSP.h"

class TSP : public QMainWindow
{
    Q_OBJECT

public:
    TSP(QWidget *parent = nullptr);
    ~TSP();

private:
    Ui::TSPClass ui;
    Mesh mainMesh;

private slots:
    void on_actionLoad_triggered();
    void on_actionSave_triggered();

    void on_pushButton_Move_clicked();
    void on_pushButton_Rotate_clicked();
    void on_pushButton_Scale_clicked();

    void on_pushButton_Area_clicked();
    void on_pushButton_Norm_clicked();
    void on_pushButton_Curv_clicked();
};

