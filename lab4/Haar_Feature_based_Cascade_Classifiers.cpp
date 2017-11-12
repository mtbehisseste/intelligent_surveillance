#include <opencv2/opencv.hpp>
#include <objdetect/objdetect.hpp>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap("SRC.mp4");
	Mat newface;
	CascadeClassifier face_cascade, eye_cascade;
	face_cascade.load("./haarcascade_frontalface_alt.xml");
	eye_cascade.load("./haarcascade_eye_tree_eyeglasses.xml");
	for (int i = 0;; i++) {
		Mat frame, frameGrey;
		cap >> frame;
		newface = frame.clone();

		vector <Rect> faces, eyes;
		cvtColor(frame, frameGrey, CV_BGR2GRAY);
		face_cascade.detectMultiScale(frameGrey, faces, 1.1, 3, 0, Size(100, 100));
		for (int j = 0; j < faces.size(); j++) {
			rectangle(newface, faces[j], Scalar(0, 255, 0), 4, 8, 0);
			eye_cascade.detectMultiScale(frameGrey, eyes, 1.1, 3, 0, Size(10, 10));
			for (int k = 0; k < eyes.size(); k++) {
				circle(newface, Point(eyes[k].x+10, eyes[k].y+10), 10, Scalar(0, 0, 255), 4, 8, 0);
			}
		}

		if (i == 100) {
			imshow("100th", newface);
			imwrite("100th.jpg", newface);
		}

		if (i == 300) {
			imshow("300th", newface);
			imwrite("300th.jpg", newface);
		}

		if (waitKey(1) >= 0)
			break;
		
		/*if (i < 10) {
			imshow("100th", newface);
			waitKey(0);
		}*/

	}
	return 0;
}