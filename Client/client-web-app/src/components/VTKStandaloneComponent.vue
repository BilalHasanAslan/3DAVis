<template>
  <div>
    <table class="controls">
      <tbody>
        <tr>
          <td>
            <select
                v-model.number="representation"
            >
              <option value="0">Points</option>
              <option value="1">Wireframe</option>
              <option value="2">Surface</option>
            </select>
          </td>
        </tr>
        <tr>
          <td>
            <input
              type="range"
              min="4"
              max="80"
              v-model.number="coneResolution"
            />
          </td>
        </tr>
      </tbody>
    </table>
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

import '@kitware/vtk.js/Rendering/Profiles/Geometry';

import vtkGenericRenderWindow from '@kitware/vtk.js/Rendering/Misc/GenericRenderWindow';
import vtkSource from 'vtk.js/Sources/Filters/Sources/ConeSource';
import vtkActor from 'vtk.js/Sources/Rendering/Core/Actor';
import vtkMapper from 'vtk.js/Sources/Rendering/Core/Mapper';

export default {
  name: 'VTKComponent',
  data() {
    return {
      coneResolution: 6,
      representation: 2,
      container: null,
      context: null
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
      const { genericRenderer, source, actor, mapper } = this.context;
      actor.delete();
      mapper.delete();
      source.delete();
      genericRenderer.delete();
      this.context = null;
    }
  },
  mounted() {
    if (!this.context) {

        this.container = document.querySelector('#window');

        // WebGL/OpenGL impl
        const genericRenderWindow = vtkGenericRenderWindow.newInstance();
        genericRenderWindow.setContainer(this.container);
        // renderWindow.addView(genericRenderWindow);

        // VTK renderWindow/renderer
        const renderWindow = genericRenderWindow.getRenderWindow();
        const renderer     = genericRenderWindow.getRenderer();
        // renderWindow.addRenderer(renderer);

        // Pipeline
        const source   = vtkSource.newInstance();
        const actor  = vtkActor.newInstance();
        const mapper = vtkMapper.newInstance();

        actor.setMapper(mapper);
        mapper.setInputConnection(source.getOutputPort());
        renderer.addActor(actor);

        // Render
        renderer.resetCamera();
        renderWindow.render(); 

        this.context = {
            genericRenderWindow,
            renderWindow,
            renderer,
            source,
            actor,
            mapper
        };
    }
  }
}
</script>

<style scoped>

</style>