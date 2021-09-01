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
    :dimensions="[64,64,64]"
    :spacing="1"
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
      timerCountdown: 5,
      clientCubeDimensions: [],
      serverCubeDimensions: []
    }
  },
  created(){
    // connect to server
    console.log("connect to server")
    this.connection = new WebSocket("ws://localhost:9000/")

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

      let points = []

      // convert points to world coordianates
      const factorX = this.serverCubeDimensions[0] / this.clientCubeDimensions[0]
      points[0] = this.cropPoints[0]*factorX
      points[1] = this.cropPoints[1]*factorX
      const factorY = this.serverCubeDimensions[1] / this.clientCubeDimensions[1]
      points[2] = this.cropPoints[3]*factorY
      points[3] = this.cropPoints[3]*factorY
      const factorZ = this.serverCubeDimensions[2] / this.clientCubeDimensions[2]
      points[4] = this.cropPoints[4]*factorZ
      points[5] = this.cropPoints[5]*factorZ

      // save previous point
      this.previousPoints = points

      // request next cube
      const request = {
        cube: points,
        // level: this.cropLevel,
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
        // level: this.cropLevel,
      }

      this.connection.send(request)
    },
    resetCube() {
      console.log("reset cube")

      // ask for initial data

      // this.cropLevel = 1
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
