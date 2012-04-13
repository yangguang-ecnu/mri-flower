#include "imagecutter.h"

ImageCutter::ImageCutter()
{

}

ImageType::Pointer ImageCutter::Cut(ImageType::Pointer image, ImageType::RegionType desiredRegion)
{

    //set region to cut
    // index = pixel where to start in dimmension
    /*ImageType::IndexType desiredStart;
    desiredStart.SetElement(0, 32);
    desiredStart.SetElement(1, 65);
    desiredStart.SetElement(2, 0);
    // size = range how many pixels to extract
    ImageType::SizeType desiredSize;
    desiredSize.SetElement(0, 56);
    desiredSize.SetElement(1, 85);
    desiredSize.SetElement(2, 26);
    */

    std::cout << "desiredRegion: " << desiredRegion << std::endl;
    //make cut
    ExtractFilterType::Pointer filter = ExtractFilterType::New();
    filter->SetExtractionRegion(desiredRegion);
    filter->SetInput(image);
    #if ITK_VERSION_MAJOR >= 4
        std::cout << "Setting colapse to identity " << std::endl;
        filter->SetDirectionCollapseToIdentity(); // This is required.
    #endif
    filter->Update();
    return filter->GetOutput();

}
/*
  TODO: Check dimension of index and size as well as range
 */
ImageType::Pointer ImageCutter::Cut(ImageType::Pointer image, ImageType::IndexType index, ImageType::SizeType size)
{
    ImageType::RegionType desiredRegion(index, size);
    std::cout << "desiredRegion: " << desiredRegion << std::endl;
    //make cut
    ExtractFilterType::Pointer filter = ExtractFilterType::New();
    filter->SetExtractionRegion(desiredRegion);
    filter->SetInput(image);
    #if ITK_VERSION_MAJOR >= 4
        std::cout << "Setting colapse to identity " << std::endl;
        filter->SetDirectionCollapseToIdentity(); // This is required.
    #endif
    filter->Update();
    return filter->GetOutput();
}
