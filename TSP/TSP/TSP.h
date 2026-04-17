#pragma once

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
};

