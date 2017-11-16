#include "opencv2/opencv.hpp"

using namespace cv;

int main()
{
	VideoCapture cap("input.mp4");
	for (int i = 0;; i++) {
		Mat frame, smooth, ycrcb, range, onlyHand;
		std::vector<std::vector<Point>> contours;
		cap >> frame;
		GaussianBlur(frame, smooth, Size(5,5), 2, 0);
		cvtColor(smooth, ycrcb, CV_BGR2YCrCb);
		inRange(ycrcb, Scalar(0, 133, 98), Scalar(255, 177, 122), range);
		frame.copyTo(onlyHand, range);
		findContours(range, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
		for (int j = 0; j < contours.size(); j++) {
			double thisContourArea = contourArea(contours[j]);
			if (thisContourArea > 1000) {
				Rect rec = boundingRect(contours[j]);
				rectangle(onlyHand, rec, Scalar(255, 255, 255), 1, 8, 0);
				putText(onlyHand, "pixel: " + std::to_string(thisContourArea), Point(rec.x, rec.y), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 0));
				drawContours(onlyHand, contours, j, Scalar(0, 0, 255));
			}
		}
		if (i == 100) {
			/*imshow("frame", frame);
			imshow("GaussianBlur", smooth);
			imshow("ycrcb", ycrcb);
			imshow("range", range);*/
			imshow("100th", onlyHand);
			imwrite("100th.jpg", onlyHand);
			waitKey(0);
			//break;
		}
		if (i == 200) {
			imshow("200th", onlyHand);
			imwrite("200th.jpg", onlyHand);
			waitKey(0);
			break;
		}
	}
}