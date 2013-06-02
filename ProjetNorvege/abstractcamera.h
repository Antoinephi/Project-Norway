/**
 * AbstractCamera
 * Class that need to be subclassed for each camera API
 * used to exchange CameraProperty between the application and the API
 */

#ifndef ABSTRACTCAMERA_H
#define ABSTRACTCAMERA_H

#include <string>
#include <QImage>
#include <QThread>
#include <QDebug>
#include "cameraproperty.h"
#include "qvideowidget.h"

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

        /**
         * @brief startAutoCapture start callback based Liveview
         */
        virtual void startAutoCapture() = 0;

        /**
         * @brief stopAutoCapture stop callback based Liveview
         */
        virtual void stopAutoCapture() = 0;

        /**
         * @brief retrieveImage get one image from camera
         * @return QImage image
         */
        virtual QImage retrieveImage() = 0;

        /**
         * @brief startCapture start liveview capture from manager
         * @param label wil update the label with images from the camera
         */
        void startCapture(QVideoWidget* videoWidget);


    protected:
        AbstractCamera();

        /**
         * @brief sendFrame send a new QImage for the view
         * @param img QImage grabbed from the camera
         */
        void sendFrame(QImage img);

    private:
        QVideoWidget* container;
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
