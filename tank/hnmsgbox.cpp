#include "hnmsgbox.h"
#include "ui_hnmsgbox.h"

HNMsgBox::HNMsgBox(QWidget *parent) :
    QCDialog(parent),
    ui(new Ui::HNMsgBox)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);
    connect(ui->btn_yes, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->btn_yes2, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->btn_no, SIGNAL(clicked()), this, SLOT(reject()));
}

HNMsgBox::~HNMsgBox()
{
    delete ui;
}

int HNMsgBox::warning(QWidget *parent, QString content )
{
    HNMsgBox* msgBox = new HNMsgBox(parent);
    return msgBox->_warning(content);
}

int HNMsgBox::tips(QWidget *parent, QString content)
{
    HNMsgBox* msgBox = new HNMsgBox(parent);
    return msgBox->_tips(content);
}

int HNMsgBox::_warning(QString content)
{
    ui->lb_content->setText(content);
    ui->stwBtn->setCurrentIndex(1);
    return exec();
}

int HNMsgBox::_tips(QString content)
{
    ui->lb_content->setText(content);
    ui->stwBtn->setCurrentIndex(0);
    return exec();
}