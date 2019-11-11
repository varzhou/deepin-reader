#include "TextOperationMenu.h"
#include "ColorWidgetAction.h"
#include "subjectObserver/MsgHeader.h"
#include "controller/MsgSubject.h"
#include "controller/NotifySubject.h"
#include "docview/docummentproxy.h"
#include "controller/DataManager.h"
#include "subjectObserver/ModuleHeader.h"
#include "application.h"

TextOperationMenu::TextOperationMenu(DWidget *parent)
    : DMenu (parent)
{
    initMenu();
}

void TextOperationMenu::execMenu(const QPoint &showPoint, const bool &bHigh, const QString &sSelectText, const QString &sUuid)
{
    QList<int> pageList = dApp->dbM->getBookMarkList();
    bool bBookState = pageList.contains(m_nClickPage);
    m_pAddBookMark->setEnabled(!bBookState);

    m_strSelectText = sSelectText;
    if (m_strSelectText == "") {
        m_pCopy->setEnabled(false);
    } else {
        m_pCopy->setEnabled(true);
    }

    m_strNoteUuid = sUuid;
    m_pRemoveHighLight->setEnabled(bHigh);

    m_pColorWidgetAction->setBtnAddLightState(bHigh);

    this->exec(showPoint);
}

void TextOperationMenu::setClickPoint(const QPoint &clickPoint)
{
    m_pClickPoint = clickPoint;
}

void TextOperationMenu::setClickPage(int nClickPage)
{
    m_nClickPage = nClickPage;
}

void TextOperationMenu::initMenu()
{
    QFont font;
    font.setPixelSize(14);
    setFont(font);
    m_pCopy = createAction(tr("copy"), SLOT(slotCopyClicked()));
    this->addSeparator();

    m_pColorWidgetAction = new ColorWidgetAction(this);
    connect(m_pColorWidgetAction, SIGNAL(sigBtnGroupClicked(int)), this, SLOT(slotSetHighLight(int)));
    connect(m_pColorWidgetAction, SIGNAL(sigBtnDefaultClicked()), this, SLOT(slotAddHighLightClicked()));
    this->addAction(m_pColorWidgetAction);
    this->addSeparator();

    m_pRemoveHighLight = createAction(tr("remove high light"), SLOT(slotRemoveHighLightClicked()));
    this->addSeparator();

    createAction(tr("add note"), SLOT(slotAddNoteClicked()));
    this->addSeparator();

    m_pAddBookMark = createAction(tr("add bookmark"), SLOT(slotAddBookMarkClicked()));
}

QAction *TextOperationMenu::createAction(const QString &text, const char *member)
{
    auto action = new  QAction(QString("       %1").arg(text), this);
    connect(action, SIGNAL(triggered()), member);
    this->addAction(action);

    return action;
}

void TextOperationMenu::sendMsgToFrame(const int &msgType, const QString &msgContent)
{
    MsgSubject::getInstance()->sendMsg(msgType, msgContent);
    this->hide();
}

void TextOperationMenu::notifyMsgToFrame(const int &msgType, const QString &msgContent)
{
    NotifySubject::getInstance()->notifyMsg(msgType, msgContent);
    this->hide();
}

void TextOperationMenu::slotSetHighLight(int nColor)
{
    m_pLightColor = nColor;

    bool bEnable = m_pRemoveHighLight->isEnabled();
    if (bEnable) {  //  移除高亮可以点,说明已有高亮, 点击操作 是 更新高亮
        sendMsgToFrame(MSG_OPERATION_TEXT_UPDATE_HIGHLIGHTED, QString("%1,%2,%3").arg(m_pLightColor).arg(m_strNoteUuid).arg(m_nClickPage));
    } else {    //  移除高亮不可点,说明没有高亮, 点击操作 是 添加高亮
        sendMsgToFrame(MSG_OPERATION_TEXT_ADD_HIGHLIGHTED, QString("%1,%2,%3").arg(m_pLightColor).arg(m_pClickPoint.x()).arg(m_pClickPoint.y()));
    }
}

void TextOperationMenu::slotCopyClicked()
{
    notifyMsgToFrame(MSG_OPERATION_TEXT_COPY, m_strSelectText);
}

void TextOperationMenu::slotAddHighLightClicked()
{
    sendMsgToFrame(MSG_OPERATION_TEXT_ADD_HIGHLIGHTED, QString("%1,%2,%3").arg(m_pLightColor).arg(m_pClickPoint.x()).arg(m_pClickPoint.y()));
}

void TextOperationMenu::slotRemoveHighLightClicked()
{
    sendMsgToFrame(MSG_OPERATION_TEXT_REMOVE_HIGHLIGHTED, QString("%1,%2").arg(m_pClickPoint.x()).arg(m_pClickPoint.y()));
}

void TextOperationMenu::slotAddNoteClicked()
{
    if (m_strNoteUuid == "") {
        QString msgContent = QString("%1").arg(m_nClickPage) + Constant::sQStringSep + QString("%1").arg(m_pClickPoint.x()) + Constant::sQStringSep + QString("%1").arg(m_pClickPoint.y());
        notifyMsgToFrame(MSG_OPERATION_TEXT_ADD_ANNOTATION, msgContent);
    } else {
        QString t_strContant = m_strNoteUuid.trimmed() + QString("%1%") + QString::number(m_nClickPage);
        notifyMsgToFrame(MSG_OPERATION_TEXT_SHOW_NOTEWIDGET, t_strContant);
    }
}

void TextOperationMenu::slotAddBookMarkClicked()
{
    sendMsgToFrame(MSG_OPERATION_TEXT_ADD_BOOKMARK, QString("%1").arg(m_nClickPage));
}
