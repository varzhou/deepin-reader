#ifndef FILEATTRWIDGET_H
#define FILEATTRWIDGET_H

#include <DLabel>
#include <QGridLayout>
#include <QList>

#include "subjectObserver/CustomWidget.h"


/**
 * @brief The FileAttrWidget class
 * @brief   文件属性框
 */

class FileAttrWidget : public CustomWidget
{
    Q_OBJECT
public:
    FileAttrWidget(CustomWidget *parent = nullptr);

public:
    void setFileAttr();

private:
    void initLabels();
    void createLabel(const int &, const QString &);

private:
    QGridLayout *m_pGridLayout = nullptr;
    QList<DLabel *> m_labelList;

    // CustomWidget interface
protected:
    void initWidget() override;

    // IObserver interface
public:
    int dealWithData(const int &, const QString &) override;
};

#endif // FILEATTRWIDGET_H