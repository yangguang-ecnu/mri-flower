#ifndef VTKIMAGEWRITER_H
#define VTKIMAGEWRITER_H

#include "vtkImageData.h"
#include "vtkDataSet.h"
#include "vtkPointData.h"
#include "vtkSmartPointer.h"
#include "vtkDataSetWriter.h"
#include "string.h"

class vtkImageWriter
{
public:
    vtkImageWriter();
    static void Write(vtkImageData* data, std::string fileName);

};

#endif // VTKIMAGEWRITER_H
