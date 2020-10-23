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
#include <QFileSystemModel>
#include<QDebug>
#include<QShortcut>


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

    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void slotShortcutCtrlC();

private:
    Ui::MainWindow *ui;

    QString currentFile = "";

    QFileSystemModel*model;

    QShortcut       *CtrlC;
};

#endif // MAINWINDOW_H
