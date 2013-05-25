#include <QDebug>
#include "abstractcamera.h"

AbstractCamera::AbstractCamera() : thread(this)
{
}

bool AbstractCamera::equalsTo(AbstractCamera* c){
    return this == c;
}
void AbstractCamera::startCapture(QLabel *label){
    if(label == NULL){
        qDebug() << "[ERROR] startCapture(QLabel): label is NULL";
        return ;
    }
    container = label;
    thread.start();

}

void AbstractCamera::sendFrame(QImage img){
    //qDebug() << "Frame sended !";
    QPixmap pxmap = QPixmap::fromImage(img.scaled(container->size(), Qt::KeepAspectRatio));
    container->setPixmap(pxmap);
    container->show();
}
