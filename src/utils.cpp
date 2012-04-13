#include "utils.h"

void CreateVectorField(vtkImageData* vtkImage, ImageType* x, ImageType* y, ImageType* z )
{
    typedef itk::ImageRegionConstIterator<ImageType> ConstScalarIterator;
    ConstScalarIterator Xiter(x, x->GetLargestPossibleRegion());
    ConstScalarIterator Yiter(y, y->GetLargestPossibleRegion());
    ConstScalarIterator Ziter(z, z->GetLargestPossibleRegion());

    vtkSmartPointer<vtkShortArray> vectors = vtkSmartPointer<vtkShortArray>::New();
    vectors->SetNumberOfComponents(3);
    vectors->SetNumberOfTuples( vtkImage->GetNumberOfPoints() );
    vectors->SetName("Velocity") ;

    int i = 0;
    while(!Xiter.IsAtEnd())
    {
        short v[3];
        v[0] = Xiter.Get();
        v[1] = Yiter.Get();
        v[2] = Ziter.Get();
     //std::cout << "Short:("<< v[0] <<","<< v[1]<< "," << v[2]<<") "<< std::endl;
        ++Xiter;
        ++Yiter;
        ++Ziter;
        vectors->SetTupleValue(i++, v );
    }
    vtkImage->GetPointData()->SetVectors(vectors);

}


