#ifndef QSYSEVENTWIDGET_H
#define QSYSEVENTWIDGET_H

#include "qsyseventview.h"
#include "hnsyseventmodel.h"

namespace Ui {
class QSysEventWidget;
}

class QSysEventWidget : public QSysEventView
{
    Q_OBJECT

public:
    explicit QSysEventWidget(QWidget *parent = 0);
    ~QSysEventWidget();

private:
    Ui::QSysEventWidget *ui;
    QSqlDatabase m_db;
    HNSysEventModel* m_model;
};

#endif // QSYSEVENTWIDGET_H
