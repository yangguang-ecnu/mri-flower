#ifndef IMAGEMASKER_H
#define IMAGEMASKER_H

#include "defines.h"
#include "itkMaskImageFilter.h"
#include "itkInputDataObjectConstIterator.h"

typedef itk::MaskImageFilter< ImageType, ImageType > MaskFilterType;
class ImageMasker
{
public:
    ImageMasker();
    static void Compute(ImageType::Pointer image, ImageType::Pointer mask);
    static ImageType::Pointer Compute2(ImageType::Pointer image, ImageType::Pointer mask);
    static void Compute3(ImageType::Pointer &image, ImageType::Pointer mask);

};

#endif // IMAGEMASKER_H
