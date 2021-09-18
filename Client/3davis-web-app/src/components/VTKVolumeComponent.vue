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

import vtkColorMaps               from '@kitware/vtk.js/Rendering/Core/ColorTransferFunction/ColorMaps';

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
    },
    resetPlanes: {
      type: Boolean,
      default: false
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
      emit("points", cropPlanes) // x1 x2 y1 y2 z1 z2
    }

    watchEffect(() => {
      if (context.value) {

        const { cropFilter, croppingWidget, camera, ctfun, ofun, actor, renderWindow} = context.value;

        // reactive source data
        if(props.sourceData) {
          // rerender with new source data
          renderWindow.render();
        }
        
        const cropState = croppingWidget.getWidgetState().getCroppingPlanes();
        // when cube is cropped
        cropState.onModified(() => {
          cropFilter.setCroppingPlanes(cropState.getPlanes());
          cropPlanes = cropState.getPlanes();
          getCropPoints()
        });

        // reset cropping planes
        if(props.resetPlanes)
        {
          console.log("Reset cropping planes")
          cropFilter.setCroppingPlanes(props.dimensions);
        }

        // when camera changes
        camera.onModified(() => {
          // get camera state
          // cameraState.ctfun = ctfun
          // cameraState.ofun = ofun
          cameraState.camera_pos = camera.getPosition()
          cameraState.camera_view_up = camera.getViewUp()
          cameraState.window_size = []
          cameraState.window_size[0] = vtkContainer.value.clientHeight
          cameraState.window_size[1] = vtkContainer.value.clientWidth
          emit("camera", cameraState)
        });
        // when ct function changes
        ctfun.onModified(() => {
          let ctObject = {}
          // console.log(actor.getProperty().getRGBTransferFunction(0).getSize());
          // get range of data
          // const range = actor.getProperty().getScalarOpacity(0).getRange())
          // get colour map
          // ctObject.spacing = Number(vtkControlsContainer.value.querySelector('.js-spacing').value);
          const nodes = actor.getProperty().getScalarOpacity(0).get().nodes
          ctObject.nodes = []
          for (let i = 0; i < nodes.length; i++) {
            ctObject.nodes.push(nodes[i].x)
            ctObject.nodes.push(nodes[i].y)
          }
          var colourMap = vtkColorMaps.getPresetByName(
            vtkControlsContainer.value.querySelector('.js-color-preset').value
          );
          ctObject.colourMap = colourMap.RGBPoints
          emit("ctfun", ctObject)
        })

        ofun.onModified(() => {
          let ctObject = {}
          // get peicewise function
          // console.log(actor.getProperty().getGrayTransferFunction());
          // console.log(actor.getProperty().getInterpolationTypeAsString());
          // get nodes of ofun
          // ctObject.spacing = Number(vtkControlsContainer.value.querySelector('.js-spacing').value);
          const nodes = actor.getProperty().getScalarOpacity(0).get().nodes
          ctObject.nodes = []
          for (let i = 0; i < nodes.length; i++) {
            ctObject.nodes.push(nodes[i].x)
            ctObject.nodes.push(nodes[i].y)
          }
          
          // const edge = Number(vtkControlsContainer.value.querySelector('.js-edge').value);
          var colourMap = vtkColorMaps.getPresetByName(
            vtkControlsContainer.value.querySelector('.js-color-preset').value
          );
          ctObject.colourMap = colourMap.RGBPoints
          emit("ctfun", ctObject)
        })
        
      }
    });

    onBeforeMount(() => {
        
    })

    onMounted(() => {
      if (!context.value) {

        // generate data cube
        const VtkDataTypes = vtkDataArray.VtkDataTypes;
 
        // get data from props
        // console.log(props.sourceData)
        const values = props.sourceData

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

        // pipeline
        // mapper.setInputData(source);
        mapper.setSampleDistance(10);

        actor.setMapper(mapper);

        // volume properties
        actor.getProperty().setRGBTransferFunction(0, ctfun);
        actor.getProperty().setScalarOpacity(0, ofun);
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
        };

        // emit intial camera state
        cameraState.position = camera.getPosition()
        cameraState.viewUp = camera.getViewUp()
        cameraState.window_size = []
        cameraState.window_size[0] = vtkContainer.value.clientHeight
        cameraState.window_size[1] = vtkContainer.value.clientWidth
        emit("camera", cameraState)

        // emit initial colour transfer function
        let ctObject = {}
        const nodes = actor.getProperty().getScalarOpacity(0).get().nodes
        ctObject.nodes = []
        for (let i = 0; i < nodes.length; i++) {
          ctObject.nodes.push(nodes[i].x)
          ctObject.nodes.push(nodes[i].y)
        }
        var colourMap = vtkColorMaps.getPresetByName(
          vtkControlsContainer.value.querySelector('.js-color-preset').value
        );
        ctObject.colourMap = colourMap.RGBPoints
        emit("ctfun", ctObject)
        console.log(ctObject)
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