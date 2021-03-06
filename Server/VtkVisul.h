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
#include <vtkJPEGWriter.h>


namespace NDAVis
{

    class VtkVisul
    {
    public:
        VtkVisul();

        vtkNew<vtkJPEGWriter> writer;
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
/*         int* imageArr;
        int imageArrSize; */
        vtkUnsignedCharArray *vtkWriterArray;
        int DimX,DimY,DimZ;

        void InsertArray(float *arr, int arrSize, int DimX, int DimY, int DimZ);
        void render(int x, int y, int z, int spacingx, int spacingy, int spacingz, int originx, int originy, int originz);
        void setColor(float *color, int colorSize,float* opacity,int opacitySize);
        void setCamera(int view1,int view2,int view3,int position1,int position2,int position3);
        void getImage();

    };
}

#endif //VTK_VISUL_H_