#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include "qvideowidget.h"
#include "mainwindow.h"

QVideoWidget::QVideoWidget(QWidget *parent) :
    QWidget(parent),
    active(this->windowState() & Qt::WindowActive),
    mouseIn( underMouse() )
{
    setMouseTracking(Ui::crosshair);
}


void QVideoWidget::setImage(QImage image){
    img = image;
    if(scaled.isNull())
        resizeEvent(NULL);
    update();
    //qApp->processEvents();
}


void QVideoWidget::paintEvent(QPaintEvent *) {
    if( img.isNull() ) return;
    //qDebug() << "scaled.topLeft()" << scaled;
    QImage scaledImg;
    QPainter painter(this);
    if( mouseIn ){
        //qDebug() << "mouse" << mouse;
        QPoint posInImg = (mouse-scaled.topLeft()) * ratio;

        QImage imgCopy = img.copy();
        QPainter painterImg(&imgCopy);
        painterImg.drawPixmap(posInImg-QPoint(15,15), QPixmap(":/icons/crosshair"));
        painterImg.drawLine(0, posInImg.y(), posInImg.x()-15, posInImg.y());
        painterImg.drawLine(posInImg.x()+16, posInImg.y(), imgCopy.width(), posInImg.y());

        painterImg.drawLine(posInImg.x(), 0, posInImg.x(), posInImg.y()-15);
        painterImg.drawLine(posInImg.x(), posInImg.y()+16, posInImg.x(), imgCopy.height());
        painterImg.end();

        scaledImg = imgCopy.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

        painter.drawImage(scaled.topLeft(), scaledImg);
        /*painter.drawText( mouse+QPoint(5,-5-painter.font().pixelSize()),
                          QString("%1,%2").arg(posInImg.x()).arg(posInImg.y())
                          );*/
        QFont font(painter.font());
        font.setPixelSize(15);
        painter.setFont(font);
        painter.fillRect( 0, 0, 50, 35, Qt::white );
        painter.drawText( 1, 16, QString("x:%1").arg(posInImg.x()) );
        painter.drawText( 1, 32, QString("y:%1").arg(posInImg.y()) );
    }else{
        /*if( active )
            scaledImg = img.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        else//*/
            scaledImg = img.scaled(this->size(), Qt::KeepAspectRatio, Qt::FastTransformation);
        painter.drawImage(scaled.topLeft(), scaledImg);
    }
    painter.end();
}

void QVideoWidget::resizeEvent(QResizeEvent *){
    if( img.isNull() ) return;
    QImage tmp = img.scaled(this->size(), Qt::KeepAspectRatio, Qt::FastTransformation);
    QPoint pos;
    if( tmp.height() == this->height() ){
        pos = QPoint( (this->width()-tmp.width())/2 , 0 );
        ratio = (float)img.width() / tmp.width();
    }else{
        pos = QPoint( 0, (this->height()-tmp.height())/2 );
        ratio = (float)img.height() / tmp.height();
    }
    //qDebug() << "ratio" << ratio;
    scaled = QRect(pos, tmp.size());
}

//void QVideoWidget::enterEvent(QEvent *){}
void QVideoWidget::leaveEvent(QEvent *){
    if(!Ui::crosshair) return;
    mouseIn = false;
    unsetCursor();
    update();
}
void QVideoWidget::mouseMoveEvent ( QMouseEvent * event ){
    if(!Ui::crosshair) return;
    mouse = event->pos();
    bool tmp = mouseIn;
    mouseIn = scaled.contains(mouse);

    if( mouseIn && !tmp )
        setCursor(Qt::BlankCursor);
    if( !mouseIn && tmp )
        unsetCursor();

    if( tmp || mouseIn )
        update();
}

void QVideoWidget::changedState(Qt::WindowStates, Qt::WindowStates newState){
    active = newState & Qt::WindowActive;
}

void QVideoWidget::activateCrosshair(bool state){
    setMouseTracking(state);
}


