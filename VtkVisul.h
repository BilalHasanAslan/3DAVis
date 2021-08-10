#include <vtkDataArray.h>
#include <vtkNew.h>
#include <vtkNamedColors.h>
#include <vtkRenderer.h>
#include <vtkFloatArray.h>

namespace NDAVis
{

    class VtkVisul
    {
    public:
        VtkVisul();
        void InsertArray(float* arr,int arrSize);
        void InsertNextArray();
        vtkNew<vtkNamedColors> colors;
        vtkNew<vtkRenderer> renderer;
        vtkNew<vtkFloatArray> vtkArr;

    };
}