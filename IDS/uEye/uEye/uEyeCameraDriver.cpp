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

INT uEyeCameraDriver::cameraPreparation()
{
	INT resultCode = IS_SUCCESS;
	INT errorCode  = IS_SUCCESS;
	if ((errorCode = uEyeCameraDriver::initUEyeCameras()) != IS_SUCCESS)
	{
		resultCode = errorCode;
	}
	if ((errorCode = uEyeCameraDriver::setAutoSensorGainShutter()) != IS_SUCCESS)
	{
		resultCode = errorCode;
	}
	uEyeCameraDriver::setAutoFocus();
	uEyeCameraDriver::getImangeForamtParameters();
	uEyeCameraDriver::allocMemoryForFreezeCapture();
	return resultCode;
}

INT uEyeCameraDriver::initUEyeCameras()
{
	cout << "Initialization:" << endl;
	INT resultCode = IS_SUCCESS;
	if ((resultCode = uEyeCameraDriver::getDeviceAndCamerasIDs()) == IS_SUCCESS)
	{
		for (vector<INT>::iterator i = mDeviceIDs->begin(); i != mDeviceIDs->end(); i++)
		{
			HIDS cameraHandle = ((HIDS) *i) | IS_USE_DEVICE_ID;
			if ((resultCode = is_InitCamera(&cameraHandle, NULL)) == IS_SUCCESS)
			{
				cout << "  Init PASS for Device ID = " << *i << endl;
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

INT uEyeCameraDriver::setAutoFocus()
{
	INT resultCode = IS_SUCCESS;
	UINT autoFocusOn = 1;
	UINT nSizeOfParam = 4;
	for (vector<HIDS>::iterator hCam = mCameraHandles->begin(); hCam != mCameraHandles->end(); hCam++)
	{
		INT errorCode = IS_SUCCESS;
		if ((errorCode = is_Focus(*hCam, FOC_CMD_GET_AUTOFOCUS_ENABLE, &autoFocusOn, nSizeOfParam)) != IS_SUCCESS)
		{
			cout << "Auto Focus wasn't set for Camera = " << *hCam << endl;
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
	// Size of Param for is_ImageFormat()
	INT nSizeOfParam = 4;
	for (vector<HIDS>::iterator hCam = mCameraHandles->begin(); hCam != mCameraHandles->end(); hCam++)
	{
		pMem = NULL;
		memID = 0;
		if ((resultCode = is_AllocImageMem(*hCam, mImageFormatInfo->nWidth, mImageFormatInfo->nHeight, bitsPerPixel, &pMem, &memID)) == IS_SUCCESS)
		{
			mCameraBuffers->push_back(pMem);
			mCameraBufferIDs->push_back(memID);
		} 
		else
		{
			cout << "is_AllocImageMem() goes wrong in allocMemoryForFreezeCapture()" << endl;
		}
		resultCode = is_SetImageMem(*hCam, pMem, memID);
		if (resultCode != IS_SUCCESS)
		{
			cout << "is_SetImageMem() goes wrong in allocMemoryForFreezeCapture()" << endl;
		}
		//Allocate image mem for current format, set format
		resultCode = is_ImageFormat(*hCam, IMGFRMT_CMD_SET_FORMAT, &(mImageFormatInfo->nFormatID), nSizeOfParam);
		if (resultCode != IS_SUCCESS)
		{
			cout << "is_ImageFormat() goes wrong in allocMemoryForFreezeCapture()" << endl;
		}
	}
	
	return resultCode;
}

INT uEyeCameraDriver::freeMemoryForFreezeCapture()
{
	INT resultCode = IS_SUCCESS;
	INT errorCode = IS_SUCCESS;
	for (INT i = 0; i < mCameraBuffers->size(); i++)
	{
		if ((errorCode = is_FreeImageMem(mCameraHandles->at(i), mCameraBuffers->at(i), mCameraBufferIDs->at(i))) != IS_SUCCESS)
		{
			resultCode = errorCode;
			cout << "is_FreeImageMem() goes wrong in freeMemoryForFreezeCapture() for Camera = " << mCameraHandles->at(i) << endl;
		}
	}
	return resultCode;
}

INT uEyeCameraDriver::makeSnapshotInFreezeCaptureWait()
{
	INT resultCode = IS_SUCCESS;
	INT errorCode = IS_SUCCESS;
	cout << "Capture ... " << endl;
	// Makes snapshot One by One
	for (int i = 0; i < mCameraHandles->size(); i++)
	{
		if ((errorCode = is_FreezeVideo(mCameraHandles->at(i), IS_WAIT)) != IS_SUCCESS)
		{
			resultCode = errorCode;
			cout << "is_FreezeVideo() goes wrong in makeSnapshotInFreezeCapture" << endl;
		}
	}
	cout << "Captured (all " << mCameraHandles->size()  << " cameras!)" << endl;
	return resultCode;
}

INT uEyeCameraDriver::makeSnapshotInFreezeCaptureNoWait()
{
	INT resultCode = IS_SUCCESS;
	INT errorCode = IS_SUCCESS;
	cout << "Capture ... " << endl;
	vector<HANDLE> eventStorage(mCameraHandles->size(), CreateEvent(NULL, FALSE, FALSE, NULL));
	for (int i = 0; i < mCameraHandles->size(); i++)
	{
		// Makes snapshot simultaneously for all cameras (except first)
		is_InitEvent(mCameraHandles->at(i), eventStorage[i], IS_SET_EVENT_FRAME);
		is_EnableEvent(mCameraHandles->at(i), IS_SET_EVENT_FRAME);
		is_FreezeVideo(mCameraHandles->at(i), IS_DONT_WAIT);
		// Wait 350ms timeout
		if (WaitForSingleObject(eventStorage[i], 350) == WAIT_TIMEOUT)
		{
			cout << "Trigged on TIMEOUT" << endl;
		}
	}
	
	for (int i = 0; i < mCameraHandles->size(); i++)
	{
		// Makes snapshot simultaneously for all cameras (except first)
		is_DisableEvent(mCameraHandles->at(i), IS_SET_EVENT_FRAME);
		is_ExitEvent(mCameraHandles->at(i), IS_SET_EVENT_FRAME);
		CloseHandle(eventStorage[i]);
	}

	cout << "Captured (all " << mCameraHandles->size() << " cameras!)" << endl;
	return resultCode;
}

INT uEyeCameraDriver::storeSnapshots()
{
	cout << "Saving images ..." << endl;
	INT resultCode = IS_SUCCESS;
	INT errorCode = IS_SUCCESS;
	IMAGE_FILE_PARAMS ImageFileParams;
	ImageFileParams.nFileType = IS_IMG_PNG;
	ImageFileParams.pnImageID = NULL;
	ImageFileParams.ppcImageMem = NULL;
	ImageFileParams.nQuality = 100;
	wchar_t imageName[20];
	int const decimal = 10;
	for (int i = 0; i < mCameraHandles->size(); i++)
	{
		swprintf_s(imageName, L"0%d.png", i + 1);
		ImageFileParams.pwchFileName = imageName;
		errorCode = is_ImageFile(mCameraHandles->at(i), IS_IMAGE_FILE_CMD_SAVE, (void*)&ImageFileParams, sizeof(ImageFileParams));
		if (errorCode != IS_SUCCESS)
		{
			resultCode = errorCode;
			cout << "is_ImageFile() goes wrong in makeSnapshotInFreezeCapture()" << endl;
		}
	}
	cout << "Saved!" << endl;
	return resultCode;
}

INT uEyeCameraDriver::setToStandbyMode()
{
	INT resultCode = IS_SUCCESS;
	INT errorCode = IS_SUCCESS;
	for (vector<HIDS>::iterator hCam = mCameraHandles->begin(); hCam != mCameraHandles->end(); hCam++)
	{
		if ((errorCode = is_CameraStatus(*hCam, IS_STANDBY, true)) != IS_SUCCESS)
		{
			cout << "Problems with setting standby mode!" << endl;
		}
	}
	return resultCode;
}

INT uEyeCameraDriver::setToFreeRunMode()
{
	INT resultCode = IS_SUCCESS;
	INT errorCode = IS_SUCCESS;
	for (vector<HIDS>::iterator hCam = mCameraHandles->begin(); hCam != mCameraHandles->end(); hCam++)
	{
		if ((errorCode = is_CameraStatus(*hCam, IS_STANDBY, false)) != IS_SUCCESS)
		{
			cout << "Problems with setting freerun mode!" << endl;
		}
	}
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
