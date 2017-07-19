//∏Ø ¥∫Õ≈Ú’Õ≤Ÿ◊˜
#include<iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void myErode(Mat& src, Mat& dst, Mat& kenerl);
void myDilate(Mat& src, Mat& dst, Mat& kenerl);
int main()
{
	Mat img = imread("1.jpg");
	Mat sp[3] = { Mat(img),Mat(img),Mat(img) };
	split(img, sp);
	Mat kern = (Mat_<uchar>(3,3)<<
		1, 1, 1,
		1, 1, 1,
		1, 1, 1);
	for (int i=0;i<3;i++)
	{
		//myDilate(sp[i], sp[i], kern);
		myErode(sp[i], sp[i], kern);
	}
	Mat dst(img.size(), img.type());
	merge(sp, 3, dst);
	imshow("merge", dst);
	waitKey(0);
}
void myErode(Mat& src, Mat& dst, Mat& kenerl) {
	int m = kenerl.rows;
	int n = kenerl.cols;
	Mat temp(dst.size(), dst.type());//for in-place operation
	for (int r = m / 2; r < src.rows - m / 2; r++)
	{
		for (int c = n / 2; c < src.cols - n / 2; c++)
		{
			int max = 0;
			for (int kr = -m / 2; kr < m / 2 + 1; kr++)
			{
				for (int kc = -n / 2; kc < n / 2 + 1; kc++)
				{
					int value = src.at<uchar>(r + kr, c + kc)*kenerl.at<uchar>(kr + m / 2, kc + n / 2);
					if (value>max)
					{
						max = value;
					}
				}
			}
			temp.at<uchar>(r, c) = max;
		}
	}
	temp.copyTo(dst);
}
void myDilate(Mat& src, Mat& dst, Mat& kenerl) {
	int kern_rows = kenerl.rows;
	int kern_cols = kenerl.cols;
	Mat temp(dst.size(), dst.type());//for in-place operation
	for (int r = kern_rows / 2; r < src.rows - kern_rows / 2; r++)
	{
		for (int c = kern_cols / 2; c < src.cols - kern_cols / 2; c++)
		{
			int min = 255;
			for (int kr = -kern_rows / 2; kr < kern_rows / 2 + 1; kr++)
			{
				for (int kc = -kern_cols / 2; kc < kern_cols / 2 + 1; kc++)
				{
					int value = src.at<uchar>(r + kr, c + kc)*kenerl.at<uchar>(kr + kern_rows / 2, kc + kern_cols / 2);
					if (value < min)
					{
						min = value;
					}
				}
			}
			temp.at<uchar>(r, c) = min;
		}
	}
	temp.copyTo(dst);
}
