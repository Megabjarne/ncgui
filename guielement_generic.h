#ifndef _guielement_generic_h
#define _guielement_generic_h

#include <string>
#include <ncurses.h>
#include <iostream>
#include <assert.h>

using std::cerr;

namespace ncgui {
	
	struct rectangle {
		int x, y, w, h;
		rectangle(int _x, int _y, int _w, int _h):x(_x),y(_y),w(_w),h(_h){}
	};
	
	struct partsize {
		enum {
			PERCENTAGE,
			ABSOLUTE,
			ANY
		} type;
		union {
			float percentage;
			int size;
		};
		int minsize;
		
		partsize(float _percentage){type = PERCENTAGE; percentage = _percentage;}
		partsize(int _size){type = ABSOLUTE; size = _size;}
		partsize(){type = ANY;}
	};
	enum orientation {
		HORIZONTAL,
		VERTICAL
	};
	
	class element_generic {
	public:
		std::string name;
		
		// makes the element cover the entire terminal screen
		void maximize(){int x, y; getmaxyx(stdscr, y, x); this->resize(rectangle(0,0,x,y));}
		// moves the element to coordinate and set size
		virtual void resize(const rectangle){};
		// searches tree for element with this name, returns nullptr if not found
		virtual element_generic* getelement(const std::string elementname){if (name == elementname) return this; return nullptr;}
		// same as getelement, but stops program if it doesn't find it (asserts that it exists)
		element_generic* agetelement(const std::string elementname){
			auto r = this->getelement(elementname); if (r == nullptr) cerr<<"unable to find element '"<<elementname<<"'\n"; assert(r != nullptr); return r;}
		// same as getelement, but returns pointer as specific type
		template <class T>
		T* getelement(const std::string elementname){ return (T*)(this->getelement(elementname)); }
		// same as agetelement, but returns pointer as specific type
		template <class T>
		T* agetelement(const std::string elementname){ return (T*)(this->agetelement(elementname)); }
		virtual void redraw(){};
		
	};
	
};

#endif

