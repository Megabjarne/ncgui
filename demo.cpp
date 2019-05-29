
#include <ncurses.h>
#include <string>

// we include the header files of the ncgui library
#include "container_split.h"
#include "guielement_placeholder.h"
#include "guielement_window.h" // not used here
#include "container_box.h"
#include "guielement_textconsole.cpp"

int main(){
	/* --------------------- GUI SESSION SETUP --------------------- */
	
	// we start ncurses, and disable the echoing of user input
	initscr();
	noecho();
	
	/* --------------------- GUI ELEMENT CREATION --------------------- */
	
	// splits the input and display. it's a horizontal split, with the first (topmost)
	// part being 6 characters big, the second one being automatic
	ncgui::split spl = ncgui::split("", ncgui::HORIZONTAL, ncgui::partsize(6), ncgui::partsize());
	
	// box to hold the console, with the title "console"
	ncgui::box inputbox = ncgui::box("", "console");
	// input console, named "input_console"
	ncgui::textconsole cons = ncgui::textconsole("input_console");
	
	// box to hold a display, in this case using a "placeholder", which just displays numbers
	// alternatively we could for example use the "window" element, which allows you to draw
	// and display anything you want on it
	ncgui::box displaybox = ncgui::box("", "bunch of numbers");
	// the placeholder display, which will simply display a bunch of numbers
	ncgui::placeholder disp = ncgui::placeholder("");
	
	// the first string argument when creating elements are the element name argument,
	// leaving them blank means we don't name it, which makes it impossible to search
	// for them in the gui tree. We only name the elements we need to access later.
	
	/* --------------------- GUI STRUCTURE CREATION --------------------- */
	
	// we put the input console in the input box
	inputbox.setelement(&cons);
	// we put the display in the displaybox
	displaybox.setelement(&disp);
	
	// we put the inputbox at the top of the split
	spl.setelement(0, &inputbox);
	// we put the display box at the bottom of the split
	spl.setelement(1, &displaybox);
	
	// we make the split cover the entire screen, all the elements contained in it
	// will then be resized to fit inside their respective containers
	spl.maximize();
	// we redraw the split, and in turn all the elements contained in it
	spl.redraw();
	
	/* --------------------- INPUT AND DISPLAY LOOP --------------------- */
	
	// we read input until we get a quit command (user presses 'q')
	int c;
	while ((c = cons.igetch()) != 'q'){
		// we search the split element for an element named "input_console",
		// it is returned as a reference to a textconsole, we add the line "read: [character"
		std::string displaystring = std::string("read: ") + (char)c;
		spl.agetelement<ncgui::textconsole>("input_console")->addline(displaystring);
		// we use the agetelement instead of getelement, getelement returns a null if no
		// element with that name is found, agetelement (assert getelement) halts the program
		// if not found.
		
		// to display this change, the textconsole needs to be redrawn. we can either redraw
		// only the textconsole element:
		// cons.redraw() or spl.agetelement<ncgui::textconsole>("input_console")->redraw()
		// or we can redraw parts of or the entire gui tree
		spl.redraw();
	}
	
	/* --------------------- CLEANUP --------------------- */
	
	// we terminate the ncurses session
	endwin();
	return 0;
}

