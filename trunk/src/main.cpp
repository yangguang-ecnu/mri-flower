
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#ifdef __BORLANDC__
#define ITK_LEAN_AND_MEAN
#endif

#include "defines.h"
#include "itkImage.h"
#include "imagereader.h"
#include "vtkimagewriter.h"
#include "itkimagewriter.h"

#include "utils.h"

#include "otsusegmentation.h"
#include "imagemasker.h"

#include "itkVTKImageIO.h"
#include "vtkKWImage.h"
#include "vtkKWImageIO.h"

#include "itkMinimumMaximumImageCalculator.h"

#include "imagecutter.h"

int main( int argc, char* argv[] )
{

    if( argc < 2 )
    {
        std::cerr << "Usage: " << std::endl;
        //     argv[1]        argv[2]
        std::cerr << argv[0] << " DicomDirectory  OutputVolimePrefix"
                  << std::endl;
        return EXIT_FAILURE;
    }
    VTKImageIOType::Pointer vtkIO = VTKImageIOType::New();
    ImageReader* reader = new ImageReader(argv[1]);

    //file format: <prefix><index>.vtk
    std::string FileExtension = "vtk";
    std::string FilePrefix = argv[2];
    itk::MinimumMaximumImageCalculator<ImageType>::Pointer minMax = itk::MinimumMaximumImageCalculator<ImageType>::New();

    for ( int FileIndex = 0; FileIndex < 20 ; ++FileIndex)
    {

        ImageType::Pointer magnitude = ImageType::New();
        ImageType::Pointer x = ImageType::New();
        ImageType::Pointer y = ImageType::New();
        ImageType::Pointer z = ImageType::New();

        magnitude = reader->ReadSeries(FileIndex, MAGNITUDE);

        //TODO: make some defaults and get input from input parameters

        //test4new (32-88, 65-150, 0-25)

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

        ImageCutter* cutter = new ImageCutter();
        magnitude = cutter->Cut(magnitude, desiredRegion);


        std::stringstream FileName2;
        FileName2 << "magnitude_" <<  FileIndex << "." << FileExtension;

        itkImageWriter::SaveImage(magnitude, FileName2.str());

        //Reader will automatically include slope and rescale intercept values so from pixel value we have positive
        // and negative values in the x, y or z images :) NICE!
        x = reader->ReadSeries(FileIndex, X);
        y = reader->ReadSeries(FileIndex, Y);
        z = reader->ReadSeries(FileIndex, Z);

        //cut x, y, z
        x = cutter->Cut(x, desiredRegion);
        y = cutter->Cut(y, desiredRegion);
        z = cutter->Cut(z, desiredRegion);

        FileName2.str("");
        FileName2 << "x_" <<  FileIndex << "." << FileExtension;
        itkImageWriter::SaveImage(x, FileName2.str());

        FileName2.str("");
        FileName2 << "y_" <<  FileIndex << "." << FileExtension;
        itkImageWriter::SaveImage(x, FileName2.str());

        FileName2.str("");
        FileName2 << "z_" <<  FileIndex << "." << FileExtension;
        itkImageWriter::SaveImage(x, FileName2.str());


        //OTSU SEGMENTATION of magnitude to create mask for vector field components
        ImageType::Pointer mask = OtsuSegmentation::Compute(magnitude, 1, 128, 0, 100);
        // why in place filtering destroy region informations ;(
        // instead Compute3 takes x by ref and substitute data with filter output
        ImageMasker::Compute3(x,mask);
        ImageMasker::Compute3(y,mask);
        ImageMasker::Compute3(z,mask);
        ImageMasker::Compute3(magnitude, mask);

        vtkKWImage* vtkImage0 = vtkKWImage::New();
        vtkImage0->SetITKImageBase( magnitude );
        //Transfer to VTK DATA
        vtkSmartPointer<vtkImageData> vtkImage = vtkSmartPointer<vtkImageData>::New();
        vtkImage = vtkImage0->GetVTKImage();
        //vtkImage0->Delete(); <-- if i delete this here i will break the pipeline and I will not be able to save vtkImage...
        //vtkImage->Print(std::cout);

        CreateVectorField(vtkImage, x,y,z);

        std::stringstream FileName;
        FileName << FilePrefix << "_" <<  FileIndex << "." << FileExtension;
        vtkImageWriter::Write(vtkImage, FileName.str());

        vtkImage0->Delete();
        delete cutter;
    }
    delete reader;
    return EXIT_SUCCESS;
}
