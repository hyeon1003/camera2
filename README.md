# 2001212 이승현

이 코드는 OpenCV와 GStreamer를 사용하여 Jetson 카메라로부터 영상을 받아 그레이스케일과 이진(binary) 영상으로 변환한 후, 세 가지 영상을 UDP 네트워크 스트림을 통해 PC로 전송하는 프로그램 입니다.

main.cpp 카메라로부터 영상을 가져오고, 변환하여 전송하는 모든 작업을 수행합니다.

src 변수는 GStreamer 파이프라인을 정의하고 



![image](https://github.com/user-attachments/assets/b78b15af-fcf6-46c7-918e-0fd9cda7d89c)


사진을 보면 33ms정도가 나오는것을 확인할 수 있다.
