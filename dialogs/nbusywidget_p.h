#ifndef _NBUSYWIDGET_P_H_
#define _NBUSYWIDGET_P_H_
/*
 *  Copyright(C) 2007 Neuros Technology International LLC.
 *               <www.neurostechnology.com>
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 2 of the License.
 *
 *
 *  This program is distributed in the hope that, in addition to its
 *  original purpose to support Neuros hardware, it will be useful
 *  otherwise, but WITHOUT ANY WARRANTY; without even the implied
 *  warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 ****************************************************************************
 *
 * NBusyWidgetPrivate implement header.
 *
 * REVISION:
 *
 * 2) Import to OSD20. ----------------------------------- 2008-07-31 WX
 * 1) Initial creation. ----------------------------------- 2008-02-27 GL
 *
 */

#include <QTimer>
#include <QRect>
#include <QString>
#include <QPixmap>

class NBusyWidgetPrivate
{
public:
    NBusyWidgetPrivate( );
    ~NBusyWidgetPrivate( );

    QTimer *flashTimer;
    QRect flashRect;
    int flashDirection; // 1 left to right, -1 right to left
    int flashOffset;
    QString title;
    QString text;

    QPixmap bgTile;
    QPixmap bgEdge;

private:

};

#endif // _NBUSYWIDGET_P_H_
