#ifndef VISION_HPP
#define VISION_HPP

#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

// 전처리 함수: 입력 영상을 그레이스케일로 변환하고 이진화 및 자르기 처리
void preprocess(VideoCapture& source, Mat& frame, Mat& gray, Mat& thresh);

// 라인 후보 객체를 찾는 함수
void findObjects(const Mat& thresh, Point& tmp_pt, Mat& result, Mat& stats, Mat& centroids);

// 객체를 표시하는 함수
void drawObjects(const Mat& stats, const Mat& centroids, const Point& tmp_pt, Mat& result);

// 에러 계산 함수: 라인의 중심과 영상 중심의 차이를 반환
int getError(const Mat& result, const Point& tmp_pt);

#endif
