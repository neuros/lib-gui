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
 * Video play back setting routines.
 *
 * REVISION:
 *
 *
 * 1) Initial creation. ----------------------------------- 2008-08-27 WX
 *
 *
 */

//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>

#include "nvideoplaybacksettings.h"
#include "nhelpdialog.h"

#define SYSTEM_CONFIG "/media/ext/data/sysconfig.ini"

NVideoPlaybackSettings::NVideoPlaybackSettings(QWidget *parent, Qt::WindowFlags f)
:QWidget(parent, f)
{
    setupUi(this);

    /* load settings */
    settings = new QSettings(SYSTEM_CONFIG,QSettings::IniFormat);
    loadConfigure();

    /* Initial  combo boxes */
    repeatModeComboBox->setCurrentIndex(repeatMode);
    playModeComboBox->setCurrentIndex(playMode);
    resumeComboBox->setCurrentIndex(resumeMode);
    proportionComboBox->setCurrentIndex(playProportion);

    /* Initial xim menu and xim icon */
    restoreAction = new NAction(tr("Restore Default"), this);

    /* connect signals and slots */
    connect(saveButton, SIGNAL(pressed()), this, SLOT(OnSaveButtonPressed()));
    connect(exitButton, SIGNAL(pressed()), this, SLOT(OnExitButtonPressed()));
    connect(restoreAction,SIGNAL(triggered()), SLOT(OnRestoreDefault()));
}

NVideoPlaybackSettings:: ~NVideoPlaybackSettings()
{
    if (!ximMenu.isNull())
    {
        delete ximMenu;
        ximMenu = NULL;
    }

    if (settings != NULL)
    {
        delete settings;
        settings = NULL;
    }

    if (restoreAction != NULL)
    {
        delete restoreAction;
        restoreAction = NULL;
    }
}

void NVideoPlaybackSettings::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Enter:
        saveButton->setFocus();
        break;
    case Qt::Key_Escape:
        OnExitButtonPressed();
        break;
    case Qt::Key_Up:
        focusPreviousChild();
        break;
    case Qt::Key_Down:
        focusNextChild();
        break;
    case Qt::Key_Menu:
    case Qt::Key_F11: // For testing on Qt-X11
        OnMenu();
        break;
    case Qt::Key_Help:
    case Qt::Key_F1: // For testing on Qt-X11
        NHelpDialog::Show(tr("Video Playmode", "Help Text Title"),
                          tr("Use this menu to change the repeat mode (Off, "
                             "Single, Folder). Off mode will play only one video. Single mode "
                             "will repeat the same video. Folder mode will play all videos in the "
                             "selected folder.\n\nAs well, for Folder mode, the device can either "
                             "play videos sequentially or randomly, as indicated by Shuffle Mode.", "Help Text"),
                          this);
        break;
    }
}

void NVideoPlaybackSettings::OnSaveButtonPressed()
{
    repeatMode = static_cast<RepeatMode>(repeatModeComboBox->currentIndex());
    playMode = static_cast<PlayMode>(playModeComboBox->currentIndex());
    resumeMode = static_cast<ResumeMode>(resumeComboBox->currentIndex());
    playProportion = static_cast<PlayProportion>(proportionComboBox->currentIndex());
    saveConfigure();
    emit completed();
    close();
}

void NVideoPlaybackSettings::OnExitButtonPressed()
{
    emit cancelled();
    close();
}

void NVideoPlaybackSettings::OnMenu()
{
    if (ximMenu.isNull())
    {
        ximMenu = new NXim(this);
        ximMenu->setFont(font());
        ximMenu->addAction(restoreAction);
    }

    ximMenu->show();
}

void NVideoPlaybackSettings::OnRestoreDefault()
{
    repeatMode = DEFAULT_REPEAT_MODE;
    playMode = DEFAULT_PLAY_MODE;
    resumeMode = DEFAULT_RESUME_MODE;
    playProportion = DEFAULT_PLAY_PROPORTION;
    repeatModeComboBox->setCurrentIndex(repeatMode);
    playModeComboBox->setCurrentIndex(playMode);
    resumeComboBox->setCurrentIndex(resumeMode);
    proportionComboBox->setCurrentIndex(playProportion);
}

void NVideoPlaybackSettings::loadConfigure()
{
    if (settings == NULL)
        return;

    repeatMode = static_cast<RepeatMode>(settings->value(REPEAT_MODE, DEFAULT_REPEAT_MODE).toInt());
    playMode = static_cast<PlayMode>(settings->value(PLAY_MODE, DEFAULT_PLAY_MODE).toInt());
    resumeMode = static_cast<ResumeMode>(settings->value(RESUME_MODE, DEFAULT_RESUME_MODE).toInt());
    playProportion = static_cast<PlayProportion>(settings->value(PLAY_PROPORTION, DEFAULT_PLAY_PROPORTION).toInt());
}

void NVideoPlaybackSettings::saveConfigure()
{
    if (settings == NULL)
        return;

    settings->setValue(REPEAT_MODE, repeatMode);
    settings->setValue(PLAY_MODE, playMode);
    settings->setValue(RESUME_MODE, resumeMode);
    settings->setValue(PLAY_PROPORTION, playProportion);
}
