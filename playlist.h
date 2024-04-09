#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QListWidget>
#include <QSet>
#include <QString>
#include <QStringList>

class PlayList : public QListWidget
{
    Q_OBJECT
public:
    PlayList(QWidget *parent = nullptr);

public:
    void    append_songs(QStringList &songs);
    void    setNext();
    void    setPrev();
    QString getCurrentSong();

private:
    QStringList   m_plist;
    QSet<QString> m_set;
};

#endif // PLAYLIST_H
