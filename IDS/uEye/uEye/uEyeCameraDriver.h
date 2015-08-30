#include <stdio.h>
#include <stdlib.h>
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
		Color depth parameter for pictures
	*/
	static const INT bitsPerPixel = 24;
	
	/**
		Constructor
	*/
	uEyeCameraDriver();
	
	/**
		Destructor
	*/
	virtual ~uEyeCameraDriver();
	
	/**
		Basic preparations before campture
		1. Initialization for all uEye cameras
		2. Auto Gain setting
		3. Auto Focus setting
		4. Getting parameters for picture with highest resolution
		5. Memory allocation for snapshots (for all connected cameras)
	*/
	INT cameraPreparation();

	/**
		Displaying information about connected uEye cameras
		(Function for testing connection)
	*/
	void displayCameraInfo();

	/**
		Disabling connected uEye cameras
	*/
	INT disableUEyeCameras();
	
	/**
		Allocates memory for images with params in mImageFormatInfo
		Allocation performs for every connected camera
		Every image memory is activated
	*/
	INT allocMemoryForFreezeCapture();

	/**
		Frees memory for all cameras which was allocated earlier
	*/
	INT freeMemoryForFreezeCapture();
	
	/**
		Makes snapshots and store in in RAM (one by one transfer with WAIT param)
	*/
	INT makeSnapshotInFreezeCaptureWait();
	
	/**
		Makes snapshots and store in in RAM (transfer with NO_WAIR param and event handling method)
	*/
	INT makeSnapshotInFreezeCaptureNoWait();

	/**
		Store snapshots on disk using PNG format 
		(for e.g. "01.png")
	*/
	INT storeSnapshots();

	/**
		Sets all connected uEye cameras to standby mode
	*/
	INT setToStandbyMode();
	
	/**
		Sets all connected uEye camera to FreeRun mode
	*/
	INT setToFreeRunMode();
	
	/**
		Setting Auto Gain for all uEye cameras
	*/
	INT setAutoSensorGainShutter();

	/**
		Enabling Auto Focus for all uEye cameras
	*/
	INT setAutoFocus();

	/**
		Make parallel snapshots
	*/
	INT makeSnapshotInFreezeCaptureParallel();
	
	/**
		Access captured images in camera memory
	*/
	INT accessCapturedImages();

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
	/**
		Info about image parameters which is used for capture
	*/
	IMAGE_FORMAT_INFO *mImageFormatInfo;
	
	/**
		uEye Camera Initialization
	*/
	virtual INT initUEyeCameras();

	/**
		Gets Image Format parameters
	*/
	virtual INT getImangeForamtParameters();
	
	/**
		Retireves Device and Cameras IDs
	*/
	INT getDeviceAndCamerasIDs();
};