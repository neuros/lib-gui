#ifndef _NMULTILANGUAGE_H_
#define _NMULTILANGUAGE_H_
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
 * 3) Import to OSD20  ----------------------------------- 2008-09-04 WX
 * 2) Rewrite for memory leak fixes and translator removal - 2008-04-14 Tom Bruno (tom@limesg.com)
 * 1) Initial creation. ----------------------------------- 2008-02-12 JChen
 *
 */

#include <QString>
#include <QTranslator>

class NMultiLanguagePrivate;

class NMultiLanguage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString applicationName READ applicationName WRITE setApplicationName);

public:
    NMultiLanguage(QObject *parent = NULL);
    NMultiLanguage(const QString &appName, QObject *parent = NULL);
    ~NMultiLanguage();

    QString applicationName() const;
    void setApplicationName(const QString &name);

public Q_SLOTS:
    void changeLanguage();

private:
    void loadLanguage();
    void unloadLanguage();

private:
    NMultiLanguagePrivate *d;
};

#endif // _NMULTILANGUAGE_H_
