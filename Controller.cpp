#include "Controller.h"



bool Controller::isSetup()
{
	return _isSetup;
}

ofSerial * Controller::getSerial()
{
	return serial;
}

int Controller::getDeviceId()
{
	return device.getDeviceID();
}

std::string Controller::getDevicePath()
{
	return device.getDevicePath();
}

std::string Controller::getDeviceName()
{
	return device.getDeviceName();
}

Controller::Controller()
{
}

Controller::Controller(ofSerialDeviceInfo device, int baud)
{
	this->device = device;
	serial = new ofSerial();
	_isSetup = serial->setup(getDevicePath(),baud);
}


Controller::~Controller()
{
}
