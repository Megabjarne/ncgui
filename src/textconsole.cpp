#include <ncgui/textconsole.h>

using namespace ncgui;

textconsole::textconsole(const std::string _name, const int _maxlines){
	name = _name;
	maxlines = _maxlines;
}

void textconsole::addline(const std::string line, bool immediate_redraw){
	textlines.push_back(line);
	while (textlines.size() > maxlines)
		textlines.pop_front();
	if (immediate_redraw)
		this->redraw();
}

void textconsole::setprompt(std::string newprompt, bool immediate_redraw){
	promptstring = newprompt;
	if (immediate_redraw)
		this->redraw();
}

void textconsole::showprompt(bool newpromptvisible){
	promptvisible = newpromptvisible;
}

void textconsole::clear(){
	textlines.clear();
}

void textconsole::redraw(){
	assert(win != nullptr);
	wclear(win);
	//write form bottom up
	int ch = h-1;
	// if we are to draw the prompt
	if (promptvisible){
		wmove(win, ch, 0);
		if (promptstring.size() < w)
			wprintw(win, "%s", promptstring.c_str());
		else
			wprintw(win, "%s", (promptstring.substr(0, w-3) + "...").c_str());
		ch--;
	}
	for (auto i = textlines.rbegin(); i != textlines.rend() && ch >= 0; i++){
		wmove(win, ch, 0);
		//if too long for the element width
		if (i->size() > w){
			std::string s = i->substr(0, w-3) + "...";
			wprintw(win, "%s", s.c_str());
		}else{
			wprintw(win, "%s", i->c_str());
		}
		ch--;
	}
	wrefresh(win);
}

void textconsole::resize(const rectangle rect){
	if (win == nullptr)
		win = newwin(rect.h, rect.w, rect.y, rect.x);
	else {
		mvwin(win, rect.y, rect.x);
		wresize(win, rect.h, rect.w);
	}
	h = rect.h;
	w = rect.w;
	redraw();
}

int textconsole::igetch(){
	assert(win != nullptr);
	return wgetch(win);
}

