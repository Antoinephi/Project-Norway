#include "flycamera.h"
#include <QPainter>


FlyCamera::FlyCamera() : AbstractCamera()
{
    cam = new Camera();
}

Camera* FlyCamera::getCamera()
{
    return cam;
}

PGRGuid* FlyCamera::getGuid()
{
    return &guid;
}

CameraInfo* FlyCamera::getCameraInfo()
{
    return &camInfo;
}

void FlyCamera::setProperty(CameraManager::CameraProperty* p)
{
    //Nothing here
}
void FlyCamera::updateProperty(CameraManager::CameraProperty* p)
{
    //Nothing here
}

QImage FlyCamera::retrieveImage(){
    getCamera()->StartCapture();
    Image img;
    getCamera()->RetrieveBuffer(&img);
    int size = img.GetDataSize();
    unsigned char* data = (unsigned char*) malloc(size * 3);
    unsigned char* picData = img.GetData();
    int j = 0;
    for(unsigned int i = 0; i<img.GetCols()  * img.GetRows() *3; i+=3)
    {
        data[i] = picData[j];
        data[i+1] = picData[j];
        data[i+2] = picData[j];
        j++;

    }

    QImage image(data, img.GetCols(), img.GetRows(), QImage::Format_RGB32);
    return image;
}


bool FlyCamera::equalsTo(AbstractCamera *c){
    return guid == *((FlyCamera *)c)->getGuid();
}

FlyCamera::~FlyCamera()
{
    //dtor
}


