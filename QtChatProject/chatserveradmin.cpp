#include "chatserveradmin.h"
#include "ui_chatserveradmin.h"

ChatServerAdmin::ChatServerAdmin(int cid, QString cname, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatServerAdmin)
{
    ui->setupUi(this);
    qDebug() << cid << ", "<< cname;
}

ChatServerAdmin::~ChatServerAdmin()
{
    delete ui;
}
