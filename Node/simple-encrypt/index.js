const addon = require('bindings')('simple_encrypt');

module.exports = {
  encrypt(text, key, iv) {
    return addon.encrypt(
      Buffer.from(text),
      Buffer.from(key),
      Buffer.from(iv)
    );
  },

  decrypt(cipher, key, iv) {
    return addon.decrypt(
      Buffer.from(cipher),
      Buffer.from(key),
      Buffer.from(iv)
    );
  }
};
