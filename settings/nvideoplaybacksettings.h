#ifndef _NVIDEOPLAYBACKSETTINGS_H_
#define _NVIDEOPLAYBACKSETTINGS_H_
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
 * Video play back setting header.
 *
 * REVISION:
 *
 *
 * 1) Initial creation. ----------------------------------- 2007-11-27 WX
 *
 *
 */

#include <QSettings>
#include <QPointer>
#include "naction.h"
#include "nxim.h"
#include "ui_nvideoplaybacksettings.h"

#define REPEAT_MODE "video/repeat-mode"
#define PLAY_MODE "video/play-mode"
#define RESUME_MODE "video/restart-last-position"
#define PLAY_PROPORTION "video/playback-proportions"

#define DEFAULT_PLAY_MODE (NVideoPlaybackSettings::PMSingle)
#define DEFAULT_REPEAT_MODE (NVideoPlaybackSettings::RPMNormal)
#define DEFAULT_RESUME_MODE (NVideoPlaybackSettings::RSMENABLED)
#define DEFAULT_PLAY_PROPORTION (NVideoPlaybackSettings::PPNormal)

class NVideoPlaybackSettings: public QWidget, private Ui::NVideoPlaybackSettings
{
    Q_OBJECT
    Q_ENUMS(PlayMode)
    Q_ENUMS(RepeatMode)
    Q_ENUMS(ResumeMode)
    Q_ENUMS(PlayProportion)

public:
    /*
     * Note: the order of the strings added on the Designer MUST follow the enumeration defined below!
     */
    enum PlayMode { PMSingle = 0, PMFolder };
    enum RepeatMode { RPMNormal = 0, RPMRepeat, RPMShuffle };
    enum ResumeMode { RSMDISABLED = 0, RSMENABLED };
    enum PlayProportion { PPNormal = 0, PPWideScreen };

    NVideoPlaybackSettings(QWidget *parent = NULL, Qt::WindowFlags f = Qt::Window);
    ~NVideoPlaybackSettings();

Q_SIGNALS:
    void completed();
    void cancelled();

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private Q_SLOTS:
    void OnSaveButtonPressed();
    void OnExitButtonPressed();
    void OnMenu();
    void OnRestoreDefault();

private:
    void loadConfigure();
    void saveConfigure();

private:
    QSettings *settings;
    NAction *restoreAction;
    QPointer<NXim> ximMenu;

    PlayMode playMode;
    RepeatMode repeatMode;
    ResumeMode resumeMode;
    PlayProportion playProportion;
};

#endif // _NVIDEOPLAYBACKSETTINGS_H_
