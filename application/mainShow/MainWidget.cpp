#include "MainWidget.h"
#include <DDesktopServices>
#include <QDebug>

#include "controller/DataManager.h"

MainWidget::MainWidget(CustomWidget *parent):
    CustomWidget ("MainWidget", parent)
{
    m_centralLayout = new QVBoxLayout();

    // Init layout and editor.
    m_centralLayout->setMargin(0);
    m_centralLayout->setSpacing(0);

    this->setLayout(m_centralLayout);

    initWidget();
}

MainWidget::~MainWidget()
{
    if (m_pAttrWidget) {
        m_pAttrWidget->deleteLater();
        m_pAttrWidget = nullptr;
    }
}

void MainWidget::initWidget()
{
    m_pFindBar = new FindBar(this);
    DAnchors<FindBar> anchors_findbar(m_pFindBar);
    anchors_findbar.setAnchor(Qt::AnchorTop, this, Qt::AnchorTop);
    anchors_findbar.setAnchor(Qt::AnchorRight, this, Qt::AnchorRight);
    anchors_findbar.setTopMargin(10);
    anchors_findbar.setRightMargin(10);
//    m_pFindBar->raise();

    m_pStackedWidget = new DStackedWidget;
    m_centralLayout->addWidget(m_pStackedWidget);

    m_pHomeWidget = new  HomeWidget;
    connect(m_pHomeWidget, SIGNAL(fileSelected(const QStringList)), this, SLOT(showFileSelected(const QStringList)));
    m_pStackedWidget->addWidget(m_pHomeWidget);

    m_pMainShowSplitter = new MainShowSplitter;
    m_pStackedWidget->addWidget(m_pMainShowSplitter);

    m_pStackedWidget->setCurrentIndex(0);
}

//  open file
void MainWidget::showFileSelected(const QStringList files)
{
    int nSize = files.count();
    QString filePath = files.at(0);

    //  判断文件 是否有损坏

    DataManager::instance()->setStrOnlyFilePath(filePath);

    sendMsg(MSG_OPEN_FILE_PATH, filePath);
    //  open  file
    m_pStackedWidget->setCurrentIndex(1);
}

//  打开文件所在文件夹
void MainWidget::openFileFolder()
{
    QString strFilePath = DataManager::instance()->strOnlyFilePath();
    if (strFilePath != "") {
        int nLastPos = strFilePath.lastIndexOf('/');
        strFilePath = strFilePath.mid(0, nLastPos);
        DDesktopServices::showFolder(strFilePath);
    }
}

//  查看 文件属性
void MainWidget::showFileAttr()
{
    if (m_pAttrWidget == nullptr) {
        m_pAttrWidget = new FileAttrWidget();
    }
    m_pAttrWidget->show();
}

int MainWidget::dealWithData(const int &msgType, const QString &msgContent)
{
    Q_UNUSED(msgContent);

    if (msgType == MSG_OPERATION_ATTR) {
        showFileAttr();
        return ConstantMsg::g_effective_res;
    }

    if (msgType == MSG_OPERATION_OPEN_FOLDER) {
        openFileFolder();
        return ConstantMsg::g_effective_res;
    }

    if (msgType == MSG_OPERATION_FIND) {
        m_pFindBar->show();

        QTimer::singleShot(10, this, [ = ] { m_pFindBar->focus(); });
        return ConstantMsg::g_effective_res;
    }
    return 0;
}

