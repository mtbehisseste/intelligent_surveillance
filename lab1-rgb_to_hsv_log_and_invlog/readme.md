# Intelligent Surveillance Lab 1

## **task**
- Convert RGB image to HSV 
- Split HSV image to three 8-bit plane
- Perform *log* and *inverse-log* gray-level transformation on H, S, and V plane.

### Convert Rgb image to HSV
```c++
Mat img = imread("lena.jpg");
Mat hsvImg;
cv::cvtColor(img, hsvImg, CV_BGR2HSV);
```
### Split HSV image to threee 8-bit plane
```c++
Mat hsvImgSp[3];
split(hsvImg, hsvImgSp);
imwrite("h.jpg", hsvImgSp[0]);
imwrite("s.jpg", hsvImgSp[1]);
imwrite("v.jpg", hsvImgSp[2]);
```
### Perform log gray-level transformation on H, S, and V plane.
```c++
int h = img.rows;
int w = img.cols;
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
```
For each pixel(which will be access by row and column), get its value by ```at<datatype>()```. Then do the calculation.  
Note that the type of the parameter of ```log()``` and the type it return are both double.  