#ifndef DEFINES_H
#define DEFINES_H
#include "itkImage.h"
#include "itkVTKImageIO.h"
#include "itkGDCMImageIO.h"

typedef signed short    PixelType;
const unsigned int      Dimension = 3;
typedef itk::Image<PixelType, Dimension> ImageType;
typedef itk::VTKImageIO  VTKImageIOType;
typedef itk::GDCMImageIO DICOMImageIOType;

#endif // DEFINES_H
