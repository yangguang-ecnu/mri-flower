#include "seriesmanager.h"

SeriesManager::SeriesManager()
{
    m_series.clear();
    m_slicesNo = 0;
    m_directory.erase();
}

SeriesManager::SeriesManager(const char *directory)
{
    typedef itk::GDCMSeriesFileNames NamesGeneratorType;
    NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();
    nameGenerator->SetUseSeriesDetails( true );
    nameGenerator->SetDirectory( directory );

    for ( std::vector<std::string>::const_iterator uuid = nameGenerator->GetSeriesUIDs().begin(); uuid < nameGenerator->GetSeriesUIDs().end(); uuid++ )
    {
       // std::cout << "UUID: " << *uuid << std::endl;
        if(uuid != nameGenerator->GetSeriesUIDs().end() )
        {
            m_series.push_back( new Series (*uuid, nameGenerator->GetFileNames(*uuid) ));
        }
    }
    m_slicesNo = m_series.size()/m_sliceComponents;
    m_TimeLenght = m_series.at(0)->GetTimeLenght();
    m_directory = directory;
}

SeriesManager::~SeriesManager()
{
    //all_the_members.push_back( new Member );
    // Access the elements
    //all_the_members[ 0 ]->menu();

    // Don't forget to free all memory before the program terminates
    for ( SeriesContainer::iterator serie = m_series.begin(); serie != m_series.end(); serie++)
    {
        delete *serie;
    }
    m_series.clear();
}

inline unsigned short SeriesManager::GetNoSlices()
{
    return m_series.size()/m_sliceComponents;
}

unsigned short SeriesManager::GetTimeLenght()
{
    return m_TimeLenght;
}

//Return a file from given slice and time moment;
std::string SeriesManager::GetSliceComponent(SliceType slice, TimeType time, SliceComponent component )
{

    if( slice > m_slicesNo )
    {
        std::cerr << "SeriesManager ERROR: Slice [" << slice << "] is out of range\n" << std::endl;
        std::cerr << "No of slices = " << m_slicesNo << std::endl;
        return "";
    }

    int idx = getSeriesIDX(slice, component);

    return m_series[idx]->GetFileName(time);

}

inline unsigned short SeriesManager::getSeriesIDX( SliceType slice, SliceComponent component )
{
    int i = slice * m_sliceComponents;
    //std::cout << "component index = " << i << std::endl;
    switch ( component )
    {
    case MAGNITUDE:
        return i;
        break;
    case X:
        return i+1;
        break;
    case Y:
        return i+2;
        break;

    case Z:
        return i+3;
        break;
    }
}


void SeriesManager::GetSlice(SliceType slice, TimeType time, SerieFileContainer& sliceSet)
{
    sliceSet.push_back( GetSliceMagnitude(slice, time) );
    sliceSet.push_back( GetSliceX(slice, time) );
    sliceSet.push_back( GetSliceY(slice, time) );
    sliceSet.push_back( GetSliceZ(slice, time) );
}

void SeriesManager::GetVolumeMagnitude(TimeType time, SerieFileContainer& volume)
{
    for ( int slice = 0; slice < m_slicesNo; ++slice)
    {
        volume.push_back( GetSliceMagnitude(slice, time));
    }
}

void SeriesManager::GetVolumeX(TimeType time, SerieFileContainer& volume)
{
    for ( int slice = 0; slice < m_slicesNo; ++slice)
    {
        volume.push_back( GetSliceX(slice, time) );
    }
}

void SeriesManager::GetVolumeY(TimeType time, SerieFileContainer& volume)
{
    for ( int slice = 0; slice < m_slicesNo; ++slice)
    {
        volume.push_back( GetSliceY(slice, time));
    }
}

void SeriesManager::GetVolumeZ(TimeType time, SerieFileContainer& volume)
{
    for ( int slice = 0; slice < m_slicesNo; ++slice)
    {
        volume.push_back( GetSliceZ(slice, time));
    }
}


void SeriesManager::Print(SliceType slice, TimeType time)
{
    std::cout << "Slice no " << slice << " at time " << time << " contain following filenames: " << std::endl;
    std::cout << " --- M: " << GetSliceMagnitude(slice, time) << std::endl;
    std::cout << " --- X: " << GetSliceX(slice, time) << std::endl;
    std::cout << " --- Y: " << GetSliceY(slice, time) << std::endl;
    std::cout << " --- Z: " << GetSliceZ(slice, time) << std::endl;

}

void SeriesManager::Print(bool displaySeries, bool displayFiles)
{
    std::cout << "In directory " << m_directory << " SeriesManager found " << m_series.size() << " series" << std::endl;
    std::cout << " It corresponds to " << m_slicesNo << " number of slices" << std::endl;

    SeriesContainer::iterator it = m_series.begin();
    if ( displaySeries )
    {
        int i = 0;
        std::cout << "Series: " << std::endl;
        while ( it != m_series.end())
        {
            int slice = i/4;
            std::cout << " SLICE [" << slice << "], ";
            switch (i%4) {
            case 0:
                std::cout << "MAGNITUDE: "; break;
            case 1:
                std::cout << "X Component: "; break;
            case 2:
                std::cout << "Y Component: "; break;
            case 3:
                std::cout << "Z Component: "; break;
            }

            std::cout << (*it)->GetSeriesID() << std::endl;
            if (displayFiles)
            {
                std::cout << "\t-- "; (*it)->Print();
            }
            it++;
            i++;
        }
    }
}

std::string SeriesManager::GetSliceMagnitude(SliceType slice, TimeType time)
{
    //std::cout << "magnitude: " << GetSliceComponent(slice, time, MAGNITUDE) << std::endl;
    return GetSliceComponent(slice, time, MAGNITUDE);
}

std::string SeriesManager::GetSliceX(SliceType slice, TimeType time)
{
    // std::cout << "X: " << GetSliceComponent(slice, time, X) << std::endl;
    return GetSliceComponent(slice, time, X);
}

std::string SeriesManager::GetSliceY(SliceType slice, TimeType time)
{
    // std::cout << "Y: " << GetSliceComponent(slice, time, Y) << std::endl;
    return GetSliceComponent(slice, time, Y);
}

std::string SeriesManager::GetSliceZ(SliceType slice, TimeType time)
{
    // std::cout << "Z: " << GetSliceComponent(slice, time, Z) << std::endl;
    return GetSliceComponent(slice, time, Z);
}
