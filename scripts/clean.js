const path = require('path');
const fs = require('fs-extra');

async function main() {
  await fs.remove('build');
  // await fs.remove('externals');
}

main();
