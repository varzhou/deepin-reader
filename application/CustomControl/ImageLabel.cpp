#include "ImageLabel.h"
#include <QPainter>

ImageLabel::ImageLabel(DWidget *parent)
    : DLabel (parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
}

void ImageLabel::setSelect(const bool &select)
{
    m_bSelect = select;
    update();
}

void ImageLabel::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    DLabel::paintEvent(e);
    qreal local = 0;
    qreal width = 0;
    qreal heigh = 0;

    QPainter painter(this);
    painter.setOpacity(1.0);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(Qt::NoBrush);

    if (m_bSelect) {
        local = 1;
        width = this->width() - 2;
        heigh = this->height() - 2;

        painter.setPen(QPen(QColor(QString("#0081FF")), 3, Qt::SolidLine));
    } else {
        local = 0;
        width = this->width() - 0;
        heigh = this->height() - 0;
        painter.setPen(QPen(QColor::fromRgbF(0,0,0,0.05), 1, Qt::SolidLine));
    }
    QRectF rectangle(local, local, width, heigh);

    painter.drawRoundedRect(rectangle, 8, 8);

    DLabel::paintEvent(e);
}
