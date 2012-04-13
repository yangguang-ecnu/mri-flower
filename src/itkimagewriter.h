#ifndef ITKIMAGEWRITER_H
#define ITKIMAGEWRITER_H
#include "defines.h"
#include "itkImageFileWriter.h"
#include "string.h"

typedef itk::ImageFileWriter< ImageType >  WriterType;

class itkImageWriter
{
public:
    itkImageWriter();
    static void SaveImage(ImageType::Pointer image, std::string fileName);
};

#endif // ITKIMAGEWRITER_H
