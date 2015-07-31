#include "uEyeCameraDriver.h"

uEyeCameraDriver::uEyeCameraDriver(INT cameraID) :
	mCameraHandles(new vector<HIDS>()),
	mCameraIDs(new vector<int>()),
	mDeviceIDs(new vector<int>()),
	mCameraBuffer(NULL),
	mCameraBufferID(0)
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