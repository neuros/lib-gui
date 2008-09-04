#ifndef _NMULTILANGUAGE_P_H_
#define _NMULTILANGUAGE_P_H_
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
 * REVISION:
 *
 * 1) Initial creation. ----------------------------------- 2008-09-04 WX
 *
 */

#include <QList>
#include <QString>
#include <QFont>
#include <QTranslator>

class NMultiLanguagePrivate
{
public:
    NMultiLanguagePrivate();
    ~NMultiLanguagePrivate();

    QList<QTranslator *> translatorList;
    QFont font ;
    QString applicationName;

private:

};

#endif // _NMULTILANGUAGE_P_H_
