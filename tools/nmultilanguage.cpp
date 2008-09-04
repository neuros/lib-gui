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
 * Find out the qm file path according to language value in system.ini
 * file. Load the qm file and save in translator. 
 *
 * REVISION:
 * 
 * 2) Import to OSD20  ----------------------------------- 2008-09-04 WX
 * 1) Initial creation. ----------------------------------- 2008-02-12 JChen
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QApplication>
#include <QSettings>
#include <QStringList>
#include "nmultilanguage.h"
#include "nmultilanguage_p.h"

#define SYSTEM_CONFIG	"/media/ext/data/sysconfig.ini"
#define QM_DIR		"/media/ext/.osd-extended/programs/translations/"

NMultiLanguage::NMultiLanguage(QObject *parent)
: QObject(parent), d(new NMultiLanguagePrivate)
{
    d->applicationName = QCoreApplication::applicationName();
    loadLanguage();
}

NMultiLanguage::NMultiLanguage(const QString &appName, QObject *parent)
: QObject(parent), d(new NMultiLanguagePrivate)
{
    d->applicationName = appName;
    if (d->applicationName.isEmpty())
        d->applicationName = QCoreApplication::applicationName();

    loadLanguage();
}

NMultiLanguage::~NMultiLanguage()
{
    unloadLanguage();

    if (d != NULL)
    {
        delete d;
        d = NULL;
    }
}

QString NMultiLanguage::applicationName() const
{
    return d->applicationName;
}

void NMultiLanguage::setApplicationName(const QString &name)
{
    if (d->applicationName == name)
        return;

    d->applicationName = name;
    unloadLanguage();
    loadLanguage();
}

void NMultiLanguage::loadLanguage()
{
    QSettings settings(SYSTEM_CONFIG, QSettings::IniFormat);

    /* Load font family configuration */
    d->font.setFamily(settings.value("regional/font","myriad pro").toString()) ;
    QApplication::setFont(d->font);

    QString lang = settings.value("regional/language", "en").toString();
    /* English do not have translation, ignore the translator install process */
    if (lang != "en")
    {
        QStringList translatorNames;
        translatorNames += d->applicationName + "_" + lang; //application translator name
        translatorNames += "neux_" + lang; //lib-widget translator name
        translatorNames += "gui_" + lang; //lib-gui  translator name

        Q_FOREACH(QString trName, translatorNames)
        {
            QTranslator *translator = new QTranslator(this);
            if (translator->load(trName, QM_DIR))
            {
                QApplication::installTranslator(translator);
                d->translatorList.append(translator);
            }
            else
            {
                delete translator;
                translator = NULL;
                qDebug() << "NMultiLanguage::loadLanguage" << "qm file:" << QM_DIR + trName + ".qm" << "is missing";
            }
        }
    }
}

void NMultiLanguage::unloadLanguage()
{
    QMutableListIterator<QTranslator*> i(d->translatorList);
    while (i.hasNext())
    {
        QTranslator *translator = i.next();
        QApplication::removeTranslator(translator);
        delete translator;
        i.remove();
    }
}

void NMultiLanguage::changeLanguage()
{
    qDebug() << "NMultiLanguage::changeLanguage";
    unloadLanguage();
    loadLanguage();
}




NMultiLanguagePrivate::NMultiLanguagePrivate()
{
}

NMultiLanguagePrivate::~NMultiLanguagePrivate()
{
}
