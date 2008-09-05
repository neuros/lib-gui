#ifndef _NSTATUSBAR_H_
#define _NSTATUSBAR_H_
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
 * NStatusBar implement header.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-09-05 WX
 *
 */

#include "ui_nstatusbar.h"

class NStatusBarPrivate;

class NStatusBar : public QWidget , private Ui::NStatusBar
{
    Q_OBJECT
    Q_PROPERTY(NProgressBar * progressBar READ progressBar);
    Q_PROPERTY(NDateTimeLabel * datetimeLabel READ datetimeLabel);
    Q_PROPERTY(QLabel * infoLabel READ infoLabel);
    Q_PROPERTY(QLabel * iconLabel READ iconLabel);

public:
    NStatusBar(QWidget * parent = NULL, Qt::WindowFlags f = 0);
    ~NStatusBar();

    /* To get the control object, so that they can be setup by application */
    NProgressBar * progressBar() const;
    NDateTimeLabel *datetimeLabel() const;
    QLabel *infoLabel() const;
    QLabel *iconLabel() const;

private:
    NStatusBarPrivate *d;
};

#endif // _NSTATUSBAR_H_
