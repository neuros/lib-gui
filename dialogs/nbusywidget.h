#ifndef _NBUSYWIDGET_H_
#define _NBUSYWIDGET_H_
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
 * NBusyWidget implement header.
 *
 * REVISION:
 *
 * 2) Import to OSD20. ----------------------------------- 2008-07-31 WX
 * 1) Initial creation. ----------------------------------- 2008-02-27 GL
 *
 */

#include <QWidget>

class NBusyWidgetPrivate;

class NBusyWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(int flashInterval READ flashInterval WRITE setFlashInterval)

public:
    NBusyWidget(QWidget *parent = NULL);
    ~NBusyWidget( );

    QString title( ) const;
    void setTitle(const QString &title);

    QString text( ) const;
    void setText(const QString &text);

    int flashInterval( ) const;
    void setFlashInterval(int msec);

public Q_SLOTS:
    void setActive(bool active);
    void start( );
    void stop( );

private slots:
    void onFlashTimeOut( );

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *e);

private:
    NBusyWidgetPrivate *d;
};

#endif // _NBUSYWIDGET_H_
