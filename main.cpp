#include<iostream>
#include<math.h>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat ChooseROI(Mat src_img, Mat template_img, Mat dst_img);
Mat HoughCircle(Mat gray_img, Mat midd_img);
Mat HoughLine(Mat midd_img, Mat midd_line_image);
float CalculateValue();

Point circle_center;
int circle_radius;

Vec4i l;
Vec4i cho_l;

int main(int argc, char** argv)
{
	// Define Window Name
	char window_name[] = "Demo";

	// Define File Path
	char src_image_path[] = "11.jpg";
	char template_path[] = "05.jpg";

	// Create a named window with the name of the file
	cvNamedWindow(window_name);

	// Define Variables
	Mat src_img, template_img, midd_img, midd_line_img,gray_img, dst_img;

	// Load the image from the given file name
	src_img = imread(src_image_path, 1);
	template_img = imread(template_path, 1);

	// Check if image is loaded fine
	/*if (src_img.empty()) {
		printf(" Error opening image\n");
		printf(" Program Arguments: [image_name -- default %s] \n", src_image_path);
		return -1;
	}*/

	// Choose a Region Of Interest(ROI)
	//midd_img = ChooseROI(src_img, template_img, midd_img);
	midd_img = src_img.clone();
	midd_line_img = src_img.clone();

	// gray
	cvtColor(midd_img, gray_img, COLOR_BGR2GRAY);

	// medianBlur filter
	medianBlur(gray_img, gray_img, 5);

	// HoughCircle
	midd_img = HoughCircle(gray_img, midd_img);

	// HoughLine
	midd_line_img = HoughLine(midd_img, midd_line_img);

	// Line Specify
	// None now

	// Calculate Value
	float angle;
	angle = CalculateValue();

	cout << "偏转角度为： " << angle << "度";
	
	// Show and save the dstImage
	namedWindow(window_name, CV_WINDOW_NORMAL);
	moveWindow(window_name, 100, 100);
	imshow(window_name, midd_img);
	waitKey(0);

	// Pause
	waitKey(0);
	destroyAllWindows();

	return 0;
}

Mat ChooseROI(Mat src_img, Mat template_img, Mat midd_img) {
	
	// resize images
	//resize(src_img, src_img, Size(), 0.2, 0.2);
	//resize(template_img, template_img, Size(), 0.2, 0.2);

	// match template 
	int match_cols = src_img.cols - template_img.cols + 1;
	int match_rows = src_img.rows - template_img.rows + 1;
	
	midd_img.create(match_cols, match_rows, CV_32FC1);

	matchTemplate(src_img, template_img, midd_img, CV_TM_SQDIFF_NORMED);
	normalize(midd_img, midd_img, 0, 1, NORM_MINMAX, -1, Mat());

	double minVal = -1;
	double maxVal;
	Point minLoc;
	Point maxLoc;
	Point matchLoc;

	minMaxLoc(midd_img, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	matchLoc = minLoc;

	rectangle(src_img, matchLoc, Point(matchLoc.x + template_img.cols, matchLoc.y + template_img.rows), Scalar(0, 255, 0), 2, 8, 0);
	// Chooses the input image

	Rect rect(matchLoc.x, matchLoc.y, template_img.cols, template_img.rows);

	midd_img = src_img(rect);

	return midd_img;
}

Mat HoughCircle(Mat gray_img, Mat midd_img) {
	
	vector<Vec3f> circles;

	HoughCircles(gray_img, circles, HOUGH_GRADIENT, 1,
		gray_img.rows / 16,     // change this value to detect circles with different distances to each other
		100, 30, 127, 138		// change the last two parameters
								// (min_radius & max_radius) to detect larger circles
	);

	for (size_t i = 0; i < circles.size(); i++)
	{
		Vec3i c = circles[i];
		circle_center = Point(c[0], c[1]);
		// circle center
		// Scalar B G R
		circle(midd_img, circle_center, 1, Scalar(0, 0, 255), 3, LINE_AA);
		// circle outline
		circle_radius = c[2];
		circle(midd_img, circle_center, circle_radius, Scalar(255, 255, 0), 3, LINE_AA);

		// cout << circle_center.x << " " <<circle_center.y << " " << circle_radius << endl;
	}

	return midd_img;
}

Mat HoughLine(Mat midd_img, Mat midd_line_img) {
	
	Mat dst_img, gray_img;

	cvtColor(midd_img, gray_img, COLOR_BGR2GRAY);

	// CannyDetect
	Canny(gray_img, midd_line_img, 23, 55, 3);

	// convert cannied image to a gray one  
	cvtColor(midd_line_img, dst_img, CV_GRAY2BGR);

	// define a vector to collect all possible lines 
	vector<Vec4i> mylines;
	int g_nthreshold = 39;
	HoughLinesP(midd_line_img, mylines, 1, CV_PI / 180, g_nthreshold + 1, 20, 5);

	// draw every line by using for
	for (size_t i = 0; i < mylines.size(); i++)
	{
		l = mylines[i];
		if (((circle_center.x - 10) <= l[0]) && (l[0] <= (circle_center.x + 10)))
			if (((circle_center.y - 10) <= l[1]) && (l[1] <= (circle_center.y + 10)))
				if (((circle_center.x - circle_radius) <= l[2]) && (l[2] <= (circle_center.x + circle_radius)))
					if (((circle_center.y - circle_radius) <= l[3]) && (l[3] <= (circle_center.y + circle_radius)))
					{
						//cout << Point(l[0], l[1]) << " " << Point(l[2], l[3]) << " " << l[0] << " " << circle_center.x - circle_radius << " " << circle_center.x + circle_radius << endl;
						// line(midd_img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23, 180, 55), 2, CV_AA);
						cho_l = l;
						line(midd_img, Point(circle_center.x, circle_center.y), Point(cho_l[2], cho_l[3]), Scalar(23, 180, 55), 2, CV_AA);
					}
	}

	return midd_img;
}

float CalculateValue() {
	
	float angle = 0;
	float x, y;

	x = cho_l[2] - cho_l[0];
	y = -(cho_l[3] - cho_l[1]);

	// Angle Correction

	if (cho_l[2] > circle_center.x)
		if (cho_l[3] > circle_center.y)
			// first quadrant
			angle = ((3 * 3.14159 / 2) - atan2(x, y)) * 180 / 3.14159;
		else
			// second quadrant
			angle = ((3 * 3.14159 / 2) - atan2(x, y)) * 180 / 3.14159;
	else
		if (cho_l[3] < circle_center.y)
			// third quadrant
			angle = ((-3.14159 / 2) - atan2(x, y)) * 180 / 3.14159;
		else
			// fourth quadrant
			angle = ((3 * 3.14159 / 2) - atan2(x, y)) * 180 / 3.14159;

	return angle;
}


