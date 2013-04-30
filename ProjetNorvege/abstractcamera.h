#ifndef ABSTRACTCAMERA_H
#define ABSTRACTCAMERA_H

#include <string>
#include <QImage>
#include "cameraproperty.h"
class AbstractCamera
{
    public:
		virtual void setProperty(CameraProperty* p) = 0;
		virtual void updateProperty(CameraProperty* p) = 0;
		virtual bool equalsTo(AbstractCamera* c);
		virtual QImage retrieveImage() = 0;

    protected:
        AbstractCamera();
};

#endif // ABSTRACTCAMERA_H
