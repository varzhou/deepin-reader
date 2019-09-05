#ifndef TEXTOPERATIONWIDGET_H
#define TEXTOPERATIONWIDGET_H

#include "subjectObserver/CustomWidget.h"

#include "LightedWidget.h"

#include <QVBoxLayout>
#include <DPushButton>

/**
 * @brief The DefaultOperationWidget class
 * @brief   右键  文本菜单操作， 复制、高亮显示、移除高亮显示、添加注释、添加书签
 */


class TextOperationWidget : public CustomWidget
{
    Q_OBJECT
public:
    TextOperationWidget(CustomWidget *parent = nullptr);

private:
    void createBtn(const QString &, const char *member);

private slots:
    void SlotBtnCopyClicked();
    void SlotBtnRemoveHighLightedClicked();
    void SlotBtnAddAnnotationClicked();
    void SlotBtnAddBookMarkClicked();

private:
    void sendMsgAndHide(const int &);

private:
    QVBoxLayout *layout = nullptr;
    LightedWidget   *m_pLightedWidget = nullptr;

    // IObserver interface
public:
    int dealWithData(const int &, const QString &) override;

    // CustomWidget interface
protected:
    void initWidget() override;
};

#endif // DEFAULTOPERATIONWIDGET_H