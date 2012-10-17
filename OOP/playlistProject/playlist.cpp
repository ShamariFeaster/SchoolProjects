/* File: PlayList.h
   Author: Shamari Feaster
   Description: Arranges and manages song objects into
   playlists
*/
#include <iostream>	
#include "playlist.h"
using namespace std;



PlayList::PlayList()
{
    playlist = new Song[1];
    song_ctr = 1;
    play_state = 0;
    mode = NORMAL;
}


PlayList::~PlayList()
{
   //delete [] playlist;
}


PlayList operator+(const PlayList& p, const Song& s)
{
	PlayList tmp; 
	tmp.resize(p.playlist, p.song_ctr);
	tmp.AddSong(s);
	return tmp;

}
PlayList operator+(const PlayList& lhs, const PlayList& rhs)
{
	PlayList tmp;
	int x;
	int y;
	for(x = 0; x < lhs.song_ctr; x++)
	{
		tmp.AddSong(lhs.playlist[x]);
	}
	for(y = 0; y < rhs.song_ctr; y++)
	{
		tmp.AddSong(rhs.playlist[x]);
	}	
	return tmp;
}
PlayList operator-(const PlayList& p, const Song& s)
{
	PlayList tmp;
	tmp.resize(p.playlist, p.song_ctr);
	tmp.DeleteSong(s);
	return tmp;
}

void PlayList::AddSong(const Song& s)
{
	int x;
	//add 1 song to the song_ctr
	int new_size = 1;
	new_size += song_ctr;
	//new array w/ 1 additional spot
	Song* new_array = new Song[new_size]; 

	for(x = 0; x < song_ctr; x++)
	{
	//populate new array with old songs
		new_array[x] = playlist[x];
	}
    //put new song on the end of new array
	new_array[new_size - 1] = s;
	song_ctr++;
	//replace old array with new one
	(*this).resize(new_array, new_size);
	//memory clean up
	delete [] new_array;
	new_array = NULL;

}

void PlayList::resize(Song* song_array, int new_size)
{
    //release playlist pre-resize
	delete [] playlist;
	//re-allocate playlist with new size
	playlist = new Song[new_size];
	int x;
	for(x = 0; x < new_size; x++)
	{
		//populate the array
        playlist[x] = song_array[x];   
    }
}

bool PlayList::DeleteSong(const Song& s)
{
	
	int x;
	int delete_ctr = 0;
	bool copy_found = false;
	//cycle thru and mark songs that are copies
	//this is to find the size of the new array
    for(x = 0; x < song_ctr; x++)
	{
		if(playlist[x] == s)
		{
			delete_ctr++;
			copy_found = true;
		}
		//cout << (s == playlist[x]) << endl;
	}
	//size of the array minus all copies
	int new_size = song_ctr - delete_ctr;
	int new_array_ctr = 0;
	//nothing more to do if copy not found
    if(!copy_found)
	   return false;
	//start deletion process here   
	Song* new_array = new Song[new_size];

	//for every song that is not a match put it into new array
	if(copy_found)
	{
		for(x = 0; x < song_ctr; x++)
		{
			if(!(s == playlist[x]))
			{
				//prevents out of bound error
				if(new_array_ctr < new_size)
				{
					new_array[new_array_ctr] = playlist[x];
					new_array_ctr++;
				}
			}

		}
		//reflects the new amount of songs
		song_ctr -= delete_ctr;
		//replace old array with new one
		(*this).resize(new_array, new_size);
	}
    //memory cleanup
	delete [] new_array;
	new_array = NULL;

	return copy_found;

}

void PlayList::Play()
{
    
	switch(mode)
	{
        case NORMAL:
			//prevents out of bounds error on playlist array	
            if(play_state < song_ctr)
	        {
                cout << playlist[play_state];
                play_state++;
            }
            else
            {
				//starts playlist over again 
                play_state = 0;
                cout << playlist[play_state];
                play_state++;
            }
           
            break;
           
        case REPEAT:
			//doesn't increment play_state so plays same song repeatedly
            cout << playlist[play_state];
            break;
        
        default:
            cout << "Your Mode Is Invalid. Please Select Again." << endl;
    }
}

PlayList PlayList::Intersect(const PlayList& p)
{
	int x;
	int y;
	int param_ctr = p.song_ctr;		//parameter's playlist size alias
	
	bool dup_flg = false;			//signals duplicate find
    
	PlayList NewPlayList;			//object to be returned
	int new_ctr = 0; 				//new playlist song counter

	//find the size of the new array of intersected
    for(x = 0; x < song_ctr; x++)
	{
		for(y = 0; y < param_ctr; y++)
		{
			//if the song is common to both and dup_flg is used to make sure we
			//only take one instance of the common song
          	if(
				 (playlist[x] == p.playlist[y]) &&
				 !dup_flg
			   )
			{
				new_ctr++;
				dup_flg = true;
			}
		}
		dup_flg = false;
	}
	//makes sure it's reset
	dup_flg = false;
	
    //if there were no intersections stop here
    if(!new_ctr)
        return NewPlayList;
	//amount of all song's common to both playlists
    NewPlayList.song_ctr = new_ctr;
	//holder array for list common songs
    Song* new_array = new Song[new_ctr];
	//used to index the new array
	int new_ctr2 = 0;

	for(x = 0; x < song_ctr; x++)
	{
		for(y = 0; y < param_ctr; y++)
		{
			if(
				 (playlist[x] == p.playlist[y]) &&
				 !dup_flg
			   )
			{
				if(new_ctr2 < new_ctr)
				{
					new_array[new_ctr2] = playlist[x];
					new_ctr2++;
					dup_flg = true;
				}
			}


		}
		dup_flg = false;
	}
	//replace old array with new one
    NewPlayList.resize(new_array, new_ctr);

    delete [] new_array;
    new_array = NULL;

	return NewPlayList;

}

void PlayList::ShowAll()
{
	int x = 0;
	for(x = 0; x < song_ctr; x++)
	{
		cout << playlist[x] << endl;
	}
}

void PlayList::SetMode(Mode m)
{
	mode = m;
}




