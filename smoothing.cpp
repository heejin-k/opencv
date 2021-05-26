#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcimage = imread("C:/∞≠¿«/≈‰≥¢.jpg", IMREAD_GRAYSCALE);
	imshow("srcimage", srcimage);

	int border = 3; 
	Size ksize(border * 2 + 1, border*2 + 1);

	Mat dstimage1;
	boxFilter(srcimage, dstimage1, -1, ksize);
	imshow("boxFilter", dstimage1);

	Mat dstimage2;
	int d = ksize.width;
	double sigmaColor = 20.0;
	double sigmaSpace = 100.0;
	bilateralFilter(srcimage, dstimage2, d, sigmaColor, sigmaSpace);
	imshow("kernel size(7,7)", dstimage2);

	Mat dstimage3;
	bilateralFilter(srcimage, dstimage3, -1, sigmaColor, sigmaSpace);
	imshow("sigmaSpace", dstimage3);

	waitKey();
	return 0;

}