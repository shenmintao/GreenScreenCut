#pragma once
#include <opencv2/opencv.hpp>

void expansionOfKnownRegions(cv::InputArray img, cv::InputOutputArray trimap, int niter = 9);
void globalMatting(cv::InputArray image, cv::InputArray trimap, cv::OutputArray foreground, cv::OutputArray alpha, cv::OutputArray conf = cv::noArray());