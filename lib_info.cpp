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
    }
}