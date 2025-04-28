import time
import cv2
import object_detection

def SplitImages(img):
    h, w, channels = img.shape
    half = w // 2
    leftsideoffset = 30
    rightsideoffset = 60
    topsideoffset = 550
    bottomsideoffset = 500

    left_part = img[:, :half - leftsideoffset]
    right_part = img[:, rightsideoffset - half:]
    # this is horizontal division
    half2 = h // 2
    top = img[:half2 - topsideoffset, ]
    bottom = img[bottomsideoffset - half2:, ]

    croptop = top[20:240, 140:320]
    cropbottom = bottom[0:240, 180:320]
    cropright = right_part[140:320, 0:320]
    cropleft = left_part[130:320, 40:320]

    return croptop, cropbottom, cropleft, cropright


vid = cv2.VideoCapture(1)
while (1):
    ret, frame = vid.read()
    capture = frame[0:480, 60:640]

    top, bottom, left, right = SplitImages(capture)  # Split single image into 4 lanes images
    # cv2.imshow("topView ", top)
    # cv2.imshow("LeftView ", left)
    cv2.imshow("RightView ", right)
    # cv2.imshow("BottomView ", bottom)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

vid.release()
cv2.destroyAllWindows()
