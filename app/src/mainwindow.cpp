#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPlainTextEdit>
#include <QtAlgorithms>
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
    widgetPosition();
    ShortCuts();
}

void MainWindow::widgetPosition() {

    QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spLeft.setHorizontalStretch(1);
    ui->fileBrowser->setSizePolicy(spLeft);

    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setHorizontalStretch(7);
    ui->tabWidget->setSizePolicy(spRight);

    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(0);
    qInfo() << ui->tabWidget;
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
        setWindowTitle(filename);
        QTextStream in(&file);
        QString text = in.readAll();
        QString name =
            filename.right(filename.size() - filename.lastIndexOf("/") - 1);
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), name);
        ui->tabWidget->setTabToolTip(ui->tabWidget->currentIndex(), filename);
        QTextEdit *mytextedit =
            qobject_cast<QTextEdit *>(ui->tabWidget->currentWidget());
        mytextedit->setText(text);
    }
}

void MainWindow::saveFile(const QString &filename) {
    QFile file(filename);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning",
                             "Cannot save file:" + file.errorString());
    } else {
        setWindowTitle(filename);
        QTextEdit *myText =
            qobject_cast<QTextEdit *>(ui->tabWidget->currentWidget());
        QString text = myText->toPlainText();
        QTextStream out(&file);
        out << text;
        file.close();
        QString name =
            filename.right(filename.size() - filename.lastIndexOf("/") - 1);
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), name);
        ui->tabWidget->setTabToolTip(ui->tabWidget->currentIndex(), filename);
    }
}

void MainWindow::on_actionOpen_triggered() {
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    openFile(filename);
}

void MainWindow::on_actionNew_triggered() {
    QTextEdit *mytext = new QTextEdit();
    ui->tabWidget->addTab(mytext, "untitled");
}

void MainWindow::on_actionSave_triggered() {
    if (ui->tabWidget->tabText(ui->tabWidget->currentIndex()) == "untitled") {
        QString filename = QFileDialog::getSaveFileName(this, "Save as");
        saveFile(filename);
    } else {
        qInfo() << ui->tabWidget->tabToolTip(ui->tabWidget->currentIndex());
        saveFile(ui->tabWidget->tabToolTip(ui->tabWidget->currentIndex()));
    }
}

void MainWindow::on_fileBrowser_doubleClicked(const QModelIndex &index) {
    if (QFileInfo(m_fileBrowserModel->filePath(index)).isFile()) {
        QString filename = m_fileBrowserModel->filePath(index);
        openFile(filename);
    }
}

void MainWindow::on_actionCopy_triggered() {
    QTextEdit *myText =
        qobject_cast<QTextEdit *>(ui->tabWidget->currentWidget());
    if (myText->hasFocus()) {
        myText->copy();
    }
}

void MainWindow::on_actionPaste_triggered() {
    QTextEdit *myText =
        qobject_cast<QTextEdit *>(ui->tabWidget->currentWidget());
    if (myText->hasFocus()) {
        myText->paste();
    }
}

void MainWindow::on_actionCut_triggered() {
    QTextEdit *myText =
        qobject_cast<QTextEdit *>(ui->tabWidget->currentWidget());
    if (myText->hasFocus()) {
        myText->cut();
    }
}

void MainWindow::on_actionUndo_triggered() {
    QTextEdit *myText =
        qobject_cast<QTextEdit *>(ui->tabWidget->currentWidget());
    if (myText->hasFocus()) {
        myText->undo();
    }
}

void MainWindow::on_actionRedo_triggered() {
    QTextEdit *myText =
        qobject_cast<QTextEdit *>(ui->tabWidget->currentWidget());
    if (myText->hasFocus()) {
        myText->redo();
    }
}

void MainWindow::slotShortcutAltCopy() { on_actionCopy_triggered(); }

void MainWindow::slotShortcutAltPaste() { on_actionPaste_triggered(); }

void MainWindow::slotShortcutAltCut() { on_actionCut_triggered(); }

void MainWindow::slotShortcutAltUndo() { on_actionUndo_triggered(); }

void MainWindow::slotShortcutAltRedo() { on_actionRedo_triggered(); }

void MainWindow::on_tabWidget_tabCloseRequested(int index) {
    ui->tabWidget->removeTab(index);
}
