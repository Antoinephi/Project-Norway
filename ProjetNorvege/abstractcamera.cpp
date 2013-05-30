#include <QDebug>
#include "abstractcamera.h"

AbstractCamera::AbstractCamera() : thread(this)
{
}

bool AbstractCamera::equalsTo(AbstractCamera* c){
    return this == c;
}
void AbstractCamera::startCapture(QVideoWidget *videoWidget){
    if(videoWidget == NULL){
        qDebug() << "[ERROR] startCapture(QVideoWidget): videoWidget is NULL";
        return ;
    }
    container = videoWidget;
    thread.start();

}

void AbstractCamera::sendFrame(QImage img){
    //qDebug() << "Frame sended !";
    //QPixmap pxmap = QPixmap::fromImage(img.scaled(container->size(), Qt::KeepAspectRatio));
    container->setImage(img);
    //container->show();
    //container->repaint();
}
