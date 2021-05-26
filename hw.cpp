#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
string title = "트랙바 이벤트";
Mat image;
void onChange(int value, void* userdata)
{
	int add_value = value - 130;
	cout << "추가 화소값 " << add_value << endl;
	Mat tmp = image + Scalar(add_value, add_value, add_value);
	imshow(title, tmp);
}int main()
{
	int value = 130;
	image = Mat(imread("C:/강의/dog2.jpg"));
	namedWindow(title, WINDOW_AUTOSIZE);
	createTrackbar("밝기값", title, &value, 255, onChange);
	imshow(title, image);
	waitKey(0);
	return 0;
}
