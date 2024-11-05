#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    string src = "nvarguscamerasrc sensor-id=0 ! \
    video/x-raw(memory:NVMM), width=(int)640, height=(int)360, \
    format=(string)NV12, framerate=(fraction)30/1 ! \
    nvvidconv flip-method=0 ! video/x-raw, \
    width=(int)640, height=(int)360, format=(string)BGRx ! \
    videoconvert ! video/x-raw, format=(string)BGR ! appsink";

    VideoCapture source(src, CAP_GSTREAMER);
    if (!source.isOpened()) {
        cout << "Camera error" << endl;
        return -1;
    }

    string dst1 = "appsrc ! videoconvert ! video/x-raw, format=BGRx ! \
    nvvidconv ! nvv4l2h264enc insert-sps-pps=true ! \
    h264parse ! rtph264pay pt=96 ! \
    udpsink host=203.234.58.166 port=8001 sync=false";
    
    VideoWriter writer1(dst1, 0, (double)30, Size(640, 360), true);
    if (!writer1.isOpened()) {
        cerr << "Writer open failed!" << endl;
        return -1;
    }

    string dst2 = "appsrc ! videoconvert ! video/x-raw, format=BGRx ! \
    nvvidconv ! nvv4l2h264enc insert-sps-pps=true ! \
    h264parse ! rtph264pay pt=96 ! \
    udpsink host=203.234.58.166 port=8002 sync=false";
    
    VideoWriter writer2(dst2, 0, (double)30, Size(640, 360), false);
    if (!writer2.isOpened()) {
        cerr << "Writer open failed!" << endl;
        return -1;
    }

    string dst3 = "appsrc ! videoconvert ! video/x-raw, format=BGRx ! \
    nvvidconv ! nvv4l2h264enc insert-sps-pps=true ! \
    h264parse ! rtph264pay pt=96 ! \
    udpsink host=203.234.58.166 port=8003 sync=false";
    
    VideoWriter writer3(dst3, 0, (double)30, Size(640, 360), false);
    if (!writer3.isOpened()) {
        cerr << "Writer open failed!" << endl;
        return -1;
    }

    Mat frame, gray, binary;
    TickMeter tm;  // TickMeter 객체 생성
    int frameCount = 0;  // 프레임 수 카운트 변수

    while (true) {
        tm.start();  // 실행 시간 측정 시작
        frameCount++;  // 프레임 수 증가

        source >> frame;
        if (frame.empty()) {
            cerr << "frame empty!" << endl;
            break;
        }

        // 그레이스케일 변환
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // 이진 변환
        threshold(gray, binary, 128, 255, THRESH_BINARY);

        // 영상 전송
        writer1 << frame;
        writer2 << gray;
        writer3 << binary;

        

        
        if (waitKey(30) >= 0) break;
		// TickMeter 초기화
		tm.stop();  // 실행 시간 측정 종료
		// 실행 시간(ms 단위) 및 프레임 수 출력
        cout << "Frame: " << frameCount << " | Execution time: " << tm.getTimeMilli() << " ms" << endl;
        tm.reset();
    }

    return 0;
}
