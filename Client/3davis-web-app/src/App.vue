<template>
  <div 
    v-if="connected"
  >
    <!-- <img alt="Vue logo" src="./assets/logo.png"> -->
    <!-- <HelloWorld/> -->
    <control-panel-component
      v-if="!loadingFile"
      :fileList="files"
      @selected="fileSelected"
      @crop="cropCube"
      @reset="resetCube"
      @high-res="getImage"
    />
    <ImageComponent
      v-if="!loadingImage"
      @mouseup="loadingImage=true"
      :sourceData="imageSource"
    />
    <VTKVolumeComponent
      v-else-if="!loadingVolume"
      @points="setCropPoints"
      @camera="setCameraState"
      @ctfun="setColourFunction"
      :sourceData="source"
      :dimensions="clientCubeDimensions"
      :spacing="1"
      :resetPlanes="reset"
    />
  </div>
</template>

<script>
import ControlPanelComponent from './components/ControlPanelComponent.vue'
import VTKVolumeComponent from './components/VTKVolumeComponent.vue'
import ImageComponent from './components/ImageComponent.vue'
// import * as zfp from 'zfp_wrapper'

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
      files: null,
      source: [],
      imageSource: [],
      connection: null,
      connected: true,
      loadingImage: true,
      loadingVolume: true,
      loadingFile: true,
      xyLevel: 0,
      zLevel: 0,
      xyMax: 0,
      zMax: 0,
      cropPoints: [],
      cropDimensions: [],
      tiles: [1,2], // keeps track which tiles it needs
      tileBuffer:[], // holds data tiles
      tileDimensions: [],
      tileChunkDimensions: [],
      reset: false,
      cameraState: null,
      timerCountdown: -1,
      timer: null,
      clientCubeDimensions: [0, 0, 0],
      serverCubeDimensions: []
    }
  },
  created(){
    // webassembly
    // this.zfpInstance = new Worker(zfp)

    // dummy source data
    // var size = this.clientCubeDimensions[0]*this.clientCubeDimensions[1]*this.clientCubeDimensions[2]

    // const valuesVolume = [];
    // for (var i = 0; i < size; i++) {
    //   valuesVolume[i] = Math.random();
    // }
    // this.tileBuffer[0] = valuesVolume

    // size = 1920*1080 // 2D image

    // const valuesImage = [];
    // for (var j = 0; j < size; j++) {
    //   valuesImage[j] = Math.random();
    // }
    // this.imageSource = valuesImage
  },
  mounted() {
    // connect to server
    this.connection = new WebSocket("ws://localhost:9000/")

    this.connection.onopen = function(event) {
      console.log(event)
      console.log("successfully connected to server")
    }

    this.connection.onmessage = async event => {

      const messageData = JSON.parse(event.data)
      console.log(messageData.type)

      if(messageData.type == "volume") // receive data tile
      {
        // const dataVar = this.decompressData(messageData.render_data)
        
        console.log(messageData)
        // add to tile buffer
        this.tileBuffer.push(messageData.floatArr)
        this.tileDimensions.push([messageData.dimensions[0],messageData.dimensions[1],messageData.dimensions[2]])
        this.tileChunkDimensions.push(messageData.chunk_dimension)

        // combine client cube dimensions
        if(this.tileBuffer.length == 1)
        {
          this.clientCubeDimensions = messageData.dimensions
        }
        else {
          this.clientCubeDimensions[0] = this.clientCubeDimensions[0] +  messageData.dimensions[0]
        }

        if(this.tileBuffer.length === this.tiles.length)
        {
          console.log("reconstruct data")
          this.source = this.constructCube()
          // this.source = this.tileBuffer[0]
          this.loadingVolume = false
          // this.reset = true
        }
          
      }
      else if(messageData.type == "BigD")
      {
        console.log(messageData)
        this.serverCubeDimensions = messageData.dimensions
        this.cropDimensions = messageData.dimensions

        this.cropPoints[0] = [0,0,0]
        this.cropPoints[1] = [0,0,this.serverCubeDimensions[2]]
        this.cropPoints[2] = [0,this.serverCubeDimensions[1],0]
        this.cropPoints[3] = [0,this.serverCubeDimensions[1],this.serverCubeDimensions[2]]
        this.cropPoints[4] = [this.serverCubeDimensions[0],0,0]
        this.cropPoints[5] = [this.serverCubeDimensions[0],0,this.serverCubeDimensions[2]]
        this.cropPoints[6] = [this.serverCubeDimensions[0],this.serverCubeDimensions[1],0]
        this.cropPoints[7] = [this.serverCubeDimensions[0],this.serverCubeDimensions[1],this.serverCubeDimensions[2]]
      
        this.xyMax = messageData.smallXYFile
        this.zMax = messageData.smallZFile
        this.xyLevel = messageData.smallXYFile
        this.zLevel = messageData.smallZFile

        // get lowest level of server cube
        // var lowestX = this.getLowestLevel(this.serverCubeDimensions[0], 0)
        // var lowestY = this.getLowestLevel(this.serverCubeDimensions[1], 1)

        // if(lowestX<lowestY)
        //   this.xyLevel = Math.pow(2,lowestX)
        // else
        //   this.xyLevel = Math.pow(2,lowestY)

        // this.zLevel = Math.pow(2,this.getLowestLevel(this.serverCubeDimensions[2], 2))
      }
      else if(messageData.type == "image")
      {
        // set image component
        console.log(messageData)
        this.imageSource = messageData.image_data
        
        this.loadingImage = false
      }
      else if(messageData.type == "file")
      {
        // file data
        console.log(messageData.files)
        this.files = messageData.files
        this.loadingFile = false
      }
    }
  },
  // watch: {
  //   timerCountdown: {
  //     handler() {
  //       if(this.timer)
  //       {
  //         clearTimeout(this.timer)
  //       }
  //       if(this.timerCountdown>0)
  //       {
  //         this.timer = setTimeout(() => {
  //           console.log(this.timerCountdown)
  //           this.timerCountdown--
  //         }, 1000)
  //       }
  //       else // sends request when timer runs out
  //       {
  //         console.log("interaction countdown finished")
  //         // console.log("loading image")
  //         // request image
  //         // this.connection.send(this.cameraState)
  //       }
  //     },
  //     immediate: true
  //   }
  // },
  methods: {
    // decompressData(data) {
    //   /* Base64 String to Uint8Array convertor -- TO TEST*/
    //     var binary_string = window.atob(data);
    //     var len = binary_string.length;
    //     var bytes = new Uint8Array(len);
    //     for (var i = 0;i < len; i++) {
    //       bytes[i] = binary_string.charCodeAt(i);
    //     }
    //     return this.zfpInstance.zfpDecompressUint8WASM(bytes.buffer, bytes.length, data.dimensions[0], data.dimensions[1], data.dimensions[2], 12);
    // },
    fileSelected(event) {
      
      // for testing purposes
      // this.loadingImage = false
      // this.loadingVolume = false
      // this.source = this.constructCube()
      
      // request initial data
      const request = {
        type: 'file',
        file: event
      }
      let messageJSON = JSON.stringify(request)
      this.connection.send(messageJSON)
      console.log("Requested file: " + event)

      // request initial image
      console.log("Request image")
      this.cameraState = {
          "type": "image",
          "camera_pos": [-0.5,-0.5,210],
          "camera_view_up": [0,1,0],
          "ctfun": {
            "nodes": [
              0.000003005679445777787,
              0.010989383333240507,
              0.003924554572632569,
              0.014470019269050218,
              0.00784610346581936,
              0.017948030304401327,
              0.011767652359006151,
              0.021423633253299518,
              0.015689201252192943,
              0.02489704807507271,
              0.019610750145379736,
              0.028368497863674957,
              0.023532299038566525,
              0.031838208834695604,
              0.027453847931753317,
              0.0353064103100107,
              0.03137539682494011,
              0.03877333470001511,
              0.0352969457181269,
              0.04223921748337242,
              0.039218494611313694,
              0.04570429718422166,
              0.043140043504500486,
              0.04916881534677852,
              0.04706159239768727,
              0.05263301650726959,
              0.050983141290874064,
              0.0560971481631414,
              0.054904690184060856,
              0.059561460739479655,
              0.05882623907724765,
              0.0630262075525835,
              0.06274778797043444,
              0.06649164477063281,
              0.06666933686362123,
              0.06995803137139196,
              0.07059088575680803,
              0.07342562909689232,
              0.07451243464999481,
              0.0768947024050366,
              0.07843398354318161,
              0.08036551841807073,
              0.0823555324363684,
              0.0838383468678676,
              0.0862770813295552,
              0.08731346003797115,
              0.09019863022274198,
              0.09079113270234654,
              0.09412017911592876,
              0.09427164206078975,
              0.09804172800911556,
              0.09775526767094303,
              0.10196327690230235,
              0.10124229137687214,
              0.10588482579548915,
              0.10473299723415772,
              0.10980637468867593,
              0.10822767143145742,
              0.11372792358186273,
              0.1117266022084962,
              0.11764947247504952,
              0.11523007977044385,
              0.12157102136823632,
              0.11873839619864227,
              0.1254925702614231,
              0.12225184535764547,
              0.1294141191546099,
              0.1257707227985385,
              0.13333566804779667,
              0.12929532565850257,
              0.13725721694098347,
              0.132825952556599,
              0.14117876583417027,
              0.13636290348574207,
              0.14510031472735707,
              0.139906479700839,
              0.14902186362054384,
              0.14345698360307385,
              0.15294341251373064,
              0.1470147186203169,
              0.15686496140691744,
              0.15057998908364295,
              0.1607865103001042,
              0.15415310009994626,
              0.164708059193291,
              0.15773435742064107,
              0.1686296080864778,
              0.1613240673064418,
              0.1725511569796646,
              0.164922536388217,
              0.17647270587285138,
              0.16853007152392108,
              0.18039425476603818,
              0.17214697965160133,
              0.18431580365922498,
              0.17577356763849095,
              0.18823735255241175,
              0.17941014212619616,
              0.19215890144559855,
              0.18305700937199226,
              0.19608045033878535,
              0.186714475086245,
              0.20000199923197215,
              0.1903828442659798,
              0.20392354812515892,
              0.19406242102462368,
              0.20784509701834572,
              0.19775350841794875,
              0.21176664591153252,
              0.2014564082662504,
              0.21568819480471932,
              0.20517142097280033,
              0.2196097436979061,
              0.20889884533861142,
              0.2235312925910929,
              0.21263897837356419,
              0.2274528414842797,
              0.21639211510394382,
              0.23137439037746646,
              0.220158548376442,
              0.23529593927065326,
              0.22393856865868295,
              0.23921748816384006,
              0.22773246383633755,
              0.24313903705702686,
              0.23154051900689313,
              0.24706058595021363,
              0.23536301627015138,
              0.25098213484340043,
              0.239200234515533,
              0.2549036837365872,
              0.24305244920626895,
              0.258825232629774,
              0.24691993216056668,
              0.2627467815229608,
              0.25080295132984176,
              0.26666833041614757,
              0.25470177057411114,
              0.27058987930933437,
              0.2586166494346486,
              0.27451142820252117,
              0.2625478429040088,
              0.27843297709570797,
              0.26649560119352844,
              0.28235452598889477,
              0.2704601694984221,
              0.28627607488208157,
              0.2744417877605901,
              0.29019762377526837,
              0.2784406904292645,
              0.2941191726684551,
              0.2824571062196216,
              0.2980407215616419,
              0.2864912578694967,
              0.3019622704548287,
              0.29054336189433694,
              0.3058838193480155,
              0.29461362834053867,
              0.3098053682412023,
              0.2987022605373143,
              0.3137269171343891,
              0.3028094548472441,
              0.3176484660275759,
              0.3069354004156686,
              0.32157001492076265,
              0.31108027891908185,
              0.32549156381394945,
              0.31524426431269476,
              0.32941311270713625,
              0.319427522577335,
              0.33333466160032305,
              0.3236302114658618,
              0.33725621049350984,
              0.32785248024927083,
              0.34117775938669664,
              0.33209446946267374,
              0.34509930827988344,
              0.3363563106513411,
              0.3490208571730702,
              0.3406381261169944,
              0.352942406066257,
              0.3449400286645464,
              0.3568639549594438,
              0.3492621213494864,
              0.3607855038526306,
              0.35360449722611004,
              0.3647070527458174,
              0.3579672390968029,
              0.3686286016390042,
              0.36235041926258227,
              0.372550150532191,
              0.36675409927511204,
              0.3764716994253777,
              0.3711783296904021,
              0.3803932483185645,
              0.37562314982441264,
              0.3843147972117513,
              0.38008858751078145,
              0.3882363461049381,
              0.38457465886089803,
              0.3921578949981249,
              0.3890813680265486,
              0.3960794438913117,
              0.39360870696536043,
              0.4000009927844985,
              0.3981566552092729,
              0.4039225416776853,
              0.4027251796362691,
              0.40784409057087206,
              0.4073142342455968,
              0.41176563946405886,
              0.41192375993671654,
              0.41568718835724566,
              0.41655368429220996,
              0.41960873725043246,
              0.42120392136488394,
              0.42353028614361926,
              0.4258743714693116,
              0.42745183503680606,
              0.4305649209780417,
              0.43137338392999286,
              0.4352754421227198,
              0.4352949328231796,
              0.44000579280035523,
              0.4392164817163664,
              0.44475581638497563,
              0.4431380306095532,
              0.4495253415449023,
              0.44705957950274,
              0.4543141820658868,
              0.4509811283959268,
              0.45912213668034313,
              0.4549026772891136,
              0.46394898890291086,
              0.4588242261823004,
              0.46879450687258273,
              0.46274577507548714,
              0.47365844320162886,
              0.46666732396867394,
              0.4785405348315471,
              0.47058887286186074,
              0.4834405028962694,
              0.47451042175504754,
              0.48835805259284654,
              0.47843197064823434,
              0.49329287305983727,
              0.48235351954142114,
              0.4982446372636201,
              0.48627506843460794,
              0.5032130018928446,
              0.4901966173277947,
              0.508197607261237,
              0.4941181662209815,
              0.5131980772189676,
              0.4980397151141683,
              0.5182140190727875,
              0.5019612640073551,
              0.5232450235151337,
              0.5058828129005418,
              0.5282906645624029,
              0.5098043617937287,
              0.533350499502582,
              0.5137259106869154,
              0.5384240688524244,
              0.5176474595801023,
              0.5435108963243545,
              0.521569008473289,
              0.5486104888032737,
              0.5254905573664759,
              0.5537223363334401,
              0.5294121062596626,
              0.5588459121155859,
              0.5333336551528494,
              0.5639806725144274,
              0.5372552040460362,
              0.5691260570767236,
              0.541176752939223,
              0.5742814885600214,
              0.5450983018324098,
              0.5794463729722295,
              0.5490198507255966,
              0.584620099622148,
              0.5529413996187834,
              0.5898020411810745,
              0.5568629485119702,
              0.5949915537556053,
              0.5607844974051569,
              0.6001879769717327,
              0.5647060462983438,
              0.6053906340703389,
              0.5686275951915305,
              0.610598832014175,
              0.5725491440847174,
              0.6158118616064068,
              0.5764706929779041,
              0.6210289976207971,
              0.580392241871091,
              0.6262494989435883,
              0.5843137907642777,
              0.6314726087271378,
              0.5882353396574644,
              0.6366975545553523,
              0.5921568885506513,
              0.6419235486209509,
              0.596078437443838,
              0.6471497879145853,
              0.5999999863370249,
              0.6523754544258293,
              0.6039215352302116,
              0.6575997153560427,
              0.6078430841233985,
              0.6628217233431031,
              0.6117646330165852,
              0.6680406166979904,
              0.615686181909772,
              0.6732555196531953,
              0.6196077308029588,
              0.6784655426229167,
              0.6235292796961456,
              0.6836697824749975,
              0.6274508285893324,
              0.6888673228145432,
              0.6313723774825192,
              0.6940572342791493,
              0.635293926375706,
              0.6992385748456615,
              0.6392154752688928,
              0.7044103901483743,
              0.6431370241620795,
              0.7095717138085658,
              0.6470585730552664,
              0.7147215677752572,
              0.6509801219484531,
              0.7198589626770697,
              0.65490167084164,
              0.7249828981850457,
              0.6588232197348267,
              0.7300923633862861,
              0.6627447686280136,
              0.7351863371682474,
              0.6666663175212003,
              0.7402637886135282,
              0.6705878664143871,
              0.7453236774049685,
              0.6745094153075739,
              0.7503649542408699,
              0.6784309642007607,
              0.7553865612601333,
              0.6823525130939475,
              0.7603874324771087,
              0.6862740619871343,
              0.7653664942259277,
              0.6901956108803211,
              0.7703226656140898,
              0.6941171597735079,
              0.7752548589850589,
              0.6980387086666946,
              0.7801619803896149,
              0.7019602575598815,
              0.7850429300657003,
              0.7058818064530682,
              0.789896602926483,
              0.709803355346255,
              0.7947218890563567,
              0.7137249042394418,
              0.7995176742145854,
              0.7176464531326286,
              0.8042828403462874,
              0.7215680020258154,
              0.8090162661004501,
              0.7254895509190021,
              0.8137168273546531,
              0.729411099812189,
              0.8183833977461745,
              0.7333326487053757,
              0.8230148492091376,
              0.7372541975985626,
              0.8276100525173572,
              0.7411757464917493,
              0.8321678778325304,
              0.7450972953849362,
              0.8366871952574093,
              0.7490188442781229,
              0.841166875393589,
              0.7529403931713097,
              0.8456057899035366,
              0.7568619420644965,
              0.8500028120764744,
              0.7607834909576833,
              0.8543568173977341,
              0.7647050398508701,
              0.8586666841211836,
              0.7686265887440569,
              0.8629312938443281,
              0.7725481376372437,
              0.8671495320856777,
              0.7764696865304305,
              0.8713202888639733,
              0.7803912354236173,
              0.8754424592788526,
              0.7843127843168041,
              0.8795149440925392,
              0.7882343332099908,
              0.8835366503121294,
              0.7921558821031777,
              0.8875064917720487,
              0.7960774309963644,
              0.8914233897162513,
              0.7999989798895513,
              0.8952862733797268,
              0.803920528782738,
              0.8990940805688779,
              0.8078420776759249,
              0.9028457582403369,
              0.8117636265691116,
              0.9065402630777772,
              0.8156851754622984,
              0.9101765620662836,
              0.8196067243554852,
              0.9137536330638387,
              0.823528273248672,
              0.9172704653694881,
              0.8274498221418588,
              0.9207260602877425,
              0.8313713710350455,
              0.9241194316887765,
              0.8352929199282324,
              0.9274496065639877,
              0.8392144688214191,
              0.930715625576479,
              0.8431360177146059,
              0.9339165436060295,
              0.8470575666077927,
              0.9370514302881201,
              0.8509791155009795,
              0.9401193705465876,
              0.8549006643941663,
              0.9431194651194779,
              0.8588222132873531,
              0.9460508310776803,
              0.8627437621805399,
              0.9489126023359201,
              0.8666653110737267,
              0.9517039301557,
              0.8705868599669134,
              0.9544239836397806,
              0.8745084088601003,
              0.9570719502177962,
              0.878429957753287,
              0.959647036122611,
              0.8823515066464739,
              0.962148466857024,
              0.8862730555396606,
              0.964575487650438,
              0.8901946044328475,
              0.9669273639051184,
              0.8941161533260342,
              0.9692033816316705,
              0.898037702219221,
              0.9714028478733743,
              0.9019592511124078,
              0.9735250911190252,
              0.9058808000055946,
              0.9755694617039359,
              0.9098023488987814,
              0.9775353321987628,
              0.9137238977919682,
              0.9794220977858348,
              0.917645446685155,
              0.9812291766226638,
              0.9215669955783418,
              0.9829560101923356,
              0.9254885444715285,
              0.9846020636404832,
              0.9294100933647154,
              0.9861668260985583,
              0.9333316422579021,
              0.9876498109931288,
              0.937253191151089,
              0.9890505563409383,
              0.9411747400442757,
              0.9903686250294786,
              0.9450962889374626,
              0.9916036050828361,
              0.9490178378306493,
              0.9927551099125848,
              0.952939386723836,
              0.9938227785535154,
              0.9568609356170229,
              0.9948062758839937,
              0.9607824845102096,
              0.9957052928307659,
              0.9647040334033965,
              0.996519546558031,
              0.9686255822965832,
              0.9972487806406217,
              0.9725471311897701,
              0.9978927652211421,
              0.9764686800829568,
              0.9984512971509313,
              0.9803902289761436,
              0.9989242001147274,
              0.9843117778693304,
              0.9993113247389293,
              0.9882333267625172,
              0.9996125486833598,
              0.992154875655704,
              0.9998277767164526,
              0.9960764245488908,
              0.9999569407737985,
              0.9999979734420776,
              0.010989383333240507
            ],
            "colourMap": [
              -1,
              0.32549,
              0.14902,
              0.960784,
              -0.866221,
              0.297047,
              0.375586,
              0.963836,
              -0.732441,
              0.180302,
              0.536818,
              0.964627,
              -0.598662,
              0.1302,
              0.649207,
              0.929647,
              -0.464883,
              0.0445143,
              0.749654,
              0.855998,
              -0.331104,
              0.0271325,
              0.830713,
              0.721527,
              -0.197324,
              0.259504,
              0.866145,
              0.543555,
              -0.0635452,
              0.428364,
              0.890725,
              0.329819,
              0.0702341,
              0.568503,
              0.898508,
              0.187623,
              0.204013,
              0.738259,
              0.890317,
              0.0825461,
              0.337793,
              0.84546,
              0.86136,
              0.0147555,
              0.471572,
              0.912191,
              0.808018,
              0,
              0.605351,
              0.962848,
              0.710445,
              0,
              0.73913,
              0.999469,
              0.600258,
              0.0176284,
              0.87291,
              0.994156,
              0.445975,
              0.193912,
              1,
              0.980407,
              0.247105,
              0.262699
            ]
          }
      }
      // console.log(this.cameraState)
      messageJSON = JSON.stringify(this.cameraState)
      this.connection.send(messageJSON)
    },
    setCropPoints(event) {
      this.cropPoints = event
    },
    getLowestLevel(num, pos) {
      var level = 0
      while(num >= this.clientCubeDimensions[pos]) {
        level++;
        num /= 2
      }
      return level-1
    },
    nearestPowTwo(num) {
      return Math.pow( 2, Math.floor( Math.log( num ) / Math.log( 2 )));
    },
    cropCube() {
      console.log("crop cube")

      // this.xyLevel = 0
      // this.zLevel = 0

      // console.log(this.cropPoints)

      let points = []

      // convert points to world coordianates
      const factorX = this.cropDimensions[0] / this.clientCubeDimensions[0]
      const factorY = this.cropDimensions[1] / this.clientCubeDimensions[1]
      const factorZ = this.cropDimensions[2] / this.clientCubeDimensions[2]

      for (let k = 0; k < this.cropPoints.length; k++) {
        points[k] = []
        points[k].push(Math.ceil(this.cropPoints[k][0]*factorX))
        points[k].push(Math.ceil(this.cropPoints[k][1]*factorY))
        points[k].push(Math.ceil(this.cropPoints[k][2]*factorZ))
      }

      // save crop dimensions
      this.cropDimensions = []
      this.cropDimensions.push(points[7][0]-points[0][0])
      this.cropDimensions.push(points[7][1]-points[0][1])
      this.cropDimensions.push(points[7][2]-points[0][2])

      // get the nearest factor
      var X = this.nearestPowTwo(this.serverCubeDimensions[0]/this.cropDimensions[0])
      var Y = this.nearestPowTwo(this.serverCubeDimensions[1]/this.cropDimensions[1])
      this.zLevel = this.nearestPowTwo(this.serverCubeDimensions[2]/this.cropDimensions[2])

      // update level
      if(X<Y)
        this.xyLevel = X
      else
        this.xyLevel = Y

      // determine which cubes to request for
      const mipmap = "DATA_XY_"+this.xyLevel+"_Z_"+this.zLevel;
      console.log(mipmap)

      // determine tiles
      // get size of single tile in world space
      let singleCube = []
      singleCube.push(this.serverCubeDimensions[0]/this.xyLevel)
      singleCube.push(this.serverCubeDimensions[1]/this.xyLevel)
      singleCube.push(this.serverCubeDimensions[2]/this.zLevel)
      // cublet coord
      let cubelet = []
      // cubelet[0] = (Math.ceil(points[0]/singleX) == 0) ? 1 : Math.ceil(points[0]/singleX)
      // cubelet[1] = (Math.ceil(points[1]/singleX) == 0) ? 1 : Math.ceil(points[1]/singleX)
      // cubelet[2] = (Math.ceil(points[2]/singleY) == 0) ? 1 : Math.ceil(points[2]/singleY)
      // cubelet[3] = (Math.ceil(points[3]/singleY) == 0) ? 1 : Math.ceil(points[3]/singleY)
      // cubelet[4] = (Math.ceil(points[4]/singleZ) == 0) ? 1 : Math.ceil(points[4]/singleZ)
      // cubelet[5] = (Math.ceil(points[5]/singleZ) == 0) ? 1 : Math.ceil(points[5]/singleZ)

      for (let j = 0; j < points.length; j++) {
        var tempPoint = []
        for (let k = 0; k < points[j].length; k++) {
          if(Math.ceil(points[j][k]/singleCube[k]) == 0)
            tempPoint.push(1)
          else
            tempPoint.push(Math.ceil(points[j][k]/singleCube[k]))
        }
        cubelet.push(tempPoint)
      }

      // let temp = []
      // temp[0] = [cubelet[0],cubelet[2],cubelet[4]]
      // temp[1] = [cubelet[1],cubelet[2],cubelet[4]]
      // temp[2] = [cubelet[0],cubelet[3],cubelet[4]]
      // temp[3] = [cubelet[1],cubelet[3],cubelet[4]]
      // temp[4] = [cubelet[0],cubelet[2],cubelet[5]]
      // temp[5] = [cubelet[1],cubelet[2],cubelet[5]]
      // temp[6] = [cubelet[0],cubelet[3],cubelet[5]]
      // temp[7] = [cubelet[1],cubelet[3],cubelet[5]]

      this.tiles = []

      for (let i = 0; i < cubelet.length; i++) {
        let tempVal = cubelet[i][0] // x
        
        if(cubelet[i][1]>1) // y
        {
          tempVal += this.xyLevel
        }
        
        if(cubelet[i][2]>1) // z
        {
          tempVal += Math.pow(this.zLevel, 2)
        }
        this.tiles.push(tempVal)
      }
      
      // remove duplicates
      this.tiles = this.tiles.filter((value, index) => this.tiles.indexOf(value) === index)

      this.tiles = this.tiles.splice(0,4)

      // conver points to xyz
      let serverPoints = []
      for (let p = 0; p < points.length; p++) {
        let tempString = points[p][0] +""+ points[p][0] +""+ points[p][0]
        serverPoints.push(parseInt(tempString))
      }

      // request next set of tiles
      const request = {
        type: "volume",
        cropPoints: serverPoints,
        XY: this.xyLevel,
        Z: this.zLevel,
        tiles: []
      }
  
      for (let i = 0; i < this.tiles.length; i++) {
        request.tiles.push(this.tiles[i])
      }

      console.log("Request tiles")
      console.log(request)

      const myJSON = JSON.stringify(request)
      this.connection.send(myJSON)
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

      const messageJSON = JSON.stringify(request)
      this.connection.send(messageJSON)
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

      const messageJSON = JSON.stringify(request)
      this.connection.send(messageJSON)
    },
    setCameraState(event) {
      this.cameraState = event
    },
    setColourFunction(event) {
      // console.log(event)
      // update colour transfer function to the server
      this.cameraState.ctfun = event
      // this.loadingImage=true
    },
    getImage() {
      // request image
      console.log("request image")
      this.cameraState.type = "image"
      const messageJSON = JSON.stringify(this.cameraState)
      this.connection.send(messageJSON)
    },
    constructCube() {

      let reconstructedCube = []

      if(this.tileBuffer.length > 1)
      {
        // combine tiles
        let xOffset = 0, yOffset = 0, zOffset = 0
        let XYChunk = 64, ZChunk = 64
        let xChunksDim = this.tileChunkDimensions[0][0]
        let yChunksDim = this.tileChunkDimensions[0][1]
        // let zChunksDim = this.tileChunkDimensions[0][2]

        for (let i = 0; i < this.clientCubeDimensions[2]; i++) // z
        {
          for (let j = 0; j < this.clientCubeDimensions[1]; j++) // y
          {
            for (let k = 0; k < this.clientCubeDimensions[0]; k++) // x
            {
              let tileNum = 1 + yChunksDim * xChunksDim * (Math.floor((i + zOffset) / ZChunk))
              tileNum += (Math.floor((j + yOffset) / XYChunk)) * xChunksDim
              tileNum += Math.floor((k + xOffset) / XYChunk)
              tileNum = Math.floor(tileNum)
              
              let tileOffsetX, tileOffsetY, tileOffsetZ;
              if (k == 0)
              {
                tileOffsetX = (xOffset % XYChunk);
              }
              else
              {
                tileOffsetX = 0;
              }

              if (j == 0)
              {
                tileOffsetY = yOffset % XYChunk;
              }
              else
              {
                tileOffsetY = 0;
              }

              if (i == 0)
              {
                tileOffsetZ = zOffset % ZChunk;
              }
              else
              {
                tileOffsetZ = 0;
              }

              let count = 0;
              for (let tile = 0; tile < this.tiles.length; tile++) {
                
                if (this.tiles[tile] == tileNum)
                {
                  count = 0;
                  for (let f = (tileOffsetX % XYChunk); f < this.tileDimensions[tile][0] && (k + f) < this.clientCubeDimensions[0]; f++)
                  {
                    reconstructedCube[(k + count) + j * this.clientCubeDimensions[0] + i * this.clientCubeDimensions[1] * this.clientCubeDimensions[0]] = this.tileBuffer[tile][(f % XYChunk) + ((tileOffsetY + j) % XYChunk) * this.tileDimensions[tile][0] + ((tileOffsetZ + i) % ZChunk) * this.tileDimensions[tile][1] * this.tileDimensions[tile][0]];
                    count++;
                  }
                  k += count - 1;
                  break;
                }
              }
                
            }
          }
        } 
        // console.log(reconstructedCube)
        return reconstructedCube
      }
      else
      {
        return this.tileBuffer[0]
      }
    },
    // interactionStart() {
    //   if(this.timer)
    //   {
    //     clearTimeout(this.timer)
    //   }
    // },
    // interactionEnd() {
    //   //start timer
    //   if(this.timer)
    //   {
    //     clearTimeout(this.timer)
    //   }
    //   this.timerCountdown = 5
    //   console.log("no interaction")
    // }
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
  background-color: black;
  height: 100vh;
}
</style>
