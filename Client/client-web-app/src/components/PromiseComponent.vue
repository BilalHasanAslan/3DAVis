<template>
    <div v-if="loading">
        Image
    </div>
    <div v-else-if="interaction">
        Volume
    </div>
</template>
<script>
import axios from 'axios'

export default {
    components: {
        
    },
    data () {
        return {
            data: null,
            loading: true,
            interaction: false
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
    }
}
</script>