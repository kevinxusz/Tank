#ifndef QPREVIEWUI_H
#define QPREVIEWUI_H

#include "qtankgui.h"
#include "qtanklinux.h"
#include "qtankdefine.h"
#include "qtankpublic.h"

namespace Ui {
class QPreviewUI;
}

class QPreviewUI : public QWidget
{
    Q_OBJECT

public:
    explicit QPreviewUI(QWidget *parent = 0);
    ~QPreviewUI();
    int play();
    int close();

private:
    Ui::QPreviewUI *ui;

    struct sensor_info sinfo;
    int pre_bpp;
    int rate;	      /* default to 15fps  */
    unsigned int addr;
    unsigned int phys;

    int fd;
    int format;

    struct camera_memory pre_memory;
    struct camera_buffer pre_buf;
    struct frm_size pre_size;
    unsigned int tlb_base_phys;

    uchar *pp;
    uchar * p;
    QImage *frame;
    QTimer *timer;

    bool bFullScreen;
    QWidget* m_parent;
    QRect geome;
    Qt::WindowFlags flags;

    int convert_yuv_to_rgb_pixel(int y, int u, int v);
    int convert_yuv_to_rgb_buffer(unsigned char *yuv, unsigned char *rgb, unsigned int width, unsigned int height);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
};

#endif // QPREVIEWUI_H
