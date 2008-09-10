#ifndef MPRISDBUSTYPES_H
#define MPRISDBUSTYPES_H
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


#include <QDBusArgument>

/*! \file mprisdbustypes.h
    \brief Mpris API DBus Argument types
*/

/*! The "media player"'s current capabilities. */
enum MprisDBusCaps
{
	NO_CAPS               = 0,
	CAN_GO_NEXT           = 1 << 0, /** There is a current next track, or at least something that equals to it */
	CAN_GO_PREV           = 1 << 1, /** Same as for NEXT, just previous track/something */
	CAN_PAUSE             = 1 << 2, /** Can currently pause. This might not always be possible, and is yet another hint for frontends as to what to indicate */
	CAN_PLAY              = 1 << 3, /** Whether playback can currently be started. This might not be the case if e.g. the playlist is empty in a player, or similar conditions. Here, again, it is entirely up to the player to decide when it can play or not, and it should signalize this using the caps API. */
	CAN_SEEK              = 1 << 4, /** Whether seeking is possible with the currently played stream (UIs/frontends can then enable/disable seeking controls) */
	CAN_PROVIDE_METADATA  = 1 << 5, /** Whether metadata can be acquired for the currently played stream/source using GetMetadata at all. */
	CAN_HAS_TRACKLIST     = 1 << 6, /** Whether the media player can hold a list of several items */
	UNKNOWN_CAP           = 1 << 7 /** Unknown Cap */
};



CAN_PLAY	
CAN_SEEK	
CAN_PROVIDE_METADATA	
CAN_HAS_TRACKLIST	 

struct MprisDBusVersion
{
	quint16 major;
	quint16 minor;
};

Q_DECLARE_METATYPE( MprisDBusVersion )

// Marshall the DBusVersion data into a D-BUS argument
QDBusArgument &operator<<( QDBusArgument &argument, const MprisDBusVersion &version );
// Retrieve the DBusVersion data from the D-BUS argument
const QDBusArgument &operator>>( const QDBusArgument &argument, MprisDBusVersion &version );


enum MprisDBusStatusPlay
{
	Playing = 0,
	Paused = 1,
	Stopped = 2
};

enum MprisDBusStatusRandom
{
	Linear = 0,
	Random = 1
};

enum MprisDBusStatusTrackRepeat
{
	GoToNext = 0,
	RepeatCurrent = 1
};

enum MprisDBusStatusPlaylistRepeat
{
	StopWhenFinished = 0,
	PlayForever = 1
};

struct MprisDBusStatus
{
	MprisDBusStatus( MprisDBusStatusPlay _play = Stopped,
		 MprisDBusStatusRandom _random = Linear,
		 MprisDBusStatusTrackRepeat _trackRepeat = GoToNext,
		 MprisDBusStatusPlaylistRepeat _playlistRepeat = StopWhenFinished )
		: play( _play ),random( _random ),trackRepeat( _trackRepeat ),	playlistRepeat( _playlistRepeat )
	{
	}

	MprisDBusStatusPlay           play;
	MprisDBusStatusRandom         random;
	MprisDBusStatusTrackRepeat    trackRepeat;
	MprisDBusStatusPlaylistRepeat playlistRepeat;
};

Q_DECLARE_METATYPE( MprisDBusStatus )

// Marshall the MprisDBusStatus data into a D-BUS argument
QDBusArgument &operator<<( QDBusArgument &argument, const MprisDBusStatus &status );
// Retrieve the MprisDBusStatus data from the D-BUS argument
const QDBusArgument &operator>>( const QDBusArgument &argument, MprisDBusStatus &status );

#endif
