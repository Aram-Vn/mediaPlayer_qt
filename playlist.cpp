#include "playlist.h"
#include <QDebug>
#include <QPushButton>

PlayList::PlayList(QWidget *parent)
    : QLabel(parent),
      m_vLeyout(new QVBoxLayout()),
      m_ind(0),
      m_curIndex(0)
{
    this->setLayout(m_vLeyout);
    m_vLeyout->setAlignment(Qt::AlignTop);
}

void PlayList::appendSongs(QStringList &songs)
{
    for (auto &song : songs)
    {
        if (m_set.contains(song))
        {
            continue;
        }

        m_set.insert(song);

        QStringList  cur_song = song.split("/");
        QPushButton *btn      = new QPushButton(cur_song[cur_song.length() - 1]);

        m_vLeyout->addWidget(btn);
        m_plist << song;

        qint64 cur_ind = this->m_curIndex;
        connect(btn, &QPushButton::clicked, [=]() { init_song(cur_ind); });
        ++m_curIndex;
    }
}

void PlayList::init_song(qint64 i)
{
    if (m_plist.isEmpty())
    {
        return;
    }

    if (i < 0)
    {
        i = m_plist.size() - 1;
    }
    else if (i >= m_plist.size())
    {
        i = 0;
    }
    m_curSong  = m_plist[i];
    m_curIndex = i;
    
    emit songIsReady();
}

void PlayList::set_next()
{
    init_song(m_curIndex + 1);
}

void PlayList::set_prev()
{
    init_song(m_curIndex - 1);
}

QString PlayList::getCurrentSong()
{
    return m_curSong;
}