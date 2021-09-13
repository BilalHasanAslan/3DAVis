<template>
  <div
    v-on:click="userInteraction()"
    v-on:click.right="userInteraction()"
  >
    <div
      id="controls"
    >
    </div>
    <div 
      ref="vtkContainer"
      id="window"
      style="height: 90vh;"
      class="w-100 m-auto"
      v-on:click="updateFocalPoint()"
      v-on:click.right="updateFocalPoint()"
    >
    </div>
  </div>
</template>

<script>


import { vec3, quat, mat4 } from 'gl-matrix';

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
import vtkImageCroppingWidget from 'vtk.js/Sources/Widgets/Widgets3D/ImageCroppingWidget';
import vtkPlane from 'vtk.js/Sources/Common/DataModel/Plane';

export default {
  name: 'VTKVolumeComponent',
  data() {
    return {
      container: null,
      controls: null,
      cropState: null,
      context: null,
      source: null,
      background: [0,0,0],
      cameraPosition: [0,0,200],
      level: 1,
      focalPoint: null,
      cameraClippingRange: null,
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

    var width = 64, height = 64, depth = 64;
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
    this.source.setDimensions(64, 64, 64);
    this.source.setSpacing(1,1,1);
    this.source.setOrigin(-32,-32,-32);
    this.source.getPointData().setScalars(scalars);
  },
  mounted() {
    if (!this.context || this.source != null) {

      this.container = document.querySelector('#window');
      this.controls = document.querySelector('#controls');

      // WebGL/OpenGL implementation
      const genericRenderWindow = vtkGenericRenderWindow.newInstance();
      genericRenderWindow.setContainer(this.container);
      genericRenderWindow.setBackground(this.background);

      // VTK renderWindow/renderer
      const renderWindow = genericRenderWindow.getRenderWindow();
      const renderer     = genericRenderWindow.getRenderer();

      // image cropping widget
      const widget = vtkImageCroppingWidget.newInstance();

      // interactor
      const interactorStyle = vtkInteractorStyleManipulator.newInstance();
      genericRenderWindow.getInteractor().setInteractorStyle(interactorStyle);

      //  remove default mainpulators
      // interactorStyle.removeAllMouseManipulators();

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
      camera.setPosition(0,0,200);
      
      // camera.setPosition(this.cameraPosition);
      // camera.setFocalPoint(this.focalPoint);

      renderer.setActiveCamera(camera);

      // Pipeline
      const actor  = vtkVolumeActor.newInstance();
      const mapper = vtkVolumeMapper.newInstance();

      actor.setMapper(mapper);
      mapper.setInputData(this.source);
      mapper.setSampleDistance(2);

      // update crop widget
      widget.copyImageDataDescription(this.source);
      this.cropState = widget.getWidgetState().getCroppingPlanes();

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
        interactorStyle,
        ctfun,
        ofun,
        widget
      };

    }
  },
  beforeDestroy() {
    if (this.context.value) {
      const { genericRenderer, actor, mapper } = this.context;
      actor.delete();
      mapper.delete();
      genericRenderer.delete();
      this.context = null;
    }
  },
  methods: {
    getCroppingPlanes(imageData, ijkPlanes) {
      console.log("here")
      const rotation = quat.create();
      mat4.getRotation(rotation, imageData.getIndexToWorld());

      const rotateVec = (vec) => {
        const out = [0, 0, 0];
        vec3.transformQuat(out, vec, rotation);
        return out;
      }
      const [iMin, iMax, jMin, jMax, kMin, kMax] = ijkPlanes;
      const origin = imageData.indexToWorld([iMin, jMin, kMin]);
      // opposite corner from origin
      const corner = imageData.indexToWorld([iMax, jMax, kMax]);
      return [
        // X min/max
        vtkPlane.newInstance({ normal: rotateVec([1, 0, 0]), origin }),
        vtkPlane.newInstance({ normal: rotateVec([-1, 0, 0]), origin: corner }),
        // Y min/max
        vtkPlane.newInstance({ normal: rotateVec([0, 1, 0]), origin }),
        vtkPlane.newInstance({ normal: rotateVec([0, -1, 0]), origin: corner }),
        // X min/max
        vtkPlane.newInstance({ normal: rotateVec([0, 0, 1]), origin }),
        vtkPlane.newInstance({ normal: rotateVec([0, 0, -1]), origin: corner }),
      ]
    },
    getCubelets() {
      let cubes = []
      Object.keys(this.frustum).forEach(key => {
        if(this.frustum[key][0] > 0) // positive x
        {
          if(this.frustum[key][1] > 0) // positive y
          {
            if(this.frustum[key][2] > 0) // positive z
            {
              cubes.push(1) // +x +y +z
            }
            else // negative z
            {
              cubes.push(5) // +x +y +z
            }
          }
          else // negative y
          {
            if(this.frustum[key][2] > 0) // positive z
            {
              cubes.push(3) // +x -y +z
            }
            else // negative z
            {
              cubes.push(7) // +x -y -z
            }
          }
        }
        else // negative x
        {
          if(this.frustum[key][1] > 0) // positive y
          {
            if(this.frustum[key][2] > 0) // positive z
            {
              cubes.push(2) // -x +y +z
            }
            else // negative z
            {
              cubes.push(6) // -x +y -z
            }
          }
          else // negative y
          {
            if(this.frustum[key][2] > 0) // positive z
            {
              cubes.push(4) // -x -y +z
            }
            else // negative z
            {
              cubes.push(8) // -x -y -z
            }
          }
        }
      })
      console.log(cubes)
    },
    getFrustum() {
      const { genericRenderWindow } = this.context;
      const renderer = genericRenderWindow.getRenderer();
      const camera = renderer.getActiveCamera();

      let clippingRange = camera.getClippingRange()
      let ratio = this.$refs.vtkContainer.clientWidth / this.$refs.vtkContainer.clientHeight
      let up = camera.getViewUp()

      let hNear = 2 * Math.tan(camera.getViewAngle()/2) * clippingRange[0]
      let wNear = hNear * ratio

      let hFar = 2 * Math.tan(camera.getViewAngle()/2) * clippingRange[1]
      let wFar = hFar * ratio

      // p - position
      let pos = camera.getPosition()

      // d - direction vector - < focal point - position >
      let focalPoint = camera.getFocalPoint()
      let forward = [focalPoint[0]-pos[0],focalPoint[1]-pos[1],focalPoint[2]-pos[2]]
      
      // right - cross product (forward.normalised, up.normalised)
      let right = this.cross(forward, up)
      
      // far centre
      let fd = [forward[0]*clippingRange[1],forward[1]*clippingRange[1],forward[2]*clippingRange[1]]
      let fc = this.add(pos,fd)

      // half hFar
      let halfH = hFar/2

      // half wFar
      let halfW = wFar/2

      console.log("Frustum")
      // far top left
      this.frustum.ftl = this.add(fc, this.subtract([up[0]*halfH, up[1]*halfH, up[2]*halfH], [right[0]*halfW, right[1]*halfW,right[2]*halfW]))
      // far top right
      this.frustum.ftr = this.add(fc, this.add([up[0]*halfH, up[1]*halfH, up[2]*halfH], [right[0]*halfW, right[1]*halfW,right[2]*halfW]))
      // far bottom left
      this.frustum.fbl = this.subtract(fc, this.subtract([up[0]*halfH, up[1]*halfH, up[2]*halfH], [right[0]*halfW, right[1]*halfW,right[2]*halfW]))
      // far bottom right
      this.frustum.fbr = this.subtract(fc, this.add([up[0]*halfH, up[1]*halfH, up[2]*halfH], [right[0]*halfW, right[1]*halfW,right[2]*halfW]))

      // near centre
      let nd = [forward[0]*clippingRange[0],forward[1]*clippingRange[0],forward[2]*clippingRange[0]]
      let nc = this.add(pos, nd)

      // half hFar
      let halfNH = hNear/2

      // half wFar
      let halfNW = wNear/2

      // near top left
      this.frustum.ntl = this.add(nc, this.subtract([up[0]*halfNH,up[1]*halfNH,up[0]*halfNH], [right[0]*halfNW,right[1]*halfNW,right[2]*halfNW]))
      // near top right
      this.frustum.ntr = this.add(nc, this.add([up[0]*halfNH,up[1]*halfNH,up[0]*halfNH], [right[0]*halfNW,right[1]*halfNW,right[2]*halfNW]))
      // near bottom left
      this.frustum.nbl = this.subtract(nc, this.subtract([up[0]*halfNH,up[1]*halfNH,up[0]*halfNH], [right[0]*halfNW,right[1]*halfNW,right[2]*halfNW]))
      // near botton right
      this.frustum.nbr = this.subtract(nc, this.add([up[0]*halfNH,up[1]*halfNH,up[0]*halfNH], [right[0]*halfNW,right[1]*halfNW,right[2]*halfNW]))


      console.log(this.frustum.ftl + " " + this.frustum.ftr + " " + this.frustum.fbl + " " + this.frustum.fbr)
      console.log(this.frustum.ntl + " " + this.frustum.ntr + " " + this.frustum.nbl + " " + this.frustum.nbr)
    },
    userInteraction() {
      let parameters = {}
      this.$emit('interaction:change', parameters)
    },
    updateFocalPoint() {
      const { genericRenderWindow, interactorStyle } = this.context;
      // const renderWindow = genericRenderWindow.getRenderWindow();
      const renderer = genericRenderWindow.getRenderer();
      // renderer.resetCameraClippingRange();
      const camera = renderer.getActiveCamera();
      // console.log("Clipping Range")
      // console.log(camera.getClippingRange())
      // console.log("Position")
      // console.log(camera.getPosition())
      // console.log("Focal Point")
      // console.log(camera.getFocalPoint())
      interactorStyle.setCenterOfRotation(camera.getFocalPoint())
      this.focalPoint = camera.getFocalPoint()
      // renderWindow.render(); 
    },
    normalize(arr) {
      let x = arr[0]
      let y = arr[1]
      let z = arr[2]
      let len = x * x + y * y + z * z
      if (len > 0) {
        len = 1 / Math.sqrt(len)
      }
      let out = [0,0,0]
      out[0] = arr[0] * len
      out[1] = arr[1] * len
      out[2] = arr[2] * len
      return out
    },
    cross(arr1, arr2) {
      let out = [0,0,0]
      out[0] = (arr1[1]*arr2[2]) - (arr1[2]*arr2[1])
      out[1] = (arr1[2]*arr2[0]) - (arr1[0]*arr2[2])
      out[2] = (arr1[0]*arr2[1]) - (arr1[1]*arr2[0])
      return out
    },
    add(arr1, arr2) {
      let out = [0,0,0]
      out[0] = arr1[0] + arr2[0]
      out[1] = arr1[1] + arr2[1]
      out[2] = arr1[2] + arr2[2]
      return out
    },
    subtract(arr1,arr2) {
      let out = [0,0,0]
      out[0] = arr1[0] - arr2[0]
      out[1] = arr1[1] - arr2[1]
      out[2] = arr1[2] - arr2[2]
      return out
    }
  },
  watch: {
    cropState: function() {
      const { mapper } = this.context
      const planes = this.getCroppingPlanes(this.source, this.cropState.getPlanes());
      console.log("here")
      mapper.removeAllClippingPlanes();
      planes.forEach((plane) => {
        mapper.addClippingPlane(plane);
      });
      mapper.modified();
    }
  }
}
</script>

<style scoped>
  #controls {
    position: relative;
  }
</style>