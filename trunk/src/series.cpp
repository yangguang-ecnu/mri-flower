#include "series.h"

Series::Series()
{
    m_Files.clear();
    m_TimeLenght = 0;
    m_SeriesIdentifier = "";
}

Series::Series( const std::string seriesIdentifier, const SerieFileContainer& FileSet)
{

    if (!FileSet.empty() && !seriesIdentifier.empty())
    {
        m_Files = FileSet;
        m_SeriesIdentifier = seriesIdentifier;
        //here sort the file names;
        sortFiles();
        m_TimeLenght = m_Files.size();
    }
    else
    {
        m_Files.clear();
        m_SeriesIdentifier = "";
        m_TimeLenght = 0;
    }


}

/*const char* Series::GetFileName(unsigned short time)
{
     std::vector<std::string>::iterator it;
     it = m_Files.begin();
     if ( time > (m_TimeLenght-1) )
     {
         std::cerr << "Series ERROR: given time: " << time << " is out of the range!\nT = [0, ..., " << m_TimeLenght -1 << "]"  << std::endl;
         return NULL;
     }
     else
     {
         it += time;
         return  (*it).c_str();
     }
}
*/

std::string Series::GetFileName(unsigned short time)
{
     std::vector<std::string>::iterator it;
     it = m_Files.begin();
     if ( time > (m_TimeLenght-1) )
     {
         std::cerr << "Series ERROR: given time: " << time << " is out of the range!\nT = [0, ..., " << m_TimeLenght -1 << "]"  << std::endl;
         return "";
     }
     else
     {
         it += time;
         return  (*it);
     }

}

unsigned short Series::GetTimeLenght()
{
    return m_TimeLenght;
}

std::string Series::GetSeriesID()
{
    return m_SeriesIdentifier;
}

void Series::Print()
{
    std::cout << " Series ID [" << m_SeriesIdentifier << "]: T = " << m_TimeLenght << std::endl;
    std::vector<std::string>::iterator itBegin = m_Files.begin();
    std::vector<std::string>::iterator itEnd = m_Files.end();
    while (itBegin != itEnd)
    {
        std::cout << "\t - " << (*itBegin) << std::endl;
        itBegin++;
    }

}

std::vector<std::string>& Series::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> Series::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}


void Series::displayTokens(std::vector<std::string> tokens)
{
    std::vector<std::string>::iterator it;
    int i = 0;
    for (it = tokens.begin(); it < tokens.end(); it++)
    {
        std::cout << " Token[" << i <<"] = " << *it << std::endl;
        i++;
    }
}

bool Series::operator() (std::string pathFileA, std::string pathFileB)
{
    //compared by instance number from the name
    //this is as well stored in the dicom header;
    std::string fileA = pathFileA.substr(pathFileA.find_last_of('/') + 1);
    std::string fileB = pathFileB.substr(pathFileB.find_last_of('/') + 1);

    std::vector<std::string> tokensA = split(fileA, '.');
    std::vector<std::string> tokensB = split(fileB, '.');

    int InstanceNumberA = atoi(tokensA[4].c_str());
    int InstanceNumberB = atoi(tokensB[4].c_str());

    if ( InstanceNumberA < InstanceNumberB)
        return true;
    else
        return false;
}

void Series::sortFiles()
{
    sort(m_Files.begin(), m_Files.end(), Series());
}

