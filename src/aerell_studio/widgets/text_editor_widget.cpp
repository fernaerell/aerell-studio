#include "aerell_studio/widgets/text_editor_widget.h"

#include <QTextBlock>
#include <QPainter>
#include <qminmax.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qpoint.h>

namespace AerellStudio
{

TextEditorWidget::TextEditorWidget(QWidget* parent) : QPlainTextEdit(parent)
{
    this->setWordWrapMode(QTextOption::NoWrap);
    this->setCenterOnScroll(false);
    this->setUndoRedoEnabled(false);
    this->init();
}

void TextEditorWidget::lineNumberAreaPaintEvent(QPainter* painter, QPaintEvent* event)
{
    // Get first text block visible on screen
    QTextBlock block = this->firstVisibleBlock();
    // Get number of block
    int blockNumber = block.blockNumber();
    // Get top/y position of first block sync with content offset top/y
    int top = (int)this->blockBoundingGeometry(block).translated(this->contentOffset()).top();
    // Get last bottom/y position number of first block
    int bottom = top + (int)this->blockBoundingRect(block).height();

    // Get top/y position of line number area rect top
    int lineNumberAreaRectTop = event->rect().top();
    // Get bottom/y position of line number area rect bottom
    int lineNumberAreaRectBottom = event->rect().bottom();

    int fontHeight = this->fontMetrics().height();

    // Loop each block can see in viewport
    while(block.isValid() && top <= lineNumberAreaRectBottom)
    {
        if(block.isVisible() && bottom >= lineNumberAreaRectTop)
        {
            painter->setPen(Qt::white);
            // Draw the line number
            painter->drawText(
                this->lineNumberAreaPaddingLeft, top,
                this->lineNumberAreaWidget->width() - this->getLineNumberAreaPaddingX(), fontHeight,
                Qt::AlignRight | Qt::AlignVCenter, QString::number(blockNumber + 1));
        }

        block = block.next();
        top = bottom;
        bottom = top + fontHeight;
        ++blockNumber;
    }
}

void TextEditorWidget::init()
{
    this->uiInit();
    this->logicInit();
}

void TextEditorWidget::uiInit()
{
    this->lineNumberAreaWidget = new LineNumberArea(this);
    this->updateLineNumberAreaWidth(0);
}

void TextEditorWidget::logicInit()
{
    this->connect(this, &TextEditorWidget::blockCountChanged, this, &TextEditorWidget::updateLineNumberAreaWidth);
    this->connect(this, &TextEditorWidget::updateRequest, this, &TextEditorWidget::updateLineNumberArea);
}

int TextEditorWidget::getLineNumberAreaWidth()
{
    int digits = 1;
    int maxLines = qMax(1, this->blockCount());

    // Formula for find digit of number with maxline
    while(maxLines >= 10)
    {
        maxLines /= 10;
        digits++;
    }

    // Reserve size for 3 digits
    if(digits < 3) digits = 3;

    // Get width of char 9, the widest number in monospaced font
    // horizontalAdvance return width in pixel
    int charWidth = this->fontMetrics().horizontalAdvance(QLatin1Char('9'));

    // Formula (char width * digits)
    return this->getLineNumberAreaPaddingX() + (charWidth * digits);
}

int TextEditorWidget::getLineNumberAreaPaddingX()
{
    return this->lineNumberAreaPaddingLeft + this->lineNumberAreaPaddingRight;
}

void TextEditorWidget::updateLineNumberAreaWidth([[maybe_unused]] int newBlockCount)
{
    int width = this->getLineNumberAreaWidth();

    // Shift margin area of text sync with line number area width
    this->setViewportMargins(width, 0, 0, 0);

    QRect rect = this->lineNumberAreaWidget->rect();

    this->lineNumberAreaWidget->update(0, rect.y(), width, rect.height());
}

void TextEditorWidget::updateLineNumberArea(const QRect& rect, int dy)
{
    if(dy != 0) this->lineNumberAreaWidget->scroll(0, dy);
    else
        this->lineNumberAreaWidget->update(0, rect.y(), this->lineNumberAreaWidget->width(), rect.height());

    if(rect.contains(this->viewport()->rect())) this->updateLineNumberAreaWidth(0);
}

void TextEditorWidget::resizeEvent(QResizeEvent* event)
{
    QPlainTextEdit::resizeEvent(event);

    // Get size of text editor area
    QRect cr = this->contentsRect();

    // Set size area of line number widget
    this->lineNumberAreaWidget->setGeometry(QRect(cr.left(), cr.top(), this->getLineNumberAreaWidth(), cr.height()));
}

LineNumberArea::LineNumberArea(TextEditorWidget* textEditorWidget)
    : QWidget(textEditorWidget), textEditorWidget(textEditorWidget)
{
}

void LineNumberArea::paintEvent(QPaintEvent* event) { 
    QPainter painter(this);
    this->textEditorWidget->lineNumberAreaPaintEvent(&painter, event); 
}

} // namespace AerellStudio