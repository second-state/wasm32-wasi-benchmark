const fs = require('fs');
var s = '#'.repeat(128*1024);
fs.writeFileSync("tmp.txt", s);
