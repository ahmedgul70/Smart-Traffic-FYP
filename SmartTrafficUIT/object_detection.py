import numpy as np
import cv2

def FindCars(imageFrame):
    detectArea = 1500
    notdetect = 2500
    TotalCars = 0;
    hsvFrame = cv2.cvtColor(imageFrame, cv2.COLOR_BGR2HSV)

    # Set range for red color and
    red_lower = np.array([0, 100, 100], np.uint8)  # 0,50,50
    red_upper = np.array([10, 255, 255], np.uint8)  # 10,255,255
    red_mask = cv2.inRange(hsvFrame, red_lower, red_upper)

    # Set range for green color and
    green_lower = np.array([36, 50, 70], np.uint8)  # 40,50,50
    green_upper = np.array([95, 255, 255], np.uint8)  # 80, 255 255
    green_mask = cv2.inRange(hsvFrame, green_lower, green_upper)

    # Set range for blue color and
    blue_lower = np.array([80, 50, 70], np.uint8)  # 10,50,50
    blue_upper = np.array([130, 255, 255], np.uint8)  # 130,255,255
    blue_mask = cv2.inRange(hsvFrame, blue_lower, blue_upper)

    # Set range for yellow color and
    yellow_lower = np.array([20, 50, 50], np.uint8)  # 10,50,50
    yellow_upper = np.array([30, 255, 255], np.uint8)  # 130,255,255
    yellow_mask = cv2.inRange(hsvFrame, yellow_lower, yellow_upper)

    kernal = np.ones((8, 8), "uint8")

    # For red color
    red_mask = cv2.dilate(red_mask, kernal)

    # For green color
    green_mask = cv2.dilate(green_mask, kernal)

    # For blue color
    blue_mask = cv2.dilate(blue_mask, kernal)

    # For yellow color
    yellow_mask = cv2.dilate(yellow_mask, kernal)

    # Creating contour to track red color
    contours, hierarchy = cv2.findContours(red_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    for pic, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        if (area > detectArea):
            TotalCars = TotalCars + 1
            x, y, w, h = cv2.boundingRect(contour)
            imageFrame = cv2.rectangle(imageFrame, (x, y), (x + w, y + h),  (0, 255, 0), 2)
            # cv2.putText(imageFrame, "CAR ", (x, y), cv2.FONT_HERSHEY_SIMPLEX, 1.0,  (0, 255, 0))

    # Creating contour to track green color
    # contours, hierarchy = cv2.findContours(green_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    # for pic, contour in enumerate(contours):
    #     area = cv2.contourArea(contour)
    #     if (area > detectArea and area < 2500):
    #         TotalCars = TotalCars + 1
    #         x, y, w, h = cv2.boundingRect(contour)
    #         imageFrame = cv2.rectangle(imageFrame, (x, y), (x + w, y + h),  (0, 255, 0), 2)
            # cv2.putText(imageFrame, "CAR", (x, y), cv2.FONT_HERSHEY_SIMPLEX, 1.0, (0, 255, 0))

    # Creating contour to track yellow color
    contours, hierarchy = cv2.findContours(yellow_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    for pic, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        if (area > detectArea):
            TotalCars = TotalCars + 1
            x, y, w, h = cv2.boundingRect(contour)
            imageFrame = cv2.rectangle(imageFrame, (x, y), (x + w, y + h),  (0, 255, 0), 2)
            # cv2.putText(imageFrame, "CAR", (x, y), cv2.FONT_HERSHEY_SIMPLEX, 1.0,  (0, 255, 0))

    # Creating contour to track blue color
    contours, hierarchy = cv2.findContours(blue_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    for pic, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        if (area > detectArea):
            TotalCars = TotalCars + 1
            x, y, w, h = cv2.boundingRect(contour)
            imageFrame = cv2.rectangle(imageFrame, (x, y), (x + w, y + h),  (0, 255, 0), 2)
            # cv2.putText(imageFrame, "CAR ", (x, y), cv2.FONT_HERSHEY_SIMPLEX, 1.0,  (0, 255, 0))

    return (int(TotalCars));