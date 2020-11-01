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

QTextEdit *MainWindow::addTab(const QString &filename) {
    QTextEdit *newTab = new QTextEdit();

    newTab->setToolTip(filename);
    ui->tabWidget->addTab(newTab, filename);
    ui->tabWidget->setCurrentWidget(newTab);

    return newTab;
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

void MainWindow::openFile(const QString &filePath) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning",
                             "Cannot open file:" + file.errorString());
    } else {
        QString fileText = file.readAll();
        QString fileName =
            filePath.right(filePath.size() - filePath.lastIndexOf("/") - 1);
        auto newTab = addTab(fileName);
        ui->tabWidget->setTabToolTip(ui->tabWidget->currentIndex(), filePath);
        newTab->setText(fileText);
    }
}

void MainWindow::saveFile(const QString &filePath) {
    if (filePath.isNull() || filePath.isEmpty()) {
        return;
    }
    QFile file(filePath);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning",
                             "Cannot save file:" + file.errorString());
    } else {
        QTextEdit *currentTab =
            qobject_cast<QTextEdit *>(ui->tabWidget->currentWidget());
        QString fileText = currentTab->toPlainText();
        QString name =
                   filePath.right(filePath.size() - filePath.lastIndexOf("/") - 1);
        ui->tabWidget->setTabToolTip(ui->tabWidget->currentIndex(), filePath);
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), name);
        QTextStream out(&file);

        out << fileText;
        file.close();
    }
}

void MainWindow::on_actionOpen_triggered() {
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");

    if (!filename.isEmpty()) {
        openFile(filename);
    }
}

void MainWindow::on_actionNew_triggered() { addTab("untitled"); }

void MainWindow::on_actionSave_triggered() {
    QTextEdit *currentTab =
        qobject_cast<QTextEdit *>(ui->tabWidget->currentWidget());

    if (!currentTab) {
        return;
    }

    if (currentTab->toolTip() == "untitled") {
        QString filename = QFileDialog::getSaveFileName(this, "Save as");
        saveFile(filename);
    } else {
        qInfo() << currentTab->toolTip();
        saveFile(currentTab->toolTip());
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

void MainWindow::keyPressEvent(QKeyEvent *pe) {
    auto currentTab = ui->tabWidget->currentWidget();

    if (pe->modifiers() & Qt::CTRL) {
        switch (pe->key()) {
        case Qt::Key_W:
            ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
            break;
        case Qt::Key_S:
            on_actionSave_triggered();
            break;
        case Qt::Key_T:
            on_actionNew_triggered();
            break;
        default:
            break;
        }
    }
}

void MainWindow::on_actionfind_and_replace_triggered()
{
    if(ui->tabWidget->count() > 0) {
    QString find;
    QString replace;
    QDialog dialog(this);
    QFormLayout form(&dialog);

    QLineEdit *findEdit = new QLineEdit(&dialog);
    QString label = QString("Find");
    form.addRow(label, findEdit);

    QLineEdit *replaceEdit = new QLineEdit(&dialog);
    label = QString("Replace");
    form.addRow(label, replaceEdit);
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted) {
        find = findEdit->text();
        replace = replaceEdit->text();
    }

    QTextEdit *myText =
        qobject_cast<QTextEdit *>(ui->tabWidget->currentWidget());
    QString text = myText->toPlainText();
    text.replace(find, replace);
    myText->setText(text);
    }
}
