#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int th = 10;
Mat image, gray, edge;

void onTrackbar(int, void*)
{
	Canny(gray, edge, th, th * 2, 3);

	Mat color_edge;
	image.copyTo(color_edge, edge);
	imshow("�÷� ����", color_edge);

}

int main()
{
	image = imread("C:/����/dog2.jpg", 1);
	CV_Assert(image.data);
	imshow("image", image);
	cvtColor(image, gray, COLOR_BGR2GRAY);

	namedWindow("�÷� ����", 1);
	createTrackbar("Canny th", "�÷�����", &th, 255, onTrackbar);
	onTrackbar(th, 0);

	waitKey(0);
}