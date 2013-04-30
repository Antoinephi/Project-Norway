#include "flycamera.h"



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

void FlyCamera::setProperty(CameraProperty* p)
{
    //Nothing here
}
void FlyCamera::updateProperty(CameraProperty* p)
{
    //Nothing here
}

QImage FlyCamera::retrieveImage(){
    Image img;
    int size = img.GetDataSize();
    unsigned char* data = (unsigned char*) malloc(size * 4);
    unsigned char* picData = img.GetData();
    getCamera()->RetrieveBuffer(&img);
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
    return image;
}


bool FlyCamera::equalsTo(AbstractCamera *c){
    return guid == *((FlyCamera *)c)->getGuid();
}

FlyCamera::~FlyCamera()
{
    //dtor
}


