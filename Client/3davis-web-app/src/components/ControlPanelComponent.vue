<template>
    <div 
        id="control-panel"
    >
        <file-selector-component
            :files="['file1','file2','file3','file4']"
            class="m-1"
            @option:selected="fileSelected"
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
            <br/>
            <button 
                type="button" 
                class="btn btn-light m-1"
                @click="$emit('back')"
            >
                Step back
            </button>
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
    data () {
        return{
            files: [],
        }
    },
    methods: {
        fileSelected(event) {
            // emit which file to get data from
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