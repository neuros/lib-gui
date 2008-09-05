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
 * NStatusBar implement routing.
 *
 * REVISION:
 * 
 * 1) Initial creation. ----------------------------------- 2008-09-05 WX
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "nstatusbar.h"
#include "nstatusbar_p.h"

NStatusBar::NStatusBar(QWidget * parent, Qt::WindowFlags f)
: QWidget(parent, f), d(new NStatusBarPrivate)
{
    setupUi(this);
}

NStatusBar::~NStatusBar()
{
    if (d != NULL)
    {
        delete d;
        d = NULL;
    }
}

/*
 * return the progress bar control
 */
NProgressBar * NStatusBar::progressBar() const
{
    return this->stProgressBar;
}

/*
 * return the date&time label control
 */
NDateTimeLabel * NStatusBar::datetimeLabel() const
{
    return this->stDateTimeLabel;
}

/*
 * return the information label control
 */
QLabel * NStatusBar::infoLabel() const
{
    return this->stInfoLabel;
}

/*
 * return the icon label control
 */
QLabel * NStatusBar::iconLabel() const
{
    return this->stIconLabel;
}



NStatusBarPrivate::NStatusBarPrivate()
{
}

NStatusBarPrivate::~NStatusBarPrivate()
{
}
