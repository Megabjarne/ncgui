#ifndef _container_split_h
#define _container_split_h

#include <ncgui/guielement_generic.h>

namespace ncgui {
	
	class split : public element_generic {
	private:
		enum orientation orientation;
		partsize size1, size2;
		element_generic *part1=nullptr, *part2=nullptr;

	public:
		split(const std::string _name, const enum orientation _orientation, const partsize _size1, const partsize _size2);
		void setsize(const int partnumber, const partsize _size);
		void setelement(const int partnumber, element_generic* p);
		element_generic* getelement(const std::string elementname);
		void resize(const rectangle rect);
		void redraw();
	};
	
};

#endif

