/*
 * Copyright (C) 2016 ~ 2018 Deepin Technology Co., Ltd.
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
#include "application.h"

#include "controller/MsgSubject.h"
#include "subjectObserver/MsgHeader.h"

#include <DApplicationSettings>
#include <QIcon>
#include <QTranslator>
#include <QDebug>
#include "subjectObserver/ModuleHeader.h"
namespace {

}  // namespace

Application::Application(int &argc, char **argv)
    : DApplication(argc, argv)
{
    setAttribute(Qt::AA_UseHighDpiPixmaps);
    // setAttribute(Qt::AA_EnableHighDpiScaling);
    // setAttribute(Qt::AA_ForceRasterWidgets);

    initI18n();

    setApplicationName(("deepin-reader"));
    setOrganizationName(tr("deepin"));

    setApplicationDisplayName(tr("deepin-reader"));
    setApplicationVersion(DApplication::buildVersion("20191022"));
    setApplicationAcknowledgementPage(Constant::sAcknowledgementLink);
    setProductIcon(QIcon(Constant::sLogoPath));
    setApplicationDescription(tr("deepin-reader is a document viewer provided by deep system"));

    initChildren();
}

void Application::handleQuitAction()
{
    MsgSubject::getInstance()->sendMsg(nullptr, MSG_OPERATION_EXIT, "");
}

void Application::initChildren()
{
    dbM = DBManager::instance();
    //   setter = ConfigSetter::instance();
}

void Application::initI18n()
{
    // install translators
    loadTranslator();
}
