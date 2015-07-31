#include "uEyeCameraDriver.h"

uEyeCameraDriver::uEyeCameraDriver() :
	mCameraHandles(new vector<HIDS>()),
	mCameraIDs(new vector<INT>()),
	mDeviceIDs(new vector<INT>()),
	mCameraBuffers(new vector<char*>()),
	mCameraBufferIDs(new vector<INT>()),
	mImageFormatInfo(NULL)
{}

uEyeCameraDriver::~uEyeCameraDriver()
{}

INT uEyeCameraDriver::initUEyeCameras()
{
	INT resultCode = IS_SUCCESS;
	if ((resultCode = uEyeCameraDriver::getDeviceAndCamerasIDs()) == IS_SUCCESS)
	{
		for (vector<INT>::iterator i = mDeviceIDs->begin(); i != mDeviceIDs->end(); i++)
		{
			HIDS cameraHandle = ((HIDS) *i) | IS_USE_DEVICE_ID;
			if ((resultCode = is_InitCamera(&cameraHandle, NULL)) == IS_SUCCESS)
			{
				cout << "Init PASS for Device ID = " << *i << endl;
				mCameraHandles->push_back(cameraHandle);
				// Sets DIM mode for handling images (not OpenGL, not DirectX)
				if ((resultCode = is_SetDisplayMode(cameraHandle, IS_SET_DM_DIB)) != IS_SUCCESS)
				{
					cout << "Device ID = " << *i << " has probem with DIM mode" << endl;
				}
			}
			else
			{
				cout << "Init FAIL for Device ID = " << *i << endl;
			}
		}
	}
	else
	{
		cout << "getDeviceAndCamerasIDs() goes wrong in initUEyeCameras()" << endl;
	}
	return resultCode;
}

INT uEyeCameraDriver::disableUEyeCameras()
{
	INT resultCode = IS_SUCCESS;
	for (vector<HIDS>::iterator i = mCameraHandles->begin(); i != mCameraHandles->end(); i++)
	{
		INT chechError = IS_SUCCESS;
		if ((chechError = is_ExitCamera(*i)) != IS_SUCCESS)
		{
			cout << "Problems with exit camera with Handle = " << *i << endl;
			resultCode = chechError;
		}
	}

	return resultCode;
}

void uEyeCameraDriver::displayCameraInfo()
{
	// At least one camera must be available
	INT uEyeCamAmount = 0;
	if (is_GetNumberOfCameras(&uEyeCamAmount) == IS_SUCCESS)
	{
		if (uEyeCamAmount >= 1)
		{
			// Create UEYE_CAMERA list 
			UEYE_CAMERA_LIST* pucl = (UEYE_CAMERA_LIST*) new BYTE[sizeof(DWORD) + uEyeCamAmount * sizeof(UEYE_CAMERA_INFO)];
			pucl->dwCount = uEyeCamAmount;
			//Retrieve camera information
			if (is_GetCameraList(pucl) == IS_SUCCESS)
			{
				for (int iCamera = 0; iCamera < (int)pucl->dwCount; iCamera++)
				{
					// Output of Camera Info
					printf("Camera %i : \n", iCamera);
					printf("  dwCameraId : %d\n", pucl->uci[iCamera].dwCameraID);
					printf("  dwDeviceId : %d\n", pucl->uci[iCamera].dwDeviceID);
					printf("  dwSensorId : %d\n", pucl->uci[iCamera].dwSensorID);
					printf("  CameraModel: %s\n", pucl->uci[iCamera].Model);
					printf("  CameraInUse: %d\n", pucl->uci[iCamera].dwInUse);
				}
			}
			delete[] pucl;
		}
	}
}

INT uEyeCameraDriver::setAutoSensorGainShutter()
{
	INT resultCode = IS_SUCCESS;
	double autoGainOn = 1;
	double dblDummy = 0;
	for (vector<HIDS>::iterator i = mCameraHandles->begin(); i != mCameraHandles->end(); i++)
	{
		INT errorCode = IS_SUCCESS;
		if ((errorCode = is_SetAutoParameter(*i, IS_SET_ENABLE_AUTO_SENSOR_GAIN_SHUTTER, &autoGainOn, &dblDummy)) != IS_SUCCESS)
		{
			cout << "Auto Sensor Gain wasn't set for Camera = " << *i << endl;
			resultCode = errorCode;
		}
	}
	return resultCode;
}

INT uEyeCameraDriver::getImangeForamtParameters()
{
	// Allocates memory for list of formats
	INT resultCode = IS_SUCCESS;
	HIDS hCam = mCameraHandles->at(0);
	INT amountOfEntries;
	UINT bytesNeeded = sizeof(IMAGE_FORMAT_LIST);
	// Size (in bytes) of the memory area to which pParam refers.
	UINT nSizeOfParam = 4;
	// Gets amount of formats for XS camera
	if ((resultCode = is_ImageFormat(hCam, IMGFRMT_CMD_GET_NUM_ENTRIES, &amountOfEntries, nSizeOfParam)) != IS_SUCCESS)
	{
		cout << "is_ImageFormat() goes wrong in getImangeForamtParameters()" << endl;
	}
	bytesNeeded += (amountOfEntries - 1) * sizeof(IMAGE_FORMAT_INFO);
	void* ptrToFormatTable = malloc(bytesNeeded);
	
	// Create and fill list
	IMAGE_FORMAT_LIST* pformatList = (IMAGE_FORMAT_LIST*) ptrToFormatTable;
	pformatList->nSizeOfListEntry = sizeof(IMAGE_FORMAT_INFO);
	pformatList->nNumListElements = amountOfEntries;
	if ((resultCode = is_ImageFormat(hCam, IMGFRMT_CMD_GET_LIST, pformatList, bytesNeeded)) != IS_SUCCESS)
	{
		cout << "is_ImageFormat() goes wrong in getImangeForamtParameters()" << endl;
	}

	// We are interested in 5M format for XS camera 
	INT xsFormatID = 4;
	IMAGE_FORMAT_INFO *formatInfo = new IMAGE_FORMAT_INFO;
	for (int i = 0; i < amountOfEntries; i++)
	{
		if (pformatList->FormatInfo[i].nFormatID == xsFormatID)
		{
			*formatInfo = pformatList->FormatInfo[i];
		}
	}
	// Saves selected format params
	mImageFormatInfo = formatInfo;
	// Free format list memory 
	free(ptrToFormatTable);
	return resultCode;
}

INT uEyeCameraDriver::allocMemoryForFreezeCapture()
{
	INT resultCode = IS_SUCCESS;
	char* pMem = NULL;
	INT memID = 0;
	for (vector<HIDS>::iterator hCam = mCameraHandles->begin(); hCam != mCameraHandles->end(); hCam)
	{
		if ((resultCode = is_AllocImageMem(*hCam, mImageFormatInfo->nWidth, mImageFormatInfo->nWidth, 24, &pMem, &memID)) == IS_SUCCESS)
		{
			mCameraBuffers->push_back(pMem);
			mCameraBufferIDs->push_back(memID);
		}
		resultCode = is_SetImageMem(*hCam, pMem, memID);
	}
	//Allocate image mem for current format, set format
	//resultCode = is_ImageFormat(hCam, IMGFRMT_CMD_SET_FORMAT, &formatInfo.nFormatID, 4);

	// Capture image
	//resultCode = is_FreezeVideo(hCam, IS_WAIT);
	return resultCode;
}

INT uEyeCameraDriver::getDeviceAndCamerasIDs()
{
	INT resultCode = IS_SUCCESS;
	// At least one camera must be available
	INT uEyeCamAmount = 0;
	if ((resultCode = is_GetNumberOfCameras(&uEyeCamAmount)) == IS_SUCCESS)
	{
		if (uEyeCamAmount >= 1)
		{
			UEYE_CAMERA_LIST* pucl = (UEYE_CAMERA_LIST*) new BYTE[sizeof(DWORD) + uEyeCamAmount * sizeof(UEYE_CAMERA_INFO)];
			pucl->dwCount = uEyeCamAmount;

			if ((resultCode = is_GetCameraList(pucl)) == IS_SUCCESS)
			{
				for (int iCamera = 0; iCamera < (int)pucl->dwCount; iCamera++)
				{
					mCameraIDs->push_back(pucl->uci[iCamera].dwCameraID);
					mDeviceIDs->push_back(pucl->uci[iCamera].dwDeviceID);
				}
			}
			else
			{
				cout << "is_GetCameraList goes wrong in initUEyeCameras()" << endl;
			}
			delete[] pucl;
		}
		else
		{
			resultCode = IS_NO_SUCCESS;
			cout << "No uEye Cameras found in initUEyeCameras()" << endl;
		}
	}
	else
	{
		cout << "is_GetNumberOfCameras goes wrong in initUEyeCameras()" << endl;
	}

	return resultCode;
}
