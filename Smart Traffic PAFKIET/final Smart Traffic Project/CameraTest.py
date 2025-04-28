# import the opencv library
import cv2

# define a video capture object
cap = cv2.VideoCapture(1)

while True:
    _, frame = cap.read()

    # right = frame[251:367, 403:620]  # Slicing to crop the image  D
    # left = frame[112:233, 110:356]  # Slicing to crop the image   B
    # top = frame[8:220, 382:502]  # Slicing to crop the image      C
    # bottom = frame[253:477, 248:370]  # Slicing to crop the image A

    cv2.imshow('Output', frame)
    cv2.imwrite('Images/sample19.jpg', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
