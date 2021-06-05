#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#define MAX_LINES 50
#define M_PI 3.141592

void Detect_Lines_By_Hough(Mat &src_img, Mat &edge_img);

void main()
{
	//Mat src_img = imread("../../Images/mkLec/line.jpg");
	//Mat src_img = imread("../../Images/mkLec/book.jpg");
	//Mat src_img = imread("../../Images/mkLec/imageTextN.jpg");
	//Mat src_img = imread("../../Images/mkLec/imageTextR.jpg");
	Mat src_img = imread("C:/강의/img/네모.jpg");
	imshow("원본 영상", src_img);

	Mat gray_img;
	cvtColor(src_img, gray_img, COLOR_BGR2GRAY);

	Mat edge_img;
	Canny(gray_img, edge_img, 30, 10);
	imshow("Canny 에지 영상", edge_img);

	Detect_Lines_By_Hough(src_img, edge_img);
	waitKey(0);
	destroyAllWindows();
}

void Detect_Lines_By_Hough(Mat &src_img, Mat &edge_img)
{
	// 직선 검출
	vector<Vec2f> lines;
	HoughLines(edge_img, lines, 1, CV_PI/180, 200);
	
	// 검출된 직선 디스플레이
	float rho, theta, a, b, x0, y0;
	Point pt1, pt2;
	for (int i=0; i < lines.size(); i++) {
		rho = lines[i][0];
		theta = lines[i][1];
	
		a = cos(theta); b = sin(theta);
		x0 = a*rho;		y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));
		line( src_img, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
	}
	imshow("Hough 직선 검출 영상", src_img);
}

