#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QHash>
#include <QLabel>
#include <QObject>
#include <QStringList>
#include <QVBoxLayout>
#include <QWidget>

class PlayList : public QLabel
{
    Q_OBJECT
public:
    PlayList(QWidget *parent = nullptr);

signals:
    void songIsReady();

public:
    void    init_song(qint64);
    void    set_next();
    void    set_prev();
    QString getCurrentSong();
    void    appendSongs(QStringList &songs);

private:
    QVBoxLayout  *m_vLeyout;
    QSet<QString> m_set;
    QStringList   m_plist;
    QString       m_curSong;
    qint64        m_ind;
    qint64        m_curIndex;
};

#endif // PLAYLIST_H
