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


// ������ ��� ���� ����
Mat get_lowpassFilter(Size size, int radius)
{
	Point center = size / 2;
	Mat filter(size, CV_32FC2, Vec2f(0, 0));
	circle(filter, center, radius, Vec2f(1, 1), -1);
	return filter;
}

// ������ ��� ���� ����
Mat get_highpassFilter(Size size, int radius)
{
	Point center = (size / 2);
	Mat filter(size, CV_32FC2, Vec2f(1, 1));
	circle(filter, center, radius, Vec2f(0, 0), -1);
	return filter;
}

void FFT(Mat image, Mat& dft_coef, Mat& dft_img)
{
	Mat complex_img;
	Mat pad_img = zeropadding(image); //�� ����
	Mat tmp[] = { pad_img, Mat::zeros(pad_img.size(), pad_img.type()) };
	merge(tmp, 2, complex_img); // ���� ��� ����
	dft(complex_img, dft_coef, 0); // fft ����
	shuffling(dft_coef, dft_coef); // ���ø�
	log_mag(dft_coef, dft_img); // ���ļ� ����Ʈ�� ����
}

Mat IFFT(Mat dft_coef, Size size)
{
	Mat idft_coef, idft_img[2];
	shuffling(dft_coef, dft_coef);
	dft(dft_coef, idft_coef, DFT_INVERSE + DFT_SCALE);
	split(idft_coef, idft_img);


	Rect img_rect(Point(0, 0), size);
	idft_img[0](img_rect).convertTo(idft_img[0], CV_8U);
	return idft_img[0];
}

int main()
{
	Mat image = imread("C:/����/Ű.png", 0);
	CV_Assert(image.data);
	Mat dft_coef, dft_img, low_dft, high_dft, filtered_mat1, filtered_mat2;

	FFT(image, dft_coef, dft_img);
	Mat low_filter = get_lowpassFilter(dft_coef.size(), 50);
	Mat high_filter = get_highpassFilter(dft_coef.size(), 20);

	multiply(dft_coef, low_filter, filtered_mat1);	//���Ұ� ����
	multiply(dft_coef, high_filter, filtered_mat2);	//���Ұ� ����
	log_mag(filtered_mat1, low_dft);	//���ļ� ����Ʈ��
	log_mag(filtered_mat2, high_dft);

	imshow("image", image);
	imshow("dft_img", dft_img);
	imshow("lowpassed_dft", low_dft);	// ���͵� ����Ʈ�� ����
	imshow("highpassed_dft", high_dft);
	imshow("lowpassed_img", IFFT(filtered_mat1, image.size()));		// Ǫ���� ȭ�� ����
	imshow("highpassed_img", IFFT(filtered_mat2,image.size()));	//Ǫ���� ȯ�� ����
	waitKey();
	return 0;
}