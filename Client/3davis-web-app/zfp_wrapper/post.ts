declare var Module: any;
const FLT_MAX = 3.402823466e+38;
​
const zfpDecompress = Module.cwrap("zfpDecompress", "number", ["number", "number", "number", "number", "number", "number", "number"]);
​
Module.zfpDecompressUint8WASM = function (u8: Uint8Array, compressedSize: number, width: number, height: number, depth: number, precision: number) {
    const numPixels = width * height * depth;
    const numBytes = numPixels * 4;
​
    // Allocate src array
    const srcPtr = Module._malloc(compressedSize);
    const srcArray = new Uint8Array(Module.HEAPU8.buffer, srcPtr, compressedSize);
    // Copy compressed data from JS memory to WASM
    srcArray.set(u8);
    
    // Allocate dest array
    const destPtr = Module._malloc(numBytes);
    const destArray = new Float32Array(Module.HEAPF32.buffer, destPtr, numBytes);
​
    // Call function and get result
    zfpDecompress(Math.floor(precision), destPtr, width, height, depth, srcPtr, compressedSize);
    
    // Copy result back from WASM memory to JS
    const result = destArray.slice();
    
    // Free WASM memory
    Module._free(srcPtr);
    Module._free(destPtr);
​
    return result;
};