const { spawn } = require('child_process');
const path = require('path');
const fs = require('fs-extra');

const isWin = process.platform === 'win32';

async function checkBuildDir() {
  const exists = await fs.pathExists('build');
  if (!exists) {
    console.log('build folder not found, generating cmake files...');

    await fs.emptyDir('build');
    await new Promise((resolve) => {
      let cmakeArgs = isWin ? ['-G', 'Visual Studio 15 2017 Win64', '..'] : ['-G', 'Xcode', '..'];

      const cmake = spawn('cmake', cmakeArgs, {
        cwd: path.join(process.cwd(), 'build'),
        env: process.env,
        encoding: 'utf-8',
      });

      cmake.stdout.pipe(process.stdout);
      cmake.stderr.pipe(process.stderr);

      cmake.on('close', (code) => {
        console.log(`cmake exited with code ${code}`);

        if (code !== 0) {
          process.exit(code);
        } else {
          resolve();
        }
      });
    });
  } else {
    console.log('build folder exsists');
  }
}

async function generateExternals() {
  return new Promise((resolve, reject) => {
    const cmakeArgs = isWin ? ['--build', '.', '--config', 'Release'] : ['--build', '.'];
    const cmake = spawn('cmake', cmakeArgs, {
      cwd: path.join(process.cwd(), 'build'),
      env: process.env,
      encoding: 'utf-8',
    });

    cmake.stdout.pipe(process.stdout);
    cmake.stderr.pipe(process.stderr);

    cmake.on('close', (code) => {
      console.log(`cmake exited with code ${code}`);

      if (code !== 0) {
        reject();
      } else {
        resolve();
      }
    });
  });
}

async function showNotification(type) {
  await new Promise((resolve) => {
    if (isWin) resolve();

    let msg;
    if (type === 'success') {
      msg =
        'display notification "All externals built successfully." with title "✅ Completed" sound name "Submarine"';
    } else if (type === 'fail') {
      msg =
        'display notification "Unable to build - check console for errors." with title "🛑 Error" sound name "Basso"';
    }
    const osaArgs = ['-e', msg];
    const osa = spawn('osascript', osaArgs, {
      cwd: path.join(process.cwd(), 'build'),
      env: process.env,
      encoding: 'utf-8',
    });

    osa.on('close', (code) => {
      resolve();
    });
  });
}

async function main() {
  await checkBuildDir();
  try {
    await generateExternals();
    await showNotification('success');
  } catch (e) {
    await showNotification('fail');
  }
}

main();
