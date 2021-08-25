#ifndef VTK_VISUL_H_
#define VTK_VISUL_H_

#include <vtkDataArray.h>
#include <vtkNew.h>
#include <vtkNamedColors.h>
#include <vtkRenderer.h>
#include <vtkFloatArray.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkSmartVolumeMapper.h>
//#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkImageData.h>
#include <vtkDataSetAttributes.h>
#include <vtkVolume.h>
#include <vtkPiecewiseFunction.h>
#include <vtkAutoInit.h>

namespace NDAVis
{

    class VtkVisul
    {
    public:
        VtkVisul();
        void InsertArray(float *arr, int arrSize);
        void render(int x, int y, int z, int spacingx, int spacingy, int spacingz, int originx, int originy, int originz);
        void setColor(int color);
        void setCamera(int view1,int view2,int view3,int position1,int position2,int position3);
        vtkNew<vtkNamedColors> colors;
        vtkNew<vtkRenderer> renderer;
        vtkNew<vtkFloatArray> vtkArr;
        vtkNew<vtkColorTransferFunction> colorTransferFunction;
        vtkNew<vtkVolumeProperty> volumeProperty;
        vtkNew<vtkSmartVolumeMapper> mapper;
        //vtkNew<vtkGPUVolumeRayCastMapper> mapper;
        vtkNew<vtkImageData> imageData;
        vtkNew<vtkVolume> volume;
        vtkNew<vtkPiecewiseFunction> volumeScalarOpacity;
        vtkCamera *camera;
    };
}

#endif //VTK_VISUL_H_