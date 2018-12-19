#pragma once

#include "ofSerial.h"

class Controller
{
public:

	bool isSetup();

	ofSerial * getSerial();

	int getDeviceId();
	std::string getDevicePath();
	std::string getDeviceName();


	Controller();
	Controller(ofSerialDeviceInfo device, int baud);
	~Controller();

private:

	ofSerial * serial;
	ofSerialDeviceInfo device;
	bool _isSetup = false;
};

