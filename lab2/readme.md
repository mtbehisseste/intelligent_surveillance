# Intelligent Surveillance Lab 2 - Gaussian Mixture Model Background Subtraction
## **task**
Generate   
- the origin video frame
- the foreground image
- remove shadow and apply morphology result
- the colored foreground image  

of the 150th and 200th frame.
### Get images from video 
Video is composed of a series of images.
```cpp
VideoCapture cap("video.avi");
for(int i=0;; i++){
    Mat frame;
    cap >> frame;
    if(frame.empty()) break;
}
```
### Get foreground
To get foreground, we have to subtract the background from current frame.  
*Gaussian Mixture Modeling:  
Find out the match of the pixel in the current frame, and update the parameters(mean, covariance, weight) with the pixel value.*  
Cpp class to use: `BackgroundSubtractorMOG2()`
```cpp
BackgroundSubtractorMOG2 mog = BackgroundSubtractorMOG2();
for(...){
    mog.operator()(frame, foreground, -1); 
    /*-1 stands for learning rate.*/
}
```
### Remove shadow
```cpp
threshold(forground, noshadow, 128, 255, THRESH_BINARY);
/*128 is the threshold, value below it will be judged as background. 255 is the max value. THRESH_BINARY stands for the threshold type.*/
```
### Morphology - remove the noise
`getStructingElement()`can get the template of the image for eroding and dilating. 
```cpp
Mat erodeStruct = getStructuringElement(MORPH_RECT, Size(3, 3)); 
/*MORPH_RECT is the shape of the template. Size can be changed.*/
erode(noshadow, erodeImg, erodeStruct);
dilate(erodeImg, dilateImg, erodeStruct);
/*erode() first to remove noise and dilate() to recover the pixel.*/
```
### Generate colored foreground image
To colored foreground image, combine the origin image(frame) and the morphology-masked image(dilateImg).
```cpp
frame.copyTo(finalImg, dilateImg);
```