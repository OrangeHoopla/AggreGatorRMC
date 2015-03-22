#!/usr/bin/env python

import rospy
import cv2
import numpy as np
from common_files.srv import Coordinates, CoordinatesResponse

debug = False

#################################################
# Runs the services for the video_processing package
#################################################
def video_processing_service():
	rospy.init_node('video_processing_service')
	coord_xy_service = rospy.Service('get_target_coordinates_in_xy', Coordinates, get_point_xy)
	coord_m_service = rospy.Service('get_target_coordinates_in_meters', Coordinates, get_point_meters);
	rospy.spin()

#################################################
# Finds the best source of red via the webcam
# @param req	the request object passed in by ROS defined in Coordinates.srv
#################################################
def process_video_input(req):
	#create the windows if debugging
	if debug: video_test()

	#get the default video feed
	capture = cv2.VideoCapture(0)
	#get the return value and the video stream- e.g. frame
	ret, frame = capture.read()

	#get the dimensions
	height, width, depth = frame.shape

	#blur frame to handle noise
	frame = cv2.GaussianBlur(frame, (3,3), 0)

	#convert RGB to HSV
	hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

	# HSV bounds for red image
	lower_red = np.array([0, 135, 135])
	upper_red = np.array([20, 255, 255])

	red_mask1 = cv2.inRange(hsv, lower_red, upper_red)

	lower_red = np.array([159, 135, 135])
	upper_red = np.array([179, 255, 255])
	red_mask2 = cv2.inRange(hsv, lower_red, upper_red)

	#create a binary image for masking purposes
	red_mask = cv2.bitwise_or(red_mask1, red_mask2)

	#denoise the binary image- e.g. remove little dots
	red_mask = cv2.medianBlur(red_mask, 7)

	#overlay binary image with color image
	red_isolated = cv2.bitwise_and(frame, frame, mask=red_mask)

	#get the contours from the mask
	contours, hierarchy = cv2.findContours(red_mask, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

	#get the contour with the best likelihood
	max_area = 0
	best_cnt = 0
	second_best_cnt = 0
	for cnt in contours:
		area = cv2.contourArea(cnt)
		if area > max_area:
			max_area = area
			second_best_cnt = best_cnt
			best_cnt = cnt

    #get the centerpoint of the best contour
	output = [];
	moments = cv2.moments(best_cnt)
	if int(moments['m00']) != 0: #zero division check
		cx = int(moments['m10']/moments['m00'])
		cy = int(moments['m01']/moments['m00'])
		if cx > 0 and cy > 0:
			output = [cx, cy]

			#draw the center point if debugging
			if debug: 
				cv2.circle(red_isolated,(cx, cy), 5, (0, 255, 255), -1)

	moments = cv2.moments(second_best_cnt)
	if int(moments['m00']) != 0: #zero division check
		cx = int(moments['m10']/moments['m00'])
		cy = int(moments['m01']/moments['m00'])
		if cx > 0 and cy > 0:
			output.append(cx)
			output.append(cy)

			#draw the center point if debugging
			if debug: 
				cv2.circle(red_isolated,(cx, cy), 5, (0, 255, 255), -1)

	#free the video feed
	capture.release()

	# acts like quadrant 1 coordinates
	try:
		#add the first pair of coordinates
		result = [float(width - output[0]), float(height - output[1])]
		try:
			#add the second pair of coordinates
			result.append(float(width - output[2]))
			result.append(float(height - output[3]))
		except Exception:
			result.append(-1)
			if len(arr) == 3: result.append(-1)

		return result, width, height
	except Exception:
		return [-1, -1, -1, -1], width, height

#################################################
# Gets the distance of the source of red based on the centerpoint
# Requires known distance
# @param req	the request object passed in by ROS defined in Coordinates.srv
#################################################
def get_distance(req):
	return -1

#################################################
# Gets the point of the source of red in pixels
# @param req	the request object passed in by ROS defined in Coordinates.srv
#################################################
def get_point_xy(req):
	response = CoordinatesResponse()
	response.output, response.width, response.height = process_video_input(req)
	return response

def get_point_meters(req):
	response = CoordinatesResponse()
	
	coords, response.width, response.height = process_video_input(req);

	#set the output param to be the pixel coordiantes
	response.output = coords

	#define the width and height params
	response.width = convertToMeters(response.width)
	response.height = convertToMeters(response.height)

	#check the first pair
	if coords[0] == -1:
		#set second pair to -1, -1
		response.output = [-1, -1, response.output[2], response.output[3]]
	else:
		#convert the first pair to meters
		response.output = [convertToMeters(response.output[0]), convertToMeters(response.output[1]), response.output[2], response.output[3]]

	#check the second pair
	if coords[2] == -1: 
		#set second pair to -1, -1
		response.output = [response.output[0], response.output[1], -1, -1]
	else:
		#convert the second pair to meters
		response.output[2] = convertToMeters(coords[2])
		response.output[3] = convertToMeters(coords[3])
		
	return response

def video_test():
	cv2.namedWindow('color',1)
	cv2.namedWindow('red',1)
	cv2.moveWindow('color', 300, 0)
	cv2.moveWindow('red',600, 0)

	#get the default video feed
	capture = cv2.VideoCapture(0)
	while True:
		#get the return value and the video stream- e.g. frame
		ret, frame = capture.read()

		#get the dimensions
		height, width, depth = frame.shape

		#blur frame to handle noise
		frame = cv2.GaussianBlur(frame, (3,3), 0)

		#convert RGB to HSV
		hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

		# HSV bounds for red image
		lower_red = np.array([0, 135, 135])
		upper_red = np.array([20, 255, 255])

		red_mask1 = cv2.inRange(hsv, lower_red, upper_red)

		lower_red = np.array([159, 135, 135])
		upper_red = np.array([179, 255, 255])
		red_mask2 = cv2.inRange(hsv, lower_red, upper_red)

		#create a binary image for masking purposes
		red_mask = cv2.bitwise_or(red_mask1, red_mask2)

		#denoise the binary image- e.g. remove little dots
		red_mask = cv2.medianBlur(red_mask, 7)

		#overlay binary image with color image
		red_isolated = cv2.bitwise_and(frame, frame, mask=red_mask)

		#get the contours from the mask
		contours, hierarchy = cv2.findContours(red_mask, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

		#get the contour with the best likelihood
		max_area = 0
		best_cnt = 0
		second_best_cnt = 0
		for cnt in contours:
			area = cv2.contourArea(cnt)
			if area > max_area:
				max_area = area
				second_best_cnt = best_cnt
				best_cnt = cnt

	    #get the centerpoint of the best contour
		output = [];
		moments = cv2.moments(best_cnt)
		if int(moments['m00']) != 0: #zero division check
			cx = int(moments['m10']/moments['m00'])
			cy = int(moments['m01']/moments['m00'])
			if cx > 0 and cy > 0:
				output = [cx, cy]

				#draw the center point if debugging
				if debug: 
					cv2.circle(red_isolated,(cx, cy), 5, (0, 255, 255), -1)

		moments = cv2.moments(second_best_cnt)
		if int(moments['m00']) != 0: #zero division check
			cx = int(moments['m10']/moments['m00'])
			cy = int(moments['m01']/moments['m00'])
			if cx > 0 and cy > 0:
				output.append(cx)
				output.append(cy)

				#draw the center point if debugging
				if debug: 
					cv2.circle(red_isolated,(cx, cy), 5, (0, 255, 255), -1)

		#set feed if debugging
		if debug:
			cv2.imshow('color', frame)
			cv2.imshow('red', red_isolated)

		if cv2.waitKey(1) & 0xFF == ord('q'):
			cv2.destroyAllWindows()
			break

	#free the video feed
	capture.release()

#################################################
# Gets the point of the source of red in meters
# @param req	the request object passed in by ROS defined in Coordinates.srv
#################################################
def convertToMeters(value):
	pixelToCm = 0.026458333;
	return value*pixelToCm/100

if __name__ == '__main__':
	try:
		video_processing_service()
	except rospy.ROSInterruptException:
		pass