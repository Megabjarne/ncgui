#ifndef _guielement_textconsole_h
#define _guielement_textconsole_h

#include <string>
#include <list>
#include <ncurses.h>
#include <ncgui/guielement_generic.h>

namespace ncgui {
	
	class textconsole : public element_generic {
	private:
		std::list<std::string> textlines;
		std::string promptstring;
		bool promptvisible = false;
		int maxlines;
		WINDOW *win = nullptr;
		int h, w;
	
	public:
		textconsole(const std::string _name, const int _maxlines=100);
		void addline(const std::string line, bool immediate_redraw=true);
		void setprompt(std::string newprompt, bool immediate_redraw=true);
		void showprompt(bool newpromptvisible);
		void clear();
		void redraw();
		void resize(const rectangle);
		int igetch();
	
	};
	
}

#endif

