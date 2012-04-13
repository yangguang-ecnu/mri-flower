#ifndef SERIES_H
#define SERIES_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

typedef std::vector<std::string> SerieFileContainer;

class Series
{
public:
    Series();
    Series( const std::string seriesIdentifier, const SerieFileContainer& FileSet);

    unsigned short GetTimeLenght();
    //const char* GetFileName(unsigned short time);
    std::string GetFileName(unsigned short time);
    std::string GetSeriesID();
    void Print();
    // comparator used in sorter
    bool operator()(std::string pathFileA, std::string pathFileB);
private:

    // time range in given serie. It is equal to number of files in serie
    unsigned short m_TimeLenght;
    // container for file names which belongs to given serie
    SerieFileContainer m_Files;
    // series identifier
    std::string m_SeriesIdentifier;

    // sort files base on file name. there is number in file name which says about time.
    void sortFiles();


    // helper to see tokens while splitting file name on
    void displayTokens(std::vector<std::string> tokens);

    //split the file name using delimiter in our case it will be "."
    std::vector<std::string> split(const std::string &s, char delim);
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

};

#endif // SERIES_H
