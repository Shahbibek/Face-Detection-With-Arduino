import cv2
from cvzone.FaceDetectionModule import FaceDetector
from cvzone.SerialModule import SerialObject

cap = cv2.VideoCapture(0)
detector = FaceDetector()
arduino = SerialObject("COM6")

while(True):
    success, img = cap.read()

    img, bboxs = detector.findFaces(img)

    if bboxs:
        arduino.sendData([0])
        # print(arduino.sendData([1]))
        # print("1", bboxs)
    else:
        arduino.sendData([1])
        # print(arduino.sendData([0]))
        # print("0", bboxs)
         

    cv2.imshow("Image", img)
    cv2.waitKey(1)

    