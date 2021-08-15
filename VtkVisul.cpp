#include "VtkVisul.h"
#include <vtkNew.h>
#include <vtkNamedColors.h>
#include <vtkRenderer.h>
#include <vtkFloatArray.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkImageData.h>
#include <vtkDataSetAttributes.h>
#include <vtkPointData.h>
#include <vtkVolume.h>
#include <vtkAutoInit.h>
#include <vtkPiecewiseFunction.h>
#include <vtkCamera.h>

#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>



VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingOpenGL2);

namespace NDAVis
{
    vtkNew<vtkNamedColors> colors;
    vtkNew<vtkRenderer> renderer;
    vtkNew<vtkFloatArray> vtkArr;
    vtkNew<vtkVolumeProperty> volumeProperty;
    vtkNew<vtkColorTransferFunction> colorTransferFunction;
    vtkNew<vtkSmartVolumeMapper> mapper;
    //vtkNew<vtkGPUVolumeRayCastMapper> mapper;
    vtkNew<vtkImageData> imageData;
    vtkNew<vtkVolume> volume;
    vtkNew<vtkPiecewiseFunction> volumeScalarOpacity;
    vtkNew<vtkPiecewiseFunction> volumeGradientOpacity;

    VtkVisul::VtkVisul()
    {
        std::array<unsigned char, 4> bkg{{51, 77, 102, 255}};
        colors->SetColor("BkgColor", bkg.data());
        //Color Transfer
        colorTransferFunction->AddRGBPoint(0, 1.0, 1.0, 1.0);
        colorTransferFunction->AddRGBPoint(0.5, 0.0, 0.0, 0.0);

        mapper->SetBlendModeToComposite();

        volumeScalarOpacity->AddPoint(0, 0.00);
        volumeScalarOpacity->AddPoint(0.2, 0.15);
        volumeScalarOpacity->AddPoint(0.4, 0.30);
        volumeScalarOpacity->AddPoint(0.8, 0.85);

        volumeGradientOpacity->AddPoint(0, 0.0);
        volumeGradientOpacity->AddPoint(90, 0.5);
        volumeGradientOpacity->AddPoint(100, 1.0);

        volumeProperty->SetColor(colorTransferFunction);
        volumeProperty->SetScalarOpacity(volumeScalarOpacity);
        volumeProperty->SetGradientOpacity(volumeGradientOpacity);

        volumeProperty->SetInterpolationTypeToLinear();
        volumeProperty->ShadeOn();
        volumeProperty->SetAmbient(0.4);
        volumeProperty->SetDiffuse(0.6);
        volumeProperty->SetSpecular(0.2);
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
        mapper->SetInputData(imageData);

        volume->SetMapper(mapper);
        volume->SetProperty(volumeProperty);

        vtkNew<vtkRenderer> renderer;
        vtkNew<vtkRenderWindow> renWin;
        renWin->AddRenderer(renderer);
        vtkNew<vtkRenderWindowInteractor> iren;
        iren->SetRenderWindow(renWin);

        renderer->AddViewProp(volume);
        //renderer->AddVolume(volume);

        vtkCamera *camera = renderer->GetActiveCamera();
        double *c = volume->GetCenter();
        camera->SetViewUp(0, 0, -1);
        camera->SetPosition(c[0], c[1] - 400, c[2]);
        camera->SetFocalPoint(c[0], c[1], c[2]);
        camera->Azimuth(30.0);
        camera->Elevation(30.0);

        renderer->SetBackground(colors->GetColor3d("BkgColor").GetData());
        renWin->SetSize(1000, 500);
        renWin->SetWindowName("3davis");
        renWin->Render();
        iren->Start();
    }

}