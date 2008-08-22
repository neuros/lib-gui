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
 * NBusyWidget implement
 *
 * REVISION:
 *
 * 2) Import to OSD20. ----------------------------------- 2008-07-31 WX
 * 1) Initial creation. ----------------------------------- 2008-02-27 GL
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QApplication>
#include <QDesktopWidget>

#include "nbusywidget.h"
#include "nbusywidget_p.h"

#define IMAGE_BACKGROUND_TILE ":/lib-gui/busy-exec-tile.png"
#define IMAGE_BACKGROUND_EDGE ":/lib-gui/busy-exec-edge.png"

#define BW_HEIGHT    156  //busy widget height
#define EDGE_HEIGHT  4    //edge height
#define MARGIN       20   //the margin of the text
#define FONT_TITLE   24
#define FONT_TEXT     22
#define FLASH_RECT_WIDTH  21
#define FLASH_RECT_HEIGHT 7
#define DEF_REFRESH_INTERVAL (400)  //ms


NBusyWidget::NBusyWidget(QWidget *parent)
: QWidget(parent), d(new NBusyWidgetPrivate)
{
    QPalette p = palette( );
    p.setColor(QPalette::WindowText, Qt::white);
    p.setColor(QPalette::Text, QColor(178,178,178));
    p.setColor(QPalette::Highlight, QColor(42, 170, 225));
    p.setColor(QPalette::Base, QColor(178,178,178));
    setPalette(p);

    QFont f = font( );
    f.setPointSize(FONT_TITLE);
    setFont(f);

    // Init the private data
    d->title = "";
    d->text = tr("One moment please ..."); // default busy text

    d->flashOffset = 0;
    d->flashDirection = 1;

    d->bgTile.load(IMAGE_BACKGROUND_TILE);
    d->bgEdge.load(IMAGE_BACKGROUND_EDGE);

    d->flashTimer = new QTimer(this);
    d->flashTimer->setInterval(DEF_REFRESH_INTERVAL);
    connect(d->flashTimer, SIGNAL(timeout( )), this, SLOT(onFlashTimeOut( )));

    /* setup the default position and size */
    QRect screenRect;
    QWidget* par = parentWidget( );
    if (par != NULL)
        screenRect = par->geometry( );
    else
        screenRect = QApplication::desktop( )->geometry( );

    resize(screenRect.width( ), screenRect.height( )/3);
    move(screenRect.x( ) + (screenRect.width( ) - this->width( ))/2,
         screenRect.y( ) + (screenRect.height( ) - this->height( ))/2);
}

NBusyWidget::~NBusyWidget( )
{
    delete d->flashTimer;
    delete d;
}

/*
 * return the window title of  this busy widget
 * The default value is a empty string
 */
QString NBusyWidget::title( ) const
{
    return d->title;
}

/*
 * set the busy title to title
 */
void NBusyWidget::setTitle(const QString &title)
{
    if (title != d->title)
    {
        d->title = title;
        update( );
    }
}

/*
 * return the window text of this busy widget
 * The default text is "One moment please ..."
 */
QString NBusyWidget::text( ) const
{
    return d->text;
}

/*
 * set the window text to text
 */
void NBusyWidget::setText(const QString &text)
{
    if (text != d->text)
    {
        d->text = text;
        update( );
    }
}

/*
 * return the interval time(msec) of the busy flash
 * The default value for this property is 400ms
 */
int NBusyWidget::flashInterval( ) const
{
    return d->flashTimer->interval( );
}

/*
 * set the flash interval to msec
 */
void NBusyWidget::setFlashInterval(int msec)
{
    d->flashTimer->setInterval(msec);
}

/*
 * start the busy flash if active is true, stop if false
 */
void NBusyWidget::setActive(bool active)
{
    if (active)
        d->flashTimer->start( );
    else
        d->flashTimer->stop( );
}

/*
 * start the busy flash, a correct timeout interval should be set firstly.
 */
void NBusyWidget::start( )
{
    setActive(true);
}

/*
 * stop the busy flash
 */
void NBusyWidget::stop( )
{
    setActive(false);
}

void NBusyWidget::onFlashTimeOut( )
{
    if (0 == d->flashOffset)
        d->flashDirection = 1;
    if (d->flashOffset >= (d->flashRect.width( ) - d->flashRect.height( )))
        d->flashDirection = -1;
    d->flashOffset += d->flashDirection * d->flashRect.height( );
    update(d->flashRect);
}

void NBusyWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    /* Draw background */
    QPixmap pixmap(size( ));
    QPainter painter(&pixmap);
    QRect tileRect(0, EDGE_HEIGHT, width( ), height( ) - EDGE_HEIGHT*2);
    QRect topEdgeRect(0, 0, width( ), EDGE_HEIGHT);
    QRect bottomEdgeRect(0, height( ) - EDGE_HEIGHT, width( ), EDGE_HEIGHT);

    painter.drawTiledPixmap(tileRect, d->bgTile, QPoint(0, 0));
    painter.drawTiledPixmap(topEdgeRect, d->bgEdge, QPoint(0, 0));
    painter.drawTiledPixmap(bottomEdgeRect, d->bgEdge, QPoint(0, 0));

    QPalette p = palette( );
    QBrush b = QBrush(pixmap);
    p.setBrush(backgroundRole( ), b);
    setPalette(p);

    /* Compute the flash rectangle */
    d->flashRect.setX((width( ) - FLASH_RECT_WIDTH)/2 );
    d->flashRect.setY(height( )/2 - FLASH_RECT_HEIGHT*2 );
    d->flashRect.setSize(QSize(FLASH_RECT_WIDTH, FLASH_RECT_HEIGHT));
}

void NBusyWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QFont f = font( );
    QPalette p = palette( );

    painter.fillRect(d->flashRect, p.color(QPalette::Base));

    QRect ret = d->flashRect.translated(d->flashOffset, 0);
    ret.setWidth(d->flashRect.height( ));
    painter.fillRect(ret, p.color(QPalette::Highlight));

    if (event->rect( ) == d->flashRect )
        return;

    if (!d->title.isEmpty( ))
    {
        painter.setFont(f);
        painter.setPen(p.color(QPalette::WindowText));
        QRect titleRect(MARGIN, MARGIN, width( ) - MARGIN*2, (height( ) - MARGIN)/4);
        painter.drawText(titleRect, Qt::AlignCenter | Qt::AlignVCenter, d->title);
    }

    if (!d->text.isEmpty( ))
    {
        f.setPointSize(f.pointSize( )*11/12);
        painter.setFont(f);
        painter.setPen(p.color(QPalette::Text));
        QRect textRect(MARGIN, (height( ))/2, width( ) - MARGIN*2, (height( ) - MARGIN)/2);
        painter.drawText(textRect, Qt::AlignCenter | Qt::AlignVCenter, d->text);
    }
}




NBusyWidgetPrivate::NBusyWidgetPrivate( )
{
}

NBusyWidgetPrivate::~NBusyWidgetPrivate( )
{
}
