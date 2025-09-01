#include <iostream>
#include <vector>
#include <string>

using namespace std;

// abstract iterator
template <typename T>
class Iterator
{
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() = 0;
    virtual T next() = 0;
};

// abstract iterable
template <typename T>
class Iterable
{
public:
    virtual ~Iterable() = default;
    virtual Iterator<T> *getIterator() = 0;
};

class Song
{
    string name, artist;

public:
    Song(string name, string artist) : name(name), artist(artist) {}
    string getName() { return name; }
    string getArtist() { return artist; }
};

// concrete iterator
class PlaylistIterator : public Iterator<Song>
{
    int idx;
    vector<Song> songs;

public:
    PlaylistIterator(vector<Song> songs) : songs(songs), idx(0) {}
    bool hasNext()
    {
        return idx < songs.size();
    }
    Song next()
    {
        return songs[idx++];
    }
};

// concrete iterarable
class Playlist : public Iterable<Song>
{
public:
    vector<Song> songs;

    void addSong(const Song &s)
    {
        songs.push_back(s);
    }

    Iterator<Song> *getIterator()
    {
        return new PlaylistIterator(songs);
    }
};

int main()
{
    Song s1("manogari", "sundar c");
    Song s2("beliver adi", "imagine dragons");
    Song s3("mad king", "rook nardin");

    Playlist playlist;

    playlist.addSong(s1);
    playlist.addSong(s2);
    playlist.addSong(s3);

    PlaylistIterator *it = new PlaylistIterator(playlist.songs);

    while (it->hasNext())
    {
        Song obj = it->next();
        cout << "Song name: " << obj.getName() << "   ";
        cout << "Song Artist: " << obj.getArtist() << endl;
    }

    delete it;

    return 0;
}
