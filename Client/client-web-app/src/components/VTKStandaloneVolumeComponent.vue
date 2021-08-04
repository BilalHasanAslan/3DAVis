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
  watch: {
    coneResolution: function() {
        this.context.source.setResolution(this.coneResolution);
        this.context.renderWindow.render();
    },
    representation: function() {
        this.context.actor.getProperty().setRepresentation(this.representation);
        this.context.renderWindow.render();
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
    // console.log(values)

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
        mapper.setSampleDistance(0.7);

        // colour transfer function
        const ctfun = vtkColorTransferFunction.newInstance();
        ctfun.addRGBPoint(200.0, 1.0, 1.0, 1.0);
        ctfun.addRGBPoint(2000.0, 0.0, 0.0, 0.0);

        actor.getProperty().setRGBTransferFunction(0, ctfun);
        actor.getProperty().setScalarOpacityUnitDistance(0, 4.5);
        actor.getProperty().setInterpolationTypeToFastLinear();

        actor.setMapper(mapper);
        mapper.setInputData(this.source);
        mapper.setSampleDistance(0.7);
        renderer.addActor(actor);

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