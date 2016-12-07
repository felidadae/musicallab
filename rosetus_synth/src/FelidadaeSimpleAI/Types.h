#ifndef LowPassFilter_Standalone_FMTypes_h
#define LowPassFilter_Standalone_FMTypes_h



#ifdef _WIN32
	 //
	 #ifdef _WIN64
			//
	 #endif
#elif __APPLE__
	#include "TargetConditionals.h"
	#import <AudioToolbox/AudioToolbox.h>
	typedef Float32 float_type;
	#if TARGET_IPHONE_SIMULATOR
		//
	#elif TARGET_OS_IPHONE
		// 
	#elif TARGET_OS_MAC
		//
	#else
	#   error "Unknown Apple platform"
	#endif
#elif __linux__
	#include <jack/jack.h>
	typedef jack_default_audio_sample_t float_type;
#elif __unix__ 
		//
#elif defined(_POSIX_VERSION)
		//
#else
#   error "Unknown compiler"
#endif







#endif
