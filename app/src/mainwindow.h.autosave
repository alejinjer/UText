#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QBoxLayout>
#include <QDebug>
#include <QDialogButtonBox>
#include <QFile>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPrintDialog>
#include <QPrinter>
#include <QPushButton>
#include <QShortcut>
#include <QSyntaxHighlighter>
#include <QTabWidget>
#include <QTextBlock>
#include <QTextEdit>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void openFile(const QString &filePath);

    void saveFile(const QString &filePath);

    void ShortCuts();

    void widgetPosition();

    QTextEdit *addTab(const QString &filename);

    void poss();

    void createFolder(const QPoint &pos);

    void createFile(const QPoint &pos);

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

    void on_actionfind_and_replace_triggered();

    void on_actionOpen_directory_triggered();

    void treeCustomMenu(const QPoint &pos);

private:
    void keyPressEvent(QKeyEvent *ре);

    Ui::MainWindow *ui;

    QFileSystemModel *m_fileBrowserModel;

    int currentTab = 0;

    // ShortCuts

    QShortcut *altCopy;

    QShortcut *altPaste;

    QShortcut *altCut;

    QShortcut *altUndo;

    QShortcut *altRedo;
};
#endif // MAINWINDOW_H
