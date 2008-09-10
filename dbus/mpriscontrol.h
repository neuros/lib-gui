#ifndef MPRISCONTROL_H
#define MPRISCONTROL_H
/*
 *  Copyright(C) 2008 Neuros Technology International LLC. 
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
 */
#include <QObject>
#include <QVariantMap>
#include <QDebug>

#include "mprisdbustypes.h"

class MprisControlPrivate;
class MprisErrorPrivate;

class MprisControl : public QObject
{
	Q_OBJECT
	Q_CLASSINFO("author","Tom Bruno")
	Q_CLASSINFO("email","tebruno99@gmail.com")
	Q_CLASSINFO("license","LGPL v2.0")
	Q_CLASSINFO("version","1.0")

public:
	MprisControl( QObject *parent );
	~MprisControl();

private:
	MprisControlPrivate *d;
	void setupConnections();

public slots:
	// Play Controls
	int GetCaps();
	void Play();
	void Pause();
	void Stop();
	void Next();
	void Prevoius();
	const MprisDBusStatus GetStatus();
	void Repeat( bool in0 );
	int PositionGet();
	void PositionSet( int in0 );
	int VolumeGet();
	void VolumeSet( int in0 );
	const QVariantMap GetMetadata();

	// Play List Controls
	int AddTrack( const QString &in0, bool in1 );
	void DelTrack( int in0 );
	int GetCurrentTrack();
	int GetTracklistLength();
	QVariantMap GetMetadata( int in0 );
	void SetLoop( bool in0 );
	void SetRandom( bool in0 );

private slots:
	/*! \internal
	 *   Lets media control relay a fired signal
	 */
	void emitCapsChange( int in0 )
	{
		qDebug() << "CapsChange in MprisControl";
		emit CapsChange( in0 );
	}

	/*! \internal
	 *   Lets media control relay a fired signal
	 */	void emitStatusChange()
	{
		qDebug() << "Status Changed in MprisControl";
		emit StatusChange();
	}

	/*! \internal
	 *   Lets media control relay a fired signal
	 */	void emitTrackChange( const QVariantMap &in0 )
	{
		qDebug() << "Track Changed in MprisControl";
		emit TrackChange( in0 );
	}

	/*! \internal
	 *   Lets media control relay a fired signal
	 */	void emitTrackListChange( int in0 )
	{
		qDebug() << "TrackList Changed in MprisControl";
		emit TrackListChange( in0 );
	}

signals:
	void CapsChange( int in0 ); /**< \brief Media player capabilities have Changed */
	void StatusChange();	/**< \brief Media player status has changed */
	void TrackChange( const QVariantMap &in0 ); /**< \brief Signal is emitted when the "Media Player" plays another "Track". Argument of the signal is the metadata attached to the new "Track" */
	void TrackListChange( int in0 ); /**< \brief Signal is emitted when the "TrackList" content has changed */

};

#endif
