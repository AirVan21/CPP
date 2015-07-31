#include "uEyeCameraDriver.h"

uEyeCameraDriver::uEyeCameraDriver(INT cameraID) :
	mCameraHandle(0),
	mCameraID(cameraID),
	mCameraBuffer(NULL),
	mCameraBufferID(0)
{}

uEyeCameraDriver::~uEyeCameraDriver()
{}

INT uEyeCameraDriver::initUEyeCamera(INT cameraID)
{
	return 0;
}

void uEyeCameraDriver::displayCameraInfo()
{
	INT uEyeCamAmount = 0;
	// At least one camera must be available
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
					printf("Camera %i Id: %d\n", iCamera, pucl->uci[iCamera].dwCameraID);
					// Extra Info from Selected Camera
					CAMINFO pInfo;
					if (is_GetCameraInfo(pucl->uci[iCamera].dwCameraID, &pInfo) == IS_SUCCESS)
					{
						printf("\nUSB Type = %s", pInfo.Version);
					} else {
						printf("Problems with Camera info!\n");
					}
				}
			}
			delete[] pucl;
		}
	}
}