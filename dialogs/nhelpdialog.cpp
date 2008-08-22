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
 * NHelpDialog implement routines.
 *
 * REVISION:
 *
 * 1) Initial creation. ----------------------------------- 2007-12-26 WX
 * 2) Add multi language support. ------------------------- 2008-02-28 JChen
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QScrollBar>

#include "nhelpdialog.h"
#include "nhelpdialog_p.h"

#define HELP_ICON ":/lib-gui/help.gif"

NHelpDialog::NHelpDialog(QWidget* parent)
:QWidget(parent), d(new NHelpDialogPrivate)
{
    setupUi(this);
    init( );
}

NHelpDialog::NHelpDialog(const QString& title, const QString& text, QWidget* parent)
:QWidget(parent), d(new NHelpDialogPrivate)
{
    setupUi(this);
    init( );

    setTitle(title);
    setText(text);
}

NHelpDialog::~NHelpDialog()
{
    if (d != NULL)
    {
        delete d;
        d = NULL;
    }
}

void NHelpDialog::init( )
{
    /* Set the QScrollArea transparent to his parent window */
    textScrollArea->viewport( )->setAutoFillBackground(false);
    textScrollArea->widget( )->setAutoFillBackground(false);

    /* load helper icon, the icon label should enable the property of scaled content */
	iconLabel->setPixmap(QPixmap(HELP_ICON).scaled(iconLabel->size( )));

    /* setup the default position and size */
    QRect screenRect;
    QWidget* par = parentWidget( );
    if (par) //get the contents rectangle of its parent if it have a parent
        screenRect = par->geometry( );
    else
        screenRect = QApplication::desktop( )->geometry( );

    QRect helperRect;
    helperRect.setWidth(screenRect.width( )/10*7);
    helperRect.setHeight(screenRect.height( ));
    helperRect.moveLeft(screenRect.left() + (screenRect.width()/2 - helperRect.width()/2));
    helperRect.moveTop(0);
    setGeometry(helperRect);
}

QString NHelpDialog::title( ) const
{
    return titleLabel->text( );
}

void NHelpDialog::setTitle(const QString& title)
{
    titleLabel->setText(title);
}

QString NHelpDialog::text( ) const
{
    return textLabel->text( );
}

void NHelpDialog::setText(const QString& text)
{
    textLabel->setText(text);
}

void NHelpDialog::keyPressEvent(QKeyEvent *event)
{
    switch (event->key( ))
    {
    case Qt::Key_PageUp:
    case Qt::Key_PageDown:
        {
            QScrollBar *vbar = textScrollArea->verticalScrollBar( );
            if (vbar)
            {
                switch (event->key())
                {
                case Qt::Key_PageUp:
                    vbar->triggerAction(QAbstractSlider::SliderPageStepSub);
                    break;
                case Qt::Key_PageDown:
                    vbar->triggerAction(QAbstractSlider::SliderPageStepAdd);
                    break;
                }
            }
        }
        break;
    case Qt::Key_HomePage:
    case Qt::Key_Escape:
    case Qt::Key_Left:
    case Qt::Key_Help:
    case Qt::Key_Enter:
    case Qt::Key_MediaRecord:
    case Qt::Key_MediaPlay:
        this->close( );
        break;
    default:
        break;
    }
}

NHelpDialog* NHelpDialog::ShowHelpBox(const QString& title, const QString& text, QWidget* parent)
{
    NHelpDialog* helper = new NHelpDialog(title, text, parent);
    helper->setAttribute(Qt::WA_DeleteOnClose, true);
    helper->show( );
}



NHelpDialogPrivate::NHelpDialogPrivate( )
{
}

NHelpDialogPrivate::~NHelpDialogPrivate( )
{
}
