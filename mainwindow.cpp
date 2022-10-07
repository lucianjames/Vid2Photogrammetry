#include <qfiledialog.h>
#include <QFuture>
#include <QtConcurrent>
#include <qmessagebox.h>
#include <filesystem>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "vid2Photogrammetry/vid2photogrammetry.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){ // Constructor
    ui->setupUi(this);
    setWindowTitle("Vid2Photogrammetry");
    setWindowIcon(QIcon(":/icon.ico"));
    connect(ui->goButton, &QPushButton::released, this, &MainWindow::startProcessingThread);
    connect(ui->inFileTool, &QPushButton::released, this, &MainWindow::inFileToolClicked);
    connect(ui->outFolderTool, &QPushButton::released, this, &MainWindow::outFolderToolClicked);
    // Connect the signals to the slots, they are called when the signal is emitted from the worker thread
    connect(this, &MainWindow::outFolderNotEmpty, this, &MainWindow::outFolderNotEmptyMessage);
    connect(this, &MainWindow::outFolderNotFound, this, &MainWindow::outFolderNotFoundMessage);
    connect(this, &MainWindow::processingComplete, this, &MainWindow::processingCompleteMessage);
    connect(this, &MainWindow::processingThreadClosed, this, &MainWindow::setProcessRunningBoolFalse);

    // Populate the output extension combo box:
    ui->outExtensionComboBox->addItem("png");
    ui->outExtensionComboBox->addItem("jpg");
    ui->outExtensionComboBox->addItem("bmp");
    
    // Set up tooltips to make program idiot-proof:
    ui->inFileTool->setToolTip("Select the input video file");
    ui->outFolderTool->setToolTip("Select the output folder");
    ui->outNameText->setToolTip("Enter the output file name");
    ui->outExtensionComboBox->setToolTip("Select the output file extension");
    ui->flipCheckBox->setToolTip("Check to flip the image vertically, use this if the image is upside down");
    ui->blurCheckbox->setToolTip("Delete images that are too blurry");
    ui->blurThreshold->setToolTip("Set the threshold for blur detection, image blurryness is quantified by the variance of the Laplacian filter. Low blur value = blurrier image");
    ui->denoiseCheckbox->setToolTip("Apply a denoising filter to the images, useful for low-light smartphone video");
    ui->denoiseStrength->setToolTip("Set the threshold for denoising, higher values remove more noise");
    ui->duplicateCheckbox->setToolTip("Delete duplicate images, works fine when there are two images which are duplicate but may fail if there are more than two similar images");
    ui->duplicateThreshold->setToolTip("Set the threshold for duplicate image detection, higher values will delete more images");
    ui->outlierCheckbox->setToolTip("Delete outlier images, useful for removing images which arent of any use for photogrammetry (for example if the camera has been covered accidentally by a finger)");
    ui->outlierThreshold->setToolTip("Set the threshold for outlier image detection, higher values will delete more images");
    ui->resizeCheckbox->setToolTip("Resize the images (usually) to a smaller size, useful to reduce the amount of data to process");
    ui->resizeWidth->setToolTip("Set the width of the resized image");
    ui->resizeHeight->setToolTip("Set the height of the resized image");
    ui->goButton->setToolTip("Start processing");
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

void MainWindow::outFolderNotEmptyMessage(){ // If the output folder is not empty, display a message box
    QMessageBox::warning(this, "Output folder not empty", "The output folder is not empty. Please choose an empty output folder.");
}

void MainWindow::outFolderNotFoundMessage(){ // If the output folder is not found, display a message box
    QMessageBox::warning(this, "Output folder not found", "The output folder does not exist. Please choose an existing output folder.");
}

void MainWindow::processingCompleteMessage(){ // If the processing is complete, display a message box
    QMessageBox::information(this, "Processing complete", "Processing complete. Output frames can be found in the output folder.");
}

void MainWindow::startProcessingThread(){ // Run the processing function in a separate thread
    if(this->processingThreadRunning == false){
        this->processingThreadRunning = true;
        QFuture<void> future = QtConcurrent::run(this, &MainWindow::startProcessing);
    }else{
        QMessageBox::warning(this, "Processing already running", "Processing is already running. Please wait for the current processing to complete.");
    }
}

void MainWindow::setProcessRunningBoolFalse(){
    this->processingThreadRunning = false;
}

void MainWindow::startProcessing(){
    // Check that the output folder is empty
    // The output folder must be empty before frames are extracted to it, because the program will modify all files in the folder
    std::filesystem::path outFolder(ui->outFolderText->text().toStdString()); // Convert QString to std::filesystem::path
    if(std::filesystem::exists(outFolder) && std::filesystem::is_directory(outFolder)){ // Check if the path exists and is a directory
        if(std::filesystem::directory_iterator(outFolder) != std::filesystem::directory_iterator()){ // Check if the directory is empty
            emit processingThreadClosed();
            emit outFolderNotEmpty();
            return;
        }
    }
    else{
        emit processingThreadClosed();
        emit outFolderNotFound();
        return;
    }
    // Extract frames from the input video
    extractFrames(ui->inFileText->text().toStdString(), 
                  ui->outFolderText->text().toStdString(), 
                  ui->outNameText->text().toStdString(), 
                  ui->outExtensionComboBox->currentText().toStdString(), 
                  ui->outFrameCount->value(), 
                  ui->flipCheckBox->isChecked());
    // Run each of the optional functions if enabled
    if(ui->resizeCheckbox->isChecked()){ // Resizes the frames to the specified dimensions
        resizeFrames(ui->outFolderText->text().toStdString(), 
                     ui->resizeWidth->value(), 
                     ui->resizeHeight->value());
    }
    // Blurry frame removal:
    if(ui->blurCheckbox->isChecked()){ // Detects and removes blurry frames based on user-defined threshold
        removeBlurryFrames(ui->outFolderText->text().toStdString(), 
                           ui->blurThreshold->value());
    }
    // Image denoising:
    if(ui->denoiseCheckbox->isChecked()){ // Denoises the frames using a user-defined strength parameter
        denoiseFrames(ui->outFolderText->text().toStdString(), 
                      ui->denoiseStrength->value());
    }
    // Duplicate frame removal:
    if(ui->duplicateCheckbox->isChecked()){ // Removes duplicate frames based on user-defined threshold
        deleteNearDuplicates(ui->outFolderText->text().toStdString(), 
                             ui->duplicateThreshold->value());
    }
    // Outlier frame removal:
    if(ui->outlierCheckbox->isChecked()){ // Removes outlier frames based on user-defined threshold
        deleteOutliers(ui->outFolderText->text().toStdString(), 
                       ui->outlierThreshold->value());
    }
    // Display a message box to indicate that the processing is complete
    emit processingThreadClosed();
    emit processingComplete();
}