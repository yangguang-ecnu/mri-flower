#ifndef IMAGECUTTER_H
#define IMAGECUTTER_H

#include "defines.h"
#include "itkExtractImageFilter.h"

/*
//set region to cut
// index = pixel where to start in dimmension
ImageType::IndexType desiredStart;
desiredStart.SetElement(0, 32);
desiredStart.SetElement(1, 65);
desiredStart.SetElement(2, 0);
// size = range how many pixels to extract
ImageType::SizeType desiredSize;
desiredSize.SetElement(0, 56);
desiredSize.SetElement(1, 85);
desiredSize.SetElement(2, 26);

ImageType::RegionType desiredRegion(desiredStart, desiredSize);
std::cout << "desiredRegion: " << desiredRegion << std::endl;
//make cut
typedef itk::ExtractImageFilter< ImageType, ImageType > ExtractFilterType;
ExtractFilterType::Pointer filter = ExtractFilterType::New();
filter->SetExtractionRegion(desiredRegion);
filter->SetInput(magnitude);
#if ITK_VERSION_MAJOR >= 4
    std::cout << "Setting colapse to identity " << std::endl;
    filter->SetDirectionCollapseToIdentity(); // This is required.
#endif
filter->Update();
*/

typedef itk::ExtractImageFilter< ImageType, ImageType > ExtractFilterType;

class ImageCutter
{
public:
    ImageCutter();
    static ImageType::Pointer Cut(ImageType::Pointer image, ImageType::RegionType desiredRegion);
    static ImageType::Pointer Cut(ImageType::Pointer image, ImageType::IndexType index, ImageType::SizeType size);
};


#endif // IMAGECUTTER_H
