#include <opencv2/highgui.hpp>
using namespace cv;

int main()
{
	Mat src = imread("C:/강의/우산.jpg");
	imshow("Before", src);

	src = src - Scalar(0, 255, 0);

	imshow("After", src);
	
	waitKey(0);
	destroyAllWindows();


}