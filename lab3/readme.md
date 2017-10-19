# Intelligent Surveillance Lab 3 - Skin Color and Shadow Detect
## **task**  
- use Gaussian Blur to get smooth video
- convert the color to YCbCr and extract the skin color pixels with the values in Cb and Cr channel 
- find the skin contour and calculate the area of pixels
- remove the noise by checking the area size  

### Get smooth video and get skin color range
Before getting contour, we need to get smooth video for removing noise.
Traditional way: each blur pixel is set to <u>the average of pixel value of neighbors</u>.
```cpp
GaussianBlur(frame, smooth, Size(5,5), 2, 0);  /*function to get smooth video*/
cvtColor(smooth, ycrcb, CV_BGR2YCrCb);  
inRange(ycrcb, Scalar(0, 133, 98), Scalar(255, 177, 122), range);
/*Scalar() set the threshold of the color in order of light(Y), red(Cr), blue(Cb)*/
```

### Get contour
```cpp
std::vector<std::vector<Point>> contours;
findContours(range, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);  /*find contour according to range*/
for (int j = 0; j < contours.size(); j++) {
    double thisContourArea = contourArea(contours[j]);  
    if (thisContourArea > 1000) {  /*the number for the area to remove noise*/
        drawContours(onlyHand, contours, j, Scalar(0, 0, 255));
    }
}
```