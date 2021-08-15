#include <vtkNamedColors.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNew.h>
#include <vtkDataArray.h>
#include <vtkPiecewiseFunction.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>

int main(int argc, char *argv[])
{

    //Color library

    vtkNew<vtkNamedColors> colors;

    // Renderer

    vtkNew<vtkRenderer> renderer;

    /*   // Create a new render window

  vtkNew<vtkRenderWindow> renWin ;
  renWin->AddRenderer(renderer);

  // Make the render window interacting

  vtkNew<vtkRenderWindowInteractor> iren ;
  iren->SetRenderWindow(renWin);
 */
    //Put in Array

    vtkNew<vtkDataArray> vtkArr;
    vtk->insertTuple(vtkDataArray.vtkDataTypes.float,arr)

    // For volume rendering, we need to first define a map from scalar values to
    // colors and opacity (transparency) values. Then add these maps to volume
    // property

    // Add a piece-wise function for color transfer functions. Piece-wise means
    // adding control (interpolation) points.

    vtkNew<vtkPiecewiseFunction> opacityTransferFunction;
    opacityTransferFunction->AddPoint(0, 0.0);
    opacityTransferFunction->AddPoint(50, 0.0);

    // Piece-wise function cannot be used for colors because colors are vectors

    vtkNew<vtkColorTransferFunction> colorTransferFunction;
    colorTransferFunction->AddRGBPoint(0, 0.0, 0.0, 1.0);
    colorTransferFunction->AddRGBPoint(25, 1.0, 0.0, 0.0);
    colorTransferFunction->AddRGBPoint(50, 1.0, 1.0, 1.0);

    // Set volume rendering properties

    vtkNew<vtkVolumeProperty> volumeProperty;
    volumeProperty->SetColor(colorTransferFunction);
    volumeProperty->SetScalarOpacity(opacityTransferFunction);
    volumeProperty->ShadeOn();
    volumeProperty->SetInterpolationTypeToLinear();

    // Add a mapper to create graphic primitives from the data

    vtkNew<vtkSmartVolumeMapper> mapper;
    mapper->SetBlendModeToComposite();
    mapper->SetInputConnection(reader->GetOutputPort());

    // Create a new actor(the actual graphics object) and add the mapped data to
    // it

    vtkNew<vtkVolume> volume;
    volume->SetMapper(mapper);
    volume->SetProperty(volumeProperty);

    // Add the volume actor to the renderer
    renderer->AddVolume(volume);

    // Set the background color

    renderer->SetBackground(colors->GetColor3d("Black").GetData());

    // Set the size of the render window
    renWin->SetSize(512, 512);

    // Render the data
    renWin->Render();

    // Start the interactor
    iren->Start();

    return EXIT_SUCCESS;
}








# create the vtkTable object
tab = vtk.vtkTable()

# create a vtkDataArray with arr values
vtkarr = vtk.vtkDoubleArray()
vtkarr.SetNumberOfComponents(arr.shape[1])
vtkarr.SetNumberOfTuples(arr.shape[0])
vtkarr.SetVoidArray(arr, arr.size, 0)

# finally assign the values to the vtkTable
tab.GetRowData().AddArray(vtkarr)
