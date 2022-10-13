#include "widget.h"

#include <QCamera>
#include <QImageCapture>
#include <QMediaRecorder>
#include <QMediaDevices>
#include <QMediaCaptureSession>
#include <QAudioInput>
#include <QVideoFrame>
#include <QVideoWidget>
#include <QUrl>
#include <QPushButton>
#include <QBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    const QList<QCameraDevice> cameras = QMediaDevices::videoInputs( );
    for (const QCameraDevice &cameraDevice : cameras) {
        qDebug( ) << cameraDevice.description( );
    }

    camera = new QCamera(QMediaDevices::defaultVideoInput( ));
    camera->setCustomFocusPoint(QPointF(0.25f, 0.75f));
    if(camera != nullptr) {
        QVideoWidget *preview = new QVideoWidget(this);
        preview->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

        imageCapture = new QImageCapture( );

        recorder = new QMediaRecorder;
        recorder->setQuality(QMediaRecorder::HighQuality);
        recorder->setOutputLocation(QUrl(QString("test.mp4")));

        QMediaCaptureSession* captureSession = new QMediaCaptureSession;
        captureSession->setCamera(camera);
        captureSession->setImageCapture(imageCapture);
        captureSession->setRecorder(recorder);
        captureSession->setVideoOutput(preview);

        QAudioInput audioInput;
        captureSession->setAudioInput(&audioInput);

        camera->start( ); // 카메라의 프리뷰 시작

        QPushButton* imageButton = new QPushButton("Image", this);
        connect(imageButton, SIGNAL(clicked( )), SLOT(captureImage( )));
        QPushButton* videoButton = new QPushButton("Video", this);
        connect(videoButton, SIGNAL(clicked( )), SLOT(recordVideo( )));

        QHBoxLayout* hboxLayout = new QHBoxLayout;
        hboxLayout->addWidget(imageButton);
        hboxLayout->addWidget(videoButton);

        QVBoxLayout* vboxLayout = new QVBoxLayout(this);
        vboxLayout->addWidget(preview);
        vboxLayout->addLayout(hboxLayout);

        QHBoxLayout* mainLayout = new QHBoxLayout(this);
        mainLayout->addWidget(preview);
        preview->resize(preview->sizeHint( ));
    }
}

void Widget::captureImage( ) {
    imageCapture->captureToFile("capture.jpg");
}

void Widget::recordVideo( ) {
    recorder->record( );
}

Widget::~Widget()
{
}
