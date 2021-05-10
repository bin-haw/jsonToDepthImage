#include <iostream>
#include <opencv2/opencv.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>

using json = nlohmann::json;
namespace fs = std::filesystem;

const int depth_width = 256;
const int depth_height = 192;

int main() {
    int processed = 0;
    for (const auto &item : fs::directory_iterator("/home/lbin/Documents/Datasets/test3/2021_04_16_15_14_48/json/json")) {
        if (!item.is_directory()) {
            std::ifstream ifs(item.path());
            json js_parser = json::parse(ifs);

            cv::Mat depth = cv::Mat::zeros(depth_height, depth_width, CV_16UC1);
            for (int i = 0; i < depth.rows; ++i) {
                for (int j = 0; j < depth.cols; ++j) {
                    depth.at<unsigned short>(i, j)=static_cast<unsigned short>(js_parser["depthMap"][j][i].get<float>()*pow(10,3));
                }
            }
            std::string path = item.path();
            auto file_name_start = path.rfind("/");
            auto file_name_end = path.rfind(".");
            auto file_name = path.substr(file_name_start + 1, file_name_end - file_name_start-1);
            cv::imwrite("./"+file_name + ".png", depth);
            processed++;
            std::cout << "\r" << processed;

//            cv::Mat depth_cvt = cv::Mat::zeros(depth.rows, depth.cols, CV_8UC1);
//            double min, max;
//            cv::minMaxLoc(depth, &min, &max);
//            for (int i = 0; i < depth.rows; ++i) {
//                for (int j = 0; j < depth.cols; ++j) {
//                    depth_cvt.at<uchar>(i, j) = static_cast<uchar>((depth.at<unsigned short>(i, j) - min) *
//                                                                   (1 / (float) (max - min)) * 256);
//                }
//            }
//            cv::Mat depth_pseudo;
//            cv::applyColorMap(depth_cvt, depth_pseudo, cv::COLORMAP_COOL);
//            cv::imshow("pseudo", depth_pseudo);
//            cv::waitKey(0);
        }
    }
    return 0;
}
