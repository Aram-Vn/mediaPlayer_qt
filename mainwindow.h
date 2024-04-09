#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "playlist.h"
#include <QAudioOutput>
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QPushButton>
#include <QScrollArea>
#include <QSlider>
#include <QString>
#include <QStringList>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void datachanged();
    void handleDuration();
    void handlePosition(qint64 m);
    void handleVolume();
    void openFile();
    void handleNext();
    void handlePrev();
    void handleCurrentChanged(qint64 curr);

private:
    void setTime(qint64 milisec);

private:
    bool          play_flag;
    bool          lock;
    QPushButton  *m_media_player_button;
    QPushButton  *m_media_stop_button;
    QPushButton  *m_open_btn;
    QMediaPlayer *m_media_player;
    QAudioOutput *m_audio_output;
    QPushButton  *m_media_forward_button;
    QPushButton  *m_media_back_button;
    QPushButton  *m_next_song_button;
    QPushButton  *m_prev_song_button;
    QSlider      *m_volumeSlider;
    QSlider      *m_DurationSlider;
    QLabel       *m_time_label;
    QLabel       *m_name_label;
    PlayList     *m_playlist;
    QScrollArea  *m_scrollArea;
    qint64        m_milis;
};
#endif // MAINWINDOW_H
