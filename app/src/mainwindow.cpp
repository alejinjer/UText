#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QListWidget>
#include<QPushButton>
#include<QLabel>
#include <QBoxLayout>
#include <QVBoxLayout>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      m_fileBrowserModel(new QFileSystemModel) {
    ui->setupUi(this);
    this->setCentralWidget(ui->widget);
    // fileBrowser
    m_fileBrowserModel->setRootPath(QDir::currentPath());
    m_fileBrowserModel->setNameFilters(QStringList("*.*"));
    ui->fileBrowser->setModel(m_fileBrowserModel);
    ui->fileBrowser->setHeaderHidden(true);
    for (int i = 1; i < m_fileBrowserModel->columnCount(); i++) {
        ui->fileBrowser->hideColumn(i);
    }
    QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spLeft.setHorizontalStretch(1);
    ui->fileBrowser->setSizePolicy(spLeft);

    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setHorizontalStretch(3);
    ui->textEdit->setSizePolicy(spRight);

    QSizePolicy spUp(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setVerticalStretch(1);
    ui->tabWidget->setSizePolicy(spUp);

    QSizePolicy spDown(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spDown.setVerticalStretch(9);
    ui->splitter->setSizePolicy(spDown);

    ShortCuts();


}

void MainWindow::ShortCuts() {

    altCopy = new QShortcut(this);
    altCopy->setKey(Qt::ALT + Qt::Key_C);
    connect(altCopy, SIGNAL(activated()), this, SLOT(slotShortcutAltCopy()));

    altPaste = new QShortcut(this);
    altPaste->setKey(Qt::ALT + Qt::Key_W);
    connect(altPaste, SIGNAL(activated()), this, SLOT(slotShortcutAltPaste()));

    altCut = new QShortcut(this);
    altCut->setKey(Qt::ALT + Qt::Key_X);
    connect(altCut, SIGNAL(activated()), this, SLOT(slotShortcutAltCut()));

    altUndo = new QShortcut(this);
    altUndo->setKey(Qt::ALT + Qt::Key_Z);
    connect(altUndo, SIGNAL(activated()), this, SLOT(slotShortcutAltUndo()));

    altRedo = new QShortcut(this);
    altRedo->setKey(Qt::ALT + Qt::Key_Y);
    connect(altRedo, SIGNAL(activated()), this, SLOT(slotShortcutAltRedo()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::openFile(const QString &filename) {
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning",
                             "Cannot open file:" + file.errorString());
    } else {
        m_currentFile = filename;
        setWindowTitle(filename);
        QTextStream in(&file);
        QString text = in.readAll();
        ui->textEdit->setText(text);
        file.close();
    }
}

void MainWindow::saveFile(const QString &filename) {
    QFile file(filename);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning",
                             "Cannot save file:" + file.errorString());
    } else {
        m_currentFile = filename;
        setWindowTitle(filename);
        QString text = ui->textEdit->toPlainText();
        QTextStream out(&file);
        out << text;
        file.close();
    }
}

void MainWindow::on_actionOpen_triggered() {
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    openFile(filename);
}

void MainWindow::on_actionNew_triggered() {
    m_currentFile.clear();
    ui->textEdit->setText(QString());

//    QWidget* wgt = new QWidget;
//    QLayout* l = new QHBoxLayout;
//    QLayout* v = new QVBoxLayout;
//    QPushButton* btn = new QPushButton( "X" );

//    v->addItem(l);
//    v->addWidget( new QLabel("Path of file") );
//    l->addWidget(btn);
//    l->setSpacing(0);
//    wgt->setLayout( v );
//    QListWidgetItem* item = new QListWidgetItem( ui->listWidget );
//    item->setSizeHint( wgt->sizeHint() );
 //   ui->listWidget->setItemWidget( item, wgt );
}

void MainWindow::on_actionSave_triggered() {
    QString filename = QFileDialog::getSaveFileName(this, "Save as");
    saveFile(filename);
}

void MainWindow::on_fileBrowser_doubleClicked(const QModelIndex &index) {
    if (QFileInfo(m_fileBrowserModel->filePath(index)).isFile()) {
        QString filename = m_fileBrowserModel->filePath(index);
        openFile(filename);
    }
}

void MainWindow::on_actionCopy_triggered() {
    if (ui->textEdit->hasFocus()) {
        ui->textEdit->copy();
    }
}

void MainWindow::on_actionPaste_triggered() {
    if (ui->textEdit->hasFocus()) {
        ui->textEdit->paste();
    }
}

void MainWindow::on_actionCut_triggered() {
    if (ui->textEdit->hasFocus()) {
        ui->textEdit->cut();
    }
}

void MainWindow::on_actionUndo_triggered() {
    if (ui->textEdit->hasFocus()) {
        ui->textEdit->undo();
    }
}

void MainWindow::on_actionRedo_triggered() {
    if (ui->textEdit->hasFocus()) {
        ui->textEdit->redo();
    }
}

void MainWindow::slotShortcutAltCopy() {
    on_actionCopy_triggered();
}

void MainWindow::slotShortcutAltPaste() {
    on_actionPaste_triggered();
}

void MainWindow::slotShortcutAltCut() {
    on_actionCut_triggered();
}

void MainWindow::slotShortcutAltUndo(){
    on_actionUndo_triggered();
}

void MainWindow::slotShortcutAltRedo(){
    on_actionRedo_triggered();
}
