<template>
    
</template>
<script>
import { Observable } from "rxjs"
import axios from 'axios'
export default {
    subscriptions() {
        return {
            const data$ = axios.get('https://data.kitware.com/api/v1/file/58e665158d777f16d095fc2e/download').pipe()
        }
    },
    data () {
        return {
            observer: null
        }
    },
    subscriptions: {
        interval$: Observable
    },
    mounted() {
        this.observer = {
            next: x => console.log('Next value: ' + x),
            error: err => console.log('Error: ' + err),
            complete: () => console.log('Complete')
        }
    }
}
</script>