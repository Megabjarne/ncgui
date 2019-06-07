#ifndef _guielement_window_h
#define _guielement_window_h

#include <ncgui/guielement_generic.h>
#include <ncurses.h>
#include <string>

// simpy a container providing direct access to it's ncurses screen
namespace ncgui{
	
	class rawdisplay : public element_generic {
	private:
		WINDOW* win = nullptr;
		
	public:
		rawdisplay(const std::string _name);
		void resize(const rectangle);
		WINDOW* getwindow();
		
	};
	
}

#endif

