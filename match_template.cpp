#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("C:/강의/alphabet.jpg", IMREAD_GRAYSCALE);
	Mat tempImage = imread("C:/강의/E.jpg", IMREAD_GRAYSCALE);
	imshow("Source Image", srcImage);
	imshow("Template Image", tempImage);

	Mat dstImage;
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);

	double minVal, maxVal;
	Point minLoc, maxLoc;
	Mat result;

	// 템플릿 정합 (template matching)
	matchTemplate(srcImage, tempImage, result, TM_SQDIFF_NORMED);
	minMaxLoc(result, &minVal, NULL, &minLoc, NULL);
	rectangle(dstImage, minLoc, Point(minLoc.x + tempImage.cols, minLoc.y + tempImage.rows), Scalar(0,255,0), 2);

	imshow("dstImage", dstImage);
	waitKey();
	return 0;
}
