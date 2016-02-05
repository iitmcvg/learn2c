import numpy as np
import cv2


# Generate more mazes
img = cv2.imread('maze.png') # Take input
rows,cols,_ = img.shape
M = cv2.getRotationMatrix2D((cols/2,rows/2),90,1)
img = cv2.warpAffine(img,M,(cols,rows))
first1r, first1c = (25.0/600)*img.shape[0], (531.0/537)*img.shape[1] # A point from segment 1
second1r, second1c = (490.0/600)*img.shape[0], (385.0/537)*img.shape[1] # A point from segment 2

# I am not going to comment much from this portion..
# Take this as an exercise, try understanding it yourself
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
ret,gray = cv2.threshold(gray,10,255,cv2.THRESH_BINARY)
#cv2.imshow('Input', gray)

# Computing distance transform
dt = cv2.distanceTransform(gray, distanceType = 3, maskSize = 5)
dt = np.array(dt)
dt = ((dt - dt.min()) / dt.max()) * 255
dt = np.array(dt, dtype = np.uint8)
for i in range(img.shape[0]) :
  for j in range(img.shape[1]) :
    img[i][j][0] = dt[i][j]
    img[i][j][1] = dt[i][j]
    img[i][j][2] = dt[i][j]

# Setting marker points
marker = np.array(gray, dtype=np.int32)
marker[:][:] = 0
marker[first1r][first1c] = 126
marker[second1r][second1c] = 254

cv2.watershed(img, marker)
final = np.zeros(img.shape)

#Plotting
inv_maze = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY_INV)[1]
gray[:] = marker + 1
path = cv2.threshold(gray, 1, 255, cv2.THRESH_BINARY)[1]

kernel = np.ones((3,3),np.uint8)
path = cv2.erode(path,kernel,iterations = 1)

final[:,:,0] =path & ~inv_maze
final[:,:,2] =   ~inv_maze
final[:,:,1] = path & ~inv_maze

#Padding the image
img = cv2.copyMakeBorder(img,10,10,10,10,cv2.BORDER_CONSTANT,value=[255,255,255])
final = cv2.copyMakeBorder(final,10,10,10,10,cv2.BORDER_CONSTANT,value=[255,255,255])

###EXERCISE 1 : mark entry and exit with circles
#entry = (x,y)
#exit = (x,y)
#cv2.circle(final,entry,10,(255,0,0), -1)
#cv2.circle(final,exit,10,(255,0,0), -1)

resultImg = np.hstack((img, final))
cv2.imshow("Maze solver", resultImg)

#cv2.imshow('Watershed result', gray)
#cv2.imshow('Path', path)
cv2.waitKey(0)
cv2.destroyAllWindows()
