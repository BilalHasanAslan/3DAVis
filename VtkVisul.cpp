#include "VtkVisul.h"
#include <vtkNew.h>
#include <vtkNamedColors.h>
#include <vtkRenderer.h>
#include <vtkFloatArray.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkImageData.h>
#include <vtkDataSetAttributes.h>
#include <vtkPointData.h>
#include <vtkVolume.h>

#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>


#include <vtkAutoInit.h> 
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingOpenGL2);

namespace NDAVis
{
    vtkNew<vtkNamedColors> colors;
    vtkNew<vtkRenderer> renderer;
    vtkNew<vtkFloatArray> vtkArr;
    float srcArr[10];
    vtkNew<vtkPiecewiseFunction> opacityTransferFunction;
    vtkNew<vtkVolumeProperty> volumeProperty;
    vtkNew<vtkColorTransferFunction> colorTransferFunction;
    //vtkNew<vtkSmartVolumeMapper> mapper;
    vtkNew<vtkGPUVolumeRayCastMapper> mapper;
    vtkNew<vtkImageData> imageData;
    vtkNew<vtkVolume> volume;

    VtkVisul::VtkVisul()
    {
        //Starting Opacity
        opacityTransferFunction->AddPoint(0, 0.0);
        opacityTransferFunction->AddPoint(50, 0.0);
        //Color Transfer
        colorTransferFunction->AddRGBPoint(0, 0.0, 0.0, 1.0);
        colorTransferFunction->AddRGBPoint(25, 1.0, 0.0, 0.0);
        colorTransferFunction->AddRGBPoint(50, 1.0, 1.0, 1.0);

        volumeProperty->SetColor(colorTransferFunction);
        volumeProperty->SetScalarOpacity(opacityTransferFunction);
        volumeProperty->ShadeOn();
        volumeProperty->SetInterpolationTypeToLinear();

        //mapper->SetBlendModeToComposite();
    }

    void VtkVisul::InsertArray(float *arr, int arrSize)
    {
        vtkArr->SetNumberOfComponents(1);
        vtkArr->SetNumberOfTuples(arrSize);
        vtkArr->SetVoidArray(arr, arrSize, 1);
    }

    void VtkVisul::render(int x, int y, int z, int spacingx, int spacingy, int spacingz, int originx, int originy, int originz)
    {
        imageData->NewInstance();
        imageData->SetDimensions(x, y, z);
        imageData->SetSpacing(spacingx, spacingy, spacingz);
        imageData->SetOrigin(originx, originy, originz);
        imageData->GetPointData()->SetScalars(vtkArr);
        ;
        mapper->SetInputData(imageData);

        volume->SetMapper(mapper);
        volume->SetProperty(volumeProperty);

        vtkNew<vtkRenderer> renderer;
        vtkNew<vtkRenderWindow> renWin;
        renWin->AddRenderer(renderer);
        vtkNew<vtkRenderWindowInteractor> iren;
        iren->SetRenderWindow(renWin);
        renderer->AddVolume(volume);
        renderer->SetBackground(colors->GetColor3d("Black").GetData());
        renWin->SetSize(512, 512);
        renWin->Render();
        iren->Start();
    }

}