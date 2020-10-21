#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile>
#include<QFileDialog>
#include<QTextBlock>
#include<QMessageBox>
#include<QPrinter>
#include<QPrintDialog>
#include <QTextStream>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionNew_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
};

#endif // MAINWINDOW_H
