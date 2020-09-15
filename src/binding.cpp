#include <napi.h>

#include "include/libbase64.h"

Napi::Value EncodeWrapped(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Expected 1-2 arguments, got " + std::to_string(info.Length())).ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString() && !info[0].IsBuffer()) {
        Napi::TypeError::New(env, "Expected type string or buffer for argument 0").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::String string = info[0].ToString();

    const char *data = string.Utf8Value().c_str();
    size_t length = strlen(data);

    size_t outAlloc = 4 + length * 4 / 3;
    char *out = static_cast<char*>(malloc(outAlloc));
    size_t outLength;

    base64_encode(data, length, out, &outLength, 0);

    return Napi::String::New(env, out, outLength);
}

//Napi::Value DecodeWrapped(const Napi::CallbackInfo &info) {
//    Napi::Env env = info.Env();
//
//    if (info.Length() != 1) {
//        Napi::TypeError::New(env, "Expected 1 argument for function call").ThrowAsJavaScriptException();
//        return env.Null();
//    }
//
//    if (!info[0].IsString()) {
//        Napi::TypeError::New(env, "Expected ").ThrowAsJavaScriptException();
//        return env.Null();
//    }
//
//    Napi::String input = info[0].ToString();
//    std::string data = input.Utf8Value();
//
//    std::string decoded = base64::decode(data);
//    return Napi::String::New(env, decoded);
//}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("encode", Napi::Function::New<EncodeWrapped>(env));
//    exports.Set("decode", Napi::Function::New<DecodeWrapped>(env));
    return exports;
}

NODE_API_MODULE(addon, Init)