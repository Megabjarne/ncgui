#ifndef _guielement_placeholder_h
#define _guielement_placeholder_h

#include <ncgui/guielement_generic.h>
#include <ncurses.h>
#include <string>

namespace ncgui {
	
	class placeholder : public element_generic {
	private:
		WINDOW* win = nullptr;
		int w, h;
		
	public:
		
		placeholder(const std::string _name);
		void resize(const ncgui::rectangle rect);
		void redraw();
		
	};
	
};

#endif

