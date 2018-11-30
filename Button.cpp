#include "Button.h"
#include <math.h>


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
	ofColor currentColor = ofApp::getOfColor();
	ofRectangle b = getBounds();

	ofSetColor(borderColor);
	ofNoFill();
	ofDrawRectangle(b);
	
	(isClicking())?
		ofSetColor(clickColor):
		(isHover()) ? ofSetColor(hoverColor) : ofSetColor(backgroundColor);
	ofFill();
	ofDrawRectangle(b.getLeft() + borderWidth, b.getTop() + borderWidth, b.getWidth() + borderWidth - padding, b.getHeight() + borderWidth - padding);

	ofSetColor(foregroundColor);
	font.drawString(getText(),fontPos.x,fontPos.y);

	ofApp::setOfColor(currentColor);
}

std::string Button::getText()
{
	return text;
}

void Button::setText(std::string text)
{
	this->text = text;
	initFontBounds();
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

double Button::getHeight()
{
	return getBounds().getHeight();
}

void Button::setHeight(double value)
{
	(value >= 0) ? requestedHeight = value : 0;
	initFontBounds();
}

double Button::getWidth()
{
	return getBounds().getWidth();
}

void Button::setWidth(double value)
{
	(value >= 0) ? requestedWidth = value : 0;
	initFontBounds();
}

void Button::mouseMoved(int x, int y)
{
	if (isIntersecting(x, y)) {
		_isHover = true;
	}
	else {
		_isHover = false;
		_isClicking = false;
	}
}

void Button::mousePressed(int x, int y, int button)
{
	if (isIntersecting(x, y) && button == 0) {
		_isClicking = true;
	}
	else {
		_isClicking = false;
	}
}

void Button::mouseReleased(int x, int y, int button)
{
	if (isIntersecting(x, y) && isClicking()  && button == 0) {
		ofNotifyEvent(clicked);
	}
	
	_isClicking = false;
}

void Button::setPosition(ofVec2f position)
{
	Drawable::setPosition(position);
	initFontBounds();
}

bool Button::isHover()
{
	return _isHover;
}

bool Button::isClicking()
{
	return _isClicking;
}

void Button::initFont()
{
	font.load("arial.ttf", fontSize, true, true);
	font.setLineHeight(fontSize*.6);
	font.setLetterSpacing(1.037);

	initFontBounds();
}
void Button::initFontBounds() {

	ofVec2f fSize = ofVec2f(font.stringWidth(getText()), font.stringHeight(getText()));
	ofVec2f bSize = ofVec2f(
		max(requestedWidth, fSize.x + 2 * borderWidth + 2 * padding),
		max(requestedHeight, fSize.y + 2 * borderWidth + 2 * padding));

	double hPad = (bSize.x - fSize.x - 2 * borderWidth - 2 * padding) / 2;
	double vPad = (bSize.y - fSize.y - 2 * borderWidth - 2 * padding) / 2;
	
	setSize(bSize);
	fontPos = ofVec2f(getBounds().getLeft() + hPad, getBounds().getBottom() - vPad);
	
}

void Button::setBounds(ofRectangle bounds)
{
	Drawable::setBounds(bounds);

}