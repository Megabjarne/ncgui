#include <ncgui/rawdisplay.h>

using namespace ncgui;
using std::string;

rawdisplay::rawdisplay(const string _name){
	win = newwin(1,1,1,1);
	name = _name;
}

void rawdisplay::resize(const rectangle rect){
	mvwin(win, rect.y, rect.x);
	wresize(win, rect.h, rect.w);
}

WINDOW* rawdisplay::getwindow(){
	return win;
}

