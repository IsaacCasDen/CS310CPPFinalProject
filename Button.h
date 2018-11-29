//#ifndef BUTTON_H
//#define BUTTON_H

#pragma once

#include "Drawable.h"
#include <string>
class Button :
	public Drawable
{
public:
	Button();
	Button(std::string text);
	Button(std::string text, double fontSize);
	~Button();

	void update();
	void draw();

	std::string getText();
	void setText(std::string text);

	double getFontSize();
	void setFontSize(double value);

	ofColor getBackgroundColor();
	void setBackgroundColor(ofColor color);

	ofColor getForegroundColor();
	void setForegroundColor(ofColor color);

protected:
	void initFont();

private:
	ofTrueTypeFont font;
	std::string text = "Button";
	double fontSize = 10;

	ofColor backgroundColor = ofColor(0,0,0);
	ofColor foregroundColor = ofColor(127,127,127);
	ofColor borderColor = ofColor(0, 0, 0);

	double borderWidth = 1;
};

//#endif