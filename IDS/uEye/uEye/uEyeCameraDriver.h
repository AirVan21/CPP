#include <stdio.h>
#include <iostream>
#include "uEye.h"

using std::cout;
using std::endl;

class uEyeCameraDriver
{

public: 
	/**
		Constructor
	*/
	uEyeCameraDriver(INT cameraID);
	
	/**
		Destructor
	*/
	virtual ~uEyeCameraDriver();
	
	/**
		uEye Camera Initialization
	*/
	virtual INT initUEyeCamera(INT cameraID);

	/**
		Displaying Camera information
	*/
	void displayCameraInfo();

private:

	HIDS mCameraHandle;
	INT mCameraID;

	char* mCameraBuffer;
	INT mCameraBufferID;


};