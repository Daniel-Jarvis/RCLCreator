#include "gui_utils.h"

#include <QTextBlock>

void resizePlainTextArea(QPlainTextEdit *textArea){
    QTextDocument* doc = textArea->document();
    QAbstractTextDocumentLayout* layout = doc->documentLayout();
    qreal height = 0;
    for (QTextBlock block = doc->begin(); block.isValid(); block = block.next()) {
        QRectF rect = layout->blockBoundingRect(block);
        height += rect.height();
    }

    // need to do this since 1. if the user hasn't entered anything there is still a minimum height. 2. the previous method somehow loses a line
    int lineHeight = textArea->fontMetrics().height();
    height = height < lineHeight ? lineHeight : height + lineHeight;

    textArea->setFixedHeight(height);
}
