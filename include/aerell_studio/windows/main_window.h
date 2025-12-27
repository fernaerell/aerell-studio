#pragma once

#include "aerell_studio/widgets/text_editor_widget.h"
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

namespace AerellStudio
{

class MainWindow : public QMainWindow
{
  public:
    MainWindow();

  private:
    QMenuBar* menuBar = nullptr;
    QMenu* fileMenu = nullptr;
    QAction* openAction = nullptr;
    QAction* exitAction = nullptr;

    TextEditorWidget* textEditorWidget = nullptr;

    void init();
    void uiInit();
    void logicInit();

    // Action
    void openFile();
};

} // namespace AerellStudio