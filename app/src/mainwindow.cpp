#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      m_fileBrowserModel(new QFileSystemModel) {
    ui->setupUi(this);

    this->setCentralWidget(ui->splitter);

    // fileBrowser
    m_fileBrowserModel->setRootPath(QDir::currentPath());
    m_fileBrowserModel->setNameFilters(QStringList("*.*"));
    ui->fileBrowser->setModel(m_fileBrowserModel);
    ui->fileBrowser->setHeaderHidden(true);
    for (int i = 1; i < m_fileBrowserModel->columnCount(); i++) {
        ui->fileBrowser->hideColumn(i);
    }
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

void MainWindow::slotShortcutCtrlC() {
    if (ui->textEdit->hasFocus()) {
        ui->textEdit->copy();
    }
}
