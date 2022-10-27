#ifndef CHATSERVERADMIN_H
#define CHATSERVERADMIN_H

#include <QWidget>
#include "chatserver.h"

namespace Ui {
class ChatServerAdmin;
}

class ChatServerAdmin : public QWidget
{
    Q_OBJECT

public:
    explicit ChatServerAdmin(int = 0, QString = "", QWidget *parent = nullptr);
    ~ChatServerAdmin();

private:
    Ui::ChatServerAdmin *ui;

    int cid;
    QString cname;
};

#endif // CHATSERVERADMIN_H
