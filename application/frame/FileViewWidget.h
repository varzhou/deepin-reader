#ifndef FILEVIEWWIDGET_H
#define FILEVIEWWIDGET_H

#include <QMouseEvent>
#include <QAction>
#include <DMenu>

#include "subjectObserver/CustomWidget.h"
#include "mainShow/DefaultOperationWidget.h"
#include "mainShow/TextOperationWidget.h"
#include "mainShow/FileAttrWidget.h"
#include "mainShow/FindWidget.h"
#include "mainShow/BookMarkStateLabel.h"

#include "docview/docummentproxy.h"

/**
 * @brief The FileViewWidget class
 * @brief   文档显示区域
 */

class FileViewWidget : public CustomWidget
{
    Q_OBJECT
public:
    FileViewWidget(CustomWidget *parent = nullptr);
    ~FileViewWidget() override;

signals:
    void sigOpenFile(const QString &);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void SlotCustomContextMenuRequested(const QPoint &);
    void openFilePath(const QString &);

private:
    int magnifying(const QString &);
    int setHandShape(const QString &);
    int screening(const QString &);
    int openFileFolder();
    void onShowFileAttr();
    void onShowFindWidget();
    void onOpenFile(const QString &filePath);

    void initConnections();

    void setBookMarkStateWidget();

private:
    BookMarkStateLabel      *m_pBookMarkStateWidgt = nullptr;
    FindWidget              *m_pFindWidget = nullptr;
    FileAttrWidget          *m_pFileAttrWidget = nullptr;
    DefaultOperationWidget  *m_pDefaultOperationWidget = nullptr;
    TextOperationWidget     *m_pTextOperationWidget = nullptr;
    DocummentProxy          *m_pDocummentProxy = nullptr;

    // CustomWidget interface
protected:
    void initWidget() override;

    // IObserver interface
public:
    int dealWithData(const int &, const QString &) override;
};


#endif // FILEVIEWWIDGET_H