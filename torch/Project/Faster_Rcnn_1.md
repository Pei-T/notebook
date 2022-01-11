# A Simple Pipeline to Train PyTorch Faster RCNN Object Detection Model 
[debuggercafe.com](https://debuggercafe.com/a-simple-pipeline-to-train-pytorch-faster-rcnn-object-detection-model/)
In one of the previous posts, we saw how to train the PyTorch Faster RCNN model on a custom dataset. That was a good starting point of a simple pipeline that we can use to train the PyTorch Faster RCNN model for object detection. So, in this tutorial, we will see how to use the pipeline (and slightly improve upon it) to try to train the PyTorch Faster RCNN model for object detection on any custom dataset.

Note that most of the code will remain similar to what we did in the previous PyTorch Faster RCNN model training post. There are a few changes (small but significant) that we will see in this post. Let’s check out what all we will cover and what are all the changes.

* The code is much simpler now. Almost any dataset that is in Pascal VOC format can be used to train the model.
The utility code and training code sit separately now making it significantly easier to change in the future.
* You will be getting a zip file with all the scripts in this post. You will also have access to the GitHub repo, which I intend to maintain for considerable time into the future.
* We will check our PyTorch Faster RCNN model training pipeline using the Uno Cards dataset from Roboflow.
* Before going into the training, we will explore the Uno Cards datasetset and try to understand the types of images we have.
* As most of the code will remain similar to the previous post, the code explanation will be minimal here. We will focus on the major changes and just go through a high-level explanation of the script. You can think of this post as less of a tutorial and more of a framework/repo explanation. Any suggestion is highly appreciated

Let’s start with knowing more about the dataset.

## The Uno Cards Detection Dataset
To train the PyTorch Faster RCNN model for object detection, we will use the Uno Cards dataset from Roboflow here.
If you visit the website, you will find that there are two different versions of the dataset. They are:

* raw: These contain the the original 8992 images.
* v1: This is an augmented version of the dataset containing 21582 images.
## The raw Dataset Version
To keep the training time short, we will use the original raw version of the dataset.
To be fair, the original version is not that small as well. It still contains almost 9000 images and around 30000 annotations. We have a good amount of data here.
The dataset consists of 15 classes in total.
The above figure shows the distribution of images across different classes. Still, it does not give us a good idea of which labels correspond to which images/objects in the dataset. These are just numbers. Let’s try to demystify that first.
Okay! This gives us a much better idea about the images and the corresponding classes.

Numbers 0 to 9 on the card have the same labels, that is, 0 to 9. That’s 10 labels there.
* Label 10 corresponds to +4 on card.
* Label 11 is +2 on the card.
* The double arrow on the card has a mapping to label 12.
* The phi (ϕ) corresponds to label 13.
* And finally, the colored circle (or wildcard symbol) is label 14.

The above points obviously do not contain the exact terms of Uno cards. But it is helpful enough for us so that we can deal with the deep learning stuff and know whether our model is correctly predicting everything or not. If you want to know about Uno cards, consider visiting this link.

Before moving further, it is important that you download the dataset from this link. Download the Pascal VOC XML format as shown in the image below.
# The Directory Structure
The following block shows the directory structure that we will use for this project.
``` dir
│   config.py
│   custom_utils.py
│   datasets.py
│   inference.py
│   inference_video.py
│   model.py
│   train.py
├───data
│   ├───Uno Cards.v2-raw.voc
│   │   ├───test
│   │   ├───train
│   │   └───valid
│   └───uno_custom_test_data
├───inference_outputs
│   ├───images
│   └───videos
├───outputs
│   ├───best_model.pth
│   ├───last_model.pth
│   ├───train_loss.png
│   ├───valid_loss.png
```
* We have 7 Python files. We will not go into the details of the content of these yet. It will be much more beneficial to discuss these when we enter the coding section.
* The data directory contains the Uno Cards datasets. After downloading the dataset, be sure to extract it and have it in the same structure as above. The train, valid, and test subdirectories contain the JPG images and the corresponding XML files for the annotations.
* The inference_outputs directory will contain all the outputs that we will be genered by running the inference.py and inference_video.py script.
* Then we have the outputs directory. This will hold the trained models and loss graphs when we carry out the training.

If you have downloaded the zip file for this post, then you already have almost everything in place. You just need to extract the dataset in the correct structure inside the data directory.

Downloading the code files will also give you access to the trained models. You need not train the models again as that can be a time-consuming and resource-intensive process. If you wish, you may train for a few iterations just to check how the training is going and move on to the next phase in the post.
## The PyTorch Version
We will use PyTorch 1.10 for coding out the Faster RCNN training pipeline. It is the latest version of PyTorch at the time of writing this post.

You may choose to use whatever new version of PyTorch that is available when you are reading this. Hopefully, everything will run fine.

### Other Library Dependencies
The code uses other common computer vision libraries like OpenCV and Albumentations. You may install them as you code along if you don’t already have them. While installing the Albumentations library, be sure to install the latest version as many new features get added frequently into it.

We will use the Albumentations library for image augmentation for object detection. If you want to learn more about the topic, please refer to these two tutorials:

Bounding Box Augmentation for Object Detection using Albumentations
Applying Different Augmentations to Bounding Boxes in Object Detection using Albumentations
### Code to Train the PyTorch Faster RCNN Model
From here onward, we will start with the coding part of the post. As discussed earlier, we will not get into the very details of the code. Rather, we will try to understand what each Python file does on a high level. Although some of the code has changed along with a few file names, you can refer to this post for a detailed explanation of the code.

We have seven Python files with us. Let’s tackle each of them in the following order:
```
config.py
custom_utils.py
datasets.py
model.py
train.py
inference.py
inference_video.py
Let’s start with the configuration file.
```
### Setting Up the Training Configuration
We will write all the training configurations in the config.py file.