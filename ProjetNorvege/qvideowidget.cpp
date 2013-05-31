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
        QString sx("x:%1"), sy("y:%1");
        if(Ui::crosshairReal){
            QPoint pos = (mouse-scaled.topLeft()) * ratio;
            sx = sx.arg(pos.x());
            sy = sy.arg(pos.y());

            QImage imgCopy = img.copy();
            QPainter painterImg(&imgCopy);
            painterImg.drawPixmap(pos-QPoint(15, 15), QPixmap(":/icons/crosshair"));
            painterImg.drawLine(0, pos.y(), pos.x()-15, pos.y());
            painterImg.drawLine(pos.x()+16, pos.y(), imgCopy.width(), pos.y());

            painterImg.drawLine(pos.x(), 0, pos.x(), pos.y()-15);
            painterImg.drawLine(pos.x(), pos.y()+16, pos.x(), imgCopy.height());
            painterImg.end();

            scaledImg = imgCopy.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            painter.drawImage(scaled.topLeft(), scaledImg);
        }else{
            QPointF pos = QPointF(mouse-scaled.topLeft()) * ratio;
            sx = sx.arg(pos.x());
            sy = sy.arg(pos.y());

            scaledImg = img.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            painter.drawImage(scaled.topLeft(), scaledImg);

            painter.drawPixmap(mouse-QPoint(15, 15), QPixmap(":/icons/crosshair"));
            painter.drawLine(scaled.left(), mouse.y(), mouse.x()-15, mouse.y());
            painter.drawLine(mouse.x()+16, mouse.y(), scaled.right(), mouse.y());

            painter.drawLine(mouse.x(), scaled.top(), mouse.x(), mouse.y()-15);
            painter.drawLine(mouse.x(), mouse.y()+16, mouse.x(), scaled.bottom());
        }
        /*painter.drawText( mouse+QPoint(5,-5-painter.font().pixelSize()),
                          QString("%1,%2").arg(posInImg.x()).arg(posInImg.y())
                          );*/
        QFont font(painter.font());
        font.setPixelSize(15);
        painter.setFont(font);
        painter.fillRect( 0, 0, 70, 35, Qt::white );
        painter.drawText( 1, 16, sx );
        painter.drawText( 1, 32, sy );
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


