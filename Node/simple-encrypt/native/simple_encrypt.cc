#include <napi.h>
#include <dlfcn.h>
#include <cstring>

typedef char* (*encrypt_fn)(char*, char*, char*);
typedef char* (*decrypt_fn)(char*, char*, char*);
typedef void (*freeme_fn)(void*);

static void* libHandle = nullptr;
static encrypt_fn encryptMessage = nullptr;
static decrypt_fn decryptMessage = nullptr;
static freeme_fn freeme = nullptr;

void LoadLibraryOrThrow(const Napi::Env& env) {
  if (libHandle) return;

  // Load bundled library (relative to .node file)
  libHandle = dlopen("../native/libs/libSimpleEncrypt.so", RTLD_LAZY);
  if (!libHandle) {
    Napi::Error::New(env, dlerror()).ThrowAsJavaScriptException();
    return;
  }

  encryptMessage = (encrypt_fn)dlsym(libHandle, "encryptMessage");
  decryptMessage = (decrypt_fn)dlsym(libHandle, "decryptMessage");
  freeme = (freeme_fn)dlsym(libHandle, "freeme");

  if (!encryptMessage || !decryptMessage || !freeme) {
    Napi::Error::New(env, "Failed to load SimpleEncrypt symbols")
      .ThrowAsJavaScriptException();
  }
}

Napi::Value Encrypt(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  LoadLibraryOrThrow(env);

  auto text = info[0].As<Napi::Buffer<char>>();
  auto key  = info[1].As<Napi::Buffer<char>>();
  auto iv   = info[2].As<Napi::Buffer<char>>();

  char* out = encryptMessage(text.Data(), key.Data(), iv.Data());
  auto result = Napi::Buffer<char>::Copy(env, out, strlen(out));
  freeme(out);

  return result;
}

Napi::Value Decrypt(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  LoadLibraryOrThrow(env);

  auto cipher = info[0].As<Napi::Buffer<char>>();
  auto key    = info[1].As<Napi::Buffer<char>>();
  auto iv     = info[2].As<Napi::Buffer<char>>();

  char* out = decryptMessage(cipher.Data(), key.Data(), iv.Data());
  auto result = Napi::Buffer<char>::Copy(env, out, strlen(out));
  freeme(out);

  return result;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("encrypt", Napi::Function::New(env, Encrypt));
  exports.Set("decrypt", Napi::Function::New(env, Decrypt));
  return exports;
}

NODE_API_MODULE(simple_encrypt, Init)
