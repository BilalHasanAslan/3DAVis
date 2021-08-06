<template>
  <div 
    id="app"
    class=""
  >
    <nav-bar-component/>
    <promise-component/>
    <VTKStandaloneComponent/>
    
  </div>
</template>

<script>
import NavBarComponent from './components/NavBarComponent.vue'
import PromiseComponent from './components/PromiseComponent.vue'
import VTKStandaloneComponent from './components/VTKStandaloneVolumeComponent.vue'

export default {
  name: 'App',
  components: {
    NavBarComponent,
    PromiseComponent,
    VTKStandaloneComponent
  }
}
</script>

<style lang="scss">
@import "~@/assets/scss/vendors/bootstrap-vue/index";

#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}
</style>
