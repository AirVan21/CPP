#include <stdio.h>
#include <iostream>
#include "uEye.h"
#include <vector>

using std::cout;
using std::endl;
using std::vector;

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
	virtual INT initUEyeCameras();

	/**
		Displaying Camera information
	*/
	void displayCameraInfo();

private:

	vector<HIDS> *mCameraHandles;
	vector<INT> *mDeviceIDs;
	vector<INT> *mCameraIDs;

	char* mCameraBuffer;
	INT mCameraBufferID;

	INT getDeviceAndCamerasIDs();

};