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

  wasi.start(instance);
})();
