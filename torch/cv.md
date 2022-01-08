# CV
## 0. module
* pip install opencv-python
* import cv2
* cv 默认size，高×宽×颜色通道

## 1. Resize
```py
im_orig = cv2.imread('./Elegent_Girl.jpg')
im = cv2.resize(im_orig, None, None, fx=im_scale, fy=im_scale, interpolation=cv2.INTER_LINEAR)
```

## 2. show
```py
# jupyter not support
cv2.namedWindow("Image")#new window
cv2.imshow('Image', im)
```

## 3. read
```py
im_orig = cv2.imread('./Elegent_Girl.jpg')
```