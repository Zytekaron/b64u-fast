#include <napi.h>

#include "base64.h"

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

    bool padding = false;

    if (info.Length() > 1) {
        padding = info[1].As<Napi::Boolean>();
    }

    Napi::String input = info[0].ToString();
    std::string data = input.Utf8Value();

    std::string encoded = base64::encode(data, padding);
    return Napi::String::New(env, encoded);
}

Napi::Value DecodeWrapped(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1) {
        Napi::TypeError::New(env, "Expected 1 argument for function call").ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "Expected ").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::String input = info[0].ToString();
    std::string data = input.Utf8Value();

    std::string decoded = base64::decode(data);
    return Napi::String::New(env, decoded);
}

Napi::Value hello(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::String::New(env, "Hello!");
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("encode", Napi::Function::New<EncodeWrapped>(env));
    exports.Set("decode", Napi::Function::New<DecodeWrapped>(env));
    return exports;
}

NODE_API_MODULE(addon, Init)

//std::string hello() {
//    return "Hello World";
//}
//
//Napi::String HelloWrapped(const Napi::CallbackInfo &info) {
//    Napi::Env env = info.Env();
//    return Napi::String::New(env, hello());
//}
