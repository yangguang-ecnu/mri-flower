#include "otsusegmentation.h"

OtsuSegmentation::OtsuSegmentation()
{
}

ImageType::Pointer OtsuSegmentation::Compute(ImageType* image, bool brightObjects, unsigned short numberOfBins, bool faceConnected, int minimumObjectSize, bool saveMask)
{

    std::cout << "Bright objects: " << (brightObjects?"true":"false") << std::endl;
    std::cout << "Number of beans: " << numberOfBins << std::endl;
    std::cout << "Face connected: " << (faceConnected?"true":"false") << std::endl;
    std::cout << "Minimum object size: " << minimumObjectSize << std::endl;

    //FILTERS
    OtsuFilterType::Pointer OtsuFilter = OtsuFilterType::New();
    CCFilterType::Pointer CCFilter = CCFilterType::New();
    RelabelType::Pointer RelabelFilter = RelabelType::New();

    OtsuFilter->SetInput( image );

    if (brightObjects)
    {
        OtsuFilter->SetOutsideValue( SHRT_MAX );
        OtsuFilter->SetInsideValue(  0  );
    }
    else
    {
        OtsuFilter->SetOutsideValue( 0 );
        OtsuFilter->SetInsideValue(  SHRT_MAX );
    }
    OtsuFilter->SetNumberOfHistogramBins( numberOfBins );

    try
    {
        OtsuFilter->Update();
    }
    catch( itk::ExceptionObject & err )
    {
        std::cerr << "ExceptionObject during otsu filtering !" << std::endl;
        std::cerr << err << std::endl;
        return NULL;
    }

    return OtsuFilter->GetOutput();
}
