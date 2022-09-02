#include <qfiledialog.h>
#include <qmessagebox.h>
#include <filesystem>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "vid2Photogrammetry/vid2photogrammetry.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Vid2Photogrammetry");
    connect(ui->goButton, &QPushButton::released, this, &MainWindow::startProcessing);
    connect(ui->inFileTool, &QPushButton::released, this, &MainWindow::inFileToolClicked);
    connect(ui->outFolderTool, &QPushButton::released, this, &MainWindow::outFolderToolClicked);
    ui->outExtensionComboBox->addItem("png");
    ui->outExtensionComboBox->addItem("jpg");
    ui->outExtensionComboBox->addItem("bmp");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::inFileToolClicked(){
    ui->inFileText->setText(QFileDialog::getOpenFileName());
}

void MainWindow::outFolderToolClicked(){
    ui->outFolderText->setText(QFileDialog::getExistingDirectory());
}

void MainWindow::startProcessing(){
    // Check that the output folder is empty
    std::filesystem::path outFolder(ui->outFolderText->text().toStdString());
    if(std::filesystem::exists(outFolder) && std::filesystem::is_directory(outFolder)){
        if(std::filesystem::directory_iterator(outFolder) != std::filesystem::directory_iterator()){
            QMessageBox::warning(this, "Output folder not empty", "The output folder is not empty. Please choose an empty output folder.");
            return;
        }
    }
    else{
        QMessageBox::warning(this, "Output folder not found", "The output folder does not exist. Please choose an existing output folder.");
        return;
    }

    // Extract frames from the input video
    // Run each of the optional functions if enabled
}