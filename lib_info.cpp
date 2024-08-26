// Eric Chtilianov and Alex Chen
// CS302 - Project 1: Manage and organize music libraries

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Song
{
    string title;
    int time;
};

struct Album
{
    map<int, Song> songs; // {track number, Song object}
    string name;
    int time;
    int nsongs; // optional variable but makes it easier
};

struct Artist
{
    map<string, Album> albums; // {album name, Album object}
    string name;
    int time;
    int nsongs;
};

int convertToSec(string time)
{
    int min, sec;
    char colon;
    istringstream sin(time);
    sin >> min >> colon >> sec; // separte mm:ss into appropriate variables

    min *= 60;
    return min + sec; // return total seconds
}

string timeToStr(int seconds)
{
    int min = seconds / 60;
    int sec = seconds % 60;
    // Used a  CS 102 lab called speeding.cpp to remind me of formatting and setw/setfill use
    ostringstream sout;
    sout << setfill('0');
    sout << min << ":" << setw(2) << sec;
    return sout.str();
}

string replaceUnderscores(string input)
{
    string res = input;
    replace(res.begin(), res.end(), '_', ' '); // https://www.geeksforgeeks.org/std-string-replace-in-cpp/
    return res;
}

int main(int argc, char *argv[])
{
    ifstream fin;
    string file = argv[1];
    fin.open(file); // referred back to cs102 boiling lab on using fin

    string line;

    map<string, Artist> artistsMap; // artist name (string) -> Artist (object)

    while (getline(fin, line))
    {
        string songTitle;
        string timeStr;
        string artistN;
        string albumN;
        string genre;
        int track;

        istringstream sin(line);
        sin >> songTitle >> timeStr >> artistN >> albumN >> genre >> track; // parsing input into correct variables
        // Standardizing input and converting time to int
        songTitle = replaceUnderscores(songTitle);
        int songTime = convertToSec(timeStr);
        artistN = replaceUnderscores(artistN);
        albumN = replaceUnderscores(albumN);

        // Initialize song struct and its varibale sbased on input
        Song song;
        song.title = songTitle;
        song.time = songTime;

        if (artistsMap.find(artistN) == artistsMap.end()) // if artist does not exist in hash map
        {
            artistsMap[artistN] = Artist{map<string, Album>(), artistN, 0, 0}; // Create a default Artist object with the name of the artist
        }
        if (artistsMap[artistN].albums.find(albumN) == artistsMap[artistN].albums.end()) // if album name does not exist in map
        {
            artistsMap[artistN].albums[albumN] = Album{map<int, Song>(), albumN, 0, 0}; // Create a default Album object with its name
        }
        // Update appropriate variables in each struct
        artistsMap[artistN].albums[albumN].songs[track] = song;
        artistsMap[artistN].albums[albumN].time += songTime;
        artistsMap[artistN].albums[albumN].nsongs++;
        artistsMap[artistN].time += songTime;
        artistsMap[artistN].nsongs++;
    }

    fin.close();

    for (map<string, Artist>::iterator it = artistsMap.begin(); it != artistsMap.end(); ++it) // Dr. Emrich hint announcement on iterators
    {
        // it->first = string name
        // it->second = Artist object
        string artistTimeStr = timeToStr(it->second.time);
        cout << it->first << ": " << it->second.nsongs << ", " << artistTimeStr << endl;

        for (map<string, Album>::iterator albumIt = it->second.albums.begin(); albumIt != it->second.albums.end(); ++albumIt)
        {
            // albumIt->first = string album name
            // albumIt->second = Album object
            string albumTimeStr = timeToStr(albumIt->second.time);
            cout << setw(8) << " " << albumIt->second.name << ": " << albumIt->second.nsongs << ", " << albumTimeStr << endl;

            for (std::map<int, Song>::iterator songIt = albumIt->second.songs.begin(); songIt != albumIt->second.songs.end(); ++songIt)
            {
                // songIt->first = track number
                // songIt->second = Song object
                string songTimeStr = timeToStr(songIt->second.time);
                cout << setw(16) << " " << songIt->first << ". " << songIt->second.title << ": " << songTimeStr << endl;
            }
        }
    }
}
