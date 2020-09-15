const binding = require('b64u-fast');

const input = "Hello, World!";

const encoded = binding.encode(input);
console.log(encoded);

const decoded = binding.decode(encoded);
console.log(decoded);