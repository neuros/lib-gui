#ifndef _NHELPDIALOG_H_
#define _NHELPDIALOG_H_
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
 * NHelpDialog implement header.
 *
 * REVISION:
 *
 * 1) Initial creation. ----------------------------------- 2007-12-26 WX
 *
 */

#include "ui_nhelpdialog.h"

class NHelpDialogPrivate;

class NHelpDialog : public QWidget, private Ui::NHelpDialog
{
    Q_OBJECT
public:
    static NHelpDialog* Show(const QString& title, const QString& text, QWidget* parent = NULL);
    explicit NHelpDialog(QWidget* parent = NULL);
    explicit NHelpDialog(const QString& title = QString( ), const QString& text = QString( ), QWidget* parent = NULL);
    virtual ~NHelpDialog( );

    QString title( ) const;
    void setTitle(const QString& title);

    QString text( ) const;
    void setText(const QString& text);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    void init( );

private:
    NHelpDialogPrivate *d;

};

#endif // _NHELPDIALOG_H_
