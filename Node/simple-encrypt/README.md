# simple-encrypt

Node.js N-API bindings for the **SimpleEncrypt AES-256** library.

This package is a **thin wrapper** around the **shipped native library** (`libSimpleEncrypt.so`) included in the npm package.  
Users do **not** need to manually install anything — the `.so` file is included under `native/libs/`.

---

## Installation

```bash
npm install @telenetix/simpleencrypt
```
Works out of the box on Linux. Windows (.dll) and Mac (.dylib) support can be added similarly.

---

### You can find the @telenetix/simple-encrypt package in the following folder structure:

@telenetix/simpleencrypt/<br>
├── binding.gyp<br>
├── index.d.ts<br>
├── index.js<br>
├── native<br>
│   ├── libs<br>
│   │   └── libSimpleEncrypt.so<br>
│   └── simple_encrypt.cc<br>
├── package.json<br>
└── README.md<br>

## Usage
```
const { encrypt, decrypt } = require('@telenetix/simpleencrypt');

const iv = '171A065A7675A09AECEC118DBC008A822A041FC2EBF2B3E4CF7A4C966E5D5897';
const key = '2B5442AD8739992F';
const text = 'TEXT';

const cipher = encrypt(text, key, iv);
const decrypted = decrypt(cipher, key, iv);

console.log(decrypted.toString());
```
**Output:** TEXT

### Test after install

Run the following command in your project root:
```
node -e "
const { encrypt, decrypt } = require('@telenetix/simpleencrypt');
const iv = '171A065A7675A09AECEC118DBC008A822A041FC2EBF2B3E4CF7A4C966E5D5897';
const key = '2B5442AD8739992F';
const text = 'TEXT';
console.log(decrypt(encrypt(text, key, iv), key, iv).toString());
"
```


### Expected output:

```TEXT```


## Notes

- The .so library is shipped in **native/libs/libSimpleEncrypt.so** and loaded automatically.

##### The core cryptographic implementation is authored by Shreyas Nayak; this package is a Node.js N-API wrapper over the original C library.

##### @telenetix/simple-encrypt is developed and published by Prathik P Telenetix. Design for Interlink Network Systems,Inc.