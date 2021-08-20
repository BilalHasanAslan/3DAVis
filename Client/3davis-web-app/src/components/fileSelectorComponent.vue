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
                value="cube-1"
            >cube 1</option>
            <option 
                value="cube-2"
            >cube 2</option>
            <option 
                value="cube-3"
            >cube 3</option>
            <option 
                value="cube-4"
            >cube 4</option>
        </select>
    </div>
</template>

<script>
export default {
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
    padding-left: 30px;
    padding-bottom: 20px;
}
</style>