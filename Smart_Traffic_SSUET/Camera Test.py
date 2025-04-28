# -*- coding: utf-8 -*-
"""
Created on Mon May  9 13:08:39 2022
"""

#import the opencv library
import cv2


# define a video capture object
vid = cv2.VideoCapture(0)
vid.set(3, 640)
vid.set(4, 480)

def SplitImages(img):
    h, w, channels = img.shape
    half = w//2
    leftsideoffset = 30
    rightsideoffset = 60
    topsideoffset = 550
    bottomsideoffset = 550

    left_part = img[:, :half - leftsideoffset]
    right_part = img[:,  rightsideoffset - half: ]
    # this is horizontal division
    half2 = h//2
    top = img[:half2 - topsideoffset, ]
    bottom = img[bottomsideoffset - half2:, ]
    
    croptop = top[0:240, 200:320]
    cropbottom = bottom[0:240, 200:320]
    cropright = right_part[180:320, 0:320]
    cropleft = left_part[180:320, 0:320]
    
    
while(True):
    
    # Capture the video frame
    # by frame
    ret, frame = vid.read()
    cropped = frame[0:480, 140:640]
    h, w, channels = cropped.shape
    half = w//2
    leftsideoffset = 30
    rightsideoffset = 60
    topsideoffset = 550
    bottomsideoffset = 550

    left_part = cropped[:, :half - leftsideoffset]
    right_part = cropped[:,  rightsideoffset - half: ]
    # this is horizontal division
    half2 = h//2
    top = cropped[:half2 - topsideoffset, ]
    bottom = cropped[bottomsideoffset - half2:, ]
    
    croptop = top[0:240, 200:320]
    cropbottom = bottom[0:240, 200:320]
    cropright = right_part[180:320, 0:320]
    cropleft = left_part[180:320, 0:320]
        
    # Display the resulting frame
    cv2.imshow('frame', cropped)
#    cv2.imshow('frameA', croptop)
#    cv2.imshow('frameB', cropleft)
#    cv2.imshow('frameC', cropright)
#    cv2.imshow('frameD', cropbottom)
    
    # the 'q' button is set as the
    # quitting button you may use any
    # desired button of your choice
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# After the loop release the cap object
vid.release()
# Destroy all the windows
cv2.destroyAllWindows()
