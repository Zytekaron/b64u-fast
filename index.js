const { encode } = require('./build/Release/b64u-fast');

/**
 * Encode a string or buffer into URL-Safe Base64
 * @param {string|buffer} data The data to encode
 * @returns {string} The URL-Safe Base64 encoded string
 */
module.exports = encode;