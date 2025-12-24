{
  "targets": [
    {
      "target_name": "simple_encrypt",
      "sources": ["native/simple_encrypt.cc"],

      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],

      "defines": [
        "NAPI_DISABLE_CPP_EXCEPTIONS"
      ],

      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],

      "libraries": ["-ldl"]
    }
  ]
}
