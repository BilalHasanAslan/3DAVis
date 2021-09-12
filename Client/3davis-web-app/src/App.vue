<template>
  <!-- <img alt="Vue logo" src="./assets/logo.png"> -->
  <!-- <HelloWorld/> -->
  <control-panel-component
    v-if="connected"
    :fileList="files"
    @selected="fileSelected"
    @crop="cropCube"
    @reset="resetCube"
    
  />
  <VTKVolumeComponent
    v-if="!loading || interaction"
    @points="setCropPoints"
    @camera="setCameraState"
    @mouseup="timerCountdown=5"
    @ctfun="setColourFunction"
    :sourceData="source"
    :dimensions="[64,64,64]"
    :spacing="1"
  />
  <ImageComponent
    v-else
  />
</template>

<script>
import ControlPanelComponent from './components/ControlPanelComponent.vue'
import VTKVolumeComponent from './components/VTKVolumeComponent.vue'
import ImageComponent from './components/ImageComponent.vue'

export default {
  name: 'App',
  components: {
    // HelloWorld
    VTKVolumeComponent,
    ControlPanelComponent,
    ImageComponent
  },
  data() {
    return {
      files: ["file1","file2"],
      source: [],
      connection: null,
      connected: true,
      interaction: false,
      loading: true,
      xyLevel: 0,
      zLevel: 0,
      cropPoints: [0, 1100, 0, 750, 0, 265],
      tiles: [], // keeps track which tiles it needs
      tileBuffer:[], // holds data tiles
      cameraState: {},
      timerCountdown: -1,
      timer: null,
      clientCubeDimensions: [64, 64, 64],
      serverCubeDimensions: [1100, 750, 265]
    }
  },
  created(){
    // dummy source data
    const size = this.clientCubeDimensions[0]*this.clientCubeDimensions[1]*this.clientCubeDimensions[2]

    const values = [];
    for (var i = 0; i < size; i++) {
      values[i] = Math.random();
    }
    this.tileBuffer[0] = values

    // connect to server
    console.log("connect to server")
    this.connection = new WebSocket("ws://192.168.101.242:9000/")
    // get server to send files when it connects to the client

    // what to do with the data from the server
    this.connection.onmessage = async function(event) {
      if(event.type == "volume") // receive data tile
      {
        console.log(event.type)
        // add to tile buffer

        if(this.tileBuffer.length === this.tiles.length)
          this.source = this.constructCube()
      }
      else if(event.type == "image")
      {
        console.log(event.type)
        // set image component
      }
      else if(event.type == "files")
      {
        console.log(event.type)
      }
    }

    this.connection.onopen = function(event) {
      console.log(event)
      console.log("successfully connected to server")
    }
  },
  watch: {
    timerCountdown: {
      handler(value) {
        if(this.timer)
        {
          clearTimeout(this.timer)
        }
        if(this.timerCountdown>0)
        {
          this.interaction = true
          this.timerCountdown = value
          this.timer = setTimeout(() => {
            console.log(this.timerCountdown)
            this.timerCountdown--
          }, 1000)
        }
        else // sends request when timer runs out
        {
          this.interaction = false
          console.log("interaction countdown finished")
          // console.log("loading image")
          // request image
          this.connection.send(this.cameraState)
        }
      },
      immediate: true
    },
    interaction: {

    }
  },
  methods: {
    fileSelected(event) {
      // request initial data
      this.source = this.constructCube()
      this.loading = false

      const request = {
        file: event
      }
      this.connection.send(request)
      console.log("Requested file: " + event)
    },
    setCropPoints(event) {
      this.cropPoints = event
    },
    cropCube() {
      console.log("crop cube")

      // this.xyLevel = 0
      // this.zLevel = 0

      let points = []
      let singleX,singleY,singleZ

      // convert points to world coordianates
      const factorX = this.serverCubeDimensions[0] / this.clientCubeDimensions[0]
      points[0] = this.cropPoints[0]*factorX
      points[1] = this.cropPoints[1]*factorX
      const rangeX = points[1]-points[0]
      const factorY = this.serverCubeDimensions[1] / this.clientCubeDimensions[1]
      points[2] = this.cropPoints[2]*factorY
      points[3] = this.cropPoints[3]*factorY
      const rangeY = points[3]-points[2]
      const factorZ = this.serverCubeDimensions[2] / this.clientCubeDimensions[2]
      points[4] = this.cropPoints[4]*factorZ
      points[5] = this.cropPoints[5]*factorZ
      const rangeZ = points[5]-points[4]

      // increment level until the single cube 

      do {
        // increment level
        this.xyLevel++
        // get dimensions of a single cube at current level in world space
        singleX = this.serverCubeDimensions[0] / Math.pow(2, this.xyLevel)
        singleY = this.serverCubeDimensions[1] / Math.pow(2, this.xyLevel)
      }
      while(rangeX<singleX && rangeY<singleY)
      this.xyLevel--
      singleX = this.serverCubeDimensions[0] / Math.pow(2, this.xyLevel)
      singleY = this.serverCubeDimensions[1] / Math.pow(2, this.xyLevel)
      
      // singleZ = this.serverCubeDimensions[2] / Math.pow(2, this.zLevel)
      do {
        // increment level
        this.zLevel++
        // get dimensions of a single cube at current level in world space
        singleZ = this.serverCubeDimensions[2] / Math.pow(2, this.zLevel)
      }
      while(rangeZ<singleZ)
      this.zLevel--
      singleZ = this.serverCubeDimensions[2] / Math.pow(2, this.zLevel)
      
      // console.log("XY level: "+this.xyLevel)
      // console.log("Z level: "+this.zLevel)

      // determine which cubes to request for
      const mipmap = "DATA_XY_"+Math.pow(2, this.xyLevel)+"_Z_"+Math.pow(2, this.zLevel);
      
      console.log(mipmap)

      // determine tiles
      // cublet coord
      let cubelet = []
      cubelet[0] = (Math.ceil(points[0]/singleX) == 0) ? 1 : Math.ceil(points[0]/singleX)// or /64
      cubelet[1] = (Math.ceil(points[1]/singleX) == 0) ? 1 : Math.ceil(points[1]/singleX)
      cubelet[2] = (Math.ceil(points[2]/singleY) == 0) ? 1 : Math.ceil(points[2]/singleY)
      cubelet[3] = (Math.ceil(points[3]/singleY) == 0) ? 1 : Math.ceil(points[3]/singleY)
      cubelet[4] = (Math.ceil(points[4]/singleZ) == 0) ? 1 : Math.ceil(points[4]/singleZ)
      cubelet[5] = (Math.ceil(points[5]/singleZ) == 0) ? 1 : Math.ceil(points[5]/singleZ)

      let temp = []
      temp[0] = [cubelet[0],cubelet[2],cubelet[4]]
      temp[1] = [cubelet[1],cubelet[2],cubelet[4]]
      temp[2] = [cubelet[0],cubelet[3],cubelet[4]]
      temp[3] = [cubelet[1],cubelet[3],cubelet[4]]
      temp[4] = [cubelet[0],cubelet[2],cubelet[5]]
      temp[5] = [cubelet[1],cubelet[2],cubelet[5]]
      temp[6] = [cubelet[0],cubelet[3],cubelet[5]]
      temp[7] = [cubelet[1],cubelet[3],cubelet[5]]

      this.tiles = []

      for (let i = 0; i < temp.length; i++) {
        let tempVal = temp[i][0] // x
        
        if(temp[i][1]>1) // y
        {
          tempVal += Math.pow(2, this.xyLevel)
        }
        
        if(temp[i][2]>1) // z
        {
          tempVal += Math.pow(Math.pow(2, this.zLevel), 2)
        }
        this.tiles.push(tempVal)
      }
      
      // remove duplicates
      this.tiles = this.tiles.filter((value, index) => this.tiles.indexOf(value) === index)

      console.log(this.tiles.splice(0,4))

      // request next set of tiles
      const request = {
        cropPoints: points,
        mipmap: mipmap, 
        tiles: this.tiles.splice(0,4)
      }

      this.connection.send(request)
    },
    stepBack() {
      console.log("step back")
      if(this.cropLevel > 1)
        this.cropLevel--

      // request cube from previous points
      const request = {
        cropPoints: this.cropPoints,
        // level: this.cropLevel,
        tiles: null
      }

      this.connection.send(request)
    },
    resetCube() {
      console.log("reset cube")

      // ask for initial data

      this.xyLevel = 0
      this.zLevel = 0

      const mipmap = "DATA_XY_"+Math.pow(2, this.xyLevel)+"_Z_"+Math.pow(2, this.zLevel);
      const request = {
        cropPoints: [0,this.serverCubeDimensions[0],0,this.serverCubeDimensions[1],0,this.serverCubeDimensions[2]],
        mipmap: mipmap, 
        tiles: [1]
      }
      this.connection.send(request)
    },
    setCameraState(event) {
      this.cameraState = event
    },
    setColourFunction(event) {
      // console.log(event)
      // update colour transfer function to the server
      this.cameraState.ctfun = event
    },
    constructCube() {
      const cubes = []
      const cube1 = []
      const cube2 = []
      const cube3 = []
      const cube4 = []
      var dimensions = [4,4,4]
      var size = dimensions[0]*dimensions[1]*dimensions[2]
      for (var a = 0; a < size; a++) {
        cube1[a] = "1:"+a;
        cube2[a] = "2:"+a;
        cube3[a] = "3:"+a;
        cube4[a] = "4:"+a;
      }
      cubes.push(cube1)
      cubes.push(cube2)
      cubes.push(cube3)
      cubes.push(cube4)


      let reconstructedCube = []

      if(this.tileBuffer.length > 1)
      {
        // combine tiles
        for (let l = 0; l < Math.pow(2, this.xyLevel); l=l+2) // y offset
        {
          for (let h = 0; h < this.clientCubeDimensions[2]; h++) // z rows
          {
            for (let j = 0; j < this.clientCubeDimensions[1]; j++) // y rows
            {
              for (let i = 0; i < Math.pow(2, this.xyLevel); i++) // x offset
              {
                for (let k = 0; k < this.clientCubeDimensions[0]; k++) // x rows
                {
                  reconstructedCube.push(this.tileBuffer[i+l][k+(j*dimensions[0])+(h*Math.pow(dimensions[2],2))])
                  // reconstructedCube.push(cubes[i+1][k+(j*dimensions[0])+(h*Math.pow(dimensions[2],2))])
                }
              }
            }
          }
        }
        return reconstructedCube
      }
      else
      {
        return this.tileBuffer[0]
      }
    }
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
