/*
* Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.
*
* Author:     leiyu <leiyu@live.com>
* Maintainer: leiyu <leiyu@deepin.com>
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef IMAGELISTVIEW_H
#define IMAGELISTVIEW_H

#include <DListView>

DWIDGET_USE_NAMESPACE
struct ImagePageInfo_t;

class DocSheet;
class ImageViewModel;
class ImageViewDelegate;
class BookMarkMenu;
class NoteMenu;
class ImageListView : public DListView
{
    Q_OBJECT
public:
    ImageListView(DocSheet *sheet, QWidget *parent = nullptr);

signals:
    void sigListMenuClick(const int &);
    void sigListItemClicked(int row);

public:
    void resetData();
    void handleOpenSuccess();
    void setBoolMarkVisible(int pageIndex, bool visible);
    void setListType(int type);
    void updatePageIndex(int index);
    void insertPageIndex(int pageIndex);
    void insertPageIndex(const ImagePageInfo_t &tImagePageInfo);
    void removePageIndex(int pageIndex);
    void removeModelIndex(int modelIndex);
    void removeItemForuuid(const QString &uuid);
    bool scrollToIndex(int pageIndex, bool scrollTo = true);
    int  getModelIndexForPageIndex(int pageIndex);
    int  getPageIndexForModelIndex(int row);
    int  findItemForuuid(const QString &uuid);
    void getModelIndexImageInfo(int modelIndex, ImagePageInfo_t &tImagePageInfo);

private:
    void initControl();
    void showNoteMenu();
    void showBookMarkMenu();

private slots:
    void onUpdatePageImage(int pageIndex);
    void onItemClicked(const QModelIndex &index);

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    int m_listType;
    DocSheet *m_docSheet;
    ImageViewModel *m_imageModel;

    BookMarkMenu *m_pBookMarkMenu;
    NoteMenu *m_pNoteMenu;
};

#endif // IMAGELISTVIEW_H