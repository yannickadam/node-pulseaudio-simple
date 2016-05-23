#include <node.h>
#include <pulse/simple.h>
#include <stdio.h>
#include <fcntl.h>

using namespace v8;

void Init(const FunctionCallbackInfo<Value>& args) {
	  Isolate* isolate = Isolate::GetCurrent();
	  HandleScope scope(isolate);

	pa_sample_spec	ss;
	ss.format = PA_SAMPLE_S16LE;
	ss.channels = 2;	
	ss.rate = 44100;

	pa_simple *s;
	int error;

	s = pa_simple_new(NULL, "npas", PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error);

	int fd = open("/home/root/da.wav", O_RDONLY);




	args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

void init(Handle<Object> exports) {
	  NODE_SET_METHOD(exports, "Init", Init);
}

NODE_MODULE(npas, init)
