#ifndef THUMBNAILITEMWIDGET_H
#define THUMBNAILITEMWIDGET_H
#include <DWidget>
#include <DLabel>
#include <QVBoxLayout>
#include <QPainter>

#include "header/CustomWidget.h"
#include "header/MsgHeader.h"

DWIDGET_USE_NAMESPACE

/**
 * @brief The ThumbnailItemWidget class
 * @brief   缩略图中的item
 */
class ThumbnailItemWidget  : public CustomWidget
{
    Q_OBJECT
public:
    ThumbnailItemWidget(CustomWidget *parent = nullptr);

public:
    // IObserver interface
    int update(const int &, const QString &) override;
    void setContantLabelPixmap(const QString &);
    void setPageLabelText(const QString &);

    inline DWidget   *getSonWidget()
    {
        if (m_sonWidget != nullptr) {
            return m_sonWidget;
        } else {
            return nullptr;
        }
    }

    inline DLabel   *getPageLabel()
    {
        if (m_pPageLabel != nullptr) {
            return m_pPageLabel;
        } else {
            return nullptr;
        }
    }

    void setPaint(const bool &paint)
    {
        m_bPaint = paint;
    }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void initWidget();

private:
    DLabel *m_pContantLabel = nullptr;
    DLabel *m_pPageLabel = nullptr;
    DWidget *m_sonWidget = nullptr;
    QVBoxLayout *m_pVLayout = nullptr;
    bool m_bPaint = false;
};

#endif // THUMBNAILITEMWIDGET_H