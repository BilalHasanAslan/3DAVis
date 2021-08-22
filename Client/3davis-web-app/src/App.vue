<template>
  <!-- <img alt="Vue logo" src="./assets/logo.png"> -->
  <!-- <HelloWorld/> -->
  <control-panel-component
    v-if="connection"
  />
  <VTKVolumeComponent/>
</template>

<script>
import ControlPanelComponent from './components/ControlPanelComponent.vue'
import VTKVolumeComponent from './components/VTKVolumeComponent.vue'

export default {
  name: 'App',
  components: {
    // HelloWorld
    VTKVolumeComponent,
    ControlPanelComponent
  },
  data() {
    return {
      connection: null,
    }
  },
  created(){
    // connect to server
    console.log("connect to server")
    this.connection = new WebSocket("ws://localhost:9000")

    // echos everything form theb server
    this.connection.onmessage = function(event) {
      console.log(event)
    }

    this.connection.onopen = function(event) {
      console.log(event)
      console.log("successfully connected to server")
    }
  },
  methods: {
    close
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
