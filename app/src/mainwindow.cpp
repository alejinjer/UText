#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setCentralWidget(ui->splitter);
    QString dir = "/";

    model = new QFileSystemModel();
    QString filesPath = dir;
    model->setRootPath(dir);
    QStringList filter;
    filter << "*.*";
    model->setNameFilters(filter);
    // model->setNameFilterDisables(false);

    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index(dir));
    ui->treeView->setAnimated(false);

    ui->treeView->setSortingEnabled(true);

    CtrlC = new QShortcut(this);
    CtrlC->setKey(Qt::ALT + Qt::Key_C);
    connect(CtrlC, SIGNAL(activated()), this, SLOT(slotShortcutCtrlC()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionOpen_triggered() {
    QString Filename = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(Filename);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warnng",
                             "Cannot open file:" + file.errorString());
    } else {
        currentFile = Filename;
        setWindowTitle(Filename);
        QTextStream in(&file);
        QString text = in.readAll();
        ui->textEdit->setText(text);
        file.close();
    }
}

void MainWindow::on_actionNew_triggered() {
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionSave_triggered() {
    QString Filename = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(Filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "warning",
                             "Cannot save file:" + file.errorString());
        return;
    }
    currentFile = Filename;
    setWindowTitle(Filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index) {
    // QFileSystemModel *modell = new QFileSystemModel;
    QFileInfo check_file(model->filePath(index));
    QString Filename = model->filePath(index);
    qInfo() << Filename;
    QFile file(Filename);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warnng",
                             "Cannot open file:" + file.errorString());
    } else {
        currentFile = Filename;
        setWindowTitle(Filename);
        QTextStream in(&file);
        QString text = in.readAll();
        ui->textEdit->setText(text);
        file.close();
    }
}

void MainWindow::on_actionCopy_triggered() { ui->textEdit->copy(); }

void MainWindow::on_actionPaste_triggered() { ui->textEdit->paste(); }

void MainWindow::on_actionCut_triggered() { ui->textEdit->cut(); }

void MainWindow::on_actionUndo_triggered() { ui->textEdit->undo(); }

void MainWindow::on_actionRedo_triggered() { ui->textEdit->redo(); }

void MainWindow::slotShortcutCtrlC() { ui->textEdit->copy(); }
