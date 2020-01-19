// signals.cc
#include <nan.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

Nan::MaybeLocal<v8::Function> fn;
Nan::Callback cb;

void sigHandler(int signo) {
  Nan::HandleScope scope;
  v8::Local<v8::Value> argv[] { Nan::New<v8::Integer>(signo) };
  Nan::Call(cb.GetFunction(), Nan::GetCurrentContext()->Global(), 1, argv);
}

NAN_METHOD(Register) {
  const v8::Local<v8::Function> val = Nan::To<v8::Function>(info[0]).ToLocalChecked();
  cb.Reset(val);
  signal(SIGINT, sigHandler);
  signal(SIGTSTP, sigHandler);
  signal(SIGQUIT, sigHandler);
}

NAN_MODULE_INIT(Init) {
  NAN_EXPORT(target, Register);
}

NODE_MODULE(addon, Init)
