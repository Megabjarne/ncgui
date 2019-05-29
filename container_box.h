#ifndef _container_box_h
#define _container_box_h

#include <string>
#include <ncurses.h>
#include "guielement_generic.h"

namespace ncgui {
	
	class box : public element_generic {
	private:
		element_generic* elem = nullptr;
		WINDOW* win = nullptr;
		std::string title;
		
	public:
	
		box(const std::string _name, const std::string _title="");
		void redraw();
		void resize(const rectangle);
		void setelement(element_generic *_elem);
		void settitle(const std::string _title);
		element_generic* getelement(const std::string elementname);
		
	};
	
}

#endif

