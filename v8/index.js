'use strict';
// require nodejs 13 or above
// nodejs --experimental-wasi-unstable-preview1 --experimental-wasm-bigint [wasm file] [args...]
const fs = require('fs');
const { WASI } = require('wasi');
const wasi = new WASI({
  args: process.argv.slice(2),
  env: process.env,
  preopens: {}
});
const importObject = { wasi_snapshot_preview1: wasi.wasiImport };

(async () => {
  const wasm = await WebAssembly.compile(fs.readFileSync(process.argv[2]));
  const instance = await WebAssembly.instantiate(wasm, importObject);

  const start = process.hrtime();
  wasi.start(instance);
  let diff = process.hrtime(start);
  let str = ("00" + (diff[0] % 60).toString()).slice(-2) + "." + ("000000000" + diff[1].toString()).slice(-9);
  diff[0] = diff[0] / 60 >> 0;
  if (diff[0] >= 0) {
    str = ("00" + (diff[0] % 60).toString()).slice(-2) + ":" + str;
    diff[0] = diff[0] / 60 >> 0;
    if (diff[0] >= 0) {
      str = diff[0].toString() + ":" + str;
    }
  }
  console.warn(`Runtime: ${str}`);
})();
