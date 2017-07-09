#ifndef SONGSKEEPER_H
#define SONGSKEEPER_H
#include <QString>
struct SongsKeeper
{
    SongsKeeper()
        : firstStartWorkSong{"qrc:/music/rmusic/BoxingBell.mp3"},
          endWorkSong{"qrc:/music/rmusic/BoxingBell.mp3"},
          endBreakSong{"qrc:/music/rmusic/BoxingBell.mp3"}
    {}

    QString firstStartWorkSong;
    QString endWorkSong;
    QString endBreakSong;
};

#endif // SONGSKEEPER_H
