/*
 *  Copyright 2008  Alex Merry <alex.merry@kdemail.net>
 *
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

#include "mprisdbustypes.h"

// Marshall the MprisDBusVersion data into a D-BUS argument
QDBusArgument &operator<<( QDBusArgument &argument, const MprisDBusVersion &version )
{
	argument.beginStructure();
	argument << version.major << version.minor;
	argument.endStructure();
	return argument;
}

// Retrieve the MprisDBusVersion data from the D-BUS argument
const QDBusArgument &operator>>( const QDBusArgument &argument, MprisDBusVersion &version )
{
	argument.beginStructure();
	argument >> version.major >> version.minor;
	argument.endStructure();
	return argument;
}

// Marshall the MprisDBusStatus data into a D-BUS argument
QDBusArgument &operator<<( QDBusArgument &argument, const MprisDBusStatus &status )
{
	argument.beginStructure();
	argument << ( qint32 )status.play;
	argument << ( qint32 )status.random;
	argument << ( qint32 )status.trackRepeat;
	argument << ( qint32 )status.playlistRepeat;
	argument.endStructure();
	return argument;
}

// Retrieve the MprisDBusStatus data from the D-BUS argument
const QDBusArgument &operator>>( const QDBusArgument &argument, MprisDBusStatus &status )
{
	qint32 play, random, trackRepeat, playlistRepeat;

	argument.beginStructure();
	argument >> play;
	argument >> random;
	argument >> trackRepeat;
	argument >> playlistRepeat;
	argument.endStructure();

	status.play = ( MprisDBusStatusPlay )play;
	status.random = ( MprisDBusStatusRandom )random;
	status.trackRepeat = ( MprisDBusStatusTrackRepeat )trackRepeat;
	status.playlistRepeat = ( MprisDBusStatusPlaylistRepeat )playlistRepeat;

	return argument;
}

// vim: sw=4 sts=4 et tw=100
