#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void main()
{
	Mat gray_img = imread("C:/강의/캡처.png", IMREAD_GRAYSCALE);
	imshow("명도영상", gray_img);

	Mat bin_img;
	threshold(gray_img, bin_img, 128, 255, THRESH_BINARY);
	//imshow("이진영상", bin_img);

	Mat dst_img(bin_img.rows, bin_img.cols, CV_8UC1);
	Mat mask = (Mat_<uchar>(3, 3) << //mask
		0, 0, 0,
		255, 255, 255,
		0, 0, 0);
	erode(gray_img, dst_img, mask, Point(-1, -1), 5);
	imshow("침식영상", dst_img);

	dilate(dst_img, dst_img, mask, Point(-1, 1), 5);
	imshow("팽창영상", dst_img);

	waitKey(0);
	destroyAllWindows();
}