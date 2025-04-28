import cv2
import numpy as np
import object_detection
import time
import serial

# ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
ser = serial.Serial(port='COM10', baudrate=9600, timeout=0.1)
time.sleep(1)

debug = True
max_time = 2000
start_time = round(time.time() * 1000)

print('Smart Traffic FYP using R-CNN UIT')

Lane1 = 0;
Lane2 = 0;
Lane3 = 0;
Lane4 = 0;

vid = cv2.VideoCapture(0)
vid.set(3, 640)
vid.set(4, 480)

while (1):
    ret, frame = vid.read()

    # Display the resulting frame
    right = frame[185:341, 374:535]  # Slicing to crop the image
    right_detected = frame[183:248, 374:532]  # Slicing to crop the image

    left = frame[188:344, 34:170]  # Slicing to crop the image
    left_detected = frame[290:338, 36:170]  # Slicing to crop the image

    top = frame[22:171, 184:361]  # Slicing to crop the image
    top_detected = frame[38:171, 189:264]  # Slicing to crop the image

    bottom = frame[345:440, 192:379]  # Slicing to crop the image
    bottom_detected = frame[356:435, 301:370]  # Slicing to crop the image

    Lane1 = object_detection.FindCars(top_detected)
    Lane2 = object_detection.FindCars(left_detected)
    Lane3 = object_detection.FindCars(right_detected)
    Lane4 = object_detection.FindCars(bottom_detected)

    cv2.imshow("FullView ", frame)
    # cv2.imshow("topView ", top)
    # cv2.imshow("LeftView ", left)
    # cv2.imshow("RightView ", right)
    # cv2.imshow("BottomView ", bottom)

    if (round(time.time() * 1000) - start_time > max_time):
        start_time = round(time.time()*1000)
        ArduinoCommand = str(Lane1) + "," + str(Lane2) + "," + str(Lane3) + "," + str(Lane4) + "&";
        # ser.write(ArduinoCommand.encode('ascii'))
        ser.write(bytes(ArduinoCommand, 'utf-8'))
        time.sleep(0.2)
        print(ArduinoCommand)

    time.sleep(1)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

vid.release()
cv2.destroyAllWindows()
