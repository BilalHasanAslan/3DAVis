<template>
  <div>
    <div class="controls">
      <file-selector-component
        class="my-1"
      />
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

import FileSelectorComponent from './fileSelectorComponent.vue'

import '@kitware/vtk.js/Rendering/Profiles/Volume';
import '@kitware/vtk.js/Rendering/Profiles/Geometry';
import '@kitware/vtk.js/Rendering/Profiles/Glyph';

import vtkFullScreenRenderWindow  from '@kitware/vtk.js/Rendering/Misc/FullScreenRenderWindow';

import vtkVolumeActor             from '@kitware/vtk.js/Rendering/Core/Volume';
import vtkVolumeMapper            from '@kitware/vtk.js/Rendering/Core/VolumeMapper';

import vtkImageData               from '@kitware/vtk.js/Common/DataModel/ImageData';
import vtkDataArray               from '@kitware/vtk.js/Common/Core/DataArray';

import vtkColorTransferFunction   from '@kitware/vtk.js/Rendering/Core/ColorTransferFunction';
import vtkPiecewiseFunction       from '@kitware/vtk.js/Common/DataModel/PiecewiseFunction';

import vtkWidgetManager           from '@kitware/vtk.js/Widgets/Core/WidgetManager';
import vtkPiecewiseGaussianWidget from '@kitware/vtk.js/Interaction/Widgets/PiecewiseGaussianWidget';
import vtkImageCroppingWidget     from '@kitware/vtk.js/Widgets/Widgets3D/ImageCroppingWidget';
import vtkImageCropFilter         from '@kitware/vtk.js/Filters/General/ImageCropFilter';


export default {
  name: 'VTKVolumeComponent',
  components : {
    FileSelectorComponent
  },
  setup() {
    const vtkContainer = ref(null);
    const vtkControlsContainer = ref(null);
    const context = ref(null);
    // const coneResolution = ref(6);
    // const representation = ref(2);

    // function setConeResolution(res) {
    //   coneResolution.value = Number(res);
    // }

    // function setRepresentation(rep) {
    //   representation.value = Number(rep);
    // }

    watchEffect(() => {
    //   const res = unref(coneResolution);
    //   const rep = unref(representation);
      if (context.value) {
        const { cropFilter, croppingWidget } = context.value;
        const cropState = croppingWidget.getWidgetState().getCroppingPlanes();
        cropState.onModified(() => {
          cropFilter.setCroppingPlanes(cropState.getPlanes());
        });
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

        const size = 64 * 64 * 64;

        const values = [];
        for (var i = 0; i < size; i++) {
            values[i] = Math.random();
        }

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
          // background: [255,255,255]
          background: [0,0,0]
        });

        const renderer = fullScreenRenderer.getRenderer();
        const renderWindow = fullScreenRenderer.getRenderWindow();
        // const apiRenderWindow = fullScreenRenderer.getApiSpecificRenderWindow();

        const mapper = vtkVolumeMapper.newInstance();
        const actor = vtkVolumeActor.newInstance();

        // colour transfer function
        const ctfun = vtkColorTransferFunction.newInstance();
        ctfun.setMappingRange(0,1);
        ctfun.updateRange();
        ctfun.setNanColor(0.0, 0.0, 0.0, 0.0);
        // set colours
        ctfun.addRGBPoint(0.0, 0.75, 0.35, 1.0);
        ctfun.addRGBPoint(1.0, 1.0, 0.0, 1.0);

        // widgets
        // widget manager
        const widgetManager = vtkWidgetManager.newInstance();
        widgetManager.setRenderer(renderer);

        // cropping widget
        const croppingWidget = vtkImageCroppingWidget.newInstance();

        // initial widget registration
        widgetManager.addWidget(croppingWidget);

        // piecewise widget
        const colourWidget = vtkPiecewiseGaussianWidget.newInstance({
          numberOfBins: 256,
          size: [400, 150],
        });
        colourWidget.updateStyle({
          backgroundColor: 'rgba(255, 255, 255, 0.6)',
          histogramColor: 'rgba(100, 100, 100, 0.5)',
          strokeColor: 'rgb(0, 0, 0)',
          activeColor: 'rgb(255, 255, 255)',
          handleColor: 'rgb(50, 150, 50)',
          buttonDisableFillColor: 'rgba(255, 255, 255, 0.5)',
          buttonDisableStrokeColor: 'rgba(0, 0, 0, 0.5)',
          buttonStrokeColor: 'rgba(0, 0, 0, 1)',
          buttonFillColor: 'rgba(255, 255, 255, 1)',
          strokeWidth: 2,
          activeStrokeWidth: 3,
          buttonStrokeWidth: 1.5,
          handleWidth: 3,
          iconSize: 20, // Can be 0 if you want to remove buttons (dblClick for (+) / rightClick for (-))
          padding: 10,
        });

        // peicewise function
        const ofun = vtkPiecewiseFunction.newInstance();
        ofun.addPoint(0.0, 0.0);
        ofun.addPoint(255.0, 1.0);

        // pipeline
        // mapper.setInputData(source);
        mapper.setSampleDistance(10);

        actor.setMapper(mapper);

        // volume properties
        actor.getProperty().setRGBTransferFunction(0, ctfun);
        // actor.getProperty().setScalarOpacity(0, ofun);
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

        // widget
        // set data, opacity, ctfun

        colourWidget.setDataArray(source);
        colourWidget.applyOpacity(ofun);

        colourWidget.setColorTransferFunction(ctfun);

        // widget
        // widget.addGaussian(0.425, 0.5, 0.2, 0.3, 0.2);
        colourWidget.addGaussian(0.75, 1, 0.3, 0, 0);

        colourWidget.setContainer(vtkControlsContainer.value);
        colourWidget.bindMouseListeners();
        // widgetManager.addWidget(colourWidget)

        // update crop widget
        const cropFilter = vtkImageCropFilter.newInstance();
        cropFilter.setInputData(source);
        mapper.setInputConnection(cropFilter.getOutputPort());

        croppingWidget.copyImageDataDescription(source);
        croppingWidget.setHandleVisibility(false);

        renderer.addVolume(actor);
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
          ofun,
          colourWidget,
          croppingWidget,
          cropFilter
          // widgetManager
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
  top: 25px;
  left: 25px;
  z-index: 1;
}
</style>