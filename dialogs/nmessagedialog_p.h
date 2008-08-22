#ifndef _NMESSAGEDIALOG_P_H_
#define _NMESSAGEDIALOG_P_H_
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
 * NMessageDialogPrivate implement header.
 *
 * REVISION:
 *
 * 1) Initial creation. ----------------------------------- 2008-08-19 WX
 *
 */

class NMessageDialogPrivate
{
public:
    NMessageDialogPrivate( );
    ~NMessageDialogPrivate( );

    bool autoAddOkButton;
    QMessageBox::Icon icon;
    QTimer *timer;
    QPixmap *tiledBackground;

    QLabel *titleLabel;
    QLabel *textLabel;
    QLabel *iconLabel;
    QScrollArea *textScrollArea;
    QDialogButtonBox *buttonBox;

    QAbstractButton *escapeButton;
    QPushButton *defaultButton;
    QAbstractButton *clickedButton;
    QAbstractButton *detectedEscapeButton;

    static const int defButtonsSpacing = 50;
    static const int defButtonsMinSpacing = 40;
};

#endif // _NMESSAGEDIALOG_P_H_
