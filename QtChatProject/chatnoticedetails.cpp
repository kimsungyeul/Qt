#include "chatnoticedetails.h"
#include "ui_chatnoticedetails.h"

ChatNoticeDetails::ChatNoticeDetails(QList<QTreeWidgetItem*> chatlist, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatNoticeDetails)
{
    ui->setupUi(this);
    QList<int> sizes;
    sizes << 150 << 650;
    ui->Nsplitter->setSizes(sizes);
}

ChatNoticeDetails::~ChatNoticeDetails()
{
    delete ui;
}
