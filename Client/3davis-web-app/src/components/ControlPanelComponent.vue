<template>
    <div 
        id="control-panel"
    >
        <file-selector-component
            :files="fileList"
            class="m-1"
            @option:selected="optionSelected"
        />
        <div
            class="mt-5"
        >
            <button 
                type="button" 
                class="btn btn-light m-1"
                @click="$emit('crop')"
            >
                Crop
            </button>
            <!-- <br/>
            <button 
                type="button" 
                class="btn btn-light m-1"
                @click="$emit('back')"
            >
                Step back
            </button> -->
            <br/>
            <button 
                type="button" 
                class="btn btn-light m-1"
                @click="$emit('reset')"
            >
                Reset
            </button>
        </div>
    </div>
</template>
<script>
import FileSelectorComponent from "./FileSelectorComponent.vue"
export default {
    components: {
        FileSelectorComponent
    },
    props: {
        fileList: {
            type: Array,
            default: () => []
        }
    },
    methods: {
        optionSelected(event) {
            // emit which file to get data from
            this.$emit("selected", event)
        }
    }
}
</script>
<style scoped>
    #control-panel {
        position: absolute;
        top: 25px;
        left: 25px;
        z-index: 1;
    }
</style>