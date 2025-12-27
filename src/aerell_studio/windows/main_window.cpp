#include <fstream>

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>

#include "aerell_studio/windows/main_window.h"

namespace AerellStudio
{

MainWindow::MainWindow()
{
    this->resize(800, 600);
    this->setWindowTitle("Aerell Studio");

    this->init();
}

void MainWindow::init()
{
    this->uiInit();
    this->logicInit();
}

void MainWindow::uiInit()
{
    // Menu bar
    this->menuBar = QMainWindow::menuBar();

    // Menu
    this->fileMenu = this->menuBar->addMenu("File");

    // Action
    this->openAction = this->fileMenu->addAction("Open");
    this->exitAction = this->fileMenu->addAction("Exit");

    // Widgets
    this->textEditorWidget = new TextEditorWidget(this);
    this->setCentralWidget(this->textEditorWidget);
}

void MainWindow::logicInit()
{
    this->connect(this->openAction, &QAction::triggered, this, &MainWindow::openFile);
    this->connect(this->exitAction, &QAction::triggered, this, &QWidget::close);
}

void MainWindow::openFile()
{
    auto fileName = QFileDialog::getOpenFileName(this, "Open file", ".");
    if(fileName.isEmpty()) return;
    std::ifstream file(fileName.toStdString());
    if(!file.is_open())
    {
        QMessageBox::information(this, "Info", "Can't not open file: " + fileName);
        return;
    }

    std::string fileContent{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};

    this->textEditorWidget->setPlainText(fileContent.c_str());
}

} // namespace AerellStudio