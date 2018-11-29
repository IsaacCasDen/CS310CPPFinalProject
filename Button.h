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

	double getHeight();
	void setHeight(double value);

	double getWidth();
	void setWidth(double value);

	virtual void setPosition(ofVec2f position);

protected:
	void initFont();
	void initFontBounds();
	virtual void setBounds(ofRectangle bounds);

	double requestedHeight = 0;
	double requestedWidth = 0;

private:
	
	ofTrueTypeFont font;
	std::string text = "Button";
	double fontSize = 10;
	double padding = 3;

	ofColor backgroundColor = ofColor(255,255,255);
	ofColor foregroundColor = ofColor(64,64,64);
	ofColor borderColor = ofColor(0, 0, 0);

	double borderWidth = 1;

	ofVec2f fontPos;
};

//#endif