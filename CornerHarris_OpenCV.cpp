// Harris 코너점
#include <stdlib.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


#define MAX_CORNERS 1000		// 코너점의 최대 개수

void main()
{
	Mat  src_img = imread("C:/강의/img/코너검출.png");
	Mat gray_img(src_img.rows, src_img.cols, CV_8UC1);
	cvtColor(src_img, gray_img, COLOR_BGR2GRAY);
	
	Mat harris_response(gray_img.rows, gray_img.cols, CV_32FC1);

	int block_size = 5;
	int aperture_size = 1;
	double k=0.04;

	cornerHarris(gray_img, harris_response, block_size, aperture_size, k);
	threshold(harris_response, harris_response, 0.01, 0, THRESH_TOZERO);

// find local maxima
	double    fValue;
	double    maxValue;
	int       x, y;
	int       m, n;
	bool      bChange;
	int       nSize = 3; // Window half size for finding local maxima
	int       nCornerCount = 0;

	for(y= nSize; y< harris_response.rows-nSize; y++) {
		for(x= nSize; x< harris_response.cols-nSize; x++) {
			bChange = false;
			maxValue = harris_response.at<float>(y, x);
			for(n= y-nSize;  n<=y+nSize; n++) {
				for(m= x-nSize; m<=x+nSize; m++) {
					if( m==x && n == y)
						continue;
					fValue = harris_response.at<float>(n, m);
					if( fValue >= maxValue)	{		// 비최대값 억제
						bChange = true;
						break;
					}
				}
			}
			if(!bChange) {
				nCornerCount++;
				printf("harris_response ( %d, %d ) = %f\n", x, y, maxValue );
				circle(src_img, Point(x, y), 5, CV_RGB(255, 0, 0), 2);
			} 		
		}
	}
	printf("nCornerCount=%d\n", nCornerCount);
	imshow("코너 검출 영상", src_img);
	waitKey(0); 
	destroyAllWindows();
}
