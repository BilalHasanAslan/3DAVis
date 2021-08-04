<template>
  <div>
    <div 
        ref="vtkContainer"
        id="window"
        class="w-100 m-auto"
    >
    </div>
  </div>
</template>

<script>
// import { ref, onMounted, onBeforeUnmount, watchEffect } from 'vue';

import '@kitware/vtk.js/Rendering/Profiles/Volume';

import vtkGenericRenderWindow from '@kitware/vtk.js/Rendering/Misc/GenericRenderWindow';
import vtkVolumeActor from '@kitware/vtk.js/Rendering/Core/Volume';
import vtkVolumeMapper from '@kitware/vtk.js/Rendering/Core/VolumeMapper';
import vtkImageData from '@kitware/vtk.js/Common/DataModel/ImageData';
import vtkDataArray from '@kitware/vtk.js/Common/Core/DataArray';
import vtkColorTransferFunction from '@kitware/vtk.js/Rendering/Core/ColorTransferFunction';
import vtkPiecewiseFunction from '@kitware/vtk.js/Common/DataModel/PiecewiseFunction';
import vtkVolumeController from '@kitware/vtk.js/Interaction/UI/VolumeController';

export default {
  name: 'VTKVolumeComponent',
  data() {
    return {
      coneResolution: 6,
      representation: 2,
      container: null,
      context: null,
      source: null
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
    this.source.setSpacing(1,1,1);
    this.source.setOrigin(0,0,0);
    this.source.getPointData().setScalars(scalars);
  },
  mounted() {
    if (!this.context || this.source != null) {

        this.container = document.querySelector('#window');

        // WebGL/OpenGL impl
        const genericRenderWindow = vtkGenericRenderWindow.newInstance();
        genericRenderWindow.setContainer(this.container);
        genericRenderWindow.setBackground([0,0,0]);

        // VTK renderWindow/renderer
        const renderWindow = genericRenderWindow.getRenderWindow();
        const renderer     = genericRenderWindow.getRenderer();

        // Pipeline
        const actor  = vtkVolumeActor.newInstance();
        const mapper = vtkVolumeMapper.newInstance();

        actor.setMapper(mapper);
        mapper.setInputData(this.source);
        mapper.setSampleDistance(0.7);
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
        actor.getProperty().setShade(true);
        actor.getProperty().setUseGradientOpacity(0, true);
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
        
        controllerWidget.setContainer(this.container);
        controllerWidget.setupContent(renderWindow, actor);

        // Render
        renderer.resetCamera();
        renderWindow.render(); 

        this.context = {
            genericRenderWindow,
            renderWindow,
            renderer,
            actor,
            mapper
        };
    }
  }
}
</script>

<style scoped>

</style>