#ifndef BOOKMARKFORM_H
#define BOOKMARKFORM_H

#include <DHorizontalLine>
#include <DPushButton>
#include "CustomListWidget.h"

#include <QMap>
#include <QThread>
#include <QVBoxLayout>

#include "CustomControl/CustomWidget.h"

/**
 * @brief The BookMarkWidget class
 * @brief   书签  列表数据
 */

class BookMarkWidget;

class LoadBookMarkThread : public QThread
{
    Q_OBJECT
    Q_DISABLE_COPY(LoadBookMarkThread)

public:
    explicit LoadBookMarkThread(QObject *parent = nullptr);

signals:
    void sigLoadImage(const int &, const QImage &);

public:
    inline void setBookMark(BookMarkWidget *bookMarkW) { m_pBookMarkWidget = bookMarkW; }

    inline void setBookMarks(const int &count) { m_bookMarks = count; }

    void stopThreadRun();

protected:
    void run() Q_DECL_OVERRIDE;

private:
    BookMarkWidget *m_pBookMarkWidget = nullptr;
    int m_bookMarks = 0;      // 书签总数
    int m_nStartIndex = 0;    // 加载图片起始位置
    int m_nEndIndex = 19;     // 加载图片结束位置
    bool m_isRunning = true;  // 运行状态
};

class BookMarkWidget : public CustomWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(BookMarkWidget)

public:
    explicit BookMarkWidget(CustomWidget *parent = nullptr);
    ~BookMarkWidget() Q_DECL_OVERRIDE;

    void prevPage();
    void nextPage();

signals:
    void sigFilePageChanged(const QString &);
    void sigOpenFileOk();
    void sigDeleteBookItem(const int &);
    void sigAddBookMark(const int &);
    void sigCloseFile();
    void sigDelBKItem();
    void sigCtrlBAddBookMark();
    void sigRightSelectItem(QString);

private slots:
    void slotAddBookMark();
    void slotAddBookMark(const int &);
    void slotOpenFileOk();
    void slotDocFilePageChanged(const QString &);
    void slotDeleteBookItem(const int &);
    void slotCloseFile();
    void slotLoadImage(const int &, const QImage &);
    void slotDelBkItem();
    void slotUpdateTheme();
    void slotRightSelectItem(QString);
    void slotSelectItemBackColor(QListWidgetItem *);

protected:
    void initWidget() Q_DECL_OVERRIDE;

private:
    void initConnection();
    QListWidgetItem *addBookMarkItem(const int &);
    void deleteIndexPage(const int &pageIndex);
    void clearItemColor();

public:
    // IObserver interface
    int dealWithData(const int &, const QString &) Q_DECL_OVERRIDE;
    int getBookMarkPage(const int &index);
    bool hasClickFoucs();

private:
    CustomListWidget *m_pBookMarkListWidget = nullptr;
    DPushButton *m_pAddBookMarkBtn = nullptr;
    LoadBookMarkThread m_loadBookMarkThread;
};

#endif  // BOOKMARKFORM_H
