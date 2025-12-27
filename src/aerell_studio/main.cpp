#include <QApplication>

#include "aerell_studio/windows/main_window.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    auto window = AerellStudio::MainWindow();
    window.show();
    return app.exec();
}