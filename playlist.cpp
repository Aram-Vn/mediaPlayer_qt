#include "playlist.h"
#include <qtypes.h>

PlayList::PlayList(QWidget *parent)
    : QListWidget(parent)
{
}

void PlayList::append_songs(QStringList &songs)
{
    for (auto &song : songs)
    {
        if (m_set.contains(song))
        {
            continue;
        }

        m_set.insert(song.section("/", -1));

        m_plist << song;

        this->addItem(song.section("/", -1));
    }
}

void PlayList::set_next()
{
    qint64 curr = currentRow();
    ++curr;

    if (curr == count())
    {
        curr = 0;
    }

    setCurrentRow(curr);
}

void PlayList::set_prev()
{
    qint64 curr = currentRow();
    --curr;

    if (curr == -1)
    {
        curr = count() - 1;
    }

    setCurrentRow(curr);
}

QString PlayList::getCurrentSong() 
{
    return m_plist[currentRow()];
}