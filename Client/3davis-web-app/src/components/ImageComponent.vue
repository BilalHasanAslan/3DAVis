<template>
    <div
        class="w-100"
    >
    </div>
</template>
<script>
export default {
    props: {
        image: {
            type: String,
            default: "space.jpeg"
        }
    },
    data () {
        return {
            
        }
    },
    setup() {
        
    },
}
</script>
<style scoped>
div {
    background-image: url('../assets/images/high-res.jpeg');
    height: 100vh;
    background-position: center;
    background-repeat: no-repeat;
    background-size: cover;
}
</style>