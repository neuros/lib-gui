#ifndef MPRISPLAYERADAPTOR_H
#define MPRISPLAYERADAPTOR_H
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

#include <QApplication>
#include <QDBusAbstractInterface>
#include <QDBusReply>

#include "mprisdbustypes.h"

class MprisPlayerInterface : public QDBusAbstractInterface
{
	Q_OBJECT
	Q_CLASSINFO( "D-Bus Interface","org.freedesktop.MediaPlayer" );

private:
	QApplication *app;

public:
	MprisPlayerInterface( const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0 );
	~MprisPlayerInterface();


public slots:
	QDBusReply<int> GetCaps();
	QDBusReply<QVariantMap> GetMetadata();
	QDBusReply<MprisDBusStatus> GetStatus();
	QDBusReply<void> Next();
	QDBusReply<void> Pause();
	QDBusReply<void> Play();
	QDBusReply<int> PositionGet();
	QDBusReply<void> PositionSet( int in0 );
	QDBusReply<void> Prev();
	QDBusReply<void> Repeat( bool in0 );
	QDBusReply<void> Stop();
	QDBusReply<int> VolumeGet();
	QDBusReply<void> VolumeSet( int in0 );

signals:
	void CapsChange( int in0 );
	void StatusChange();
	void TrackChange( const QVariantMap &in0 );

};

#endif


inline QDBusReply<int> MprisPlayerInterface::GetCaps()
{
	QList<QVariant> argumentList;
	return callWithArgumentList( QDBus::Block, QLatin1String( "GetCaps" ), argumentList );
}

inline QDBusReply<QVariantMap> MprisPlayerInterface::GetMetadata()
{
	QList<QVariant> argumentList;
	return callWithArgumentList( QDBus::Block, QLatin1String( "GetMetadata" ), argumentList );
}

inline QDBusReply<MprisDBusStatus> MprisPlayerInterface::GetStatus()
{
	QList<QVariant> argumentList;
	return callWithArgumentList( QDBus::Block, QLatin1String( "GetStatus" ), argumentList );
}

inline QDBusReply<void> MprisPlayerInterface::Next()
{
	QList<QVariant> argumentList;
	return callWithArgumentList( QDBus::Block, QLatin1String( "Next" ), argumentList );
}

inline QDBusReply<void> MprisPlayerInterface::Pause()
{
	QList<QVariant> argumentList;
	return callWithArgumentList( QDBus::Block, QLatin1String( "Pause" ), argumentList );
}

inline QDBusReply<void> MprisPlayerInterface::Play()
{
	QList<QVariant> argumentList;
	return callWithArgumentList( QDBus::Block, QLatin1String( "Play" ), argumentList );
}

inline QDBusReply<int> MprisPlayerInterface::PositionGet()
{
	QList<QVariant> argumentList;
	return callWithArgumentList( QDBus::Block, QLatin1String( "PositionGet" ), argumentList );
}

inline QDBusReply<void> MprisPlayerInterface::PositionSet( int in0 )
{
	QList<QVariant> argumentList;
	argumentList << qVariantFromValue( in0 );
	return callWithArgumentList( QDBus::Block, QLatin1String( "PositionSet" ), argumentList );
}

inline QDBusReply<void> MprisPlayerInterface::Prev()
{
	QList<QVariant> argumentList;
	return callWithArgumentList( QDBus::Block, QLatin1String( "Prev" ), argumentList );
}

inline QDBusReply<void> MprisPlayerInterface::Repeat( bool in0 )
{
	QList<QVariant> argumentList;
	argumentList << qVariantFromValue( in0 );
	return callWithArgumentList( QDBus::Block, QLatin1String( "Repeat" ), argumentList );
}

inline QDBusReply<void> MprisPlayerInterface::Stop()
{
	QList<QVariant> argumentList;
	return callWithArgumentList( QDBus::Block, QLatin1String( "Stop" ), argumentList );
}

inline QDBusReply<int> MprisPlayerInterface::VolumeGet()
{
	QList<QVariant> argumentList;
	return callWithArgumentList( QDBus::Block, QLatin1String( "VolumeGet" ), argumentList );
}

inline QDBusReply<void> MprisPlayerInterface::VolumeSet( int in0 )
{
	QList<QVariant> argumentList;
	argumentList << qVariantFromValue( in0 );
	return callWithArgumentList( QDBus::Block, QLatin1String( "VolumeSet" ), argumentList );
}



