#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat in_image, out_image;
	in_image = imread("C:/강의/우산.jpg", 0);

	namedWindow("in_image");
	imshow("in_image", in_image);
	int ddepth = CV_8U;

	in_image.copyTo(out_image);
	Laplacian(in_image, out_image, ddepth, 1, 1);
	threshold(out_image, out_image, 25, 255, THRESH_BINARY);

	namedWindow("Laplacian");
	imshow("Laplacian", out_image);

	waitKey(0);
	return 0;
}
