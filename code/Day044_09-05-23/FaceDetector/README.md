#link: https://medium.com/analytics-vidhya/building-a-face-detector-with-opencv-in-c-8814cd374ea1

# Face Detector
Using OpenCV, the task is to read video from the camera, process the frame to detect human faces, and display the video highlighting the faces that have been detected showing the confidence score. 

We use the `cv::dnn::Net` class to load weights from OpenCV's DNN Face Detector, a pre-trained Caffe model based on the Single Shot-Multibox Detector (SSD) that uses ResNet-10 architecture as its backbone. It was introduced post OpenCV 3.3 in its deep neural network module. 

DNN performance comes well positioned in a comparison of vs alternatives such as Haar Cascade classifier, Dlib or MTCNN, e.g. in terms of speed, dealing with lighting, partial occlusion and head quick movements and angles, see this article: https://towardsdatascience.com/face-detection-models-which-to-use-and-why-d263e82c302c 

Note: The Caffee model files in the original link (`deploy.prototxt` and `res10_300x300_ssd_iter_140000_fp16.caffemodel`) did not work, I took them instead from this python implementation: https://www.analyticsvidhya.com/blog/2022/04/face-detection-using-the-caffe-model/ (repo: https://github.com/Aman-Preet-Singh-Gulati/face-detection-caffee )

However, the original source is: https://github.com/opencv/opencv/tree/master/samples/dnn#face-detection. 

Note this comment:

> To achieve the best accuracy run the model on BGR images resized to 300x300 applying mean subtraction of values (104, 177, 123) for each blue, green and red channels correspondingly.
>

The files can be download from here: https://github.com/opencv/opencv/blob/4.x/samples/dnn/face_detector/. Check out `weights.meta4` for the link to `res10_300x300_ssd_iter_140000_fp16.caffemodel` (5Mb)

Credit sample video: Thirdman https://www.pexels.com/video/woman-taking-selfie-with-friends-8020479/

#tags: 

- [ ] basics
- [ ] algorithms
- [ ] data_structures: trees, graphs
- [ ] strings: regex
- [ ] dates_times: timezones
- [ ] file_management: input, output, folders and files
- [ ] testing
- [ ] exceptions
- [ ] logging
- [ ] object_oriented_programming
- [ ] GUI
- [ ] plotting_data
- [ ] CLI
- [ ] arduino
- [ ] ROS
- [ ] AI_tools: chat GPT
- [ ] databases
- [ ] API
- [ ] web_scraping
- [x] OpenCV