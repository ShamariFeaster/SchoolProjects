// sample main.cpp

#include <iostream>
#include "playlist.h"

using namespace std;

int main()
{
	PlayList a;
	PlayList b;
	PlayList c;
	
	Song s;
	Song s1;
	Song s2;
	
	s.Set("me", "you");
	s1.Set("chick", "ry");
	s2.Set("die", "too");

	a.AddSong(s);
	c = a + s1;
	c.ShowAll();

	return 0;
}
