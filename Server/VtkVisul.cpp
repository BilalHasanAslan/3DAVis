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
#include "LogKeeper.h"
#include <vtkJPEGWriter.h>
#include <vtkWindowToImageFilter.h>
#include <vtkUnsignedCharArray.h>
#include <vtkRayCastImageDisplayHelper.h>

VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);
/* VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingOpenGL2); */

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

    VtkVisul::VtkVisul()
    {
    }

    void VtkVisul::setColor(float *color, int colorSize, float *opacity, int opacitySize)
    {

        mapper->SetBlendModeToComposite();
        //will be updated
        /*std::array<unsigned char, 3> bkg{{0, 0, 0}};
        colors->SetColor("BkgColor", bkg.data());   */
        std::array<unsigned char, 4> bkg{{51, 77, 102, 255}};
        colors->SetColor("BkgColor", bkg.data());

        /*         colorTransferFunction->AddRGBPoint(0, 0, 0, 0);
        colorTransferFunction->AddRGBPoint(0.01, 0.5, 0.5, 0.5);
        colorTransferFunction->AddRGBPoint(0.05, 0.6, 0.6, 0.6);
        colorTransferFunction->AddRGBPoint(0.015, 0.25, 0.25, 0.25);
        colorTransferFunction->AddRGBPoint(0.02, 0.40, 0.40, 0.1);
        colorTransferFunction->AddRGBPoint(1, 0.70, 0.70, 0.70); */

        int max = 1;
        int min = 0;
        int range = max - min;
        for (int i = 0; i < colorSize; i += 4)
        {
            colorTransferFunction->AddRGBPoint(min + (range * color[i]), color[i + 1], color[i + 2], color[i + 3]);
            
        }

        volumeProperty->SetColor(colorTransferFunction);
        //opacity

        for (int i = 0; i < opacitySize; i++)
        {
            volumeScalarOpacity->AddPoint(opacity[i], opacity[i]);
        }

        /*         volumeScalarOpacity->AddPoint(0.0, 0.0001);
        volumeScalarOpacity->AddPoint(0.000000000000000001, 0.1);
        volumeScalarOpacity->AddPoint(1.0, 1.0); */

        volumeProperty->SetScalarOpacity(volumeScalarOpacity);

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
        renderer->AddViewProp(volume);
        renderer->SetBackground(colors->GetColor3d("BkgColor").GetData());

    }

    void VtkVisul::setCamera(int view1, int view2, int view3, int position1, int position2, int position3)
    {
        camera = renderer->GetActiveCamera();
        /*camera->SetViewUp(view1, view2, view3);
        camera->SetPosition(position1, position2, position3); */
        //camera->SetFocalPoint(c[0], c[1], c[2]);
        double *c = volume->GetCenter();
        camera->SetViewUp(0, 0, -1);
        camera->SetPosition(c[0], c[1] - 400, c[2]);
        camera->SetFocalPoint(c[0], c[1], c[2]);
    }

    void VtkVisul::getImage()
    {   
        

        vtkNew<vtkRenderWindow> renWin;
        renWin->AddRenderer(renderer);
        renWin->OffScreenRenderingOn();
        renWin->SetSize(1080, 720);
        //vtkNew<vtkRenderWindowInteractor> iren;
        //iren->SetRenderWindow(renWin);
        //renWin->SetWindowName("3davis");
        renWin->Render();
        //iren->Start();
        

        vtkNew<vtkWindowToImageFilter> window_to_image_filter;
        window_to_image_filter->SetInput(renWin);
        window_to_image_filter->SetScale(1);
        window_to_image_filter->SetInputBufferTypeToRGB();
        //window_to_image_filter->ReadFrontBufferOff();
        window_to_image_filter->Update();
        writer->SetWriteToMemory(1);
        writer->SetInputConnection(window_to_image_filter->GetOutputPort());
        writer->Write(); 
        vtkUnsignedCharArray *temparr;
        temparr = writer->GetResult();
        imageArrSize = temparr->GetNumberOfTuples();
        imageArr = new int[imageArrSize];
        for (int i = 0; i < imageArrSize; i++)
        {
            imageArr[i] = temparr->GetValue(i);
        }


    }

}