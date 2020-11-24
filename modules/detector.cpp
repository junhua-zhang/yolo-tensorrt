#include "detector.h"

std::unique_ptr<Detector> detector(new Detector());

int init(const char* model_cfg, const char* model_weights)
{
	Config config_v5;
	config_v5.net_type = YOLOV5;
	config_v5.detect_thresh = 0.25;
	config_v5.file_model_cfg = model_cfg;
	config_v5.file_model_weights = model_weights;
	config_v5.inference_precison = FP32;
	
	detector->init(config_v5);
	return 1;
}

int detect_image(const char* file_name, bbox_t_container &container)
{
	std::vector<BatchResult> batch_res;
	std::vector<bbox_t> return_res;
	//Timer timer;
	
	//prepare batch data
	std::vector<cv::Mat> batch_img;
	cv::Mat image = cv::imread(file_name);
	batch_img.push_back(image);

	//detect
	//timer.reset();
	detector->detect(batch_img, batch_res);
	//timer.out("detect");
	
	int res_len = batch_res[0].size();
	for (size_t i = 0; i < res_len && i < C_SHARP_MAX_OBJECTS; ++i)
	{
		auto r = batch_res[0][i];
		//std::cout << " id:" << r.id << " prob:" << r.prob << " rect:" << r.rect << std::endl;
		bbox_t res_i;
		res_i.x = r.rect.x> 0 ? r.rect.x : 0;
		res_i.y = r.rect.y> 0 ? r.rect.y : 0;
		res_i.w = r.rect.width ? r.rect.width : 0;
		res_i.h = r.rect.height ? r.rect.height : 0;
		res_i.prob = r.prob;
		res_i.obj_id = r.id;

		container.candidates[i] = res_i;
	}

	return res_len;
}


int detect_mat(const uint8_t* data, const size_t data_length, bbox_t_container &container)
{
	std::vector<char> vdata(data, data + data_length);
	cv::Mat image = imdecode(cv::Mat(vdata), 1);
	std::vector<cv::Mat> batch_img;
	batch_img.push_back(image);

	std::vector<BatchResult> batch_res;
	
	detector->detect(batch_img, batch_res);

	int res_len = batch_res[0].size();

	for (size_t i = 0; i < res_len && i < C_SHARP_MAX_OBJECTS; ++i)
	{
		auto r = batch_res[0][i];
		//std::cout << " id:" << r.id << " prob:" << r.prob << " rect:" << r.rect << std::endl;
		bbox_t res_i;
		res_i.x = r.rect.x> 0 ? r.rect.x : 0;
		res_i.y = r.rect.y> 0 ? r.rect.y : 0;
		res_i.w = r.rect.width ? r.rect.width : 0;
		res_i.h = r.rect.height ? r.rect.height : 0;
		res_i.prob = r.prob;
		res_i.obj_id = r.id;

		container.candidates[i] = res_i;
	}

	return res_len;
}


int dispose() 
{
	detector.reset();
	return 1;
}
