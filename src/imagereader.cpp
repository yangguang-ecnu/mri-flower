#include "imagereader.h"

ImageReader::ImageReader()
{

    m_sm = NULL;

}

ImageReader::ImageReader(const char *directory)
{

    m_sm = new SeriesManager(directory);
}

ImageReader::~ImageReader()
{
    delete m_sm;
}

ImageType::Pointer ImageReader::ReadSeries(FileNamesContainer files, itk::ImageIOBase* io )
{
    ReaderType::Pointer m_reader = ReaderType::New();
    if(io)
    {
        m_reader->SetImageIO(io);
    }else
    {

        m_reader->SetImageIO( DICOMImageIOType::New());
    }
    m_reader->SetFileNames(files);
    try
    {
        m_reader->Update();
    }
    catch (itk::ExceptionObject &ex)
    {
        std::cout << ex << std::endl;
        return NULL;
    }
    return m_reader->GetOutput();
}

ImageType::Pointer ImageReader::ReadFile(std::string file, itk::ImageIOBase* io )
{
    ReaderType::Pointer m_reader = ReaderType::New();
    if(io)
    {
        m_reader->SetImageIO(io);
    } else
    {
        m_reader->SetImageIO( DICOMImageIOType::New());
    }
    m_reader->SetFileName(file);
    try
    {
        m_reader->Update();
    }
    catch (itk::ExceptionObject &ex)
    {
        std::cout << ex << std::endl;
        return NULL;
    }
    return m_reader->GetOutput();
}

ImageType::Pointer ImageReader::ReadSeries(unsigned int Time, SliceComponent COMPONENT, itk::ImageIOBase* io )
{
    FileNamesContainer files;
    switch(COMPONENT)
    {
    case MAGNITUDE:
        //TODO: here change to m_sm2 which will have cine files
        m_sm->GetVolumeMagnitude(Time, files); break;;
    case X:
        m_sm->GetVolumeX(Time, files); break;;
    case Y:
        m_sm->GetVolumeY(Time, files); break;;
    case Z:
        m_sm->GetVolumeZ(Time, files); break;;
    }
    ReaderType::Pointer m_reader = ReaderType::New();

    if(io)
    {
        m_reader->SetImageIO(io);
    }else
    {
        m_reader->SetImageIO( DICOMImageIOType::New());
    }

    m_reader->SetFileNames(files);

    try
    {
        m_reader->Update();
    }
    catch (itk::ExceptionObject &ex)
    {
        std::cout << ex << std::endl;
        return NULL;
    }
    return m_reader->GetOutput();
}

void ImageReader::Print()
{
    m_sm->Print(true, true);
}

/*
void ImageReader::Update()
{
    try
    {
        m_reader->Update();
    }
    catch (itk::ExceptionObject &ex)
    {
        std::cout << ex << std::endl;
    }
}
*/
