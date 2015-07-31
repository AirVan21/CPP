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
	uEyeCameraDriver();
	
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

	/**
		Disabling Cameras
	*/
	virtual INT disableUEyeCameras();
	
	/**
		Setting Auto Gain 
	*/
	virtual INT setAutoSensorGainShutter();
	
	/**
		Gets Image Format parameters
	*/
	virtual INT getImangeForamtParameters();

	/**
		Memory allocation for FreezeVideo()
	*/
	virtual INT allocMemoryForFreezeCapture();

private:
	/**
		XS Cameara Inforamtion
	*/
	vector<HIDS> *mCameraHandles;
	vector<INT> *mDeviceIDs;
	vector<INT> *mCameraIDs;
	/**
		Buffer Information for uEye Cameras
	*/
	vector<char*> *mCameraBuffers;
	vector<INT> *mCameraBufferIDs;

	IMAGE_FORMAT_INFO *mImageFormatInfo;

	INT getDeviceAndCamerasIDs();

};