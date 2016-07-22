#include "qdebugwidget.h"
#include "ui_qdebugwidget.h"

QDebugWidget::QDebugWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QDebugWidget)
{
    ui->setupUi(this);
}

QDebugWidget::~QDebugWidget()
{
    delete ui;
}

void QDebugWidget::slotRecvMsg(QByteArray msg)
{
    QString buf;
    for(int i = 0; i < msg.count(); i++){
        QString s;
        s.sprintf("%d ", (unsigned char)msg.at(i));
        buf += s;
    }
    ui->txtBrower->clear();
    ui->txtBrower->append(buf);
}
