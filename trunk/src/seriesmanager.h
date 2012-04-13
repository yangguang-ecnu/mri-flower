#ifndef SERIESMANAGER_H
#define SERIESMANAGER_H

#include "series.h"
#include "itkGDCMSeriesFileNames.h"

typedef std::vector<Series*> SeriesContainer;
typedef std::vector<std::string> SerieFileContainer;
typedef unsigned short SliceType;
typedef unsigned short TimeType;

typedef enum {
    MAGNITUDE = 0,
    X,
    Y,
    Z
} SliceComponent;

/*
struct SliceComponent
{
    int MAGNITUDE;
    int X;
    int Y;
    int Z;

    SliceComponent() :
        MAGNITUDE(0), X(0), Y(0), Z(0)
    {

    }

    int GetX() { return X; }
    int GetY() { return Y; }
    int GetZ() { return Z; }
    int GetMagnitude() { return MAGNITUDE; }

};
*/


class SeriesManager
{
public:
    SeriesManager();
    SeriesManager(const char* directory);
    ~SeriesManager();

    //Return a file from given slice and time moment;
    std::string GetSliceComponent(SliceType slice, TimeType time, SliceComponent component );

    std::string GetSliceMagnitude(SliceType slice, TimeType time);
    std::string GetSliceX(SliceType slice, TimeType time);
    std::string GetSliceY(SliceType slice, TimeType time);
    std::string GetSliceZ(SliceType slice, TimeType time);

    // Take all slices of Magnitude, X, Y or Z to build volume i current time.
    void GetVolumeMagnitude(TimeType time, SerieFileContainer& volume);

    void GetVolumeX(TimeType time, SerieFileContainer& volume);
    void GetVolumeY(TimeType time, SerieFileContainer& volume);
    void GetVolumeZ(TimeType time, SerieFileContainer& volume);


    // 4 element vector with file names corresponding to magnitude, x, y, z in given time
     void GetSlice(SliceType slice, TimeType time, SerieFileContainer& sliceSet);

    // get number of slices; Should be m_series/4;
    inline unsigned short GetNoSlices();
    unsigned short GetTimeLenght();
    void Print(SliceType slice, TimeType time);
    void Print(bool displaySeries = false, bool displayFiles = false);

private:
    SeriesContainer m_series;
    unsigned short m_slicesNo;
    unsigned short m_TimeLenght;
    static const unsigned short m_sliceComponents = 4;
    std::string m_directory;
    inline unsigned short getSeriesIDX( SliceType slice, SliceComponent component );


};

#endif // SERIESMANAGER_H
