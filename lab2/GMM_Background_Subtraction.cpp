#include "opencv2/opencv.hpp"

using namespace cv;

int main() {
	VideoCapture cap("video.avi");
	BackgroundSubtractorMOG2 mog = BackgroundSubtractorMOG2();
	for (int i = 0;; i++){
		Mat frame, forground, noshadow, erodeImg, dilateImg, finalImg;
		Mat erodeStruct = getStructuringElement(MORPH_RECT, Size(3, 3)); // size can change
		cap >> frame;
		mog.operator()(frame, forground, -1);
		if (i == 150){
			imshow("frame", frame);
			imwrite("150_origin_frame.jpg", frame);
			threshold(forground, noshadow, 128, 255, THRESH_BINARY);
			imshow("forground", forground);
			imwrite("150_forgroud.jpg", forground);
			//imshow("noshadow", noshadow);
			erode(noshadow, erodeImg, erodeStruct);
			dilate(erodeImg, dilateImg, erodeStruct);
			imshow("dilateImg", dilateImg);
			imwrite("150_morphology.jpg", dilateImg);
			frame.copyTo(finalImg, dilateImg);
			imshow("finalImg", finalImg);
			imwrite("150_origin_morphologyMask.jpg", finalImg);
			waitKey(0);
		}
		if (i == 200){
			imshow("frame", frame);
			imwrite("200_origin_frame.jpg", frame);
			threshold(forground, noshadow, 128, 255, THRESH_BINARY);
			imshow("forground", forground);
			imwrite("200_forgroud.jpg", forground);
			//imshow("noshadow", noshadow);
			erode(noshadow, erodeImg, erodeStruct);
			dilate(erodeImg, dilateImg, erodeStruct);
			imshow("dilateImg", dilateImg);
			imwrite("200_morphology.jpg", dilateImg);
			frame.copyTo(finalImg, dilateImg);
			imshow("finalImg", finalImg);
			imwrite("200_origin_morphologyMask.jpg", finalImg);
			waitKey(0);
			break;
		}
		//if(frame.empty()) break;
	}
	return 0;
}