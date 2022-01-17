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

## 4. cv to numpy

```py
# 1、cv2.imread()接口读图像，读进来直接是BGR 格式数据格式在 0~255
# 需要特别注意的是图片读出来的格式是BGR，不是我们最常见的RGB格式，颜色肯定有区别。
image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB).astype(np.float32)
 ```
