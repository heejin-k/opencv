#include <opencv2/highgui.hpp>
using namespace cv;

int main()
{
	Mat src = imread("C:/����/���.jpg");
	imshow("Before", src);

	src = src - Scalar(0, 255, 0);

	imshow("After", src);
	
	waitKey(0);
	destroyAllWindows();


}