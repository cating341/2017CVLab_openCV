#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main() {
	//VideoCapture cap(0); // open the default camera
	VideoCapture camera(1);  // second camera
	VideoCapture vedio("eat_lemon.mp4");  // load from video
	if (!camera.isOpened() || !vedio.isOpened()) {
		cout << "cannot open camera or vedio" << endl;
		return -1;
	}
	namedWindow("My Camera", 1);
	Mat cameraFrame, vedioFrame;

	while (true)
	{
		camera >> cameraFrame;
		vedio >> vedioFrame;
		if (vedioFrame.empty()) break;
		resize(cameraFrame, cameraFrame, Size(cameraFrame.cols / 4, cameraFrame.rows / 4));
		Mat img = vedioFrame(Rect(0, 0, cameraFrame.cols, cameraFrame.rows));
		rectangle(vedioFrame, Point(0, 0), Point(cameraFrame.cols - 1, cameraFrame.rows - 1), Scalar(0, 0, 0), CV_FILLED);
		addWeighted(img, 1, cameraFrame, 1, 0, img);

		imshow("img", vedioFrame);
		waitKey(33);
	}

	waitKey(0);
	return 0;
}