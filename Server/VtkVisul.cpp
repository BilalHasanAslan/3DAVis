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

    /*
    The empty constructor for the VtkVisul
    
    Args:
      self: the object itself
    Returns:
      Nothing
    */
    VtkVisul::VtkVisul()
    {
    }

    /*
    The code is used to set the color and opacity of the volume.
    
    Args:
      color: a float array of size 4*N, where N is the number of points. The first set of 4 values are the RGBA values for the first point, the second set are the values for the second point, etc.
      colorSize: the number of elements in the color array.
      opacity: a 1D array of opacity values.
      opacitySize: the number of opacity values in the opacity array
    Returns:
      Nothing
    */
    void VtkVisul::setColor(float *color, int colorSize, float *opacity, int opacitySize)
    {

        mapper->SetBlendModeToComposite();
        //will be updated
        /*std::array<unsigned char, 3> bkg{{0, 0, 0}};
        colors->SetColor("BkgColor", bkg.data());   */
        std::array<unsigned char, 4> bkg{{0, 0, 0, 255}};
        colors->SetColor("BkgColor", bkg.data());
    
        colorTransferFunction->AddRGBPoint(0, 0, 0, 0);
        colorTransferFunction->AddRGBPoint(0.01, 0.5, 0.5, 0.5);
        colorTransferFunction->AddRGBPoint(0.05, 0.6, 0.6, 0.6);
        colorTransferFunction->AddRGBPoint(0.015, 0.25, 0.25, 0.25);
        colorTransferFunction->AddRGBPoint(0.02, 0.40, 0.40, 0.1);
        colorTransferFunction->AddRGBPoint(1, 0.70, 0.70, 0.70);  

/*         int max = 0.19177940487861633;
        int min = 0;
        int range = max - min;
        for (int i = 0; i < colorSize; i += 4)
        {
            colorTransferFunction->AddRGBPoint(min + (range * color[i]), color[i + 1], color[i + 2], color[i + 3]);
            
        }  */

        volumeProperty->SetColor(colorTransferFunction);
        //opacity
 
/*         for (int i = 0; i < opacitySize; i+=2)
        {
            volumeScalarOpacity->AddPoint(opacity[i], opacity[i+1]);
        }  */

        volumeScalarOpacity->AddPoint(0.0, 0.0001);
        volumeScalarOpacity->AddPoint(0.000000000000000001, 0.1);
        volumeScalarOpacity->AddPoint(1.0, 1.0);  

        volumeProperty->SetScalarOpacity(volumeScalarOpacity);

    }

    /*
    The InsertArray function takes a pointer to an array, the size of the array, and the dimensions of the volume.
    
    Args:
      arr: the array to be inserted
      arrSize: the size of the array
      DimX: the number of points along the x-axis
      DimY: The number of rows in the array.
      DimZ: the number of slices in the z direction
    Returns:
      Nothing.
    */
    void VtkVisul::InsertArray(float *arr, int arrSize, int DimX, int DimY, int DimZ)
    {
        vtkArr->SetNumberOfComponents(1);
        vtkArr->SetNumberOfTuples(arrSize);
        vtkArr->SetVoidArray(arr, arrSize, 1);
        this->DimX = DimX;
        this->DimY = DimY;
        this->DimZ = DimZ;
    }

    /*
    ```
    Renders the 3D volume
    
    Args:
      x: The number of pixels in the x-direction.
      y: The number of pixels in the y-direction.
      z: The number of slices in the z direction.
      spacingx: The spacing between adjacent pixels in the x direction.
      spacingy: The spacing between adjacent pixels in the y direction.
      spacingz: The spacing between slices in the z direction.
      originx: the x coordinate of the origin of the image.
      originy: The y-coordinate of the origin of the image.
      originz: The z-coordinate of the origin of the image.
    Returns:
      Nothing.
    */
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

    /*
    Sets camera of the render
    Args:
      view1: camera view.
      view2: camera view.
      view3: camera view.
      position1: camera position.
      position2: camera position.
      position3: camera position.
    Returns:
      Nothing.
    */
    void VtkVisul::setCamera(int view1, int view2, int view3, int position1, int position2, int position3)
    {
        camera = renderer->GetActiveCamera();
        double *c = volume->GetCenter();
        camera->SetViewUp(view1, view2, view3);
        camera->SetPosition(position1, position2, position3); 
        //camera->SetFocalPoint(-(DimX/2), -(DimY/2), -(DimZ/2));
        camera->SetFocalPoint(c[0], c[1], c[2]);
        
/*      camera->SetViewUp(0, 0, -1);
        camera->SetPosition(c[0], c[1] - 400, c[2]);
        camera->SetFocalPoint(c[0], c[1], c[2]);
         [-(xDimension/2),-(yDimension/2),-(zDimension/2)]
         */
    }

    /*
    The below code is used to get the image from the 3D volume.
    
    Args:
      None
    Returns:
      The image array
    */
    void VtkVisul::getImage()
    {   
        

        vtkNew<vtkRenderWindow> renWin;
        renWin->AddRenderer(renderer);
        renWin->OffScreenRenderingOn();
        renWin->SetSize(1080, 720);
        //vtkNew<vtkRenderWindowInteractor> iren;
        //iren->SetRenderWindow(renWin);
        renWin->SetWindowName("3davis");
        renWin->Render();
        //iren->Start();
        

        vtkNew<vtkWindowToImageFilter> window_to_image_filter;
        window_to_image_filter->SetInput(renWin);
        window_to_image_filter->SetScale(1);
        window_to_image_filter->SetInputBufferTypeToRGB();
        window_to_image_filter->ReadFrontBufferOff();
        window_to_image_filter->Update();
        writer->SetWriteToMemory(1);
        writer->SetInputConnection(window_to_image_filter->GetOutputPort());
        //writer->SetFileName("awe.jpg");
        writer->Write();
        vtkWriterArray = writer->GetResult();


/*         imageArrSize = vtkWriterArray->GetNumberOfTuples();
        imageArr = new int[imageArrSize];
        for (int i = 0; i < imageArrSize; i++)
        {
            imageArr[i] = vtkWriterArray->GetValue(i);
        } */


    }


}