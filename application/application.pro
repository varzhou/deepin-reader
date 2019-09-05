QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += core gui
QT       += xml

TARGET = deepin_reader
TEMPLATE = app
CONFIG += c++11 link_pkgconfig
PKGCONFIG += dtkwidget
PKGCONFIG += poppler-qt5

SOURCES += \
        main.cpp \
    tabbar.cpp \
    utils.cpp \
    window.cpp \
    settings.cpp \
    toolbar.cpp \
    widgets/MainOperationWidget.cpp \
    widgets/MainWidget.cpp \
    widgets/TitleWidget.cpp \
    widgets/HomeWidget.cpp \
    widgets/LeftSidebarWidget.cpp \
    widgets/FileViewWidget.cpp \
    widgets/MainShowSplitter.cpp \
    widgets/FileAttrWidget.cpp \
    data/DataManager.cpp \
    listWidget/PagingWidget.cpp \
    listWidget/NotesWidget.cpp \
    listWidget/BookMarkWidget.cpp \
    listWidget/ThumbnailItemWidget.cpp \
    listWidget/ThumbnailWidget.cpp \
    listWidget/BookMarkItemWidget.cpp \
    listWidget/NotesItemWidget.cpp \
    view/MagnifyingWidget.cpp \
    header/MsgSubject.cpp \
    header/CustomWidget.cpp\
    pdfview/documentview.cpp \
    pdfview/pdfmodel.cpp \
    pdfview/loadhandler.cpp \
    pdfview/pageitem.cpp \
    pdfview/documentlayout.cpp \
    pdfview/viewsettings.cpp \
    pdfview/rendertask.cpp \
    pdfview/tileitem.cpp



RESOURCES +=         resources.qrc

HEADERS +=\
    tabbar.h \
    utils.h \
    window.h \
    settings.h \
    toolbar.h \
    widgets/MainOperationWidget.h \
    widgets/TitleWidget.h \
    widgets/MainWidget.h \
    widgets/HomeWidget.h \
    widgets/LeftSidebarWidget.h \
    widgets/FileViewWidget.h \
    widgets/MainShowSplitter.h \
    widgets/FileAttrWidget.h \
    data/DataManager.h \
    header/ISubject.h \
    header/IObserver.h \
    listWidget/ThumbnailItemWidget.h \
    listWidget/NotesWidget.h \
    listWidget/ThumbnailWidget.h \
    listWidget/PagingWidget.h \
    listWidget/BookMarkWidget.h \
    listWidget/BookMarkItemWidget.h \
    listWidget/NotesItemWidget.h \
    view/MagnifyingWidget.h \
    header/MsgSubject.h \
    header/IMsgObserver.h \
    header/MsgHeader.h \
    header/CustomWidget.h\
    pdfview/documentview.h \
    pdfview/model.h \
    pdfview/global.h \
    pdfview/pdfmodel.h \
    pdfview/loadhandler.h \
    pdfview/pageitem.h \
    pdfview/renderparam.h \
    pdfview/documentlayout.h \
    pdfview/viewsettings.h \
    pdfview/rendertask.h \
    pdfview/tileitem.h

DISTFILES += \
    themes/solarized_light.theme \
    themes/atom_dark.theme \
    themes/deepin_dark.theme \
    themes/solarized_dark.theme \
    themes/deepin.theme\


