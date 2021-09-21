<template>
    <div
        id="imageContainer"
        class="w-100 mx-auto d-block"
    >
        
    </div>
</template>
<script>
import {onMounted} from 'vue';

export default {
    props: {
        sourceData: {
            type: String,
            default: ""
        }
    },
    data () {
        return {
            
        }
    },
    setup(props) {
    
        onMounted(() => {
            var image = new Image()
            image.src = "data:image/jpeg;base64,"+props.sourceData
            document.getElementById('imageContainer').appendChild(image)
            document.getElementsByTagName("IMG")[0].classList.add("img-fluid")
            document.getElementsByTagName("IMG")[0].classList.add("h-100")
            document.getElementsByTagName("IMG")[0].classList.add("w-100")
            document.getElementsByTagName("IMG")[0].classList.add("mx-auto")
            document.getElementsByTagName("IMG")[0].classList.add("overflow-hidden")
        })
    },
}
</script>
<style scoped>
#imageContainer {
    height: 100vh;
    overflow: auto;
}
</style>