#pragma once

#include <QWidget>
#include <QPlainTextEdit>
#include <QPaintEvent>

namespace AerellStudio
{

class TextEditorWidget : public QPlainTextEdit
{
  public:
    TextEditorWidget(QWidget* parent);

    void lineNumberAreaPaintEvent(QPainter* painter, QPaintEvent* event);

  private:
    int lineNumberAreaPaddingRight = 10;
    int lineNumberAreaPaddingLeft = 10;
    QWidget* lineNumberAreaWidget = nullptr;

    void init();
    void uiInit();
    void logicInit();

    // Get
    int getLineNumberAreaWidth();
    int getLineNumberAreaPaddingX();

    // Update
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect& rect, int dy);

    // Event
    void resizeEvent(QResizeEvent* event) override;
};

class LineNumberArea : public QWidget
{
  public:
    LineNumberArea(TextEditorWidget* textEditorWidget);

  protected:
    void paintEvent(QPaintEvent* event) override;

  private:
    TextEditorWidget* textEditorWidget = nullptr;
};

} // namespace AerellStudio