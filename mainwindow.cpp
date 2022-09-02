#include <qfiledialog.h>
#include <qmessagebox.h>
#include <filesystem>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "vid2Photogrammetry/vid2photogrammetry.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){ // Constructor
    ui->setupUi(this);
    setWindowTitle("Vid2Photogrammetry");
    setWindowIcon(QIcon(":/icon.ico"));
    connect(ui->goButton, &QPushButton::released, this, &MainWindow::startProcessing);
    connect(ui->inFileTool, &QPushButton::released, this, &MainWindow::inFileToolClicked);
    connect(ui->outFolderTool, &QPushButton::released, this, &MainWindow::outFolderToolClicked);
    // Pupulate the output extension combo box:
    ui->outExtensionComboBox->addItem("png");
    ui->outExtensionComboBox->addItem("jpg");
    ui->outExtensionComboBox->addItem("bmp");
}

MainWindow::~MainWindow(){ // Destructor
    delete ui;
}

void MainWindow::inFileToolClicked(){ // If the user clicks the "..." button next to the input file path, open a file dialog to select a file
    ui->inFileText->setText(QFileDialog::getOpenFileName());
}

void MainWindow::outFolderToolClicked(){ // If the user clicks the "..." button next to the output folder path, open a file dialog to select a folder
    ui->outFolderText->setText(QFileDialog::getExistingDirectory());
}

void MainWindow::startProcessing(){
    // Check that the output folder is empty
    // The output folder must be empty before frames are extracted to it, because the program will modify all files in the folder
    std::filesystem::path outFolder(ui->outFolderText->text().toStdString()); // Convert QString to std::filesystem::path
    if(std::filesystem::exists(outFolder) && std::filesystem::is_directory(outFolder)){ // Check if the path exists and is a directory
        if(std::filesystem::directory_iterator(outFolder) != std::filesystem::directory_iterator()){ // Check if the directory is empty
            QMessageBox::warning(this, "Output folder not empty", "The output folder is not empty. Please choose an empty output folder.");
            return;
        }
    }
    else{
        QMessageBox::warning(this, "Output folder not found", "The output folder does not exist. Please choose an existing output folder.");
        return;
    }
    // Extract frames from the input video
    extractFrames(ui->inFileText->text().toStdString(), ui->outFolderText->text().toStdString(), ui->outNameText->text().toStdString(), ui->outExtensionComboBox->currentText().toStdString(), ui->outFrameCount->value());
    // Run each of the optional functions if enabled
    if(ui->resizeCheckbox->isChecked()){ // Resizes the frames to the specified dimensions
        resizeFrames(ui->outFolderText->text().toStdString(), ui->resizeWidth->value(), ui->resizeHeight->value());
    }
    if(ui->blurCheckbox->isChecked()){ // Detects and removes blurry frames based on user-defined threshold
        removeBlurryFrames(ui->outFolderText->text().toStdString(), ui->blurThreshold->value());
    }
    if(ui->denoiseCheckbox->isChecked()){ // Denoises the frames using a user-defined strength parameter
        denoiseFrames(ui->outFolderText->text().toStdString(), ui->denoiseStrength->value());
    }
    if(ui->duplicateCheckbox->isChecked()){ // Removes duplicate frames based on user-defined threshold
        deleteNearDuplicates(ui->outFolderText->text().toStdString(), ui->duplicateThreshold->value());
    }
    if(ui->outlierCheckbox->isChecked()){ // Removes outlier frames based on user-defined threshold
        deleteOutliers(ui->outFolderText->text().toStdString(), ui->outlierThreshold->value());
    }
    // Display a message box to indicate that the processing is complete
    QMessageBox::information(this, "Processing complete", "Processing complete. Output frames can be found in the output folder.");
}