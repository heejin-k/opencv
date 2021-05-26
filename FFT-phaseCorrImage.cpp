// ----------------------------------------------------------------------------------------
// 실습: 위상상관을 이용한 매칭
// ----------------------------------------------------------------------------------------
#include <stdlib.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

double Phase_Correlation(const Mat &mat_A, const Mat &mat_B, Point *pMaxLoc, bool bShow)
{
	// 자료형 변환: CV_8UC1 --> CV_32FC1
	Mat mat_floatA, mat_floatB;
	mat_A.convertTo(mat_floatA, CV_32F);	// CV_8UC1 --> CV_32FC1
	mat_B.convertTo(mat_floatB, CV_32F);	// CV_8UC1 --> CV_32FC1

	int	rows = mat_A.rows + mat_B.rows - 1;
	int	cols = mat_A.cols + mat_B.cols - 1;

	// step 1:  Calculate DFT_A of the input mat_A
	Mat planes[] = {
		Mat::zeros(rows, cols, CV_32F),
		Mat::zeros(rows, cols, CV_32F)
	};
	Mat mat_roiA(planes[0], Rect(0, 0, mat_floatA.cols, mat_floatA.rows));
	mat_floatA.copyTo(mat_roiA);
	Mat imgComplex_A;
	merge(planes, 2, imgComplex_A);		// 복소평면(실수부+허수부) 영상
	dft(imgComplex_A, imgComplex_A);	// 2D DFT

	//step 2:  Calculate DFT_B of the input mat_T
	planes[0] = Mat::zeros(rows, cols, CV_32F);
	Mat mat_roiB(planes[0], Rect(0, 0, mat_floatB.cols, mat_floatB.rows));
	mat_floatB.copyTo(mat_roiB);
	Mat imgComplex_B;
	merge(planes, 2, imgComplex_B);		// 복소평면(실수부+허수부) 영상
	dft(imgComplex_B, imgComplex_B);	// 2D DFT

	//step 3: DFT_A = DFT_A * CONJ(DFT_B)
	mulSpectrums(imgComplex_A, imgComplex_B, imgComplex_A, DFT_ROWS, true);		
	  // if TRUE, then DFT_A = DFT_A * CONJ(DFT_B) = 상관	
  	  // if FALSE, then DFT_A = DFT_A * DFT_B	 = 회선	

	//step 4:Normalize by spectrum (pDFT_A* conj(DFT_B))/(| DFT_A * conj(DFT_B) |)
	split(imgComplex_A, planes);

	// Calculate spectrum
	Mat mag;
	magnitude(planes[0], planes[1], mag);	// magnitude 크기 계산 (아래 주석처리된 코드 참조)
	divide(planes[0], mag, planes[0]);
	divide(planes[1], mag, planes[1]);
	merge(planes, 2, imgComplex_A);

	//step 5 : A = IDFT( (pDFT_A* conj(DFT_B))/(| DFT_A * conj(DFT_B) |) )	
	dft(imgComplex_A, imgComplex_A, DFT_INVERSE + DFT_SCALE);		// 2D IDFT
	split(imgComplex_A, planes);

	double   min_val, max_val;
	minMaxLoc(planes[0], &min_val, &max_val, NULL, pMaxLoc);
	return max_val;
}

void main()
{
	Mat src_img = imread("C:/강의/test_car/06.jpg", IMREAD_GRAYSCALE);
	Mat tpl_img = imread("C:/강의/5.png", IMREAD_GRAYSCALE);
	imshow("srcImage", src_img);
	imshow("tplImage", tpl_img);
	waitKey(0);

	Point max_loc;
	double phaseCorr = Phase_Correlation(src_img, tpl_img, &max_loc, 1);
	printf("phaseCorr=%f\n", phaseCorr);
	printf("max_loc = (%d, %d)\n", max_loc.x, max_loc.y);

	// 매칭 영역 디스플레이
	Mat dst_img(src_img.rows, src_img.cols, CV_8UC3);
	cvtColor(src_img, dst_img, COLOR_GRAY2BGR);
 	rectangle(dst_img, max_loc, Point(max_loc.x + tpl_img.cols, max_loc.y + tpl_img.rows), CV_RGB(255,0,0));
	imshow("dstImage", dst_img);

	waitKey(0);
	destroyAllWindows();
}
