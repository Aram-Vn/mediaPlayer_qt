#include "mainwindow.h"
#include "playlist.h"
#include <qt6/QtCore/qdebug.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      play_flag(false),
      lock(false),
      m_media_player_button(new QPushButton(this)),
      m_media_stop_button(new QPushButton(this)),
      media_forward_button(new QPushButton(this)),
      media_back_button(new QPushButton(this)),
      next_song_button(new QPushButton(this)),
      prev_song_button(new QPushButton(this)),
      m_media_player(new QMediaPlayer(this)),
      audio_output(new QAudioOutput(this)),
      m_volumeSlider(new QSlider(Qt::Orientation::Horizontal, this)),
      m_DurationSlider(new QSlider(Qt::Orientation::Horizontal, this)),
      time_label(new QLabel("", this)),
      name_label(new QLabel("", this)),
      m_open_btn(new QPushButton("open", this)),
      m_playlist(new PlayList(this))
{
    m_media_player->setAudioOutput(audio_output);

    this->setGeometry(100, 200, 850, 500);
    this->setFixedWidth(820);

    m_media_player_button->setGeometry(50, 50, 80, 50);
    m_media_player_button->setText("▶");
    m_media_player_button->setStyleSheet("background-color: dimGray;");

    prev_song_button->setGeometry(150, 50, 50, 50);
    prev_song_button->setStyleSheet("background-color: dimGray;");
    prev_song_button->setText("⏮");

    media_back_button->setGeometry(210, 50, 50, 50);
    media_back_button->setStyleSheet("background-color: dimGray;");
    media_back_button->setText("-10");

    connect(media_back_button, &QPushButton::clicked,
            [this]() { m_media_player->setPosition(m_media_player->position() - 10000); });

    m_media_stop_button->setGeometry(270, 50, 50, 50);
    m_media_stop_button->setStyleSheet("background-color: dimGray;");
    m_media_stop_button->setText("⟳");
    QFont font;
    font.setPointSize(17);
    m_media_stop_button->setFont(font);

    media_forward_button->setGeometry(330, 50, 50, 50);
    media_forward_button->setStyleSheet("background-color: dimGray;");
    media_forward_button->setText("+10");

    connect(media_forward_button, &QPushButton::clicked,
            [this]() { m_media_player->setPosition(m_media_player->position() + 10000); });

    next_song_button->setGeometry(390, 50, 50, 50);
    next_song_button->setStyleSheet("background-color: dimGray;");
    next_song_button->setText("⏭");

    name_label->setGeometry(460, 50, 170, 50);
    name_label->setStyleSheet("background-color: dimGray;");
    name_label->setAlignment(Qt::AlignCenter);
    name_label->setText(song_name);

    m_volumeSlider->setGeometry(640, 50, 140, 50);
    m_volumeSlider->setValue(50);

    m_DurationSlider->setGeometry(50, 115, 600, 50);

    time_label->setGeometry(675, 122, 100, 35);
    time_label->setStyleSheet("background-color: dimGray;");

    m_playlist->setGeometry(50, 175, 725, 180);
    m_playlist->setStyleSheet("background:#31363F; color: white;");

    connect(m_media_player, &QMediaPlayer::metaDataChanged, this, &MainWindow::datachanged);
    connect(m_media_player, &QMediaPlayer::positionChanged, this, &MainWindow::handlePosition);
    connect(m_DurationSlider, &QSlider::valueChanged, this, &MainWindow::handleDuration);
    connect(m_volumeSlider, &QSlider::valueChanged, this, &MainWindow::handleVolume);
    connect(m_open_btn, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(next_song_button, &QPushButton::clicked, this, &MainWindow::handle_next);
    connect(prev_song_button, &QPushButton::clicked, this, &MainWindow::handle_prev);
    connect(m_playlist, &PlayList::songIsReady, this, &MainWindow::handleSongReady);

    connect(m_media_player_button, &QPushButton::clicked,
            [this]()
            {
                if (!play_flag)
                {
                    m_media_player->play();
                    play_flag = true;
                    m_media_player_button->setText("▐▐");
                }

                else
                {
                    m_media_player->pause();
                    play_flag = false;
                    m_media_player_button->setText("▶");
                }
            });

    connect(m_media_stop_button, &QPushButton::clicked,
            [this]()
            {
                m_media_player->stop();
                m_media_player_button->setText("▶");
            });
}

void MainWindow::datachanged()
{
    m_milis = m_media_player->duration();
    m_DurationSlider->setMinimum(0);
    m_DurationSlider->setMaximum(m_milis);
    setTime(0);
}

void MainWindow::setTime(qint64 m)
{
    qint64 time = m_milis - m;
    time_label->setText(QString::number(time / 60000) + " : " + QString::number((time % 60000) / 1000));
    time_label->setAlignment(Qt::AlignCenter);
}

void MainWindow::handlePosition(qint64 m)
{
    if (!lock)
    {
        lock = true;
        m_DurationSlider->setValue(m);
        setTime(m);
        lock = false;
    }
}

void MainWindow::handleDuration()
{
    if (!lock)
    {
        lock     = true;
        qint64 t = m_DurationSlider->value();
        setTime(t);
        m_media_player->setPosition(t);
        lock = false;
    }
}

void MainWindow::handleVolume()
{
    audio_output->setVolume(m_volumeSlider->value() / 100.0);
}

void MainWindow::openFile()
{
    QStringList songs = QFileDialog::getOpenFileNames(this, tr("Open Audio File"), QDir::homePath(),
                                                      tr("Audio Files (*.mp3 *.wav *.ogg)"));
    m_playlist->appendSongs(songs);
}

void MainWindow::handle_next()
{
    m_playlist->set_next();
    m_media_player->play();
    m_media_player_button->setText("▐▐");
}

void MainWindow::handle_prev()
{
    m_playlist->set_prev();
    m_media_player->play();
    m_media_player_button->setText("▐▐");
}

void MainWindow::handleSongReady()
{
    m_media_player->setSource(m_playlist->getCurrentSong());
    QStringList song_list = m_playlist->getCurrentSong().split("/");
    QString     song_name = song_list[song_list.length() - 1];

    if (song_name.size() > 16)
    {
        song_name = song_name.left(19);
        song_name += "...";
    }

    name_label->setText(song_name);
    m_media_player->play();
    m_media_player_button->setText("▐▐");
}

MainWindow::~MainWindow() {}
