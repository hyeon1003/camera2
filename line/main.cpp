#include <iostream>
#include <unistd.h>
#include <signal.h>
#include "vison.hpp"
#include "dxl.hpp"
using namespace std;
using namespace cv;

int main(void)
{
    string input="5_lt_cw_100rpm_out.mp4";//동영상 저장경로
    VideoCapture cap(input);//동영상 불러오기
    if (!cap.isOpened()) {	
		cout << "카메라 열기 실패" << endl;
		return -1;
	}
    Mat src,frame,gray,binary; //gray-->그레이 스케일,binary-->이진화
    string dst1 = "appsrc ! videoconvert ! video/x-raw, format=BGRx ! \
    nvvidconv ! nvv4l2h264enc insert-sps-pps=true ! \
    h264parse ! rtph264pay pt=96 ! \
    udpsink host=203.234.58.166 port=8001 sync=false";
    VideoWriter writer1(dst1, 0, (double)30, Size(640, 360), true);
    string dst2 = "appsrc ! videoconvert ! video/x-raw, format=BGRx ! \
    nvvidconv ! nvv4l2h264enc insert-sps-pps=true ! \
    h264parse ! rtph264pay pt=96 ! \
    udpsink host=203.234.58.166 port=8002 sync=false";
    VideoWriter writer2(dst2, 0, (double)30, Size(640, 360), false);
    string dst3 = "appsrc ! videoconvert ! video/x-raw, format=BGRx ! \
    nvvidconv ! nvv4l2h264enc insert-sps-pps=true ! \
    h264parse ! rtph264pay pt=96 ! \
    udpsink host=203.234.58.166 port=8003 sync=false";
    VideoWriter writer3(dst3, 0, (double)30, Size(640, 360), false);
    TickMeter tm;
    while(true)
    {
        tm.start();  // 실행 시간 측정 시작
        cap>>src;
        if(src.empty()){
            cerr<<"frame empty"<<endl;
            return -1;
        }
        frame=src(Rect(0,0,640,90));
        cvtColor(frame,gray,COLOR_BGR2GRAY);
        threshold(gray,binary,128,255,THRESH_BINARY);
        writer1 << frame;
        writer2 << gray;
        writer3 << binary;
        waitKey(30);
        tm.stop();  // 실행 시간 측정 종료
        cout << "Execution time: " << tm.getTimeMilli() << " ms" << endl;// 실행 시간(ms 단위) 및 프레임 수 출력
        tm.reset();
    }
    return 0;
}
