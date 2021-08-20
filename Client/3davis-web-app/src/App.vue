<template>
  <!-- <img alt="Vue logo" src="./assets/logo.png"> -->
  <!-- <HelloWorld/> -->
  <VTKVolumeComponent/>
</template>

<script>
import VTKVolumeComponent from './components/VTKVolumeComponent.vue'

export default {
  name: 'App',
  components: {
    // HelloWorld
    VTKVolumeComponent
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
}
</style>
