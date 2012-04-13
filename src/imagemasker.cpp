#include "imagemasker.h"

ImageMasker::ImageMasker()
{
}

void ImageMasker::Compute(ImageType::Pointer image, ImageType::Pointer mask)
{

    MaskFilterType::Pointer maskFilter = MaskFilterType::New();
    maskFilter->SetInput(image);
    maskFilter->SetMaskImage(mask);
    maskFilter->InPlaceOn();

    try
    {
        maskFilter->Update();
    }
    catch (itk::ExceptionObject &ex)
    {
        std::cout << ex << std::endl;
      //  return NULL;
    }
    //return maskFilter->GetOutput();
}

ImageType::Pointer ImageMasker::Compute2(ImageType::Pointer image, ImageType::Pointer mask)
{

    MaskFilterType::Pointer maskFilter = MaskFilterType::New();
    maskFilter->SetInput(image);
    maskFilter->SetMaskImage(mask);
    //maskFilter->InPlaceOn();

    try
    {
        maskFilter->Update();
    }
    catch (itk::ExceptionObject &ex)
    {
        std::cout << ex << std::endl;
        return NULL;
    }
    return maskFilter->GetOutput();
}


void ImageMasker::Compute3(ImageType::Pointer &image, ImageType::Pointer mask)
{
    MaskFilterType::Pointer maskFilter = MaskFilterType::New();
    maskFilter->SetInput(image);
    maskFilter->SetMaskImage(mask);
    //maskFilter->InPlaceOn();

    try
    {
        maskFilter->Update();
    }
    catch (itk::ExceptionObject &ex)
    {
        std::cout << ex << std::endl;
    //    return NULL;
    }
    image = maskFilter->GetOutput();

}
