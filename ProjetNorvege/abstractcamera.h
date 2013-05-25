/**
 * AbstractCamera
 * Class that need to be subclassed for each camera API
 * used to exchange CameraProperty between the application and the API
 */

#ifndef ABSTRACTCAMERA_H
#define ABSTRACTCAMERA_H

#include <string>
#include <QImage>
#include <QLabel>
#include <QThread>
#include <QDebug>
#include "cameraproperty.h"
class AbstractCamera
{
    public:
        /**
         * @brief setProperty set the camera according to that property
         * @param p property to set
         */
        virtual void setProperty(CameraManager::CameraProperty* p) = 0;

        /**
         * @brief updateProperty get the value of that property for that camera
         * @param p property to update
         */
        virtual void updateProperty(CameraManager::CameraProperty* p) = 0;

        /**
         * @brief equalsTo compare 2 cameras
         * @param c camera to compare
         * @return true if the cameras are physically the same
         */
        virtual bool equalsTo(AbstractCamera* c);

        /**
         * @brief getString get the name corresponding to the camera model and id
         * @return String containing these informations
         */
        virtual std::string getString() = 0;

        virtual void startAutoCapture() = 0;
        virtual void stopAutoCapture() = 0;
        //may be changed
        virtual QImage retrieveImage() = 0;

        void sendFrame(QImage img);
        void startCapture(QLabel* label);



    protected:
        AbstractCamera();
    private:
        QLabel* container;        
        class CaptureThread : public QThread {
            public :
                CaptureThread(AbstractCamera* cam) : QThread() { c = cam; }
                void run(){
                    qDebug() << "Thread Started";
                    c->startAutoCapture();
                }
            private:
                AbstractCamera* c;
        };
        CaptureThread thread;
};

#endif // ABSTRACTCAMERA_H
