import tensorflow as tf
import cv2
import matplotlib.pyplot as plt

from detection import Detector

def draw_bboxes(img, bboxes, color = (255,0,0)):
	h, w = img.shape[:2]
	d_img = img.copy()
	d_img = cv2.cvtColor(d_img, cv2.COLOR_RGB2BGR)
	for b in bboxes:
		xmin, ymin, xmax, ymax, prop = b[:]
		if prop > 0.5:
			''' draw rectangle ex.position of topleft = int(xmin*w)'''
			cv2.rectangle(d_img, (int(xmin*w), int(ymin*h)), (int(xmax*w), int(ymax*h)), (0, 255, 0), 2)
	return d_img
	
def main():
	''' load image '''
	image = cv2.imread('data/img_1.jpg')

	''' load models '''
	det_mod_path = 'det_nets_3.ckpt'
	cal_mod_path = 'cal_nets_14.ckpt'
	detector = Detector(det_mod_path, cal_mod_path)

	''' build pyramids '''
	bboxes = detector.img_pyramids(image)



	''' 12-net , calibration 12-net , non maximum supression'''
	bboxes = detector.predict(image, bboxes, net='net12', threshold=0.9)
	det12_img = draw_bboxes(image, bboxes, color = (255, 0, 0))
	bboxes = detector.predict(image, bboxes, net='net12_cal', threshold=0.9)
	cal12_img = draw_bboxes(image, bboxes, color = (255, 0, 0))
	bboxes = detector.non_max_sup(bboxes,iou_thresh = 0.8)
	nms12_img = draw_bboxes(image, bboxes, color = (255, 0, 0))

	''' 24-net , calibration 24-net , non maximum supression'''
	bboxes = detector.predict(image, bboxes, net='net24', threshold=0.9)
	det24_img = draw_bboxes(image, bboxes, color = (255, 0, 0))
	bboxes = detector.predict(image, bboxes, net='net24_cal', threshold=0.9)
	cal24_img = draw_bboxes(image, bboxes, color = (255, 0, 0))
	bboxes = detector.non_max_sup(bboxes,iou_thresh = 0.5)
	nms24_img = draw_bboxes(image, bboxes, color = (255, 0, 0))


	''' 48-net , calibration 48-net , non maximum supression'''
	bboxes = detector.predict(image, bboxes, net='net48', threshold=0.9)
	det48_img = draw_bboxes(image, bboxes, color = (255, 0, 0))
	bboxes = detector.predict(image, bboxes, net='net48_cal', threshold=0.9)
	cal48_img = draw_bboxes(image, bboxes, color = (255, 0, 0))
	bboxes = detector.non_max_sup(bboxes,iou_thresh = 0.2)
	nms48_img = draw_bboxes(image, bboxes, color = (255, 0, 0))
	
	
	# ploting result
	show_list = [ det12_img, cal12_img, nms12_img,\
				  det24_img, cal24_img, nms24_img,\
				  det48_img, cal48_img, nms48_img]
	# rows and cols of figure
	row = 3
	col = 3
	# create figure 
	fig = plt.figure()

	# set img to each subplot
	for i, image in enumerate(show_list):    
		a = fig.add_subplot(row, col, i+1)
		plt.imshow(image)
	# show result combination
	plt.show()
	
if __name__ == "__main__":
	main()
	