#include <opencv2/core/core.hpp> //basic
#include <opencv2/highgui/highgui.hpp> //imread or ¡K
#include <opencv2/nonfree/nonfree.hpp>  //sift or surf <- important
#include <opencv2/legacy/legacy.hpp>  //matcher

using namespace cv;
using namespace std;

int main()
{
	SIFT sift(100, 3, 0.04, 10, 1.6f);
	Mat obj = imread("obj.jpg");
	Mat scene = imread("scene.jpg");
	Mat descriptor_obj, descriptor_scene, output;
	vector <KeyPoint> keypoints_obj;
	vector <KeyPoint> keypoints_scene;
	sift(obj, noArray(), keypoints_obj, descriptor_obj, 0);
	sift(scene, noArray(), keypoints_scene, descriptor_scene, 0);
	//drawKeypoints(obj, keypoints_obj, output, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	//imshow("out", output);

	BruteForceMatcher< L2<float> > matcher;
	vector <DMatch> matches;
	matcher.match(descriptor_obj, descriptor_scene, matches);
	Mat img_matches;
	//drawMatches(obj, keypoints_obj, scene, keypoints_scene, matches, img_matches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	//imshow("", img_matches);

	double min_dist = 1000;
	for (int i = 0; i < (int)matches.size(); i++) {
		double dist = matches[i].distance;
		if (dist < min_dist) {
			min_dist = dist;
		}
	}
	vector <DMatch> good_matches;
	for (int i = 0; i < (int)matches.size(); i++) {
		if (matches[i].distance < 5 * min_dist) {
			good_matches.push_back(matches[i]);
		}
	}
	drawMatches(obj, keypoints_obj, scene, keypoints_scene, good_matches, img_matches, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	imshow("", img_matches);
	imwrite("draw_matches.jpg", img_matches);
	waitKey(0);

	vector <Point2f> src;
	vector <Point2f> target;
	for (int i = 0; i < good_matches.size(); i++) {
		src.push_back(keypoints_obj[good_matches[i].queryIdx].pt);
		target.push_back(keypoints_scene[good_matches[i].trainIdx].pt);
	}
	Mat H = findHomography(target, src, CV_RANSAC);
	Mat output_img;
	warpPerspective(scene, output_img, H, Size(scene.cols * 2, scene.rows));
	//imshow("", output_img);


	Mat target_in_big_mat(output_img, Rect(0, 0, obj.cols, obj.rows));
	obj.copyTo(target_in_big_mat);
	imshow("", output_img);
	imwrite("merging_result.jpg", output_img);
	waitKey(0);
}