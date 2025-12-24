/**
 * SimpleEncrypt – Node.js bindings
 * System dependency: libSimpleEncrypt.so
 */

export function encrypt(
    plainText: Buffer | string,
    key: Buffer | string,
    iv: Buffer | string
  ): Buffer;
  
export function decrypt(
    cipherText: Buffer | string,
    key: Buffer | string,
    iv: Buffer | string
  ): Buffer;