#include "flycameramanager.h"
#include "flycamera.h"
#include <QImage>
using namespace std;

FlyCameraManager::FlyCameraManager()
	: AbstractCameraManager()
{
    //ctor
}

FlyCameraManager::~FlyCameraManager()
{
    //dtor
}

void FlyCameraManager::PrintCameraInfo(CameraInfo* pCamInfo)
{
    printf(
        "\n*** CAMERA INFORMATION ***\n"
        "Serial number - %u\n"
        "Camera model - %s\n"
        "Camera vendor - %s\n"
        "Sensor - %s\n"
        "Resolution - %s\n"
        "Firmware version - %s\n"
        "Firmware build time - %s\n\n",
        pCamInfo->serialNumber,
        pCamInfo->modelName,
        pCamInfo->vendorName,
        pCamInfo->sensorInfo,
        pCamInfo->sensorResolution,
        pCamInfo->firmwareVersion,
        pCamInfo->firmwareBuildTime );
}


void FlyCameraManager::detectNewCameras()
{
    busMgr.GetNumOfCameras(&numCameras);
    for(unsigned int i = 0; i<numCameras; i++){
        FlyCamera* flyCam = new FlyCamera();
        busMgr.GetCameraFromIndex(i, flyCam->getGuid());
        flyCam->getCamera()->Connect(flyCam->getGuid());
        flyCam->getCamera()->GetCameraInfo(flyCam->getCameraInfo());
        PrintCameraInfo(flyCam->getCameraInfo());
        flyCameras.push_back(*flyCam);
        addNewCamera("cam" ,flyCam);

    }
}

void FlyCameraManager::takePicture(unsigned int numCam)
{
      if(numCameras >= 1 && numCam <= numCameras){
            FlyCamera tmpCam = flyCameras.at(numCam);
            Image img;
            tmpCam.getCamera()->RetrieveBuffer(&img);
            camBuffer[0]->post(img);


       } else {
        cout << "No camera connected" << endl;
    }
}

void FlyCameraManager::getPicture(unsigned int numCam)
{

    if(numCameras >= 1 && numCam <= numCameras){
        FlyCamera tmpCam = flyCameras.at(numCam);
        Image img;
        int size = img.GetDataSize();
        unsigned char* data = (unsigned char*) malloc(size * 4);
        unsigned char* picData = img.GetData();

            tmpCam.getCamera()->RetrieveBuffer(&img);
            int j = 0;
            for(unsigned int i = 0; i<img.GetCols()  * img.GetRows() *4; i+=4)
            {
                data[i] = picData[j];
                data[i+1] = picData[j];
                data[i+2] = picData[j];
                data[i+3] = picData[j];
                j++;

            }
            QImage image(data, img.GetCols(), img.GetRows(), QImage::Format_ARGB32);
    } else {
        cout << "No camera connected" << endl;
    }

}

void FlyCameraManager::disconnectAllCameras()
{
    for(unsigned int i = 0; i < flyCameras.size();i++)
    {
        flyCameras.at(i).getCamera()->Disconnect();
    }
    cout << "All cameras are disconnected" << endl;
}


void FlyCameraManager::startCapture(int numCam)
{
    flyCameras.at(numCam-1).getCamera()->StartCapture();
}

void FlyCameraManager::stopCapture(int numCam)
{
    flyCameras.at(numCam-1).getCamera()->StopCapture();
}

void FlyCameraManager::getCamerasPropertiesList() const
{
    //Nothing here
}

string FlyCameraManager::getName() const
{
    return "FlyCapture Camera Manager";
}


