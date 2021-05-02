const path = require('path');

module.exports = {
  entry: './lib/js/src/infrastructure/rendering/Index.bs.js',
  mode: 'production',
  output: {
    path: path.join(__dirname, "js"),
    filename: 'index.js',
  },
};
