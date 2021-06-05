#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void main()
{
	//Mat src_img = imread("../../Images/당구공.jpg");
	//Mat src_img = imread("../../Images/add1.jpg");
	//Mat src_img = imread("../../Images/logo.jpg");
	Mat src_img = imread("C:/강의/img/당구공.png");
	imshow("원본 영상", src_img);

	Mat gray_img;
	cvtColor(src_img, gray_img, COLOR_BGR2GRAY);
	imshow("명도 영상", gray_img);

	medianBlur(gray_img, gray_img, 5);
	
	vector<Vec3f> circles;
	HoughCircles(gray_img, circles, HOUGH_GRADIENT, 1,
		gray_img.rows / 16, 100, 50, 30, 200);
	//imshow("circles image", circles);
	
	for (size_t i = 0; i < circles.size(); i++)	{
		Vec3i c = circles[i];
		circle(src_img, Point(c[0], c[1]), c[2], Scalar(0, 0, 255), 3, LINE_AA);
		circle(src_img, Point(c[0], c[1]), 2, Scalar(0, 255, 0), 3, LINE_AA);
	}
	imshow("detected circles", src_img);
	waitKey(0);
	destroyAllWindows();
}

