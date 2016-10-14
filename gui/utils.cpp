#include "gui/pages.h"

using namespace rapidxml;

// Helper routine to convert a string to a color declaration
int ConvertStrToColor(std::string str, COLOR* color)
{
	// Set the default, solid black
	memset(color, 0, sizeof(COLOR));
	color->alpha = 255;

	// Translate variables
	DataManager::GetValue(str, str);

	// Look for some defaults
	if (str == "black")		return 0;
	else if (str == "white")	{ color->red = color->green = color->blue = 255; return 0; }
	else if (str == "red")		{ color->red = 255; return 0; }
	else if (str == "green")	{ color->green = 255; return 0; }
	else if (str == "blue")		{ color->blue = 255; return 0; }

	// At this point, we require an RGB(A) color
	if (str[0] != '#')
		return -1;

	str.erase(0, 1);

	int result;
	if (str.size() >= 8) {
		// We have alpha channel
        std::string alpha = str.substr(6, 2);
		result = strtol(alpha.c_str(), NULL, 16);
		color->alpha = result & 0x000000FF;
		str.resize(6);
		result = strtol(str.c_str(), NULL, 16);
		color->red = (result >> 16) & 0x000000FF;
		color->green = (result >> 8) & 0x000000FF;
		color->blue = result & 0x000000FF;
	} else {
		result = strtol(str.c_str(), NULL, 16);
		color->red = (result >> 16) & 0x000000FF;
		color->green = (result >> 8) & 0x000000FF;
		color->blue = result & 0x000000FF;
	}
	return 0;
}

// Helper APIs
xml_node<>* FindNode(xml_node<>* parent, const char* nodename, int depth /* = 0 */)
{
	if (!parent)
		return NULL;

	xml_node<>* child = parent->first_node(nodename);
	if (child)
		return child;

	if (depth == 10) {
		LOGERR("Too many style loops detected.\n");
		return NULL;
	}

	xml_node<>* style = parent->first_node("style");
	if (style) {
		while (style) {
			if (!style->first_attribute("name")) {
				LOGERR("No name given for style.\n");
				continue;
			} else {
				std::string name = style->first_attribute("name")->value();
				xml_node<>* node = PageManager::FindStyle(name);

				if (node) {
					// We found the style that was named
					xml_node<>* stylenode = FindNode(node, nodename, depth + 1);
					if (stylenode)
						return stylenode;
				}
			}
			style = style->next_sibling("style");
		}
	} else {
		// Search for stylename in the parent node <object type="foo" style="foo2">
		xml_attribute<>* attr = parent->first_attribute("style");
		// If no style is found anywhere else and the node wasn't found in the object itself
		// as a special case we will search for a style that uses the same style name as the
		// object type, so <object type="button"> would search for a style named "button"
		if (!attr)
			attr = parent->first_attribute("type");
		// if there's no attribute type, the object type must be the element name
		std::string stylename = attr ? attr->value() : parent->name();
		xml_node<>* node = PageManager::FindStyle(stylename);
		if (node) {
			xml_node<>* stylenode = FindNode(node, nodename, depth + 1);
			if (stylenode)
				return stylenode;
		}
	}
	return NULL;
}

std::string LoadAttrString(xml_node<>* element, const char* attrname, const char* defaultvalue)
{
	if (!element)
		return defaultvalue;

	xml_attribute<>* attr = element->first_attribute(attrname);
	return attr ? attr->value() : defaultvalue;
}

int LoadAttrInt(xml_node<>* element, const char* attrname, int defaultvalue)
{
    std::string value = LoadAttrString(element, attrname);
	// resolve variables
	DataManager::GetValue(value, value);
	return value.empty() ? defaultvalue : atoi(value.c_str());
}

int LoadAttrIntScaleX(xml_node<>* element, const char* attrname, int defaultvalue)
{
	return scale_theme_x(LoadAttrInt(element, attrname, defaultvalue));
}

int LoadAttrIntScaleY(xml_node<>* element, const char* attrname, int defaultvalue)
{
	return scale_theme_y(LoadAttrInt(element, attrname, defaultvalue));
}

COLOR LoadAttrColor(xml_node<>* element, const char* attrname, bool* found_color, COLOR defaultvalue)
{
    std::string value = LoadAttrString(element, attrname);
	*found_color = !value.empty();
	// resolve variables
	DataManager::GetValue(value, value);
	COLOR ret = defaultvalue;
	if (ConvertStrToColor(value, &ret) == 0)
		return ret;
	else
		return defaultvalue;
}

COLOR LoadAttrColor(xml_node<>* element, const char* attrname, COLOR defaultvalue)
{
	bool found_color = false;
	return LoadAttrColor(element, attrname, &found_color, defaultvalue);
}

FontResource* LoadAttrFont(xml_node<>* element, const char* attrname)
{
	std::string name = LoadAttrString(element, attrname, "");
	if (name.empty())
		return NULL;
	else
		return PageManager::GetResources()->FindFont(name);
}

ImageResource* LoadAttrImage(xml_node<>* element, const char* attrname)
{
	std::string name = LoadAttrString(element, attrname, "");
	if (name.empty())
		return NULL;
	else
		return PageManager::GetResources()->FindImage(name);
}

AnimationResource* LoadAttrAnimation(xml_node<>* element, const char* attrname)
{
	std::string name = LoadAttrString(element, attrname, "");
	if (name.empty())
		return NULL;
	else
		return PageManager::GetResources()->FindAnimation(name);
}

int tw_x_offset = 0;
int tw_y_offset = 0;

bool LoadPlacement(xml_node<>* node, int* x, int* y, int* w /* = NULL */, int* h /* = NULL */, Placement* placement /* = NULL */)
{
	if (!node)
		return false;

	if (node->first_attribute("x"))
		*x = LoadAttrIntScaleX(node, "x") + tw_x_offset;

	if (node->first_attribute("y"))
		*y = LoadAttrIntScaleY(node, "y") + tw_y_offset;

	if (w && node->first_attribute("w"))
		*w = LoadAttrIntScaleX(node, "w");

	if (h && node->first_attribute("h"))
		*h = LoadAttrIntScaleY(node, "h");

	if (placement && node->first_attribute("placement"))
		*placement = (Placement) LoadAttrInt(node, "placement");

	return true;
}

