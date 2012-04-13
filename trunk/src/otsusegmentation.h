#ifndef OTSUSEGMENTATION_H
#define OTSUSEGMENTATION_H

#include "defines.h"
#include "itkOtsuThresholdImageFilter.h"
#include "itkConnectedComponentImageFilter.h"
#include "itkRelabelComponentImageFilter.h"


// Filter Types
typedef itk::OtsuThresholdImageFilter<
        ImageType, ImageType >  OtsuFilterType;
typedef itk::ConnectedComponentImageFilter<
        ImageType, ImageType >  CCFilterType;
typedef itk::RelabelComponentImageFilter<
        ImageType, ImageType > RelabelType;

class OtsuSegmentation
{
public:
    OtsuSegmentation();
    static ImageType::Pointer Compute(ImageType* image, bool brightObjects, unsigned short numberOfBins, bool faceConnected, int minimumObjectSize, bool saveMask = false);

};

#endif // OTSUSEGMENTATION_H
