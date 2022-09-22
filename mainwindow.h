#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots: // Slots are functions that are called when a signal is emitted
    void startProcessingThread();
    void startProcessing();
    void inFileToolClicked();
    void outFolderToolClicked();
    void outFolderNotEmptyMessage();
    void outFolderNotFoundMessage();
    void processingCompleteMessage();

signals:
    void outFolderNotEmpty();
    void outFolderNotFound();
    void processingComplete();

private:
    Ui::MainWindow *ui;
    bool processingThreadRunning = false;
};
#endif // MAINWINDOW_H
