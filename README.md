# 2001212 이승현

이 코드는 OpenCV와 GStreamer를 사용하여 Jetson 카메라로부터 영상을 받아 그레이스케일과 이진(binary) 영상으로 변환한 후, 세 가지 영상을 UDP 네트워크 스트림을 통해 PC로 전송하는 프로그램 입니다.

main.cpp 카메라로부터 영상을 가져오고, 변환하여 전송하는 모든 작업을 수행합니다.

src 변수는 GStreamer 파이프라인을 정의하고 영상 데이터를 OpenCV에서 사용하기 위해서 BGR형식으로 바꾼다

VideoCapture 객체를 사용하여 Gstreamer 파이프라인을 통해 카메라 영상을 캡처한다.

dst1 = 컬러 영상을 전송할 GStreamer파이프라인 정의
dst2 = 그레이 영상을 전송할 GStreamer파이프라인 정의
dst3 = 이진 영상을 전송할 GStreamer파이프라인 정의

반복문을 통해 지속적으로 영상을 처리하고 전송한다.




![image](https://github.com/user-attachments/assets/b78b15af-fcf6-46c7-918e-0fd9cda7d89c)


사진을 보면 33ms정도가 나오는것을 확인할 수 있다.
