#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat cameraFrame_orig, cameraFrame_canny, cameraFrame_dst;
Mat vedioFrame;
int slider_value = 0;
int slider_max = 100;
double a = 1, b = 0;

void on_trackbar(int value, void* userData) {
	a = 1.0 - b;
	b = (double)slider_value / 100.0;
}

int main() {
	namedWindow("Demo", 1);

	//VideoCapture cap(0); // open the default camera
	VideoCapture camera(1);  // second camera
	VideoCapture vedio("eat_lemon.mp4");  // load from video
	if (!camera.isOpened() || !vedio.isOpened()) {
		cout << "cannot open camera or vedio" << endl;
		return -1;
	}

	createTrackbar("Canny", "Demo", &slider_value, slider_max, on_trackbar);
	on_trackbar(slider_value, 0);

	while (true) {
		camera >> cameraFrame_orig;
		vedio >> vedioFrame;
		if (vedioFrame.empty()) break;
		int camera_cols = cameraFrame_orig.cols / 4;
		int camera_rows = cameraFrame_orig.rows / 4;
		int x = vedioFrame.cols - camera_cols - 1;
		resize(cameraFrame_orig, cameraFrame_orig, Size(camera_cols, camera_rows));
		//blur(cameraFrame_orig, cameraFrame_canny, Size(1, 1));
		Canny(cameraFrame_orig, cameraFrame_canny, 50, 150, 3);
		Mat imgROI = vedioFrame(Rect(x, 0, camera_cols, camera_rows));
		rectangle(vedioFrame, Point(x, 0), Point(vedioFrame.cols - 1, camera_rows - 1), Scalar(0, 0, 0), CV_FILLED);

		cvtColor(cameraFrame_canny, cameraFrame_canny, CV_GRAY2RGB);
		addWeighted(cameraFrame_orig, a, cameraFrame_canny, b, 0, cameraFrame_dst);
		addWeighted(imgROI, 1, cameraFrame_dst, 1, 0, imgROI);
		//imshow("destination", cameraFrame_dst);
		imshow("Demo", vedioFrame);
		waitKey(33);
	}

	waitKey(0);
	return 0;
}