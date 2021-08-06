<template>
  <div>
    <div
      id="controls"
    >
    </div>
    <div 
        ref="vtkContainer"
        id="window"
        style="height: 90vh;"
        class="w-100 m-auto"
    >
    </div>
  </div>
</template>

<script>
// import { ref, onMounted, onBeforeUnmount, watchEffect } from 'vue';

import '@kitware/vtk.js/Rendering/Profiles/Volume';

import vtkGenericRenderWindow from '@kitware/vtk.js/Rendering/Misc/GenericRenderWindow';
// import vtkCamera from '@kitware/vtk.js/Rendering/Core/Camera'
import vtkVolumeActor from '@kitware/vtk.js/Rendering/Core/Volume';
import vtkVolumeMapper from '@kitware/vtk.js/Rendering/Core/VolumeMapper';
import vtkImageData from '@kitware/vtk.js/Common/DataModel/ImageData';
import vtkDataArray from '@kitware/vtk.js/Common/Core/DataArray';
import vtkColorTransferFunction from '@kitware/vtk.js/Rendering/Core/ColorTransferFunction';
import vtkPiecewiseFunction from '@kitware/vtk.js/Common/DataModel/PiecewiseFunction';
import vtkVolumeController from '@kitware/vtk.js/Interaction/UI/VolumeController';

import vtkInteractorStyleManipulator from '@kitware/vtk.js/Interaction/Style/InteractorStyleManipulator';
import vtkMouseCameraTrackballPanManipulator from '@kitware/vtk.js/Interaction/Manipulators/MouseCameraTrackballPanManipulator';
import vtkMouseCameraTrackballRollManipulator from '@kitware/vtk.js/Interaction/Manipulators/MouseCameraTrackballRollManipulator';
import vtkMouseCameraTrackballRotateManipulator from '@kitware/vtk.js/Interaction/Manipulators/MouseCameraTrackballRotateManipulator';
import vtkMouseCameraTrackballZoomManipulator from '@kitware/vtk.js/Interaction/Manipulators/MouseCameraTrackballZoomManipulator';
// import vtkMouseCameraTrackballZoomToMouseManipulator from '@kitware/vtk.js/Interaction/Manipulators/MouseCameraTrackballZoomToMouseManipulator';
import vtkGestureCameraManipulator from 'vtk.js/Sources/Interaction/Manipulators/GestureCameraManipulator';

export default {
  name: 'VTKVolumeComponent',
  data() {
    return {
      container: null,
      controls: null,
      context: null,
      source: null,
      background: [0,0,0],
      cameraPosition: [0,0,10],
      focalPoint: [0,0,0]
    }
  },
  beforeMount() {
    if (this.context) {
      const { genericRenderer, actor, mapper } = this.context;
      actor.delete();
      mapper.delete();
      genericRenderer.delete();
      this.context = null;
    }

    // generate data cube
    var VtkDataTypes = vtkDataArray.VtkDataTypes;

    var width = 50, height = 50, depth = 50;
    var size = width * height * depth;

    var values = [];
    for (var i = 0; i < size; i++) {
      values[i] = Math.random();
    }

    var scalars = vtkDataArray.newInstance({
      values: values,
      numberOfComponents: 1, // number of channels (grayscale)
      dataType: VtkDataTypes.FLOAT, // values encoding
      name: 'data source'
    });

    // render data
    this.source = vtkImageData.newInstance();
    this.source.setDimensions(50, 50, 50);
    this.source.setSpacing(2,2,2);
    this.source.setOrigin(-50,-50,-50);
    this.source.getPointData().setScalars(scalars);
  },
  mounted() {
    if (!this.context || this.source != null) {

        this.container = document.querySelector('#window');
        this.controls = document.querySelector('#controls');

        // WebGL/OpenGL impl
        const genericRenderWindow = vtkGenericRenderWindow.newInstance();
        genericRenderWindow.setContainer(this.container);
        genericRenderWindow.setBackground(this.background);

        // VTK renderWindow/renderer
        const renderWindow = genericRenderWindow.getRenderWindow();
        const renderer     = genericRenderWindow.getRenderer();

        // interactor
        const interactorStyle = vtkInteractorStyleManipulator.newInstance();
        genericRenderWindow.getInteractor().setInteractorStyle(interactorStyle);

        //  remove default mainpulators
        interactorStyle.removeAllMouseManipulators();

        // mouse manipulators
        // pan
        const pan = vtkMouseCameraTrackballPanManipulator.newInstance();
        pan.setButton(3); // right mouse button
        interactorStyle.addMouseManipulator(pan);

        // rotate
        const rotate = vtkMouseCameraTrackballRotateManipulator.newInstance();
        rotate.setButton(1); // left mouse button
        interactorStyle.addMouseManipulator(rotate);

        // zoom
        const zoom = vtkMouseCameraTrackballZoomManipulator.newInstance();
        // zoom to mouse
        // const zoom = vtkMouseCameraTrackballZoomToMouseManipulator.newInstance();
        zoom.setScrollEnabled(true);
        interactorStyle.addMouseManipulator(zoom);

        // roll
        const roll = vtkMouseCameraTrackballRollManipulator.newInstance();
        roll.setButton(2); // middle mouse button
        interactorStyle.addMouseManipulator(roll);

        // gesture
        interactorStyle.addGestureManipulator(
          vtkGestureCameraManipulator.newInstance()
        );

        // camera
        const camera = renderer.getActiveCamera();
        camera.setFocalPoint(0,0,0);
        camera.setPosition(0,0,-500);
        
        // camera.setPosition(this.cameraPosition);
        // camera.setFocalPoint(this.focalPoint);

        renderer.setActiveCamera(camera);

        // Pipeline
        const actor  = vtkVolumeActor.newInstance();
        const mapper = vtkVolumeMapper.newInstance();

        actor.setMapper(mapper);
        mapper.setInputData(this.source);
        mapper.setSampleDistance(2);
        renderer.addActor(actor);

        // colour transfer function
        const ctfun = vtkColorTransferFunction.newInstance();
        ctfun.addRGBPoint(200.0, 1.0, 1.0, 1.0);
        ctfun.addRGBPoint(2000.0, 0.0, 0.0, 0.0);

        const ofun = vtkPiecewiseFunction.newInstance();
        ofun.addPoint(200.0, 0.0);
        ofun.addPoint(1200.0, 0.2);
        ofun.addPoint(4000.0, 0.4);

        actor.getProperty().setRGBTransferFunction(0, ctfun);
        actor.getProperty().setScalarOpacityUnitDistance(0, 4.5);
        actor.getProperty().setScalarOpacityUnitDistance(0, 4.5);
        actor.getProperty().setInterpolationTypeToFastLinear();
        // shading
        actor.getProperty().setShade(true);
        actor.getProperty().setUseGradientOpacity(0, true);
        // good default values - suggested by vtk documentation
        actor.getProperty().setGradientOpacityMinimumOpacity(0, 0.0);
        actor.getProperty().setGradientOpacityMaximumOpacity(0, 1.0);
        actor.getProperty().setAmbient(0.2);
        actor.getProperty().setDiffuse(0.7);
        actor.getProperty().setSpecular(0.3);
        actor.getProperty().setSpecularPower(8.0);

        

        // control UI
        const controllerWidget = vtkVolumeController.newInstance({
          size: [400, 150],
          rescaleColorMap: true,
        });

        const isBackgroundDark = this.background[0] + this.background[1] + this.background[2] < 1.5;
        
        controllerWidget.setContainer(this.controls);
        controllerWidget.setupContent(renderWindow, actor, isBackgroundDark);

        // controllerWidget.render();

        // first render
        // renderer.resetCamera();
        // renderWindow.render(); 

        // rezise to adjust
        genericRenderWindow.resize();

        this.context = {
            genericRenderWindow,
            renderWindow,
            renderer,
            actor,
            mapper,
            ctfun,
            ofun
        };
    }
  }
}
</script>

<style scoped>
  #controls {
    position: relative;
  }
</style>