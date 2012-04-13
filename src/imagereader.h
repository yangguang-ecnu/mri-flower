#ifndef IMAGEREADER_H
#define IMAGEREADER_H

#include "defines.h"
#include "itkImageIOBase.h"
#include "itkImageSeriesReader.h"
#include "itkImageFileReader.h"
#include "seriesmanager.h"



typedef itk::ImageSeriesReader<ImageType>   ReaderType;
typedef std::vector< std::string >   FileNamesContainer;

class ImageReader
{
public:
    ImageReader();
    ~ImageReader();
    ImageReader(const char* directory);

    ImageType::Pointer ReadSeries(FileNamesContainer files, itk::ImageIOBase* io = 0);
    ImageType::Pointer ReadFile(std::string file, itk::ImageIOBase* io = 0);
    ImageType::Pointer ReadSeries(unsigned int Time, SliceComponent COMPONENT, itk::ImageIOBase* io = 0);

    void Print();

private:
    //void Update();
    SeriesManager* m_sm;
};

#endif // IMAGEREADER_H
