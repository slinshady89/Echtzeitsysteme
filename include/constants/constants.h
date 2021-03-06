//
// Created by frederic on 31.01.19.
//

#ifndef PROJECT_CONSTANTS_H
#define PROJECT_CONSTANTS_H

#include <opencv2/opencv.hpp>
#include <lane_detection/CameraCalibration.hpp>

namespace constants {
    /* webcam configuration */
    const int WEBCAM_WIDTH = 800;
    const int WEBCAM_HEIGHT = 480;

    namespace calibrations {
        namespace myphoto2 {
            const std::string MY_PHOTO_2 = "my_photo-2.jpg";
            const int SRC_WIDTH = 1920;
            const int SRC_HEIGHT = 1080;
            const cv::Vec2i BOTTOM_LEFT = cv::Vec2i(549,799);
            const cv::Vec2i BOTTOM_RIGHT = cv::Vec2i(1384, 786);
            const cv::Vec2i TOP_RIGHT = cv::Vec2i(1129, 490);
            const cv::Vec2i TOP_LEFT = cv::Vec2i(800,493);
            const double RECT_WIDTH =  59.0;
            const double RECT_HEIGHT = 84.0;
            const double OFFSET_ORIGIN = 20.0;
            const int TARGET_WIDTH = 180;
            const int TARGET_HEIGHT = 180;
        }
        namespace calibrationtest2 {
            const std::string RIGHT_CURVE = "2018-12-05-220033.jpg";
            const std::string LEFT_CURVE = "2018-12-05-220138.jpg";
            const std::string STRAIGHT_LEFT = "2018-12-05-220157.jpg";
            const int SRC_WIDTH = 640;
            const int SRC_HEIGHT = 480;
            const cv::Vec2i BOTTOM_LEFT = cv::Vec2i(0,366);
            const cv::Vec2i BOTTOM_RIGHT = cv::Vec2i(632,363);
            const cv::Vec2i TOP_RIGHT = cv::Vec2i(404,238);
            const cv::Vec2i TOP_LEFT = cv::Vec2i(237,237);
            const double RECT_WIDTH =  59.0;
            const double RECT_HEIGHT = 84.0;
            const double OFFSET_ORIGIN = 30.0;
            const int TARGET_WIDTH = 180;
            const int TARGET_HEIGHT = 180;
        }
        namespace calibration_02_25 {
            const int SRC_WIDTH = 1280;
            const int SRC_HEIGHT = 720;
            const cv::Vec2i BOTTOM_LEFT = cv::Vec2i(345,513);
            const cv::Vec2i BOTTOM_RIGHT = cv::Vec2i(918,521);
            const cv::Vec2i TOP_RIGHT = cv::Vec2i(747,311);
            const cv::Vec2i TOP_LEFT = cv::Vec2i(522,308);
            const double RECT_WIDTH =  59.0;
            const double RECT_HEIGHT = 84.0;
            const double OFFSET_ORIGIN = 37.0;
            const int TARGET_WIDTH = 150;
            const int TARGET_HEIGHT = 200;
            const int TARGET_PX_PER_CM = 5;
            const CameraCalibration calibration_150_200_px(
                    RECT_WIDTH, RECT_HEIGHT, OFFSET_ORIGIN,
                    TARGET_WIDTH, TARGET_HEIGHT,
                    BOTTOM_LEFT, BOTTOM_RIGHT, TOP_RIGHT, TOP_LEFT,
                    TARGET_PX_PER_CM
            );


        }
    }
}

#endif //PROJECT_CONSTANTS_H
