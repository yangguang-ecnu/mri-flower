#ifndef UTILS_H
#define UTILS_H

#include "defines.h"
#include "itkImageRegionConstIterator.h"


#include "vtkSmartPointer.h"
#include "vtkDataSet.h"
#include "vtkPointData.h"
#include "vtkImageData.h"
#include "vtkShortArray.h"


void CreateVectorField(vtkImageData* vtkImage, ImageType* x, ImageType* y, ImageType* z );
#endif // UTILS_H
