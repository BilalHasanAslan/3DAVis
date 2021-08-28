<template>
  <!-- <img alt="Vue logo" src="./assets/logo.png"> -->
  <!-- <HelloWorld/> -->
  <control-panel-component
    v-if="connected"
    :fileList="files"
    @selected="fileSelected"
    @crop="cropCube"
    @back="stepBack"
    @reset="resetCube"
  />
  <VTKVolumeComponent
    v-if="loading"
    @points="setCropPoints"
    @camera="setCameraState"
    @mouseup="timerCountdown=5"
  />
  <VTKImageComponent
    v-else
  />
</template>

<script>
import ControlPanelComponent from './components/ControlPanelComponent.vue'
import VTKVolumeComponent from './components/VTKVolumeComponent.vue'
import VTKImageComponent from './components/VTKImageComponent.vue'

export default {
  name: 'App',
  components: {
    // HelloWorld
    VTKVolumeComponent,
    ControlPanelComponent,
    VTKImageComponent
  },
  data() {
    return {
      files: null,
      connection: null,
      connected: true,
      interaction: false,
      loading: true,
      cropLevel: 1,
      cropPoints: null,
      previousPoints: null,
      cameraState: null,
      timerCountdown: 5
    }
  },
  created(){
    // connect to server
    console.log("connect to server")
    this.connection = new WebSocket("ws://192.168.101.242:9000/")

    // what to do with the data from the server
    this.connection.onmessage = function(event) {
      console.log("data received")
      console.log(event)
    }

    this.connection.onopen = function(event) {
      console.log(event)
      console.log("successfully connected to server")
    }
  },
  watch: {
    timerCountdown: {
      handler(value) {
        if(value > 0) {
          this.interaction = true
          this.timerCountdown = value
          setTimeout(() => {
            console.log(this.timerCountdown)
            this.timerCountdown--
          }, 1000)
        }
        else {
          // this.interaction = false
          console.log("interaction countdown finished")
          console.log("loading image")
          // request image
          // this.connection.send(this.cameraState)
        }
      },
      immediate: true
    }
  },
  methods: {
    fileSelected(event) {
      console.log(event)
    },
    setCropPoints(event) {
      this.cropPoints = event
    },
    cropCube() {
      console.log("crop cube")
      this.cropLevel++

      // save previous point
      this.previousPoints = this.cropPoints

      // request next cube
      const request = {
        cube: this.cropPoints,
        level: this.cropLevel,
      }

      this.connection.send(request)
    },
    stepBack() {
      console.log("step back")
      if(this.cropLevel > 1)
        this.cropLevel--

      // request cube from previous points
      const request = {
        cube: this.cropPoints,
        level: this.cropLevel,
      }

      this.connection.send(request)
    },
    resetCube() {
      console.log("reset cube")

      // ask for initial data

      this.cropLevel = 1
    },
    setCameraState(event) {
      this.cameraState = event

    },
    // combining promises and websockets 
    // connect() {
    //   return new Promise(function(resolve, reject) {
    //     var server = new WebSocket('ws://echo.websocket.org')
    //     server.onopen = function() {
    //       resolve(server)
    //     }
    //     server.onerror = function(err) {
    //       reject(err)
    //     }
    //   })
    // },
    // async promiseMethod() {
    //   try{
    //     // let server = await connect()
    //     // use server
    //   }
    //   catch (error) {
    //     console.log('oops ', error)
    //   }
    // }
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
