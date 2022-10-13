#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtMultimedia>
#include <QVideoWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QMediaPlayer* m_player;
    QMediaPlayer* m_playlist;
    QVideoWidget* m_videoWidget;
    QAudioOutput* m_audioOutput;
};
#endif // WIDGET_H
