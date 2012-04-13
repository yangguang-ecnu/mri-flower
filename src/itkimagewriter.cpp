#include "itkimagewriter.h"


itkImageWriter::itkImageWriter()
{
}

void itkImageWriter::SaveImage(ImageType::Pointer image, std::string fileName)
{

    WriterType::Pointer writer = WriterType::New();
    writer->SetImageIO(itk::VTKImageIO::New());
    writer->SetInput( image );
    writer->SetFileName(fileName );
    writer->SetUseCompression(1);
    try
    {
        std::cout << "Saving: " << fileName << std::endl;
        writer->Update();
    }
    catch (itk::ExceptionObject &ex)
    {
        std::cout << ex << std::endl;
    }
}
