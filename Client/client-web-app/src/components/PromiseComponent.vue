<template>
    <visualisation-component
        v-if="!loading"
       :render-data="data"
    />
</template>
<script>
import VisualisationComponent from './VTKVolumeComponent.vue'
import axios from 'axios'

export default {
    components: {
        VisualisationComponent
    },
    data () {
        return {
            data: null,
            loading: true
        }
    },
    created () {
        
    },
    async mounted () {
        // axios protocol buffer
        // axios.create({
        //     timeout: 45000,
        //     method: 'post',
        //     headers: {
        //         'X-Requested-With': 'XMLHttpRequest',
        //         'Content-Type': 'application/octet-stream'
        //     },
        //     responseType: 'arraybuffer'
        // })

        // axios async/await
        try {
            // arbitrary http call - its just a big file
            let response = await axios.get('https://data.kitware.com/api/v1/file/58e665158d777f16d095fc2e/download')
            this.data = await response;
            this.loading = false
            console.log('data received')
        }
        catch(error) {
            console.log(error);
        }
    }
}
</script>