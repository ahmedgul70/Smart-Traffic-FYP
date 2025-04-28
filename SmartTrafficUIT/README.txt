
import cv2
import numpy as np
import time 
import serial



ser = serial.Serial('/dev/ttyACM0',9600,timeout=1)
#ser.open()
time.sleep(1)

debug = True

max_time = 6000
start_time = round(time.time()*1000)
print(start_time )
#print(round(time.time()*1000) )

Lane1 = 0;
Lane2 = 0;
Lane3 = 0;
Lane4 = 0;
Ambulance = 0;  
Ambulance1 = 0;   #Lane-1 
Ambulance2 = 0;
Ambulance3 = 0;
Ambulance4 = 0;

#Frame = cv2.imread('TF1.jpg')
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
    cv2.imwrite('Images/top.jpg', croptop)
    cv2.imwrite('Images/bottom.jpg', cropbottom)
    cv2.imwrite('Images/right.jpg', cropright)
    cv2.imwrite('Images/left.jpg', cropleft)

def FindCars(path):
    Ambulancess = 0;
    imageFrame = cv2.imread(path)
    detectArea = 2000
    
    TotalCars = 0;
    hsvFrame = cv2.cvtColor(imageFrame, cv2.COLOR_BGR2HSV)

    # Set range for red color and
    red_lower = np.array([0, 100, 100], np.uint8) #0,50,50
    red_upper = np.array([10, 255, 255], np.uint8) # 10,255,255
    red_mask = cv2.inRange(hsvFrame, red_lower, red_upper)

    # Set range for green color and
    green_lower = np.array([36, 50, 70], np.uint8) # 40,50,50
    green_upper = np.array([95, 255, 255], np.uint8) # 80, 255 255
    green_mask = cv2.inRange(hsvFrame, green_lower, green_upper)

    # Set range for blue color and
    blue_lower = np.array([80, 50,70], np.uint8) #10,50,50
    blue_upper = np.array([130, 255, 255], np.uint8) #130,255,255
    blue_mask = cv2.inRange(hsvFrame, blue_lower, blue_upper)
    
       # Set range for yellow color and
    yellow_lower = np.array([20, 50,50], np.uint8) #10,50,50
    yellow_upper = np.array([30, 255, 255], np.uint8) #130,255,255
    yellow_mask = cv2.inRange(hsvFrame, yellow_lower, yellow_upper)

    # Morphological Transform, Dilation
    # for each color and bitwise_and operator
    # between imageFrame and mask determines
    # to detect only that particular color
    kernal = np.ones((8, 8), "uint8")

    # For red color
    red_mask = cv2.dilate(red_mask, kernal)
    #res_red = cv2.bitwise_and(imageFrame, imageFrame, mask = red_mask)

    # For green color
    green_mask = cv2.dilate(green_mask, kernal)
    #res_green = cv2.bitwise_and(imageFrame, imageFrame, mask = green_mask)

    # For blue color
    blue_mask = cv2.dilate(blue_mask, kernal)
    #res_blue = cv2.bitwise_and(imageFrame, imageFrame,mask = blue_mask)
    
    yellow_mask = cv2.dilate(yellow_mask, kernal)

    # Creating contour to track red color
    contours, hierarchy = cv2.findContours(red_mask,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

    for pic, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        if(area > detectArea):
            TotalCars = TotalCars + 1
            x, y, w, h = cv2.boundingRect(contour)
            imageFrame = cv2.rectangle(imageFrame, (x, y),(x + w, y + h),(0, 0, 255), 2)
            cv2.putText(imageFrame, "Red ", (x, y),cv2.FONT_HERSHEY_SIMPLEX, 1.0,(0, 0, 255))
            Ambulancess = 11;
        cv2.imwrite('Images/red' +str(TotalCars)+'.jpg', imageFrame)

    # Creating contour to track green color
    contours, hierarchy = cv2.findContours(green_mask, cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

    for pic, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        if(area > detectArea):
            TotalCars = TotalCars + 1
            x, y, w, h = cv2.boundingRect(contour)
            imageFrame = cv2.rectangle(imageFrame, (x, y),(x + w, y + h),(0, 255, 0), 2)
            cv2.putText(imageFrame, "Green", (x, y),cv2.FONT_HERSHEY_SIMPLEX,1.0, (0, 255, 0))
        cv2.imwrite('Images/Green' +str(TotalCars)+'.jpg', imageFrame)
    # Creating contour to track green color
    contours, hierarchy = cv2.findContours(yellow_mask, cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
       
    for pic, contour in enumerate(contours):
        area = cv2.contourArea(contour)
        if(area > detectArea):
            TotalCars = TotalCars + 1
            x, y, w, h = cv2.boundingRect(contour)
            imageFrame = cv2.rectangle(imageFrame, (x, y),(x + w, y + h),(0, 255, 0), 2)
            cv2.putText(imageFrame, "Yellow", (x, y),cv2.FONT_HERSHEY_SIMPLEX,1.0, (0, 255, 0))
        cv2.imwrite('Images/Yellow' +str(TotalCars)+'.jpg', imageFrame)
            
    # Creating contour to track blue color
#     contours, hierarchy = cv2.findContours(blue_mask,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
#     for pic, contour in enumerate(contours):
#         area = cv2.contourArea(contour)
#         if(area > detectArea):
#             TotalCars = TotalCars + 1
#             x, y, w, h = cv2.boundingRect(contour)
#             imageFrame = cv2.rectangle(imageFrame, (x, y),(x + w, y + h),(255, 0, 0), 2)
#             cv2.putText(imageFrame, "Blue ", (x, y),cv2.FONT_HERSHEY_SIMPLEX,1.0, (255, 0, 0))
#             Ambulancess = 11;
#         
#     cv2.imwrite('Images/Blue'+str(TotalCars) + '.jpg', imageFrame)
    return (int(TotalCars), int(Ambulancess));



while(1):
    ret, frame = vid.read()
    #cv2.imshow("Main ",capture)
    
    capture = frame[0:480, 140:640]
    cv2.imwrite('Images/Full.jpg', capture)
    Frame = cv2.imread('Images/Full.jpg')
    #cv2.imshow("Main ",capture)

    SplitImages(Frame)  # Split single image into 4 lanes images
   
    Lane1, Ambulance1 = FindCars('Images/top.jpg')
    Lane2, Ambulance2 = FindCars('Images/left.jpg')
    Lane3, Ambulance3 = FindCars('Images/right.jpg')
    Lane4, Ambulance4 = FindCars('Images/bottom.jpg')
    

    #print(round(time.time()*1000) - start_time)
#     if (round(time.time()*1000) - start_time > max_time):
#         start_time = round(time.time()*1000)
#         if(Ambulance1 == 0 and Ambulance2 == 0 and Ambulance3 == 0 and Ambulance4 == 0 ):
# #             ArduinoCommand = str(Lane1) + "," + str(Lane2) + "," + str(Lane3) + "," + str(Lane4) + "&";
# #             ser.write(ArduinoCommand.encode('ascii'))
#             print(ArduinoCommand)
#         else:
#             if(Ambulance1 == 11):
# #                 ArduinoCommand = ("1,0,0,0&");
# #                 ser.write(b'1,0,0,0&');
#                 #print(ArduinoCommand)
#             elif(Ambulance2 == 11):
# #                 ArduinoCommand = ("0,1,0,0&");
# #                 ser.write(b'0,1,0,0&');
#                 #print(ArduinoCommand)
#             elif(Ambulance3 == 11):
# #                 ArduinoCommand = ("0,0,1,0&");
# #                 ser.write(b'0,0,1,0&');
#                 #print(ArduinoCommand)
#         
#             elif(Ambulance4 == 11):
# #                 ArduinoCommand = ("0,0,0,1&");
# #                 ser.write(b'0,0,0,1&');
#                 #print(ArduinoCommand)
#         #print(start_time - round(time.time()*1000) )
        
            
        
    #time.sleep(10)
    if(debug == True):
        print("Lane-1:" , Lane1)
        print("Lane-2:" , Lane2)
        print("Lane-3:" , Lane3)
        print("Lane-4:" , Lane4)
    
        if(Ambulance1 == 11):
            print("Ambulance-1")
        elif(Ambulance2 == 11):
            print("Ambulance-2")
        elif(Ambulance3 == 11):
            print("Ambulance-3")
        elif(Ambulance4 == 11):
            print("Ambulance-4")
            
#    if cv2.waitKey(1) & 0xFF == ord('q'):
#        break
    #time.sleep(5)

# After the loop release the cap object
vid.release()
# Destroy all the windows
cv2.destroyAllWindows()
   
    
    
    
    
    
    
    
    
    
    
    
    
    
