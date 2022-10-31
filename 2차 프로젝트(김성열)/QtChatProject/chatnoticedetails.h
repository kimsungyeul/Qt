#ifndef CHATNOTICEDETAILS_H
#define CHATNOTICEDETAILS_H

#include "qtreewidget.h"
#include <QWidget>

namespace Ui {
class ChatNoticeDetails;
}

class ChatNoticeDetails : public QWidget
{
    Q_OBJECT

public:
    explicit ChatNoticeDetails(QList<QTreeWidgetItem*>, QWidget *parent = nullptr);
    ~ChatNoticeDetails();

private:
    Ui::ChatNoticeDetails *ui;

    QList<QTreeWidgetItem*> chatList;
};

#endif // CHATNOTICEDETAILS_H
