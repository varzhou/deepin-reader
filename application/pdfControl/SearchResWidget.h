#ifndef SEARCHRESWIDGET_H
#define SEARCHRESWIDGET_H

#include <DListWidget>

#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QThread>

#include "translator/Frame.h"
#include "NotesItemWidget.h"
#include "subjectObserver/CustomWidget.h"
#include "docview/docummentproxy.h"
#include "CustomListWidget.h"

/**
 * @brief The ThumbnailItemWidget class
 * @brief   搜索结果显示窗体
 */

class SearchResWidget;

class LoadSearchResThread : public QThread
{
    Q_OBJECT
public:
    LoadSearchResThread(QObject *parent = nullptr);

signals:
    void signal_loadImage(int, QImage);

public:
    inline void setSearchResW(SearchResWidget *searchResW)
    {
        m_pSearchResWidget = searchResW;
    }

    inline void setRunning(const bool &state)
    {
        m_isRunning = state;
    }

    inline void setPages(const int &pages)
    {
        m_pages = pages;
    }

    void stopThread();

protected:
    void run() override;

private:
    SearchResWidget *m_pSearchResWidget = nullptr;
    bool m_isRunning                    = false;
    int m_nStartIndex                   = 0;      //　每次加载开始页
    int m_nEndIndex                     = 19;     //　每次加载结束页
    int m_pages                         = -1;     //  搜索内容总页数
};

class SearchResWidget : public CustomWidget
{
    Q_OBJECT

public:
    SearchResWidget(CustomWidget *parent = nullptr);
    ~SearchResWidget() override;

signals:
    void sigFlushSearchWidget(QVariant);
    void sigClearWidget();
    void sigCloseFile();

private slots:
    void slotFlushSearchList(QVariant);
    void slotClearWidget();
    void slotCloseFile();
    void slot_loadImage(int, QImage);

protected:
    void initWidget() override;

private:
    void initConnections();

private:
    void addNotesItem(const int &page, const QString &text, const int &resultNum);

private:
    CustomListWidget *m_pNotesList            = nullptr;
    NotesItemWidget *m_pSearchItemWidget = nullptr;
    LoadSearchResThread m_loadSearchResThread;

public:
    // IObserver interface
    int dealWithData(const int &, const QString &) override;
    int getSearchPage(const int &);
    int setSearchItemImage(const QImage &);
};

#endif // NOTESFORM_H
