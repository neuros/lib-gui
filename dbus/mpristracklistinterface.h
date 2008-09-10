#ifndef MPRISTRACKLISTINTERFACE_H
#define MPRISTRACKLISTINTERFACE_H
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

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>


class MprisTracklistInterface: public QDBusAbstractInterface
{
	Q_OBJECT
	Q_CLASSINFO( "D-Bus Interface","org.freedesktop.MediaPlayer" );

public:
	MprisTracklistInterface( const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0 );

	~MprisTracklistInterface();

public slots:
	inline QDBusReply<int> AddTrack( const QString &in0, bool in1 )
	{
		QList<QVariant> argumentList;
		argumentList << qVariantFromValue( in0 ) << qVariantFromValue( in1 );
		return callWithArgumentList( QDBus::Block, QLatin1String( "AddTrack" ), argumentList );
	}

	inline QDBusReply<void> DelTrack( int in0 )
	{
		QList<QVariant> argumentList;
		argumentList << qVariantFromValue( in0 );
		return callWithArgumentList( QDBus::Block, QLatin1String( "DelTrack" ), argumentList );
	}

	inline QDBusReply<int> GetCurrentTrack()
	{
		QList<QVariant> argumentList;
		return callWithArgumentList( QDBus::Block, QLatin1String( "GetCurrentTrack" ), argumentList );
	}

	inline QDBusReply<int> GetLength()
	{
		QList<QVariant> argumentList;
		return callWithArgumentList( QDBus::Block, QLatin1String( "GetLength" ), argumentList );
	}

	inline QDBusReply<QVariantMap> GetMetadata( int in0 )
	{
		QList<QVariant> argumentList;
		argumentList << qVariantFromValue( in0 );
		return callWithArgumentList( QDBus::Block, QLatin1String( "GetMetadata" ), argumentList );
	}

	inline QDBusReply<void> SetLoop( bool in0 )
	{
		QList<QVariant> argumentList;
		argumentList << qVariantFromValue( in0 );
		return callWithArgumentList( QDBus::Block, QLatin1String( "SetLoop" ), argumentList );
	}

	inline QDBusReply<void> SetRandom( bool in0 )
	{
		QList<QVariant> argumentList;
		argumentList << qVariantFromValue( in0 );
		return callWithArgumentList( QDBus::Block, QLatin1String( "SetRandom" ), argumentList );
	}

signals: // SIGNALS
	void TrackListChange( int in0 );
};

#endif
