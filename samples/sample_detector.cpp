//#include "class_timer.hpp"
//#include "class_detector.h"
//#include "dirent.h"
#include "detector.h"

//#include <memory>
//#include <thread>


int main()
{
	init("../configs/yolov5x.cfg", "../configs/x_best.weights");
	//detect("../test/1.jpg");
}


/*
#define INPUT_DIR "../test"
#define OUTPUT_DIR "../result"

int read_files_in_dir(const char *p_dir_name, std::vector<std::string> &file_names) {
    DIR *p_dir = opendir(p_dir_name);
    if (p_dir == nullptr) {
        return -1;
    }

    struct dirent* p_file = nullptr;
    while ((p_file = readdir(p_dir)) != nullptr) {
        if (strcmp(p_file->d_name, ".") != 0 &&
            strcmp(p_file->d_name, "..") != 0) {
            //std::string cur_file_name(p_dir_name);
            //cur_file_name += "/";
            //cur_file_name += p_file->d_name;
            std::string cur_file_name(p_file->d_name);
            file_names.push_back(cur_file_name);
        }
    }

    closedir(p_dir);
    return 0;
}

int main()
{
	Config config_v5;
	config_v5.net_type = YOLOV5;
	config_v5.detect_thresh = 0.25;
	config_v5.file_model_cfg = "../configs/yolov5x.cfg";
	config_v5.file_model_weights = "../configs/yolov5-3.0/yolov5s.weights";
	config_v5.inference_precison = FP32;

	std::unique_ptr<Detector> detector(new Detector());
	detector->init(config_v5);
	
	std::vector<std::string> file_names;
	if (read_files_in_dir(INPUT_DIR, file_names) < 0) {
		std::cout << "read files in dir failed." << std::endl;
		return -1;
	}
	
	std::vector<BatchResult> batch_res;
	Timer timer;
	for (int f = 0; f < (int)file_names.size(); f++)
	{
		//prepare batch data
		std::vector<cv::Mat> batch_img;
		cv::Mat image0 = cv::imread(std::string(INPUT_DIR + file_names[f]));
		cv::Mat temp0 = image0.clone();
		batch_img.push_back(temp0);
//		batch_img.push_back(temp1);

		//detect
		timer.reset();
		detector->detect(batch_img, batch_res);
		timer.out("detect");

		//disp
		for (int i=0;i<batch_img.size();++i)
		{
			for (const auto &r : batch_res[i])
			{
				std::cout <<"batch "<<i<< " id:" << r.id << " prob:" << r.prob << " rect:" << r.rect << std::endl;
				cv::rectangle(batch_img[i], r.rect, cv::Scalar(255, 0, 0), 2);
				std::stringstream stream;
				stream << std::fixed << std::setprecision(2) << "id:" << r.id << "  score:" << r.prob;
				cv::putText(batch_img[i], stream.str(), cv::Point(r.rect.x, r.rect.y - 5), 0, 0.5, cv::Scalar(0, 0, 255), 2);
			}
			cv::imwrite(OUTPUT_DIR + file_names[f], batch_img[i]);
		}
	}
}
*/