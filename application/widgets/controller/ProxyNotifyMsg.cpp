/*
 * Copyright (C) 2019 ~ 2020 UOS Technology Co., Ltd.
 *
 * Author:     wangzhxiaun
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
#include "ProxyNotifyMsg.h"

#include <QJsonObject>
#include <QJsonDocument>

#include "application.h"

#include "MsgHeader.h"
#include "ModuleHeader.h"
#include "WidgetHeader.h"

using namespace DR_SPACE;

ProxyNotifyMsg::ProxyNotifyMsg(QObject *parent) : QObject(parent)
{

}

//  文档书签状态改变
void ProxyNotifyMsg::slotBookMarkStateChange(int nPage, bool bState)
{
    QJsonObject obj;
    obj.insert("content", QString::number(nPage));
    obj.insert("to", MAIN_TAB_WIDGET + Constant::sQStringSep + LEFT_SLIDERBAR_WIDGET + Constant::sQStringSep + BOOKMARK_WIDGET);

    QJsonDocument doc(obj);

    if (!bState) {
        dApp->m_pModelService->notifyMsg(MSG_OPERATION_DELETE_BOOKMARK, doc.toJson(QJsonDocument::Compact));
    } else {
        dApp->m_pModelService->notifyMsg(MSG_OPERATION_ADD_BOOKMARK, doc.toJson(QJsonDocument::Compact));
    }
}

//  文档页变化了
void ProxyNotifyMsg::slotDocFilePageChanged(int page)
{
    QJsonObject obj;
    obj.insert("content", QString::number(page));
    obj.insert("to", MAIN_TAB_WIDGET + Constant::sQStringSep + LEFT_SLIDERBAR_WIDGET);

    QJsonDocument doc(obj);

    dApp->m_pModelService->notifyMsg(MSG_FILE_PAGE_CHANGE, doc.toJson(QJsonDocument::Compact));
}
