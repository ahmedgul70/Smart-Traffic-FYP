import cv2
import numpy as np
import time
import serial
import firebase_admin
from firebase_admin import db
from firebase_admin import credentials, initialize_app, storage

ser = serial.Serial(port='COM6', baudrate=9600, timeout=0.1)
time.sleep(1)
cred_obj = firebase_admin.credentials.Certificate('smarttrafficpafkiet-firebase-adminsdk.json')
default_app = firebase_admin.initialize_app(cred_obj, {
    'databaseURL': 'https://smarttrafficpafkiet-default-rtdb.firebaseio.com/',
    'storageBucket': 'smarttrafficpafkiet.appspot.com'})
ref = db.reference("/Parameters")
ref.update({"cars": "0"})
ref.update({"amb": "0"})
max_time = 3000
start_time = round(time.time() * 1000)

print('Smart Traffic FYP PAFKIET 2023')
Lane1 = 0
Lane2 = 0
Lane3 = 0
Lane4 = 0
CheckStatus = 0
Ambulance1 = 0
Ambulance2 = 0
Ambulance3 = 0
Ambulance4 = 0


# get grayscale image
def get_grayscale(image):
    return cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)


# noise removal
def remove_noise(image):
    return cv2.medianBlur(image, 5)


# thresholding
def thresholding(image):
    return cv2.threshold(image, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)[1]


# dilation
def dilate(image):
    kernel = np.ones((5, 5), np.uint8)
    return cv2.dilate(image, kernel, iterations=1)


def FindShades(imageFrame):
    detectArea = 1500
    notdetect = 2500
    TotalCars = 0;
    hsvFrame = cv2.cvtColor(imageFrame, cv2.COLOR_BGR2HSV)

    # Set range for red color and
    red_lower = np.array([0, 100, 100], np.uint8)  # 0,50,50
    red_upper = np.array([10, 255, 255], np.uint8)  # 10,255,255
    red_mask = cv2.inRange(hsvFrame, red_lower, red_upper)

    kernal = np.ones((8, 8), "uint8")

    # For red color
    red_mask = cv2.dilate(red_mask, kernal)

    # Creating contour to track red color
    contours, hierarchy = cv2.findContours(red_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    for pic, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        if (area > detectArea):
            TotalCars = TotalCars + 1
            x, y, w, h = cv2.boundingRect(contour)
            imageFrame = cv2.rectangle(imageFrame, (x, y), (x + w, y + h), (0, 255, 0), 2)
            # cv2.putText(imageFrame, "CAR ", (x, y), cv2.FONT_HERSHEY_SIMPLEX, 1.0,  (0, 255, 0))
    return (int(TotalCars))


def FindCars(img, min, max):
    ref.update({"cars": "1"})
    MinArea = min
    MaxArea = max
    TotalCars = 0

    # Convert to grayscale
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # apply binary thresholding
    ret, thresh = cv2.threshold(gray, 150, 255, cv2.THRESH_BINARY)
    # detect the contours on the binary image using cv2.CHAIN_APPROX_NONE
    contours, hierarchy = cv2.findContours(image=thresh, mode=cv2.RETR_TREE, method=cv2.CHAIN_APPROX_NONE)

    # draw contours on the original image
    image_copy = img.copy()
    cv2.drawContours(image=image_copy, contours=contours, contourIdx=-1, color=(0, 255, 0), thickness=2,
                     lineType=cv2.LINE_AA)
    for pic, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        # print(area)
        if (area > MinArea and area < MaxArea):
            TotalCars = TotalCars + 1
            # x, y, w, h = cv2.boundingRect(contour)
            # img = cv2.rectangle(img, (x, y), (x + w, y + h), (0, 255, 0), 2)

    return (int(TotalCars))


def FindEmergency(imageFrame, detectAreamin, detectAreamax):
    ref.update({"amb": "1"})
    TotalCars = 0
    hsvFrame = cv2.cvtColor(imageFrame, cv2.COLOR_BGR2HSV)

    # Set range for red color and
    red_lower = np.array([0, 50, 50], np.uint8)  # 0,50,50
    red_upper = np.array([180, 255, 255], np.uint8)  # 10,255,255
    red_mask = cv2.inRange(hsvFrame, red_lower, red_upper)

    kernal = np.ones((8, 8), "uint8")

    # For red color
    red_mask = cv2.dilate(red_mask, kernal)

    # Creating contour to track red color
    contours, hierarchy = cv2.findContours(red_mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    for pic, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        # print('Area : ' , area)
        if (area > detectAreamin and area < detectAreamax):
            TotalCars = TotalCars + 1
            # x, y, w, h = cv2.boundingRect(contour)
            # imageFrame = cv2.rectangle(imageFrame, (x, y), (x + w, y + h), (0, 255, 0), 2)
            # cv2.putText(imageFrame, "CAR ", (x, y), cv2.FONT_HERSHEY_SIMPLEX, 1.0,  (0, 255, 0))

    return (int(TotalCars))


def process():
    if (ref.child("command").get() == "1"):
        Lane1, Lane2, Lane3, Lane4 = 1, 0, 0, 0
        ArduinoCommand = str(Lane1) + "," + str(Lane2) + "," + str(Lane3) + "," + str(Lane4) + "&"
        # ser.write(bytes(ArduinoCommand, 'utf-8'))
    elif (ref.child("command").get() == "2"):
        Lane1, Lane2, Lane3, Lane4 = 0, 1, 0, 0
        ArduinoCommand = str(Lane1) + "," + str(Lane2) + "," + str(Lane3) + "," + str(Lane4) + "&"
        # ser.write(bytes(ArduinoCommand, 'utf-8'))
    elif (ref.child("command").get() == "3"):
        Lane1, Lane2, Lane3, Lane4 = 0, 0, 1, 0
        ArduinoCommand = str(Lane1) + "," + str(Lane2) + "," + str(Lane3) + "," + str(Lane4) + "&"
        # ser.write(bytes(ArduinoCommand, 'utf-8'))
    elif (ref.child("command").get() == "4"):
        Lane1, Lane2, Lane3, Lane4 = 0, 0, 0, 1
        ArduinoCommand = str(Lane1) + "," + str(Lane2) + "," + str(Lane3) + "," + str(Lane4) + "&"
        # ser.write(bytes(ArduinoCommand, 'utf-8'))
    elif (ref.child("command").get() == "5"):
        Lane1, Lane2, Lane3, Lane4 = 2, 0, 0, 0
        ArduinoCommand = str(Lane1) + "," + str(Lane2) + "," + str(Lane3) + "," + str(Lane4) + "&"
        # ser.write(bytes(ArduinoCommand, 'utf-8'))
    elif (ref.child("command").get() == "6"):
        Lane1, Lane2, Lane3, Lane4 = 0, 2, 0, 0
        ArduinoCommand = str(Lane1) + "," + str(Lane2) + "," + str(Lane3) + "," + str(Lane4) + "&"
        # ser.write(bytes(ArduinoCommand, 'utf-8'))
    elif (ref.child("command").get() == "7"):
        Lane1, Lane2, Lane3, Lane4 = 0, 0, 2, 0
        ArduinoCommand = str(Lane1) + "," + str(Lane2) + "," + str(Lane3) + "," + str(Lane4) + "&"
        # ser.write(bytes(ArduinoCommand, 'utf-8'))
    elif (ref.child("command").get() == "8"):
        Lane1, Lane2, Lane3, Lane4 = 0, 0, 0, 2
        ArduinoCommand = str(Lane1) + "," + str(Lane2) + "," + str(Lane3) + "," + str(Lane4) + "&"
        # ser.write(bytes(ArduinoCommand, 'utf-8'))
    else:
        Lane1, Lane2, Lane3, Lane4 = 0, 0, 0, 0
        ArduinoCommand = str(Lane1) + "," + str(Lane2) + "," + str(Lane3) + "," + str(Lane4) + "&"

    return ArduinoCommand


config_file = 'ssd_mobilenet_v3_large_coco_2020_01_14.pbtxt'
frozen_model = 'frozen_inference_graph.pb'
model = cv2.dnn_DetectionModel(frozen_model, config_file)

# Model Configuration
model.setInputSize(320, 320)
model.setInputScale((1.0 / 127.5))  # 255/2 = 127.5
model.setInputMean((127.5, 127.5, 127.5))
model.setInputSwapRB(True)

# define a video capture object
cap = cv2.VideoCapture(1)
cap.set(3, 640)
cap.set(4, 480)
min = 3000
max = 5000
min2 = 3000
max2 = 5000
count = 0
fileName = "sample.jpg"
bucket = storage.bucket()

while True:
    _, frame = cap.read()
    right = frame[251:367, 403:620]  # Slicing to crop the image  D
    left = frame[112:233, 110:356]  # Slicing to crop the image   B
    top = frame[8:220, 382:502]  # Slicing to crop the image      C
    bottom = frame[253:477, 248:370]  # Slicing to crop the image A

    Ambulance1 = FindEmergency(right, 3000, 5000)
    Ambulance2 = FindEmergency(top, 3000, 5000)
    Ambulance3 = FindEmergency(left, 3000, 5000)
    Ambulance4 = FindEmergency(bottom, 3000, 5000)

    Lane1 = FindCars(right, min, max)  # Route D
    Lane2 = FindCars(top, min, max)    # Route C
    Lane3 = FindCars(left, min, max)   # Route B
    Lane4 = FindCars(bottom, min, max) # Route A

    if ser.inWaiting() > 0 and CheckStatus == 0:
        # Read the available bytes
        data = ser.read(ser.inWaiting())
        datad = data.decode()
        print(data)
        if datad.find("Check") != -1:
            ref.update({"image": "0"})
            print("Start Testing Image")
            cv2.imwrite('sample.jpg', frame)
            CheckStatus = 1
        else:
            print("Wrong Data From Arduino")
            CheckStatus = 0

    if (CheckStatus == 1):
        print("Algorithm Apply")
        blob = bucket.blob(fileName)
        blob.upload_from_filename(fileName)
        ref.update({"image": "1"})
        print('Success.')
        time.sleep(4)
        CheckStatus = 0
        if (round(time.time() * 1000) - start_time > max_time):
            start_time = round(time.time() * 1000)
            ArduinoCommand = process()
            print(ArduinoCommand)
            ser.write(bytes(ArduinoCommand, 'utf-8'))
            # ref.update({"image": "0"})

            # else:
            #     if(Ambulance1 == 1):
            #         ArduinoCommand = ("1,0,0,0&")
            #         ser.write(b'1,0,0,0&')
            #     elif(Ambulance2 == 1):
            #         ArduinoCommand = ("0,1,0,0&")
            #         ser.write(b'0,1,0,0&')
            #     elif(Ambulance3 == 1):
            #         ArduinoCommand = ("0,0,1,0&")
            #         ser.write(b'0,0,1,0&')
            #     elif(Ambulance4 == 1):
            #         ArduinoCommand = ("0,0,0,1&")
            #         ser.write(b'0,0,0,1&')
            #     print(ArduinoCommand)

    cv2.imshow('Output', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

ser.close()
cap.release()
cv2.destroyAllWindows()
