#include <ncgui/box.h>

using namespace ncgui;

box::box(const std::string _name, const std::string _title){
	name = _name;
	title = _title;
	win = newwin(1,1,0,0);
}

void box::redraw(){
	if (elem != nullptr)
		elem->redraw();
}

void box::resize(const rectangle rect){
	wresize(win, rect.h, rect.w);
	mvwin(win, rect.y, rect.x);
	
	// we onlyredraw this window when resizing
	wclear(win);
	::box(win, 0, 0);
	if (title != ""){
		wmove(win, 0, 1);
		wprintw(win, " %s ", title.c_str());
	}
	wrefresh(win);
	
	if (elem != nullptr)
		elem->resize(rectangle(rect.x+1, rect.y+1, rect.w-2, rect.h-2));
}

void box::setelement(element_generic *_elem){
	elem = _elem;
}

void box::settitle(const std::string _title){
	title = _title;
}

element_generic* box::getelement(const std::string elementname){
	if (name == elementname)
		return this;
	return elem->getelement(elementname);
}

