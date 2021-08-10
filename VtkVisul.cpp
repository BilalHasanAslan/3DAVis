#include "VtkVisul.h"
#include <vtkNew.h>
#include <vtkNamedColors.h>
#include <vtkRenderer.h>
#include <vtkFloatArray.h>

namespace NDAVis
{
    vtkNew<vtkNamedColors> colors;
    vtkNew<vtkRenderer> renderer;
    vtkNew<vtkFloatArray> vtkArr;
    float srcArr[10];
    void VtkVisul::InsertArray(float* arr,int arrSize){
    vtkArr->SetNumberOfComponents(1);
    vtkArr->SetNumberOfTuples(100);
    vtkArr->SetVoidArray(arr, arrSize, 1);

    }

}