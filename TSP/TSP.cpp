#include "TSP.h"
#include <QFileDialog>
#include <QMessageBox>

TSP::TSP(QWidget* parent) : QMainWindow(parent) {
    ui.setupUi(this);
}

TSP::~TSP()
{
}

void TSP::on_actionLoad_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, "Load Mesh", "", "VTK Files (*.vtk)");

    if (!fileName.isEmpty()) {
        if (mainMesh.loadFromVTK(fileName)) {
            QMessageBox::information(this, "Success", "Model loaded successfully!");
        }
        else {
            QMessageBox::critical(this, "Error", "Failed to read file.");
        }
    }
}

void TSP::on_actionSave_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Mesh", "", "VTK Files (*.vtk)");

    if (!fileName.isEmpty()) {
        if (mainMesh.saveToVTK(fileName)) {
            QMessageBox::information(this, "Saved", "File saved successfully.");
        }
    }
}

void TSP::on_pushButton_Move_clicked() {
    double dx = ui.X_Axes_sb->value();
    double dy = ui.Y_Axes_sb->value();
    double dz = ui.Z_Axes_sb->value();
}

void TSP::on_pushButton_Rotate_clicked() {
    QString axis = ui.comboBox_Axes->currentText();
    double angle = ui.doubleSpinBox_Angle->value();
}

void TSP::on_pushButton_Scale_clicked() {
    double factor = ui.doubleSpinBox_Scale->value();
}

void TSP::on_pushButton_Area_clicked() {
    double area = 0.0;
    ui.lblAreaValue->setText(QString("Area: %1").arg(area));
    ui.lblStatus->setText("Calculation Done");
}

void TSP::on_pushButton_Norm_clicked()
{

    ui.lblStatus->setText("Calculating Normals...");
    //
    // доробить
}
void TSP::on_pushButton_Curv_clicked()
{
    ui.lblStatus->setText("Calculating Curvature...");
    //
    // доробить
}