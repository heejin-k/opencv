#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image = imread("C:/����/dog2.jpg");
string title1 = "â ũ�⺯��1 - AUTOSIZE";
string title2 = "â ũ�⺯��2 - NORMAL";
namedWindow(title1, WINDOW_AUTOSIZE);
namedWindow(title2, WINDOW_NORMAL);
resizeWindow(title1, 500, 200);
resizeWindow(title2, 500, 200);
imshow(title1, image);
imshow(title2, image);
waitKey();
return 0;
}