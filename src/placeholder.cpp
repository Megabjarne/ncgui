
#include <ncgui/placeholder.h>

using namespace ncgui;

placeholder::placeholder(const std::string _name){
	name = _name;
}

void placeholder::resize(const ncgui::rectangle rect){
	if (win == nullptr){
		win = newwin(rect.h, rect.w, rect.y, rect.x);
	} else {
		mvwin(win, rect.y, rect.x);
		wresize(win, rect.h, rect.w);
	}
	w = rect.w;
	h = rect.h;
	for (int x = 0; x < w; x++){
		for (int y = 0; y < h; y++){
			wmove(win, y, x);
			waddch(win, '0' + ((x+y)%10));
		}
	}
}

void placeholder::redraw(){
	wrefresh(win);
}

