<template>
    <div
        id="selector"
    >
        <label 
            for="cubes"
            class="text-light"
        >
            Data cubes
        </label>
        <br/>
        <select 
            v-model="selected"
            name="data-cubes" 
            id="cubes"
            @change="fileSelected"
        >
            <option 
                v-for="(file, index) in files"
                :key="index"
                :value="file"
            >
                {{ file }}
            </option>
        </select>
    </div>
</template>

<script>
export default {
    props: {
        files: {
            type: Array,
            default : () => []
        }
    },
    data() {
        return {
            selected: ''
        }
    },
    methods: {
        fileSelected() {
            this.$emit('option:selected', this.selected)
        }
    }
}
</script>

<style>
#selector {
    /* padding-left: 30px;
    padding-bottom: 20px; */
}
</style>