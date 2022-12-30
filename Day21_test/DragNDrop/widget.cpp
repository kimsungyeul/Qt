#include "widget.h"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QDragEnterEvent>
#include <QMimeData>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setAcceptDrops(true);

    label = new QLabel("Hello World", this);
    lineEdit = new QLineEdit(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(lineEdit);
}

Widget::~Widget()
{
}

void Widget::dragEnterEvent(QDragEnterEvent* event)
{
    event->acceptProposedAction();
}

void Widget::dragMoveEvent(QDragMoveEvent* event)
{
    event->acceptProposedAction();
}

void Widget::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();
    QPixmap pixmap;
    label->clear();

    if (mimeData->hasUrls())
    {
        QList<QUrl> paths = mimeData->urls();
        foreach(QUrl path, paths) {
            lineEdit->setText(path.toLocalFile());
            pixmap.load(path.toLocalFile());

            if(!pixmap.isNull()) {
                label->setPixmap(pixmap);
            }
        }
    }
}
