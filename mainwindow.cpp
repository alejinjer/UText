#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString Filename = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(Filename);

    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warnng","Cannot open file:" + file.errorString());
    }
    else {
        currentFile = Filename;
        setWindowTitle(Filename);
        QTextStream in(&file);
        QString text = in.readAll();
        ui->textEdit->setText(text);
        file.close();
    }
}



void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionSave_triggered()
{
    QString Filename = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(Filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "warning","Cannot save file:" + file.errorString());
        return;
    }
    currentFile = Filename;
    setWindowTitle(Filename);
    QTextStream out (&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();

}
