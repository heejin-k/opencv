#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat gray_img = imread("C:/강의/dog2.jpg", IMREAD_GRAYSCALE);
	if (!gray_img.data)
		return -1;
	imshow("명도영상", gray_img);

	Mat dst_img(gray_img.rows, gray_img.cols, gray_img.type());
	Mat kernel = (Mat_<double>(5, 5)
		<< 1. / 25., 1. / 25., 1. / 25., 1. / 25., 1. / 25.,
			1. / 25., 1. / 25., 1. / 25., 1. / 25., 1. / 25.,
			1. / 25., 1. / 25., 1. / 25., 1. / 25., 1. / 25.,
			1. / 25., 1. / 25., 1. / 25., 1. / 25., 1. / 25.,
			1. / 25., 1. / 25., 1. / 25., 1. / 25., 1. / 25. );
	filter2D(gray_img, dst_img, -1, kernel);

	imshow("결과영상", dst_img);
	waitKey(0);
	destroyAllWindows();
	}



