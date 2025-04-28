# Import packages
import cv2
import numpy as np

img = cv2.imread('Images/Full.jpg')
print(img.shape)  # Print image shape
cv2.imshow("original", img)

# cropped = img[start_row:end_row, start_col:end_col]
# right = img[156:313, 424:576] # Slicing to crop the image
# left = img[173:330, 118:250] # Slicing to crop the image
# top = img[6:140, 248:420] # Slicing to crop the image
# bottom = img[340:468, 259:424] # Slicing to crop the image

right = img[185:345, 372:530] # Slicing to crop the image
# left = img[173:330, 118:250] # Slicing to crop the image
# top = img[6:140, 248:420] # Slicing to crop the image
# bottom = img[340:468, 259:424] # Slicing to crop the image

# Display cropped image
# cv2.imshow("cropped1", top)
# cv2.imshow("cropped2", left)
cv2.imshow("cropped3", right)
# cv2.imshow("cropped4", bottom)

cv2.waitKey(0)
cv2.destroyAllWindows()