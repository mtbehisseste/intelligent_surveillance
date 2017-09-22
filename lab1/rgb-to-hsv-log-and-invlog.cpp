#include "opencv2/opencv.hpp"
#include <vector>
#include <math.h>


using namespace cv;
using namespace std;

int main() {
	Mat img = imread("lena.jpg");
	imshow("jpg", img);
	Mat hsvImg;
	cvtColor(img,hsvImg,CV_BGR2HSV);
	int h = img.rows;
	int w = img.cols;

	Mat hsvImgSp[3];
	split(hsvImg, hsvImgSp);
	imshow("h.jpg", hsvImgSp[0]);
	imshow("s.jpg", hsvImgSp[1]);
	imshow("v.jpg", hsvImgSp[2]);
	imwrite("h.jpg", hsvImgSp[0]);
	imwrite("s.jpg", hsvImgSp[1]);
	imwrite("v.jpg", hsvImgSp[2]);

	Mat logHsvImgSp0 = Mat::zeros(h, w, CV_32FC1);
	Mat logHsvImgSp1 = Mat::zeros(h, w, CV_32FC1);
	Mat logHsvImgSp2 = Mat::zeros(h, w, CV_32FC1);
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			logHsvImgSp0.at<float>(i, j) = 32 * ((log(hsvImgSp[0].at<uchar>(i, j) + 1) / log(2)));
			logHsvImgSp1.at<float>(i, j) = 32 * ((log(hsvImgSp[1].at<uchar>(i, j) + 1) / log(2)));
			logHsvImgSp2.at<float>(i, j) = 32 * ((log(hsvImgSp[2].at<uchar>(i, j) + 1) / log(2)));
		}
	}
	imwrite("H-log.jpg", logHsvImgSp0);
	imwrite("S-log.jpg", logHsvImgSp1);
	imwrite("V-log.jpg", logHsvImgSp2);
	logHsvImgSp0 /= 255;
	logHsvImgSp1 /= 255;
	logHsvImgSp2 /= 255;
	imshow("H-log.jpg", logHsvImgSp0);
	imshow("S-log.jpg", logHsvImgSp1);
	imshow("V-log.jpg", logHsvImgSp2);

	Mat inlogHsvImgSp0 = Mat::zeros(h, w, CV_32FC1);
	Mat inlogHsvImgSp1 = Mat::zeros(h, w, CV_32FC1);
	Mat inlogHsvImgSp2 = Mat::zeros(h, w, CV_32FC1);
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			inlogHsvImgSp0.at<float>(i, j) = (pow(2, (hsvImgSp[0].at<uchar>(i, j) / 32.0))) - 1;
			inlogHsvImgSp1.at<float>(i, j) = (pow(2, (hsvImgSp[1].at<uchar>(i, j) / 32.0))) - 1;
			inlogHsvImgSp2.at<float>(i, j) = (pow(2, (hsvImgSp[2].at<uchar>(i, j) / 32.0))) - 1;
		}
	}
	imwrite("H-invlog.jpg", inlogHsvImgSp0);
	imwrite("V-invlog.jpg", inlogHsvImgSp2);
	imwrite("S-invlog.jpg", inlogHsvImgSp1);
	inlogHsvImgSp0 /= 255;
	inlogHsvImgSp1 /= 255;
	inlogHsvImgSp2 /= 255;
	imshow("H-invlog.jpg", inlogHsvImgSp0);
	imshow("S-invlog.jpg", inlogHsvImgSp1);
	imshow("V-invlog.jpg", inlogHsvImgSp2);

	waitKey(0);
	
	return 0;
}
