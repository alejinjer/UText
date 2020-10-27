#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QPrintDialog>
#include <QPrinter>
#include <QShortcut>
#include <QTextBlock>
#include <QTextStream>
#include<QListWidget>
#include<QPushButton>
#include<QLabel>
#include <QBoxLayout>
#include<QTabWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void openFile(const QString &filename);

    void saveFile(const QString &filename);

    void MainWindow::ShortCuts();

    void MainWindow::widgetPosition();

private slots:
    void on_actionOpen_triggered();

    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_fileBrowser_doubleClicked(const QModelIndex &index);

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void slotShortcutAltCopy();

    void slotShortcutAltPaste();

    void slotShortcutAltCut();

    void slotShortcutAltUndo();

    void slotShortcutAltRedo();

    void on_tabWidget_tabCloseRequested(int index);

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;

    QString m_currentFile = "";

    QFileSystemModel *m_fileBrowserModel;

    QMap <int,QString> fileTabsData;

    int currentTab = 0;

    //ShortCuts

    QShortcut *altCopy;

    QShortcut *altPaste;

    QShortcut *altCut;

    QShortcut *altUndo;

    QShortcut *altRedo;
};

#endif // MAINWINDOW_H
