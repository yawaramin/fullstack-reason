const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const dist = 'dist';
const outputDir = path.join(__dirname, dist);

const isProd = process.env.NODE_ENV === 'production';

module.exports = {
  entry: './frontend/Index.bs.js',
  mode: isProd ? 'production' : 'development',
  output: {
    path: path.resolve(__dirname, dist),
    filename: 'dist/index.[contenthash].js'
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: 'frontend/index.html'
    })
  ],
  devServer: {
    compress: true,
    contentBase: outputDir,
    port: process.env.PORT || 8000,
    historyApiFallback: true
  }
};
