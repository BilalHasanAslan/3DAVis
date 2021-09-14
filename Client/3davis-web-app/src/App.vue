<template>
  <div 
    v-if="connected"
  >
    <!-- <img alt="Vue logo" src="./assets/logo.png"> -->
    <!-- <HelloWorld/> -->
    <control-panel-component
      :fileList="files"
      @selected="fileSelected"
      @crop="cropCube"
      @reset="resetCube"
      @high-res="getImage"
    />
    <ImageComponent
      v-if="!loadingImage"
      @mouseup="loadingImage=true"
    />
    <VTKVolumeComponent
      v-if="!loadingVolume"
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
      loadingImage: true,
      loadingVolume: true,
      xyLevel: 0,
      zLevel: 0,
      cropPoints: [0, 1100, 0, 750, 0, 265],
      tiles: [], // keeps track which tiles it needs
      tileBuffer:[], // holds data tiles
      reset: false,
      cameraState: {
        "position": [-0.5,-0.5,210],
        "viewUp": [0,1,0],
        "ctfun": {
          "nodes": [
            [
              0.00000834570346341934,
              0.010989383333240507
            ],
            [
              0.003929861968194303,
              0.014470019269050218
            ],
            [
              0.007851378232925187,
              0.017948030304401327
            ],
            [
              0.011772894497656072,
              0.021423633253299518
            ],
            [
              0.015694410762386955,
              0.02489704807507271
            ],
            [
              0.019615927027117838,
              0.028368497863674957
            ],
            [
              0.023537443291848724,
              0.031838208834695604
            ],
            [
              0.027458959556579607,
              0.0353064103100107
            ],
            [
              0.03138047582131049,
              0.03877333470001511
            ],
            [
              0.03530199208604137,
              0.04223921748337242
            ],
            [
              0.039223508350772256,
              0.04570429718422166
            ],
            [
              0.04314502461550314,
              0.04916881534677852
            ],
            [
              0.04706654088023403,
              0.05263301650726959
            ],
            [
              0.05098805714496491,
              0.0560971481631414
            ],
            [
              0.054909573409695794,
              0.059561460739479655
            ],
            [
              0.05883108967442668,
              0.0630262075525835
            ],
            [
              0.06275260593915756,
              0.06649164477063281
            ],
            [
              0.06667412220388845,
              0.06995803137139196
            ],
            [
              0.07059563846861933,
              0.07342562909689232
            ],
            [
              0.07451715473335022,
              0.0768947024050366
            ],
            [
              0.07843867099808109,
              0.08036551841807073
            ],
            [
              0.08236018726281198,
              0.0838383468678676
            ],
            [
              0.08628170352754286,
              0.08731346003797115
            ],
            [
              0.09020321979227375,
              0.09079113270234654
            ],
            [
              0.09412473605700464,
              0.09427164206078975
            ],
            [
              0.09804625232173551,
              0.09775526767094303
            ],
            [
              0.1019677685864664,
              0.10124229137687214
            ],
            [
              0.10588928485119728,
              0.10473299723415772
            ],
            [
              0.10981080111592817,
              0.10822767143145742
            ],
            [
              0.11373231738065905,
              0.1117266022084962
            ],
            [
              0.11765383364538994,
              0.11523007977044385
            ],
            [
              0.12157534991012081,
              0.11873839619864227
            ],
            [
              0.1254968661748517,
              0.12225184535764547
            ],
            [
              0.1294183824395826,
              0.1257707227985385
            ],
            [
              0.13333989870431348,
              0.12929532565850257
            ],
            [
              0.13726141496904434,
              0.132825952556599
            ],
            [
              0.14118293123377523,
              0.13636290348574207
            ],
            [
              0.14510444749850612,
              0.139906479700839
            ],
            [
              0.149025963763237,
              0.14345698360307385
            ],
            [
              0.15294748002796787,
              0.1470147186203169
            ],
            [
              0.15686899629269876,
              0.15057998908364295
            ],
            [
              0.16079051255742965,
              0.15415310009994626
            ],
            [
              0.16471202882216054,
              0.15773435742064107
            ],
            [
              0.16863354508689143,
              0.1613240673064418
            ],
            [
              0.1725550613516223,
              0.164922536388217
            ],
            [
              0.1764765776163532,
              0.16853007152392108
            ],
            [
              0.18039809388108408,
              0.17214697965160133
            ],
            [
              0.18431961014581497,
              0.17577356763849095
            ],
            [
              0.18824112641054586,
              0.17941014212619616
            ],
            [
              0.19216264267527672,
              0.18305700937199226
            ],
            [
              0.1960841589400076,
              0.186714475086245
            ],
            [
              0.2000056752047385,
              0.1903828442659798
            ],
            [
              0.2039271914694694,
              0.19406242102462368
            ],
            [
              0.20784870773420025,
              0.19775350841794875
            ],
            [
              0.21177022399893114,
              0.2014564082662504
            ],
            [
              0.21569174026366203,
              0.20517142097280033
            ],
            [
              0.21961325652839292,
              0.20889884533861142
            ],
            [
              0.2235347727931238,
              0.21263897837356419
            ],
            [
              0.22745628905785467,
              0.21639211510394382
            ],
            [
              0.23137780532258556,
              0.220158548376442
            ],
            [
              0.23529932158731645,
              0.22393856865868295
            ],
            [
              0.23922083785204734,
              0.22773246383633755
            ],
            [
              0.2431423541167782,
              0.23154051900689313
            ],
            [
              0.2470638703815091,
              0.23536301627015138
            ],
            [
              0.25098538664624,
              0.239200234515533
            ],
            [
              0.25490690291097085,
              0.24305244920626895
            ],
            [
              0.25882841917570176,
              0.24691993216056668
            ],
            [
              0.2627499354404326,
              0.25080295132984176
            ],
            [
              0.26667145170516354,
              0.25470177057411114
            ],
            [
              0.2705929679698944,
              0.2586166494346486
            ],
            [
              0.27451448423462527,
              0.2625478429040088
            ],
            [
              0.2784360004993562,
              0.26649560119352844
            ],
            [
              0.28235751676408705,
              0.2704601694984221
            ],
            [
              0.28627903302881796,
              0.2744417877605901
            ],
            [
              0.2902005492935488,
              0.2784406904292645
            ],
            [
              0.2941220655582797,
              0.2824571062196216
            ],
            [
              0.2980435818230106,
              0.2864912578694967
            ],
            [
              0.30196509808774147,
              0.29054336189433694
            ],
            [
              0.30588661435247233,
              0.29461362834053867
            ],
            [
              0.30980813061720325,
              0.2987022605373143
            ],
            [
              0.3137296468819341,
              0.3028094548472441
            ],
            [
              0.317651163146665,
              0.3069354004156686
            ],
            [
              0.3215726794113959,
              0.31108027891908185
            ],
            [
              0.32549419567612675,
              0.31524426431269476
            ],
            [
              0.32941571194085767,
              0.319427522577335
            ],
            [
              0.33333722820558853,
              0.3236302114658618
            ],
            [
              0.33725874447031945,
              0.32785248024927083
            ],
            [
              0.3411802607350503,
              0.33209446946267374
            ],
            [
              0.3451017769997812,
              0.3363563106513411
            ],
            [
              0.3490232932645121,
              0.3406381261169944
            ],
            [
              0.35294480952924295,
              0.3449400286645464
            ],
            [
              0.35686632579397387,
              0.3492621213494864
            ],
            [
              0.36078784205870473,
              0.35360449722611004
            ],
            [
              0.3647093583234356,
              0.3579672390968029
            ],
            [
              0.3686308745881665,
              0.36235041926258227
            ],
            [
              0.3725523908528974,
              0.36675409927511204
            ],
            [
              0.3764739071176283,
              0.3711783296904021
            ],
            [
              0.38039542338235915,
              0.37562314982441264
            ],
            [
              0.38431693964709,
              0.38008858751078145
            ],
            [
              0.38823845591182093,
              0.38457465886089803
            ],
            [
              0.3921599721765518,
              0.3890813680265486
            ],
            [
              0.39608148844128266,
              0.39360870696536043
            ],
            [
              0.4000030047060136,
              0.3981566552092729
            ],
            [
              0.40392452097074444,
              0.4027251796362691
            ],
            [
              0.40784603723547536,
              0.4073142342455968
            ],
            [
              0.4117675535002062,
              0.41192375993671654
            ],
            [
              0.4156890697649371,
              0.41655368429220996
            ],
            [
              0.419610586029668,
              0.42120392136488394
            ],
            [
              0.42353210229439886,
              0.4258743714693116
            ],
            [
              0.4274536185591298,
              0.4305649209780417
            ],
            [
              0.43137513482386064,
              0.4352754421227198
            ],
            [
              0.4352966510885915,
              0.44000579280035523
            ],
            [
              0.4392181673533224,
              0.44475581638497563
            ],
            [
              0.4431396836180533,
              0.4495253415449023
            ],
            [
              0.4470611998827842,
              0.4543141820658868
            ],
            [
              0.45098271614751506,
              0.45912213668034313
            ],
            [
              0.4549042324122459,
              0.46394898890291086
            ],
            [
              0.45882574867697684,
              0.46879450687258273
            ],
            [
              0.4627472649417077,
              0.47365844320162886
            ],
            [
              0.46666878120643857,
              0.4785405348315471
            ],
            [
              0.4705902974711695,
              0.4834405028962694
            ],
            [
              0.47451181373590035,
              0.48835805259284654
            ],
            [
              0.47843333000063126,
              0.49329287305983727
            ],
            [
              0.4823548462653621,
              0.4982446372636201
            ],
            [
              0.486276362530093,
              0.5032130018928446
            ],
            [
              0.4901978787948239,
              0.508197607261237
            ],
            [
              0.49411939505955477,
              0.5131980772189676
            ],
            [
              0.4980409113242857,
              0.5182140190727875
            ],
            [
              0.5019624275890165,
              0.5232450235151337
            ],
            [
              0.5058839438537475,
              0.5282906645624029
            ],
            [
              0.5098054601184783,
              0.533350499502582
            ],
            [
              0.5137269763832092,
              0.5384240688524244
            ],
            [
              0.5176484926479401,
              0.5435108963243545
            ],
            [
              0.5215700089126709,
              0.5486104888032737
            ],
            [
              0.5254915251774018,
              0.5537223363334401
            ],
            [
              0.5294130414421327,
              0.5588459121155859
            ],
            [
              0.5333345577068637,
              0.5639806725144274
            ],
            [
              0.5372560739715945,
              0.5691260570767236
            ],
            [
              0.5411775902363254,
              0.5742814885600214
            ],
            [
              0.5450991065010563,
              0.5794463729722295
            ],
            [
              0.5490206227657871,
              0.584620099622148
            ],
            [
              0.552942139030518,
              0.5898020411810745
            ],
            [
              0.556863655295249,
              0.5949915537556053
            ],
            [
              0.5607851715599798,
              0.6001879769717327
            ],
            [
              0.5647066878247107,
              0.6053906340703389
            ],
            [
              0.5686282040894416,
              0.610598832014175
            ],
            [
              0.5725497203541725,
              0.6158118616064068
            ],
            [
              0.5764712366189033,
              0.6210289976207971
            ],
            [
              0.5803927528836342,
              0.6262494989435883
            ],
            [
              0.5843142691483652,
              0.6314726087271378
            ],
            [
              0.588235785413096,
              0.6366975545553523
            ],
            [
              0.5921573016778269,
              0.6419235486209509
            ],
            [
              0.5960788179425578,
              0.6471497879145853
            ],
            [
              0.6000003342072886,
              0.6523754544258293
            ],
            [
              0.6039218504720195,
              0.6575997153560427
            ],
            [
              0.6078433667367504,
              0.6628217233431031
            ],
            [
              0.6117648830014812,
              0.6680406166979904
            ],
            [
              0.6156863992662122,
              0.6732555196531953
            ],
            [
              0.6196079155309431,
              0.6784655426229167
            ],
            [
              0.623529431795674,
              0.6836697824749975
            ],
            [
              0.6274509480604048,
              0.6888673228145432
            ],
            [
              0.6313724643251357,
              0.6940572342791493
            ],
            [
              0.6352939805898666,
              0.6992385748456615
            ],
            [
              0.6392154968545974,
              0.7044103901483743
            ],
            [
              0.6431370131193284,
              0.7095717138085658
            ],
            [
              0.6470585293840593,
              0.7147215677752572
            ],
            [
              0.6509800456487901,
              0.7198589626770697
            ],
            [
              0.654901561913521,
              0.7249828981850457
            ],
            [
              0.6588230781782519,
              0.7300923633862861
            ],
            [
              0.6627445944429828,
              0.7351863371682474
            ],
            [
              0.6666661107077136,
              0.7402637886135282
            ],
            [
              0.6705876269724446,
              0.7453236774049685
            ],
            [
              0.6745091432371755,
              0.7503649542408699
            ],
            [
              0.6784306595019063,
              0.7553865612601333
            ],
            [
              0.6823521757666372,
              0.7603874324771087
            ],
            [
              0.6862736920313681,
              0.7653664942259277
            ],
            [
              0.6901952082960989,
              0.7703226656140898
            ],
            [
              0.6941167245608298,
              0.7752548589850589
            ],
            [
              0.6980382408255608,
              0.7801619803896149
            ],
            [
              0.7019597570902916,
              0.7850429300657003
            ],
            [
              0.7058812733550225,
              0.789896602926483
            ],
            [
              0.7098027896197534,
              0.7947218890563567
            ],
            [
              0.7137243058844843,
              0.7995176742145854
            ],
            [
              0.7176458221492151,
              0.8042828403462874
            ],
            [
              0.721567338413946,
              0.8090162661004501
            ],
            [
              0.725488854678677,
              0.8137168273546531
            ],
            [
              0.7294103709434078,
              0.8183833977461745
            ],
            [
              0.7333318872081387,
              0.8230148492091376
            ],
            [
              0.7372534034728696,
              0.8276100525173572
            ],
            [
              0.7411749197376004,
              0.8321678778325304
            ],
            [
              0.7450964360023313,
              0.8366871952574093
            ],
            [
              0.7490179522670622,
              0.841166875393589
            ],
            [
              0.7529394685317932,
              0.8456057899035366
            ],
            [
              0.756860984796524,
              0.8500028120764744
            ],
            [
              0.7607825010612549,
              0.8543568173977341
            ],
            [
              0.7647040173259858,
              0.8586666841211836
            ],
            [
              0.7686255335907166,
              0.8629312938443281
            ],
            [
              0.7725470498554475,
              0.8671495320856777
            ],
            [
              0.7764685661201784,
              0.8713202888639733
            ],
            [
              0.7803900823849093,
              0.8754424592788526
            ],
            [
              0.7843115986496402,
              0.8795149440925392
            ],
            [
              0.7882331149143711,
              0.8835366503121294
            ],
            [
              0.7921546311791019,
              0.8875064917720487
            ],
            [
              0.7960761474438328,
              0.8914233897162513
            ],
            [
              0.7999976637085637,
              0.8952862733797268
            ],
            [
              0.8039191799732947,
              0.8990940805688779
            ],
            [
              0.8078406962380255,
              0.9028457582403369
            ],
            [
              0.8117622125027564,
              0.9065402630777772
            ],
            [
              0.8156837287674873,
              0.9101765620662836
            ],
            [
              0.8196052450322181,
              0.9137536330638387
            ],
            [
              0.823526761296949,
              0.9172704653694881
            ],
            [
              0.8274482775616799,
              0.9207260602877425
            ],
            [
              0.8313697938264107,
              0.9241194316887765
            ],
            [
              0.8352913100911417,
              0.9274496065639877
            ],
            [
              0.8392128263558726,
              0.930715625576479
            ],
            [
              0.8431343426206034,
              0.9339165436060295
            ],
            [
              0.8470558588853343,
              0.9370514302881201
            ],
            [
              0.8509773751500652,
              0.9401193705465876
            ],
            [
              0.8548988914147961,
              0.9431194651194779
            ],
            [
              0.8588204076795269,
              0.9460508310776803
            ],
            [
              0.8627419239442579,
              0.9489126023359201
            ],
            [
              0.8666634402089888,
              0.9517039301557
            ],
            [
              0.8705849564737196,
              0.9544239836397806
            ],
            [
              0.8745064727384505,
              0.9570719502177962
            ],
            [
              0.8784279890031814,
              0.959647036122611
            ],
            [
              0.8823495052679122,
              0.962148466857024
            ],
            [
              0.8862710215326431,
              0.964575487650438
            ],
            [
              0.8901925377973741,
              0.9669273639051184
            ],
            [
              0.894114054062105,
              0.9692033816316705
            ],
            [
              0.8980355703268358,
              0.9714028478733743
            ],
            [
              0.9019570865915667,
              0.9735250911190252
            ],
            [
              0.9058786028562976,
              0.9755694617039359
            ],
            [
              0.9098001191210284,
              0.9775353321987628
            ],
            [
              0.9137216353857593,
              0.9794220977858348
            ],
            [
              0.9176431516504903,
              0.9812291766226638
            ],
            [
              0.9215646679152211,
              0.9829560101923356
            ],
            [
              0.925486184179952,
              0.9846020636404832
            ],
            [
              0.9294077004446829,
              0.9861668260985583
            ],
            [
              0.9333292167094137,
              0.9876498109931288
            ],
            [
              0.9372507329741446,
              0.9890505563409383
            ],
            [
              0.9411722492388755,
              0.9903686250294786
            ],
            [
              0.9450937655036065,
              0.9916036050828361
            ],
            [
              0.9490152817683373,
              0.9927551099125848
            ],
            [
              0.9529367980330682,
              0.9938227785535154
            ],
            [
              0.9568583142977991,
              0.9948062758839937
            ],
            [
              0.9607798305625299,
              0.9957052928307659
            ],
            [
              0.9647013468272608,
              0.996519546558031
            ],
            [
              0.9686228630919917,
              0.9972487806406217
            ],
            [
              0.9725443793567226,
              0.9978927652211421
            ],
            [
              0.9764658956214535,
              0.9984512971509313
            ],
            [
              0.9803874118861844,
              0.9989242001147274
            ],
            [
              0.9843089281509153,
              0.9993113247389293
            ],
            [
              0.9882304444156461,
              0.9996125486833598
            ],
            [
              0.992151960680377,
              0.9998277767164526
            ],
            [
              0.996073476945108,
              0.9999569407737985
            ],
            [
              0.9999949932098388,
              0.010989383333240507
            ]
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
      },
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
        {
          this.source = this.constructCube()
          this.loadingVolume = false
          this.reset = true
        }
          
      }
      else if(event.type == "image")
      {
        console.log(event.type)
        // set image component
        this.loadingImage = false
      }
      else if(event.type == "files")
      {
        console.log(event.type)
      }
    }

    this.connection.onopen = function(event) {
      console.log(event)
      console.log("successfully connected to server")
      // send initial camera values
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
    fileSelected(event) {
      
      // for testing purposes
      this.loadingImage = false
      this.loadingVolume = false
      this.source = this.constructCube()
      
      // request initial data
      const request = {
        type: 'file',
        file: event
      }
      const myJSON =  JSON.stringify(request)
      this.connection.send(myJSON)
      console.log("Requested file: " + event)
    },
    setCropPoints(event) {
      this.cropPoints = event
      this.loadingImage = true
    },
    cropCube() {
      console.log("crop cube")

      // this.xyLevel = 0
      // this.zLevel = 0

      console.log(this.cropPoints)

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
        tiles: this.tiles
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
      // this.loadingImage=true
    },
    getImage() {
      // request image
      console.log("request image")
      this.connection.send(this.cameraState)
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
