# import the opencv library
import cv2

# define a video capture object
vid = cv2.VideoCapture(0)

def SplitImages(img):
    h, w, channels = img.shape
    half = w // 2
    leftsideoffset = 30
    rightsideoffset = 60
    topsideoffset = 550
    bottomsideoffset = 550

    left_part = img[:, :half - leftsideoffset]
    right_part = img[:, rightsideoffset - half:]
    # this is horizontal division
    half2 = h // 2
    top = img[:half2 - topsideoffset, ]
    bottom = img[bottomsideoffset - half2:, ]

    croptop = top[0:240, 200:320]
    cropbottom = bottom[0:240, 200:320]
    cropright = right_part[180:320, 0:320]
    cropleft = left_part[180:320, 0:320]

while True:
    _, frame = vid.read()

    cv2.imshow('frame', frame)
    # cv2.imwrite('Images/Full.jpg', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

vid.release()
cv2.destroyAllWindows()
