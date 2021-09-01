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
import '@kitware/vtk.js/Rendering/Profiles/Glyph';

import vtkFullScreenRenderWindow  from '@kitware/vtk.js/Rendering/Misc/FullScreenRenderWindow';

import vtkVolumeActor             from '@kitware/vtk.js/Rendering/Core/Volume';
import vtkVolumeMapper            from '@kitware/vtk.js/Rendering/Core/VolumeMapper';

import vtkImageData               from '@kitware/vtk.js/Common/DataModel/ImageData';
import vtkDataArray               from '@kitware/vtk.js/Common/Core/DataArray';

import vtkColorTransferFunction   from '@kitware/vtk.js/Rendering/Core/ColorTransferFunction';
import vtkPiecewiseFunction       from '@kitware/vtk.js/Common/DataModel/PiecewiseFunction';

import vtkWidgetManager           from '@kitware/vtk.js/Widgets/Core/WidgetManager';
import vtkImageCroppingWidget     from '@kitware/vtk.js/Widgets/Widgets3D/ImageCroppingWidget';
import vtkImageCropFilter         from '@kitware/vtk.js/Filters/General/ImageCropFilter';
import vtkVolumeController        from '@kitware/vtk.js/Interaction/UI/VolumeController';


export default {
  name: 'VTKVolumeComponent',
  components : {
    // FileSelectorComponent
  },
  props: {
    sourceData: {
      type: Array,
      default: () => []
    },
    dimensions: {
      type: Array,
      default: () => []
    },
    spacing: {
      type: Number,
      default: 1
    }
  },
  setup(props,{emit}) {
    const vtkContainer = ref(null);
    const vtkControlsContainer = ref(null);
    const context = ref(null);

    var cropPlanes = null
    var cropPoints = []
    var cameraState = {}

    // get crop points
    function getCropPoints() {
      // cropPoints[0] = [cropPlanes[0],cropPlanes[2],cropPlanes[4]] //x1y1z1
      // cropPoints[1] = [cropPlanes[1],cropPlanes[2],cropPlanes[4]] //x2y1z1
      // cropPoints[2] = [cropPlanes[0],cropPlanes[3],cropPlanes[4]] //x1y2z1
      // cropPoints[3] = [cropPlanes[0],cropPlanes[2],cropPlanes[4]] //x2y2z1
      // cropPoints[4] = [cropPlanes[0],cropPlanes[2],cropPlanes[5]] //x1y1z2
      // cropPoints[5] = [cropPlanes[1],cropPlanes[2],cropPlanes[5]] //x2y1z2
      // cropPoints[6] = [cropPlanes[0],cropPlanes[3],cropPlanes[5]] //x1y2z2
      // cropPoints[7] = [cropPlanes[1],cropPlanes[3],cropPlanes[5]] //x2y2z2
      emit("points", cropPlanes) // x1 x2 y1 y2 z1 z2
    }

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
        const { cropFilter, croppingWidget, camera, ctfun, ofun } = context.value;
        const cropState = croppingWidget.getWidgetState().getCroppingPlanes();
        // when cube is cropped
        cropState.onModified(() => {
          cropFilter.setCroppingPlanes(cropState.getPlanes());
          cropPlanes = cropState.getPlanes();
          getCropPoints()
        });
        // when camera changes
        camera.onModified(() => {
          // get camera state
          cameraState.ctfun = ctfun
          cameraState.ofun = ofun
          cameraState.position = camera.getPosition()
          cameraState.viewUp = camera.getViewUp()
          cameraState.window_size = []
          cameraState.window_size[0] = vtkContainer.value.clientHeight
          cameraState.window_size[1] = vtkContainer.value.clientWidth
          emit("camera", cameraState)
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

        const size = props.dimensions[0]*props.dimensions[1]*props.dimensions[2]

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
        source.setDimensions(props.dimensions[0], props.dimensions[1], props.dimensions[2]);
        source.setSpacing(1,1,1);
        source.setOrigin(-(props.dimensions[0]/2),-(props.dimensions[1]/2),-(props.dimensions[2]/2));
        source.getPointData().setScalars(scalars);

        const fullScreenRenderer = vtkFullScreenRenderWindow.newInstance({
          container: vtkContainer.value,
          // background: [255,255,255]
          background: [0,0,0]
        });

        const renderer = fullScreenRenderer.getRenderer();
        const renderWindow = fullScreenRenderer.getRenderWindow();
        // const apiRenderWindow = fullScreenRenderer.getApiSpecificRenderWindow();

        // camera
        const camera = renderer.getActiveCamera();
        
        const mapper = vtkVolumeMapper.newInstance();
        const actor = vtkVolumeActor.newInstance();

        // colour transfer function
        const ctfun = vtkColorTransferFunction.newInstance();
        ctfun.addRGBPoint(200.0, 1.0, 1.0, 1.0);
        ctfun.addRGBPoint(2000.0, 0.0, 0.0, 0.0);

        // widgets
        // widget manager
        const widgetManager = vtkWidgetManager.newInstance();
        widgetManager.setRenderer(renderer);

        // cropping widget
        const croppingWidget = vtkImageCroppingWidget.newInstance();

        // initial widget registration
        widgetManager.addWidget(croppingWidget);
        // widgetManager.addWidget(controllerWidget);

        // peicewise function
        const ofun = vtkPiecewiseFunction.newInstance();
        ofun.addPoint(200.0, 0.0);
        ofun.addPoint(1200.0, 0.2);
        ofun.addPoint(4000.0, 0.4);

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

        // controls widget
        const controllerWidget = vtkVolumeController.newInstance({
          size: [400, 150],
          rescaleColorMap: true,
        });
        controllerWidget.setContainer(vtkControlsContainer.value);
        controllerWidget.setupContent(renderWindow, actor, true);

        context.value = {
          fullScreenRenderer,
          renderWindow,
          renderer,
          source,
          actor,
          mapper,
          ctfun,
          ofun,
          croppingWidget,
          cropFilter,
          camera
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
      context,
      cropPoints
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
  right: 425px;
  z-index: 1;
}
</style>