#include <node.h>
#include <node_buffer.h>
#include <pulse/simple.h>
#include <stdio.h>
#include <fcntl.h>

using namespace v8;
using namespace node;

pa_simple *s;


void Write(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  // Sound data buffer
  v8::Local<v8::Value> tt = args[0];
  char *data = node::Buffer::Data(tt.As<v8::Object>());

  // Buffer Length
  int size = (int)args[1]->NumberValue();

  pa_simple_write(s, data, size, NULL);

  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "hello world"));
}

void Init(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
  Local<Object> obj = Object::New(isolate);

  pa_sample_format_t sampleType = (pa_sample_format_t)args[0]->NumberValue();

	pa_sample_spec	ss;
	ss.format = sampleType;
	ss.channels = 2;
	ss.rate = 44100;

	int error;
	s = pa_simple_new(NULL, "npas", PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error);

  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, Write);
  Local<Function> fn = tpl->GetFunction();

  // omit this to make it anonymous
  fn->SetName(String::NewFromUtf8(isolate, "write"));
  obj->Set(String::NewFromUtf8(isolate, "write"), fn);

	args.GetReturnValue().Set(obj);
}

/*
void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Local<Object> obj = Object::New(isolate);
  obj->Set(String::NewFromUtf8(isolate, "msg"), args[0]->ToString());
}*/

void init(Handle<Object> exports, Handle<Object> module) {
	  NODE_SET_METHOD(module, "exports", Init);
}

NODE_MODULE(npas, init)
