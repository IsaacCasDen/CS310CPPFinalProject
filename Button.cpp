#include "Button.h"



Button::Button()
{
	initFont();
}

Button::Button(std::string text)
{
	setText(text);
}

Button::Button(std::string text, double fontSize)
{
	setText(text);
	setFontSize(fontSize);
}


Button::~Button()
{
}

void Button::update()
{
}

void Button::draw()
{
	ofRectangle b = getBounds();

	ofSetColor(borderColor);
	ofNoFill();
	ofDrawRectangle(b);
	
	ofSetColor(backgroundColor);
	ofFill();
	ofDrawRectangle(b.getLeft() + borderWidth, b.getTop() + borderWidth, b.getWidth() - 2 * borderWidth, b.getHeight() - 2 * borderWidth);

	font.drawString(getText(),b.getLeft() + borderWidth, b.getTop() + borderWidth);
}

std::string Button::getText()
{
	return text;
}

void Button::setText(std::string text)
{
	this->text = text;
	initFont();
}

double Button::getFontSize()
{
	return fontSize;
}

void Button::setFontSize(double value)
{
	fontSize = value;
	initFont();
}

ofColor Button::getBackgroundColor()
{
	return backgroundColor;
}

void Button::setBackgroundColor(ofColor color)
{
	backgroundColor = color;
}

ofColor Button::getForegroundColor()
{
	return foregroundColor;
}

void Button::setForegroundColor(ofColor color)
{
	foregroundColor = color;
}

void Button::initFont()
{
	font.load("arial.ttf", fontSize, true, true);
	font.setLineHeight(fontSize*.6);
	font.setLetterSpacing(1.037);

	setSize(ofVec2f(font.stringWidth(getText())+2*borderWidth, font.stringHeight(getText()))+2*borderWidth);
}
