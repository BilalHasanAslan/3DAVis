<template>
  <div>
    <div class="controls">
      <!-- <file-selector-component
        class="my-1"
      /> -->
      <div 
        ref="vtkControlsContainer"
      />
    </div>
    <div ref="vtkContainer"
      style="height: 100vh;"
      class="w-100"
    />
  </div>
</template>

<script>
import { ref, onBeforeMount, onMounted, onBeforeUnmount, watchEffect } from 'vue';
// import { ref, unref, onBeforeMount, onMounted, onBeforeUnmount, watchEffect } from 'vue';

// import FileSelectorComponent from './fileSelectorComponent.vue'

import '@kitware/vtk.js/Rendering/Profiles/Volume';
import '@kitware/vtk.js/Rendering/Profiles/Geometry';

import vtkFullScreenRenderWindow  from '@kitware/vtk.js/Rendering/Misc/FullScreenRenderWindow';

// import vtkVolumeActor             from '@kitware/vtk.js/Rendering/Core/Volume';
// import vtkVolumeMapper            from '@kitware/vtk.js/Rendering/Core/VolumeMapper';

import vtkImageMapper             from '@kitware/vtk.js/Rendering/Core/ImageMapper';
import vtkImageSlice              from '@kitware/vtk.js/Rendering/Core/ImageSlice';

import vtkImageData               from '@kitware/vtk.js/Common/DataModel/ImageData';
import vtkDataArray               from '@kitware/vtk.js/Common/Core/DataArray';

import vtkColorTransferFunction   from '@kitware/vtk.js/Rendering/Core/ColorTransferFunction';
import vtkPiecewiseFunction       from '@kitware/vtk.js/Common/DataModel/PiecewiseFunction';

// import vtkWidgetManager           from '@kitware/vtk.js/Widgets/Core/WidgetManager';
// import vtkPiecewiseGaussianWidget from '@kitware/vtk.js/Interaction/Widgets/PiecewiseGaussianWidget';
// import vtkImageCroppingWidget     from '@kitware/vtk.js/Widgets/Widgets3D/ImageCroppingWidget';
// import vtkImageCropFilter         from '@kitware/vtk.js/Filters/General/ImageCropFilter';


export default {
  name: 'VTKVolumeComponent',
  components : {
    // FileSelectorComponent
  },
  props: {
    sourceData: {
      type: Array,
      default: () => []
    }
  },
  setup() {
    const vtkContainer = ref(null);
    const vtkControlsContainer = ref(null);
    const context = ref(null);

    // volume render
    // function volumeRender() {
    //   console.log('volume render')
    // }

    // image render
    // function imageRender() {
    //   console.log('image render')
    // }

    watchEffect(() => {
    //   const res = unref(coneResolution);
    //   const rep = unref(representation);
      if (context.value) {
        
        // coneSource.setResolution(res);
        // actor.getProperty().setRepresentation(rep);
      }
    });

    onBeforeMount(() => {
        
    })

    onMounted(() => {
      if (!context.value) {

        // generate data cube
        const VtkDataTypes = vtkDataArray.VtkDataTypes;

        const size = 64 * 64 // 2D image

        const values = [];
        for (var i = 0; i < size; i++) {
            values[i] = Math.random();
        }

        // get data from props
        // const values = props.sourceData

        var scalars = vtkDataArray.newInstance({
          values: values,
          numberOfComponents: 1, // number of channels
          dataType: VtkDataTypes.FLOAT, // values encoding
          name: 'data source'
        });

        // render data
        const source = vtkImageData.newInstance();
        source.setDimensions(64, 64, 64);
        source.setSpacing(1,1,1);
        source.setOrigin(-32,-32,-32);
        source.getPointData().setScalars(scalars);

        const fullScreenRenderer = vtkFullScreenRenderWindow.newInstance({
          container: vtkContainer.value,
        //   background: [255,255,255]
          background: [0,0,0]
        });

        const renderer = fullScreenRenderer.getRenderer();
        const renderWindow = fullScreenRenderer.getRenderWindow();

        // fullScreenRenderer.getInteractor().removeAllMouseManipulators();

        const mapper = vtkImageMapper.newInstance();
        const actor = vtkImageSlice.newInstance();

        // colour transfer function
        const ctfun = vtkColorTransferFunction.newInstance();
        ctfun.setMappingRange(0,1);
        ctfun.updateRange();
        ctfun.setNanColor(0.0, 0.0, 0.0, 0.0);
        // set colours
        ctfun.addRGBPoint(0.0, 0.75, 0.35, 1.0);
        ctfun.addRGBPoint(1.0, 1.0, 0.0, 1.0);

        // peicewise function
        const ofun = vtkPiecewiseFunction.newInstance();
        // ofun.addPoint(0.0, 0.0);
        // ofun.addPoint(255.0, 1.0);
        ofun.addPoint(0, 1);
        ofun.addPoint(150, 1);
        ofun.addPoint(180, 0);
        ofun.addPoint(255, 0);

        // pipeline
        mapper.setInputData(source);
        actor.setMapper(mapper);

        // image properties
        actor.getProperty().setColorWindow(255);
        actor.getProperty().setColorLevel(127);
        // Uncomment this if you want to use a fixed colorwindow/level
        actor.getProperty().setRGBTransferFunction(ctfun);
        actor.getProperty().setPiecewiseFunction(ofun);

        actor.setMapper(mapper);
        renderer.addActor(actor);

        renderer.resetCamera();
        renderer.resetCameraClippingRange();
        renderWindow.render();

        context.value = {
          fullScreenRenderer,
          renderWindow,
          renderer,
          source,
          actor,
          mapper,
          ctfun,
          ofun
        };
      }
    });

    onBeforeUnmount(() => {
      if (context.value) {
        const { fullScreenRenderer, source, actor, mapper } = context.value;
        actor.delete();
        mapper.delete();
        source.delete();
        fullScreenRenderer.delete();
        context.value = null;
      }
    });

    return {
      vtkContainer,
      vtkControlsContainer,
      context
    //   setRepresentation,
    //   setConeResolution,
    //   coneResolution,
    //   representation,
    };
  }
}
</script>

<style scoped>
.controls {
  position: absolute;
  text-align: right;
  top: 25px;
  right: 25px;
  z-index: 1;
}
</style>