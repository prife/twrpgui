#pragma once

//#include <string>
//#include "gui/rapidxml.h"

extern int tw_x_offset; //FIXME
extern int tw_y_offset;

// Utility Functions
int ConvertStrToColor(std::string str, COLOR* color);

rapidxml::xml_node<>* FindNode(rapidxml::xml_node<>* parent, const char* nodename, int depth = 0);

std::string LoadAttrString(rapidxml::xml_node<>* element, const char* attrname, const char* defaultvalue = "");

int LoadAttrInt(rapidxml::xml_node<>* element, const char* attrname, int defaultvalue = 0);

int LoadAttrIntScaleX(rapidxml::xml_node<>* element, const char* attrname, int defaultvalue = 0);

int LoadAttrIntScaleY(rapidxml::xml_node<>* element, const char* attrname, int defaultvalue = 0);

COLOR LoadAttrColor(rapidxml::xml_node<>* element, const char* attrname, bool* found_color, COLOR defaultvalue = COLOR(0,0,0,0));

COLOR LoadAttrColor(rapidxml::xml_node<>* element, const char* attrname, COLOR defaultvalue = COLOR(0,0,0,0));

FontResource* LoadAttrFont(rapidxml::xml_node<>* element, const char* attrname);

ImageResource* LoadAttrImage(rapidxml::xml_node<>* element, const char* attrname);

AnimationResource* LoadAttrAnimation(rapidxml::xml_node<>* element, const char* attrname);

bool LoadPlacement(rapidxml::xml_node<>* node, int* x, int* y, int* w = NULL, int* h = NULL, Placement* placement = NULL);

