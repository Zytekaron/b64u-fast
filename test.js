const b64u = require('./build/Release/b64u-fast').encode;

const input = "Hello, World!";

const encoded = b64u(input);
console.log(encoded);
const decoded = new Buffer(encoded, 'base64').toString();
console.log('Success:', input === decoded);


const b64u_old = require('b64u');

const { randomString } = require('jvar/utility');
const text = randomString(2 ** 16, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890");

const tests = 10000;
const fastAverage = getRunTime(b64u,     tests, text);
const b64uAverage = getRunTime(b64u_old, tests, text);

console.log('b64u      :', b64uAverage);
console.log('b64u-fast :', fastAverage);



function getRunTime(encoder, tests, text) {
    const start = Date.now();
    for (let i = 0; i < tests; i++) {
        encoder(text);
    }
    return Date.now() - start;
}