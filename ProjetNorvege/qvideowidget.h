#ifndef QVIDEOWIDGET_H
#define QVIDEOWIDGET_H

#include <QWidget>
#include <QThread>

class QVideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QVideoWidget(QWidget *parent = 0);
    ~QVideoWidget(){};

    void setImage (QImage image);

public slots:
    void changedState (Qt::WindowStates oldState, Qt::WindowStates newState);
    void activateCrosshair(bool state);
protected:
    void paintEvent (QPaintEvent * event);
    void resizeEvent (QResizeEvent * event = NULL);

    void mouseMoveEvent (QMouseEvent * event);
    //void enterEvent (QEvent *);
    void leaveEvent (QEvent *);

private:
    QImage img;
    QSize lastSize;
    QRect scaled;
    float ratio;
    bool active, mouseIn;
    QPoint mouse;
};

#endif // QVIDEOWIDGET_H
