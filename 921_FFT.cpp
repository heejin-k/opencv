#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void log_mag(Mat complex_mat, Mat& dst)
{
	Mat planes[2];
	split(complex_mat, planes);
	magnitude(planes[0], planes[1], dst);
	log(dst + 1, dst);
	normalize(dst, dst, 0, 255, NORM_MINMAX);
	dst.convertTo(dst, CV_8U);
}

void shuffling(Mat mag_img, Mat& dst)
{
	int cx = mag_img.cols / 2;
	int cy = mag_img.rows / 2;
	Rect q1(cx, 0, cx, cy);
	Rect q2(0, 0, cx, cy);
	Rect q3(0, cy, cx, cy);
	Rect q4(cx, cy, cx, cy);

	dst = Mat(mag_img.size(), mag_img.type());
	mag_img(q1).copyTo(dst(q3));
	mag_img(q3).copyTo(dst(q1));
	mag_img(q2).copyTo(dst(q4));
	mag_img(q4).copyTo(dst(q2));
}

Mat zeropadding(Mat img)
{
	int m = 1 << (int)ceil(log2(img.rows));
	int n = 1 << (int)ceil(log2(img.cols));
	Mat dst(m, n, img.type(), Scalar(0));

	Rect rect(Point(0, 0), img.size());
	img.copyTo(dst(rect));
	dst.convertTo(dst, CV_32F);
	return dst;
}


int main()
{
	Mat image = imread("C:/강의/키.png", 0);
	CV_Assert(image.data);

	Mat complex_img, idft_img, img_tmp[2];
	Mat dft_coef, dft_img, shuffling_img;

	Mat pad_img = zeropadding(image);
	Mat tmp[] = { pad_img, Mat::zeros(pad_img.size(), pad_img.type()) };
	merge(tmp, 2, complex_img);

	double t = (double)getTickCount(); // 시간 계산 함수 
	dft(complex_img, dft_coef);
	log_mag(dft_coef, dft_img);
	shuffling(dft_img, shuffling_img);

	dft(dft_coef, idft_img, DFT_INVERSE + DFT_SCALE);
	split(idft_img, img_tmp);
	img_tmp[0].convertTo(img_tmp[0], CV_8U);
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "Times passed in seconds: " << t << endl;

	imshow("image", image);
	imshow("shuffling_img", shuffling_img);
	imshow("idft_img", img_tmp[0]);
	waitKey();
	return 0;
}