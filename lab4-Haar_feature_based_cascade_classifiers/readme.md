# Intelligent Surveillance Lab 4 - Haar Feature Based Cascade Classifiers
## **task**  
- Convert each frame of the video to gray level image
- Use a CascadeClassifier to collect subWindow(faces) information
- Use another CascadeClassifier to do nestedCascade to collect subWindow (eyes) informations
- Label the location of face and eyes with rectangles or circles  

> Training strategy:
AdaBoost, Cascaded learning approach and with haar features.

### Convert each frame of the vide to gray level image
```cpp
cvtColor(frame, frameGrey, CV_BGR2GRAY);
```

### Collecting face and eyes informations
Use trained cascade haar features `haarcascade_frontalface_alt.xml` and `haarcascade_eye_tree_eyeglasses.xml` to find the face and eyes.
```cpp
CascadeClassifier face_cascade, eye_cascade;
face_cascade.load("./haarcascade_frontalface_alt.xml");
eye_cascade.load("./haarcascade_eye_tree_eyeglasses.xml");
```
Then use the detection functions.
```cpp
/*** reference
Void CascadeClassifier::detectMultiScale(
    const Mat& image, 
    vector<Rect>& objects, 
    double scaleFactor=1.1, 
    int minNeighbors=3, 
    int flags=0, 
    Size minSize=Size(), 
    Size maxSize=Size())
***/
vector <Rect> faces, eyes;  /* vectors with Rect type for detection results */
face_cascade.detectMultiScale(frameGrey, faces, 1.1, 3, 0, Size(100, 100));
eye_cascade.detectMultiScale(frameGrey, eyes, 1.1, 3, 0, Size(10, 10));
/* noted that these functions require input images to be gray level images. */
```

### Label the location of face and eyes with rectangles or circles 
```cpp
/*** reference
cv::rectangle(Mat& img, Rect rect, const Scalar& color, int thickness=1, int lineType=8, int shift=0)

cv::circle(Mat& img, Point center, int radius, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
***/
rectangle(newface, faces[j], Scalar(0, 255, 0), 4, 8, 0);
circle(newface, Point(eyes[k].x+10, eyes[k].y+10), 10, Scalar(0, 0, 255), 4, 8, 0);
```