#include "vtkimagewriter.h"

vtkImageWriter::vtkImageWriter()
{
}

void vtkImageWriter::Write(vtkImageData *data, std::string fileName)
{

    vtkSmartPointer<vtkDataSetWriter> writer = vtkSmartPointer<vtkDataSetWriter>::New();
    writer->SetFileName( fileName.c_str() );
    writer->SetInputConnection(data->GetProducerPort());
    try {
        std::cout << "saving : " << fileName << std::endl;
        writer->Write();
    } catch ( ... )
    {
        std::cerr << "Problem during writing: " << fileName << std::endl;
    }

}
