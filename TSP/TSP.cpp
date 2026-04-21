#include "TSP.h"
#include <QFileDialog>
#include <QMessageBox>

TSP::TSP(QWidget* parent) : QMainWindow(parent) {
    ui.setupUi(this);
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