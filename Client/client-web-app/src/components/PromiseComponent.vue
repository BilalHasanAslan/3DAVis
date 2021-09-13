<template>
    <div>
        <div v-if="!loading">
            <div 
                v-if="!interaction"
                @mousedown="interaction=true"
                @mouseup="setInteraction()"
            >
                <div>
                    Image Component
                </div>
                <VTKImageComponent/>
            </div>
            <div 
                v-else
            >
                <div>
                    Volume Component
                </div>
                <VTKStandAloneVolumeComponent
                    @interaction:change="setInteraction()"
                />
            </div>
        </div>
        
    </div>
</template>
<script>
import axios from 'axios'

import VTKImageComponent from './VTKImageComponent.vue';
import VTKStandAloneVolumeComponent from './VTKStandaloneVolumeComponent.vue';

export default {
    components: {
        VTKImageComponent,
        VTKStandAloneVolumeComponent
    },
    data () {
        return {
            stream: null,
            data: null,
            loading: false,
            interaction: true,
            timeout: null,
        }
    },
    created () {
        
    },
    async mounted () {
        // axios instance
        // const instance = axios.create({
        //     baseURL: '',
        //     timeout: 1000,
        //     headers: {}
        // });

        // instance.get('/longRequest', {
        //     url: '',
        //     timeout: 5000
        // });

        // axios protocol buffer
        // axios({
        //     timeout: 45000,
        //     method: 'post',
        //     headers: {
        //         'X-Requested-With': 'XMLHttpRequest',
        //         'Content-Type': 'application/octet-stream'
        //     },
        //     responseType: 'arraybuffer'
        // });

        // cancel token if interaction continues before high res image is fully loaded

        // axios async/await to get data
        try {
            // arbitrary http call - its just a big file
            let response = await axios.get('https://data.kitware.com/api/v1/file/58e665158d777f16d095fc2e/download')
            this.data = await response;
            this.loading = false
        }
        catch(error) {
            console.log(error);
        }

        //  readable stream + axios
        // try {
        //     // arbitrary http call - its just a big file
        //     axios.get('https://data.kitware.com/api/v1/file/58e665158d777f16d095fc2e/download')
        //     .then(response => response.body)
        //     .then(body => {
        //         const reader = body.getReader();

        //         return new ReadableStream({
        //             start(controller) {
        //                 function push() {
        //                     // "done" is a Boolean and value a "Uint8Array"
        //                     reader.read().then( ({done, value}) => {
        //                     // If there is no more data to read
        //                     if (done) {
        //                         console.log('done', done);
        //                         controller.close();
        //                         return;
        //                     }
        //                     // Get the data and send it to the browser via the controller
        //                     controller.enqueue(value);
        //                     // Check chunks by logging to the console
        //                     console.log(done, value);
        //                     push();
        //                     })
        //                 }

        //                 push();
        //             }
        //         });
        //     })
        //     .then(stream => {
        //         // Respond with our stream
        //         return new Response(stream, { headers: { "Content-Type": "text/html" } }).text();
        //     })
        //     .then(result => {
        //         // Do things with result
        //         console.log(result);
        //     })
        // }
        // catch(error) {
        //     console.log(error);
        // }
    },
    methods: {
        setInteraction() {
            this.interaction = true
            // clearTimeout(this.timeout)
            // this.timeout = setTimeout(() => {
            //     this.interaction = false
            // }, 10000)
        }
    }
}
</script>