/*
 * Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     duanxiaohui
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "PagingWidget.h"

#include <QValidator>

#include "docview/docummentproxy.h"

#include "CentralDocPage.h"
#include "DocSheet.h"

PagingWidget::PagingWidget(DocSheet *sheet, DWidget *parent)
    : CustomWidget(PAGE_WIDGET, parent), m_sheet(sheet)
{
    initWidget();

    slotUpdateTheme();

    dApp->m_pModelService->addObserver(this);
}

PagingWidget::~PagingWidget()
{
    dApp->m_pModelService->removeObserver(this);
}

/**
 * @brief PagingWidget::initWidget
 * 初始化界面
 */
void PagingWidget::initWidget()
{
    m_pTotalPagesLab = new CustomClickLabel(QString("/xxx"));
    DFontSizeManager::instance()->bind(m_pTotalPagesLab, DFontSizeManager::T6);
    m_pTotalPagesLab->setForegroundRole(DPalette::Text);

    int tW = 36;
    int tH = 36;
//    dApp->adaptScreenView(tW, tH);
    m_pPrePageBtn = new DIconButton(DStyle::SP_ArrowLeft);
    m_pPrePageBtn->setFixedSize(QSize(tW, tH));
    connect(m_pPrePageBtn, SIGNAL(clicked()), SLOT(slotPrePageBtnClicked()));

    m_pNextPageBtn = new DIconButton(DStyle::SP_ArrowRight);
    m_pNextPageBtn->setFixedSize(QSize(tW, tH));
    connect(m_pNextPageBtn, SIGNAL(clicked()), SLOT(slotNextPageBtnClicked()));

    m_pJumpPageLineEdit = new DLineEdit();
    tW = 60;
    tH = 36;
//    dApp->adaptScreenView(tW, tH);
    m_pJumpPageLineEdit->setFixedSize(tW, tH);
    connect(m_pJumpPageLineEdit, SIGNAL(returnPressed()), SLOT(SlotJumpPageLineEditReturnPressed()));
    m_pJumpPageLineEdit->setClearButtonEnabled(false);
    DFontSizeManager::instance()->bind(m_pJumpPageLineEdit, DFontSizeManager::T6);
    m_pJumpPageLineEdit->setForegroundRole(DPalette::Text);

    m_pCurrantPageLab = new CustomClickLabel("");
    DFontSizeManager::instance()->bind(m_pCurrantPageLab, DFontSizeManager::T6);
    m_pCurrantPageLab->setForegroundRole(DPalette::Text);

    auto hLayout = new QHBoxLayout;
    hLayout->setContentsMargins(10, 6, 10, 6);
    hLayout->addWidget(m_pJumpPageLineEdit);
    hLayout->addSpacing(5);

    hLayout->addWidget(m_pCurrantPageLab);
    hLayout->addWidget(m_pTotalPagesLab);
    hLayout->addStretch(1);
    hLayout->addWidget(m_pPrePageBtn);
    hLayout->addWidget(m_pNextPageBtn);

    this->setLayout(hLayout);
}

/**
 * @brief PagingWidget::dealWithData
 * 处理全局消息接口
 * @param msgType
 * @return
 */
int PagingWidget::dealWithData(const int &msgType, const QString &msgContent)
{
    if (msgType == MSG_OPERATION_UPDATE_THEME) {    //  颜色主题切换
        slotUpdateTheme();
    } else if (msgType == MSG_FILE_PAGE_CHANGE) {                  //  文档页变化了
        OnDocFilePageChange(msgContent);
    }

    return MSG_NO_OK;
}

void PagingWidget::slotUpdateTheme()
{
    if (m_pTotalPagesLab) {
        m_pTotalPagesLab->setForegroundRole(DPalette::Text);
    }

    if (m_pCurrantPageLab) {
        m_pCurrantPageLab->setForegroundRole(DPalette::Text);
    }
}

void PagingWidget::__SetBtnState(const int &currntPage, const int &totalPage)
{
    if (currntPage == 1) {                  //  第一页
        m_pPrePageBtn->setEnabled(false);
        if (totalPage == 1) {               //  也是最后一页
            m_pNextPageBtn->setEnabled(false);
        } else {
            m_pNextPageBtn->setEnabled(true);
        }
    } else if (currntPage == totalPage) {   //    最后一页
        m_pPrePageBtn->setEnabled(true);
        m_pNextPageBtn->setEnabled(false);
    } else {                                //  中间页
        m_pPrePageBtn->setEnabled(true);
        m_pNextPageBtn->setEnabled(true);
    }
}

void PagingWidget::OnDocFilePageChange(const QString &msgContent)
{
    if (nullptr == m_sheet)
        return;

    DocummentProxy *_proxy = m_sheet->getDocProxy();

    if (_proxy) {
        int totalPage = _proxy->getPageSNum();

        int inputData = msgContent.toInt();

        int currntPage = inputData + 1;     //  + 1 是为了 数字 从1 开始显示
        __SetBtnState(currntPage, totalPage);

        if (m_pCurrantPageLab) {
            m_pCurrantPageLab->setText(QString::number(currntPage));

            QString sPage = _proxy->pagenum2label(inputData);

            m_pJumpPageLineEdit->setText(sPage);
        } else {
            m_pJumpPageLineEdit->setText(QString::number(currntPage));
        }
    }
}

/**
 * 文档打开成功
 * 1. 进行控件初始化
 * 2.设置总页数 和 当前页码
 *
 */
void PagingWidget::handleOpenSuccess()
{
    if (nullptr == m_sheet)
        return;

    DocummentProxy *_proxy = m_sheet->getDocProxy();

    if (_proxy) {
        bool isHasLabel = _proxy->haslabel();
        if (!isHasLabel) {
            delete m_pCurrantPageLab;
            m_pCurrantPageLab =  nullptr;
        }

        int totalPage = _proxy->getPageSNum();

        if (m_pCurrantPageLab == nullptr) {   //  不可读取页码, 则设置只能输入大于 0 的数字
            //  m_pJumpPageLineEdit->lineEdit()->setValidator(new QIntValidator(1, totalPage, this));
        }

        m_pTotalPagesLab->setText(QString("/ %1").arg(totalPage));

        int nCurPage = _proxy->currentPageNo();

        OnDocFilePageChange(QString::number(nCurPage));
    }
}

//  输入框  敲回车键 响应
void PagingWidget::SlotJumpPageLineEditReturnPressed()
{
    if (m_pCurrantPageLab == nullptr) {
        __NormalChangePage();
    } else {
        __PageNumberJump();
    }
}

void PagingWidget::__NormalChangePage()
{
    DocummentProxy *_proxy =  CentralDocPage::Instance()->getCurFileAndProxy(m_strBindPath);
    QString sText = m_pJumpPageLineEdit->text();
    int iPage = sText.toInt();
    if (iPage <= 0 || iPage > _proxy->getPageSNum()) {
        m_sheet->showTips(tr("Invalid page number"));
    } else {
        CentralDocPage::Instance()->qDealWithData(MSG_DOC_JUMP_PAGE, QString::number(iPage - 1));
        setFocus();
    }
}

void PagingWidget::__PageNumberJump()
{
    CentralDocPage *pMtwe = CentralDocPage::Instance();
    DocummentProxy *_proxy = pMtwe->getCurFileAndProxy(m_strBindPath);
    if (_proxy) {
        int nPageSum = _proxy->getPageSNum();

        QString sText = m_pJumpPageLineEdit->text();

        int iPage = _proxy->label2pagenum(sText);

        if (iPage > -1 && iPage < nPageSum) {   //  输入的页码 必须在 0-最大值 之间, 才可以
            CentralDocPage::Instance()->qDealWithData(MSG_DOC_JUMP_PAGE, QString::number(iPage));
            setFocus();
        } else {
            m_sheet->showTips(tr("Invalid page number"));
        }
    }
}

void PagingWidget::slotPrePageBtnClicked()
{
    CentralDocPage::Instance()->qDealWithData(MSG_OPERATION_PREV_PAGE, "");
}

void PagingWidget::slotNextPageBtnClicked()
{
    CentralDocPage::Instance()->qDealWithData(MSG_OPERATION_NEXT_PAGE, "");
}
