# Intelligent Surveillance Lab 5 - Face Detection (Using Convolutional Neural Network Cascade)

> cascade classifiers:  
&nbsp;&nbsp;&nbsp;&nbsp; net\<S> : detection net  
&nbsp;&nbsp;&nbsp;&nbsp; nms : non maximum suppression  
&nbsp;&nbsp;&nbsp;&nbsp; net\<S>_cal : calibration net

## **task**  
- Load image with OpenCV
- Restore pre-trained models
- Process image pyramids
- Construct the cascade structure
- Plot all details


### Pre-work
Install `tensorflow`, `matplotlib`, and `openCV` with python 3.5.x or 3.6.x
```bash
pip install tensorflow
pip install matplotlib
pip install opencv-python
```
Face detection APIs:  [https://github.com/liumusicforever/CNN_Face_Detection](https://github.com/liumusicforever/CNN_Face_Detection)  
Pre-trained models: [https://drive.google.com/file/d/170IlbvlBxrrtML_j3rmLFMDNIgX44Rgw/view?usp=sharing](https://drive.google.com/file/d/170IlbvlBxrrtML_j3rmLFMDNIgX44Rgw/view?usp=sharing)  

Loading models:  
```python
from detection import Detector

det_mod_path = '/path/to/detection/model'
cal_mod_path = '/path/to/calibration/model'
detector = Detector(det_mod_path, cal_mod_path)
```

### Process image pyramids
```python
bboxes = detector.img_pyramids(image)
```
### Construct the cascade structure
net\<s> :
```python
bboxes = detector.predict(image, bboxes, net='net12', threshold=0.9)
```
net\<s>_cal :
```python
bboxes = detector.predict(image, bboxes, net='net12_cal', threshold=0.9)
```
nms: 
```python 
bboxes = detector.non_max_sup(bboxes,iou_thresh = 0.8)
```
### Plot
```python
import matplotlib.pyplot as plt

fig = plt.figure()

row = 3
col = 3
for i, image in enumerate(show_list):    
	a = fig.add_subplot(row, col, i+1)
	plt.imshow(image)

plt.show()
```