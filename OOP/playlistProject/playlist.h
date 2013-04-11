/* File: PlayList.h
   Author: Shamari Feaster
   Description: Arranges and manages song objects into
   playlists
*/
#include <iostream>	
#include "song.h"	
using namespace std;


    enum Mode
    { 
        NORMAL, REPEAT
    };

class PlayList {

friend PlayList operator+(const PlayList& p, const Song& s);
friend PlayList operator+(const PlayList& lhs, const PlayList& rhs);
friend PlayList operator-(const PlayList& p, const Song& s);

public:
    PlayList();
    ~PlayList();
    //insert copy constructor here
    void AddSong(const Song& s);
	/*Add a new song to the playlist*/
    bool DeleteSong(const Song& s);
	/*Delete all occurances of the passed in song*/
    void SetMode(Mode m);
	/*Set the play mode*/
    void ShowAll();
	/*Prints all songs on the playlist*/
    void Play();
	/*Play (print) a song*/
	PlayList Intersect(const PlayList& p);
	/*Returns a PlayList with playlist that is intersection of the calling
	  object and passed in object's playlist*/
private:
    
    void resize(Song* s, int new_size);
	/*replaces the calling PlayList's playlist with the one passed in*/
    int play_state;		//song being played
    Song* playlist;		//array of songs
    int song_ctr;		//sound counter
    Mode mode;			//play mode

    
};
