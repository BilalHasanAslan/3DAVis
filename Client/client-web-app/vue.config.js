module.exports = {
    chainWebpack: config => {
      // GraphQL Loader
      config.module
        .rule('glsl')
        .test(/\.glsl$/)
        .use('vtk.js')
          .loader('shader-loader')
          .end()
    }
  }