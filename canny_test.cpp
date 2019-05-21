//#include <opencv2/opencv.hpp>  
//#include <opencv2/highgui/highgui.hpp>  
//#include <opencv2/imgproc/imgproc.hpp>  
//
//using namespace std;
//using namespace cv;
//
//
//Mat g_srcImage, g_dstImage, g_midImage;//原始图、中间图和效果图  
//vector<Vec4i> g_lines;//定义一个矢量结构g_lines用于存放得到的线段矢量集合  
//					  //变量接收的TrackBar位置参数  
//int g_nthreshold = 100;
//
//static void showImage1(int, void*);
//static void showImage2(int, void*);
//int thred1 = 23;
//int thred2 = 55;
//// 23 55
//int main()
//{
//	//载入原始图和Mat变量定义     
//	g_srcImage = imread("12.jpg", 0);
//	//显示原始图    
//	imshow("Origin Image", g_srcImage);
//	//创建滚动条  
//	namedWindow("Dst Image", 1);
//
//	createTrackbar("阈值1", "Dst Image", &thred1, 200, showImage1);
//	createTrackbar("阈值2", "Dst Image", &thred2, 200, showImage2);
//	//进行边缘检测和转化为灰度图  
//	Canny(g_srcImage, g_midImage, thred1, thred2, 3);//进行一次canny边缘检测  
//	cvtColor(g_midImage, g_dstImage, CV_GRAY2BGR);//转化边缘检测后的图为灰度图  
//												  //调用一次回调函数，调用一次HoughLinesP函数  
//	showImage1(thred1, 0);
//	showImage2(thred2, 0);
//	//显示效果图    
//	imshow("Dst Image", g_dstImage);
//	waitKey(0);
//	return 0;
//}
//
//static void showImage1(int thred1, void*) {
//	Canny(g_srcImage, g_midImage, thred1, thred2, 3);//进行一次canny边缘检测  
//	imshow("Dst Image", g_midImage);
//}
//
//static void showImage2(int thred2, void*) {
//	Canny(g_srcImage, g_midImage, thred1, thred2, 3);//进行一次canny边缘检测  
//	imshow("Dst Image", g_midImage);
//}