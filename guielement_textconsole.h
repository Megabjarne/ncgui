#ifndef _guielement_textconsole_h
#define _guielement_textconsole_h

#include <string>
#include <list>
#include <ncurses.h>
#include "guielement_generic.h"

namespace ncgui {
	
	class textconsole : public element_generic {
	private:
		std::list<std::string> textlines;
		int maxlines;
		WINDOW *win = nullptr;
		int h, w;
	
	public:
		textconsole(const std::string _name, const int _maxlines=100);
		void addline(const std::string line, bool immediate_redraw=true);
		void clear();
		void redraw();
		void resize(const rectangle);
		int igetch();
	
	};
	
}

#endif

