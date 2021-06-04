#include <stdlib.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat src_img = imread("C:/강의/dog2.jpg");
	if (!src_img.data)
		return -1;
	imshow("컬러영상", src_img);
	waitKey(0);

	// 컬러영상을 채널별로 분리
	vector<Mat> src_rgbChs;
	split(src_img, src_rgbChs);

	vector<Mat> rgbChannels;
	Mat kernel = (Mat_<double>(3, 3)
		<< 0, -1, 0, -1, 5, -1, 0, -1, 0);
	
	// RGB 채널별 필터링
	Mat compB;
	filter2D(src_rgbChs[0], compB, CV_32F, kernel);
	compB.convertTo(compB, CV_8U);
	rgbChannels.push_back(compB);


	Mat compG;
	filter2D(src_rgbChs[1], compG, CV_32F, kernel);
	compG.convertTo(compG, CV_8U);
	rgbChannels.push_back(compG);

	Mat compR;
	filter2D(src_rgbChs[2], compR, CV_32F, kernel);
	compR.convertTo(compR, CV_8U);
	rgbChannels.push_back(compR);

	// RGGB채널별 필터링 결과를 병합
	Mat dst_img;
	merge(rgbChannels, dst_img);
	imshow("결과영상", dst_img);
	waitKey(0);
	destroyAllWindows();
}

