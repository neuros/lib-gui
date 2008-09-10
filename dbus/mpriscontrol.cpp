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
#include "mpriscontrol.h"
#include "mprisplayerinterface.h"
#include "mpristracklistinterface.h"


/*!
	\internal
	
	 Private data for MprisControl for PIMPL binary compat
*/
class MprisControlPrivate
{

public:
	MprisControlPrivate():mprisplayer( 0 ),mpristracklist( 0 )
	{
		mprisplayer = new MprisPlayerInterface( "org.mpris.vlc","/Player",QDBusConnection::sessionBus() );
		mpristracklist = new MprisTracklistInterface( "org.mpris.vlc","/TrackList",QDBusConnection::sessionBus() );
	}

	~MprisControlPrivate()
	{
		delete mprisplayer;
		mprisplayer = NULL;
		delete mpristracklist;
		mpristracklist = NULL;
	}

	/*!  \internal */
        MprisPlayerInterface *getPlayer()
	{
		return mprisplayer;
	}

	/*! \internal */
	MprisTracklistInterface *getTracklist()
	{
		return mpristracklist;
	}

private:
	MprisPlayerInterface *mprisplayer;
	MprisTracklistInterface *mpristracklist;


};


MprisControl::MprisControl( QObject *parent )
		: QObject( parent )
{
	d = new MprisControlPrivate;
	setupConnections();

}

MprisControl::~MprisControl()
{
	delete d;
}

/*!
 *  \internal Used to connect DBus interface signals to slots
*/
void MprisControl::setupConnections()
{
	// Connect Player dbus signals to local slots.
	connect( d->getPlayer(),SIGNAL( StatusChange() ),this,SLOT( emitStatusChange() ) );
	connect( d->getPlayer(),SIGNAL( CapsChange( int ) ),this,SLOT( emitCapsChange( int ) ) );
	connect( d->getPlayer(),SIGNAL( TrackChange( const QVariantMap& ) ),this,SLOT( TrackChange( const QVariantMap& ) ) );
	connect( d->getTracklist(),SIGNAL( TrackListChange( int ); ),this,SLOT( emitTrackListChange( int ) ) );


}

/*!
 *  \brief Fetch the Current Capabilities of the Media Service
 *
 *  \return int Contains MprisDBusCaps value
 *
 *  See the MprisDBusCaps enum for information in mprisdbustypes.h
 */
int MprisControl::GetCaps()
{
	return d->getPlayer()->GetCaps();
}

/*!
 *  \brief Start|Rewind playback
 *
 *  \return void
 *
 * Starts or Rewindes playback to beginning of current track. Mpris standard states that
 * sending Play multiple times rewinds back to the beginning.
 */
void MprisControl::Play()
{
	d->getPlayer()->Play();
}


/*!
 *  \brief Pause|Unpause playback
 *  \return void
 *
 * Pauses or Unpauses playback of current track. Resend Pause to Unpause playback.
 */
void MprisControl::Pause()
{
	d->getPlayer()->Pause();
}

/*!
 *  \brief Stop Playback
 *  \return void
 *
 * Stop resets video playback to beginning.
 */
void MprisControl::Stop()
{
	d->getPlayer()->Stop();
}

/*!
 *  \brief Goes to the next element
 *  \return void
 *
 * Next causes media player to play the next track in the playlist.
 * Check Media player capabilities to see if Next track is available. If no
 * track is available the media player will just ignore.
 */
void MprisControl::Next()
{
	d->getPlayer()->Next();
}

/*!
 *  \brief Goes to the prevoius element
 *  \return void
 *
 * Previous causes media player to play the next track in the playlist.
 * Check Media player capabilities to see if Previous track is available. If no
 * track is available the media player will just ignore.
 */
void MprisControl::Prevoius()
{
	d->getPlayer()->Prev();
}

/*!
 *  \brief Sets the playing position
 *  \param int Playing position in milliseconds
 *  \return void
 *
 * Sets the playing position in milliseconds. Must check track length before using!
 */
void MprisControl::PositionSet( int in0 )
{
	d->getPlayer()->PositionSet( in0 );
}

/*!
 *  \brief Gets the current playing position
 *  \return int playing position in milliseconds.
 */
int MprisControl::PositionGet()
{
	return d->getPlayer()->PositionGet();
}

/*!
 *  \brief Set repeat on current track
 *  \param bool Repeat (true or false)
*/
void MprisControl::Repeat( bool in0 )
{
	d->getPlayer()->Repeat( in0 );
}

/*!
 * \brief Set Volume level of playback
 * \param int Volume level 0 to 100
 *
 * Sets the playback volume to passed value.
 * Value 0 to 100 
*/
void MprisControl::VolumeSet( int in0 )
{
	d->getPlayer()->VolumeSet( in0 );
}

/*!
 * \brief Get current volume level
 * \return int current volume level between 0 and 100
*/
int MprisControl::VolumeGet()
{
	return d->getPlayer()->VolumeGet();
}


/*!
 *  \brief Appends an URI in the TrackList. 
 *  \param QString The uri of the item to append. 
 *  \param bool True if item should be played immediately, False otherwise 
 *  \return int 0 means Success
*/
int MprisControl::AddTrack( const QString &in0, bool in1 )
{
	return d->getTracklist()->AddTrack( in0,in1 );
}

/*!
 *  \brief Removes an URI from the TrackList. 
 *  \param int Position in the tracklist of the item to remove. 
*/
void MprisControl::DelTrack( int in0 )
{
	d->getTracklist()->DelTrack( in0 );
}

/*!
 *  \brief Return the position of current URI in the TrackList
 *  \return int Position in the TrackList of the active element. 
 *
 * Return the position of current URI in the TrackList.
 * The return value is zero-based, so the position of the first URI
 * in the TrackList is 0. The behavior of this method is unspecified
 * if there are zero elements in the TrackList.
*/
int MprisControl::GetCurrentTrack()
{
	return d->getTracklist()->GetCurrentTrack();
}

/*!
 *  \brief Number of elements in the TrackList
 *  \return int Number of elements in the TrackList
*/
int MprisControl::GetTracklistLength()
{
	return d->getTracklist()->GetLength();
}



/*!
 *  \brief Gives all meta data available for element at given position in the TrackList
 *  \param int Position in the TrackList of the item of which the metadata is requested 
 *  \return QVarianMap (string,variant)
 *
 * Gives all meta data available for element at given position in the TrackList, counting from 0. 
*/
QVariantMap MprisControl::GetTracklistMetadata( int in0 )
{
	return d->getTracklist()->GetMetadata( in0 );
}


/*!
 *  \brief Toggle playlist loop.
 *  \param bool true to loop, false to stop looping 
*/
void MprisControl::SetLoop( bool in0 )
{
	d->getTracklist()->SetLoop( in0 );
}


/*!
 *  \brief Toggle playlist shuffle / random. It may or may not play tracks only once.  
 *  \param bool TRUE to play randomly / shuffle playlist, FALSE to play normally / reorder playlist 
 *  \return
*/
void MprisControl::SetRandom( bool in0 )
{
	d->getTracklist()->SetRandom( in0 );
}


/*!
 *  \brief Gives all meta data available for the currently played element 
 *  \return QVarianMap (string,variant)
*/
const QVariantMap MprisControl::GetMetadata()
{
	return d->getPlayer()->GetMetadata();
}

/*!
 *  \brief Return the status of "Media Player"
 *  \return MprisDBusStatus Struct holding status data.
*/
const MprisDBusStatus MprisControl::GetStatus()
{
	MprisDBusStatus status = d->getPlayer()->GetStatus();
	return status;

}
