#pragma once
#include "class_timer.hpp"
#include "class_detector.h"
#include "dirent.h"
//#include <string>

#define C_SHARP_MAX_OBJECTS 20

struct bbox_t {
	unsigned int x, y, w, h;       // (x,y) - top-left corner, (w, h) - width & height of bounded box
	float prob;                    // confidence - probability that the object was found correctly
	unsigned int obj_id;           // class of object - from range [0, classes-1]
	unsigned int track_id;
	unsigned int frames_counter;
};

struct bbox_t_container {
	bbox_t candidates[C_SHARP_MAX_OBJECTS];
};


extern "C" __declspec(dllexport) int init(const char* model_cfg, const char* model_weights);
extern "C" __declspec(dllexport) int detect_image(const char* file_name, bbox_t_container &container);
extern "C" __declspec(dllexport) int detect_mat(const uint8_t* data, const size_t data_length, bbox_t_container &container);
extern "C" __declspec(dllexport) int dispose();
