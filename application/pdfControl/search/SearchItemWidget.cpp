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
#include "SearchItemWidget.h"
#include "MsgHeader.h"
#include "ModuleHeader.h"
#include "CustomControl/RotateImageLabel.h"

#include <QVBoxLayout>

SearchItemWidget::SearchItemWidget(DWidget *parent)
    : CustomItemWidget(parent)
{
    initWidget();
    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged, this, &SearchItemWidget::slotUpdateTheme);
}

SearchItemWidget::~SearchItemWidget()
{
}

void SearchItemWidget::setLabelImage(const QImage &image)
{
    if (m_label != nullptr) {
        QPixmap pixmap = QPixmap::fromImage(image);
        m_label->setBackgroundPix(pixmap);
    }
}

//  搜索显示内容
void SearchItemWidget::setTextEditText(const QString &contant)
{
    m_strNote = contant;
    if (m_pTextLab) {
        m_pTextLab->clear();

        m_strNote.replace(QChar('\n'), QString(""));
        m_strNote.replace(QChar('\t'), QString(""));
        m_pTextLab->setText(m_strNote);
        //m_pTextLab->setText(calcText(m_pTextLab->font(), m_strNote, m_pTextLab->size()));
    }
}

//  搜索結果
void SearchItemWidget::setSerchResultText(const QString &result)
{
    if (m_pSearchResultNum) {
        m_pSearchResultNum->setText(result);
    }
}

bool SearchItemWidget::bSelect()
{
    if (m_label) {
        m_label->setSelect(true);
    }
    return true;
}

void SearchItemWidget::setBSelect(const bool &paint)
{
    if (m_label) {
        m_label->setSelect(paint);
    }
    m_bPaint = paint;
    update();
}

void SearchItemWidget::setRotate(int rotate)
{
    m_label->setRotateAngle(rotate);
    m_label->rotateImage();
}

void SearchItemWidget::slotUpdateTheme()
{
    if (m_pPageNumber) {
        m_pPageNumber->setForegroundRole(DPalette::TextTitle);
    }
    if (m_pTextLab) {
        m_pTextLab->setForegroundRole(QPalette::BrightText);
    }
    if (m_pSearchResultNum) {
        m_pSearchResultNum->setForegroundRole(DPalette::TextTips);
    }
}

void SearchItemWidget::adaptWindowSize(const double &scale)
{
    if (m_label) {
        m_label->scaleImage(scale);
    }
}

void SearchItemWidget::initWidget()
{
    auto t_vLayoutPicture = new QVBoxLayout;
    t_vLayoutPicture->setContentsMargins(0, 3, 0, 0);
    m_label = new RotateImageLabel(this);
    int tW = 48;
    int tH = 68;
    t_vLayoutPicture->addWidget(m_label);
    t_vLayoutPicture->addStretch(1);

    m_pPageNumber = new PageNumberLabel(this);
    tW = 31;
    tH = 18;
//    dApp->adaptScreenView(tW, tH);
    m_pPageNumber->setMinimumWidth(tW);
    m_pPageNumber->setFixedHeight(tH);
    m_pPageNumber->setForegroundRole(DPalette::WindowText);
    DFontSizeManager::instance()->bind(m_pPageNumber, DFontSizeManager::T8);

    m_pSearchResultNum = new DLabel(this);
    m_pSearchResultNum->setMinimumWidth(tW);
    m_pSearchResultNum->setFixedHeight(tH);
    m_pSearchResultNum->setForegroundRole(DPalette::TextTips);
    DFontSizeManager::instance()->bind(m_pSearchResultNum, DFontSizeManager::T10);

    m_pTextLab = new DLabel(this);
    m_pTextLab->setTextFormat(Qt::PlainText);
    tW = 80;
    tH = 54;
    m_pTextLab->setFixedHeight(tH);
    m_pTextLab->setMinimumWidth(tW);
    m_pTextLab->setFrameStyle(QFrame::NoFrame);
    m_pTextLab->setWordWrap(true);
    m_pTextLab->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_pTextLab->setForegroundRole(DPalette::BrightText);
    DFontSizeManager::instance()->bind(m_pTextLab, DFontSizeManager::T9);

    auto hLine = new DHorizontalLine(this);

    auto t_hLayout = new QHBoxLayout;
    t_hLayout->setContentsMargins(0, 0, 0, 0);
    t_hLayout->setSpacing(0);
    t_hLayout->addWidget(m_pPageNumber);
    t_hLayout->addWidget(m_pSearchResultNum);

    auto t_vLayout = new QVBoxLayout;
    t_vLayout->setContentsMargins(15, 0, 10, 0);
    t_vLayout->setSpacing(0);
    t_vLayout->addItem(t_hLayout);
    t_vLayout->addWidget(m_pTextLab);
    t_vLayout->addStretch(1);
    t_vLayout->addWidget(hLine);

    auto m_pHLayout = new QHBoxLayout;

    m_pHLayout->setSpacing(1);
    m_pHLayout->setContentsMargins(0, 0, 10, 0);
//    m_pHLayout->addWidget(m_label);
    m_pHLayout->addItem(t_vLayoutPicture);
    m_pHLayout->addItem(t_vLayout);
    m_pHLayout->setSpacing(1);

    this->setLayout(m_pHLayout);
}

void SearchItemWidget::resizeEvent(QResizeEvent *event)
{
//    QString note = m_strNote;

//    m_pTextLab->setText(calcText(m_pTextLab->font(), note, m_pTextLab->size()));      //加上此行 效率低下

    CustomItemWidget::resizeEvent(event);
}

void SearchItemWidget::paintEvent(QPaintEvent *e)
{
    CustomItemWidget::paintEvent(e);

    //  涉及到 主题颜色
    if (m_bPaint) {
        m_label->setForegroundRole(DPalette::Highlight);
    } else {
        m_label->setForegroundRole(QPalette::Shadow);
    }
}
