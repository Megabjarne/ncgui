#include "guielement_window.h"

using namespace ncgui;
using std::string;

window::window(const string _name){
	win = newwin(1,1,1,1);
	name = _name;
}

void window::resize(const rectangle rect){
	mvwin(win, rect.y, rect.x);
	wresize(win, rect.h, rect.w);
}

WINDOW* window::getwindow(){
	return win;
}

