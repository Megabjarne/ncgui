
#include "container_split.h"

#include <iostream>
using std::cerr;

using namespace ncgui;
using std::string;
using std::min;

split::split(const std::string _name, const enum orientation _orientation, const partsize _size1, const partsize _size2){
	name = _name;
	orientation = _orientation;
	size1 = _size1;
	size2 = _size2;
}

void split::setsize(const int partnumber, const partsize _size){
	if (partnumber == 0)
		size1 = _size;
	if (partnumber == 1)
		size2 = _size;
}

void split::setelement(const int partnumber, element_generic* p){
	if (partnumber == 0)
		part1 = p;
	if (partnumber == 1)
		part2 = p;
}

element_generic* split::getelement(const string elementname){
	if (name == elementname)
		return this;
	if (part1 != nullptr){
		element_generic *p1ret = part1->getelement(elementname);
		if (p1ret != nullptr)
			return p1ret;
	}
	if (part2 != nullptr){
		element_generic *p2ret = part2->getelement(elementname);
		if (p2ret != nullptr)
			return p2ret;
	}
	return nullptr;
}

void split::resize(const ncgui::rectangle rect){
	// the split element doesn't need to remember it's position, so we just notify the underlying elems
	int len1 = -1;
	int len2 = -1;
	int lenmax = (orientation==VERTICAL)?rect.w:rect.h;
	auto t1 = size1.type;
	auto t2 = size2.type;
	
	if (t1 == partsize::ABSOLUTE)
		len1 = size1.size;
	if (t2 == partsize::ABSOLUTE)
		len2 = size2.size;
	if (t1 == partsize::PERCENTAGE)
		len1 = (int)((((float)lenmax) * size1.percentage)/100);
	if (t1 == partsize::PERCENTAGE)
		len2 = (int)((((float)lenmax) * size2.percentage)/100);
	if (t1 == partsize::ANY && t2 == partsize::ANY){
		len1 = lenmax/2;
		len2 = lenmax-len1;
	}
	if (len1 + len2 > lenmax){
		// if they're the same type, then just split the reduction evenly
		if ((t1 == t2)){
			int lensum = len1 + len2;
			len1 = (len1 * lenmax) / lensum;
			len2 = (len2 * lenmax) / lensum;
			if (len1+len2 < lenmax)
				len1 = lenmax - len2;
		}
		else
		// absolute takes precedence
		if (t1 == partsize::ABSOLUTE){
			len1 = min(len1, lenmax);
			len2 = lenmax - len1;
		}
		else
		if (t2 == partsize::ABSOLUTE){
			len2 = min(len2, lenmax);
			len1 = lenmax - len2;
		}
		else
		// then comes percentage
		if (t1 == partsize::PERCENTAGE){
			len1 = min(len1, lenmax);
			len2 = lenmax - len1;
		}
		else
		if (t2 == partsize::PERCENTAGE){
			len2 = min(len2, lenmax);
			len1 = lenmax - len2;
		}
	}
	if (len1 == -1)
		len1 = lenmax - len2;
	if (len2 == -1)
		len2 = lenmax - len1;
	if (orientation == VERTICAL){
		if (part1 != nullptr){
			part1->resize(rectangle(rect.x, rect.y, len1, rect.h));
		}
		if (part2 != nullptr){
			part2->resize(rectangle(rect.x+len1, rect.y, len2, rect.h));
		}
	}else{
		if (part1 != nullptr){
			part1->resize(rectangle(rect.x, rect.y, rect.w, len1));
		}
		if (part2 != nullptr){
			part2->resize(rectangle(rect.x, rect.y+len1, rect.w, len2));
		}
	}
}

void split::redraw(){
	if (part1 != nullptr)
		part1->redraw();
	if (part2 != nullptr)
		part2->redraw();
}

