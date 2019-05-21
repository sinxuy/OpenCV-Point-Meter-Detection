//// Test.cpp : 定义控制台应用程序的入口点。
//
////#include "opencv2/cv.hpp"
//#include "opencv2/opencv.hpp"
//#include "opencv2/core.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/imgproc.hpp"
//#include <iostream>
//#include <string>
//#include <stack>
//using namespace cv;
//using namespace std;
//
//typedef uchar BYTE;
//
//void imgreverse(Mat srcImg, Mat outImg, int w, int h);
//void thresholdImg(Mat inputImg, Mat outImg, BYTE thr, int w, int h);
//void HilditchThin(BYTE* inputImg, BYTE* outImg, int w, int h);
//void ZhangFastThin(BYTE* inputimg, BYTE* outImg, int w, int h);
//void PavlidisThin(BYTE* inputImg, BYTE* outImg, int w, int h);
//void RosenfeldThin(BYTE* inputImg, BYTE* outImg, int w, int h);
//void BasedIndexTableThin(BYTE* inputImg, BYTE* outImg, int w, int h);
//void MorphologyThin(BYTE* inputImg, BYTE* outImg, int w, int h);
//void MorphologySharp(BYTE* inputImg, BYTE* outImg, int w, int h);
//int main()
//{
//	Mat pImageBuffer;
//	pImageBuffer = imread("11.jpg", 1);
//
//	//灰度图像
//	Mat srcImg;
//	srcImg.create(pImageBuffer.size(), CV_8UC1);
//	cvtColor(pImageBuffer, srcImg, CV_BGR2GRAY);
//
//	int w = srcImg.cols;
//	int h = srcImg.rows;
//	int n = w * h;
//
//	//翻转图像
//	//imgreverse(srcImg, srcImg,w,h);
//
//	//二值化图像
//	thresholdImg(srcImg, srcImg, 50, w, h);
//
//	//待细化图像
//	BYTE* inputImg = new BYTE[n];
//	memcpy(inputImg, srcImg.data, n);
//
//	//显示图像
//	Mat imgshow;
//	imgshow.create(srcImg.size(), srcImg.type());
//
//
//	//Zhang并行快速算法
//	BYTE* ZhangFastImg = new BYTE[n];
//	ZhangFastThin(inputImg, ZhangFastImg, w, h);
//	memcpy(imgshow.data, ZhangFastImg, n);
//	imshow("ZhangFast...", imgshow);
//	delete[] ZhangFastImg;
//
//	//Hilditch算法
//	BYTE* HilditchImg = new BYTE[n];
//	HilditchThin(inputImg, HilditchImg, w, h);
//	memcpy(imgshow.data, HilditchImg, n);
//	imshow("Hilditch...", imgshow);
//	delete[] HilditchImg;
//
//
//	//Pavlidis算法
//	BYTE* PavlidisImg = new BYTE[n];
//	PavlidisThin(inputImg, PavlidisImg, w, h);
//	memcpy(imgshow.data, PavlidisImg, n);
//	imshow("Pavlidis...", imgshow);
//	delete[] PavlidisImg;
//
//	//Rosenfeld算法
//	BYTE* RosenfeldImg = new BYTE[n];
//	RosenfeldThin(inputImg, RosenfeldImg, w, h);
//	memcpy(imgshow.data, RosenfeldImg, n);
//	imshow("Rosenfeld...", imgshow);
//	delete[] RosenfeldImg;
//
//	//BasedIndexTableThin算法
//	BYTE* BasedIndexTableImg = new BYTE[n];
//	BasedIndexTableThin(inputImg, BasedIndexTableImg, w, h);
//	memcpy(imgshow.data, BasedIndexTableImg, n);
//	imshow("BasedIndexTable...", imgshow);
//	delete[] BasedIndexTableImg;
//
//
//	//MorphologyThin算法
//	BYTE* MorphologyImg = new BYTE[n];
//	MorphologyThin(inputImg, MorphologyImg, w, h);
//	memcpy(imgshow.data, MorphologyImg, n);
//	imshow("Morphology...", imgshow);
//	delete[] MorphologyImg;
//
//
//	//删除动态申请的内存
//	delete[] inputImg;
//
//	waitKey(0);
//	return 0;
//}
//
////图像反转
//void imgreverse(Mat srcImg, Mat outImg, int w, int h)
//{
//	double sum = 0;
//	for (int i = 0; i < h; i++)
//	{
//		uchar* pin = srcImg.ptr<uchar>(i);
//		for (int j = 0; j <w; j++)
//		{
//			sum += pin[j];
//		}
//	}
//
//	double avr = sum / (w*h);
//
//	if (avr > 128)
//	{
//		for (int i = 0; i < h; i++)
//		{
//			uchar* pin = srcImg.ptr<uchar>(i);
//			uchar* pout = outImg.ptr<uchar>(i);
//			for (int j = 0; j <w; j++)
//			{
//				pout[j] = 255 - pin[j];
//
//			}
//		}
//	}
//
//}
//
////阈值分割，二值化图像
//void thresholdImg(Mat inputImg, Mat outImg, BYTE thr, int w, int h)
//{
//	for (int i = 0; i<h; ++i)
//	{
//		BYTE* pin = inputImg.ptr<BYTE>(i);
//		BYTE* pout = outImg.ptr<BYTE>(i);
//		for (int j = 0; j < w; ++j)
//		{
//			if (pin[j] >= thr)
//				pout[j] = 1;
//			else
//				pout[j] = 0;
//
//		}
//	}
//}
//
////Zhang并行快速细化算法
//void ZhangFastThin(BYTE* inputImg, BYTE* outImg, int w, int h)
//{
//	int sizen = w * h;
//	memcpy(outImg, inputImg, sizen);
//
//	BYTE foreground = 1; //前景点
//	BYTE background = 1 - foreground;//背景点
//
//									 //8领域编码
//									 //p3  p2  p1
//									 //p4   p   p0
//									 //p5  p6  p7
//	static int d[8] = { 1, 1 - w, -w, -1 - w, -1, w - 1, w, w + 1 };
//
//	bool bOdd = true;
//	bool bDel = true;
//	bool *mask = new bool[sizen];
//	memset(mask, 0, sizen);
//
//	while (bDel || bOdd)
//	{
//		bDel = false;
//		for (int i = 1; i < h - 1; i++)
//			for (int j = 1; j < w - 1; j++)
//			{
//				int k = i * w + j;
//
//				//条件1：p必须是前景点
//				if (outImg[k] != foreground) continue;
//
//				//条件2：2 <= N(p) <= 6
//				int np = 0;
//				for (int i = 0; i < 8; i++)
//					if (outImg[k + d[i]] != foreground) np++;
//				if (np < 2 || 6 < np) continue;
//
//				//条件3：S(p) = 1
//				int sp = 0;
//				for (int i = 0; i < 8; i++)
//					if (outImg[k + d[i & 7]] != foreground && outImg[k + d[(i + 1) & 7]] != background) sp++;
//				if (sp != 1) continue;
//
//				if (bOdd)
//				{
//					//条件4：p2*p0*p6 = 0
//					if (outImg[k + d[2]] != background && outImg[k + d[0]] != background && outImg[k + d[6]] != background) continue;
//					//条件5：p0*p6*p4 = 0
//					if (outImg[k + d[0]] != background && outImg[k + d[6]] != background && outImg[k + d[4]] != background) continue;
//				}
//				else
//				{
//					//条件4：p6*p4*p2==0
//					if (outImg[k + d[6]] != background && outImg[k + d[4]] != background && outImg[k + d[2]] != background) continue;
//					//条件5：p4*p2*p0==0
//					if (outImg[k + d[4]] != background && outImg[k + d[2]] != background && outImg[k + d[0]] != background) continue;
//				}
//				bDel = true;
//				mask[k] = true; //标记删除
//			}
//
//		bOdd = !bOdd;
//		if (!bDel) continue;
//		//将标记删除的点置为背景色
//		for (int i = 0; i < sizen; ++i)
//		{
//			if (mask[i])
//				outImg[i] = background;
//		}
//	}
//
//	delete[] mask;
//
//	for (int i = 0; i < sizen; i++) outImg[i] *= 255;
//}
//
////Pavlidis图像细化算法
//void FillNeighbor8(BYTE* p, BYTE* list, int w)
//{
//	list[0] = p[1];
//	list[1] = p[-w + 1];
//	list[2] = p[-w];
//	list[3] = p[-w - 1];
//	list[4] = p[-1];
//	list[5] = p[w - 1];
//	list[6] = p[w];
//	list[7] = p[w + 1];
//}
//void PavlidisThin(BYTE* inputImg, BYTE* outImg, int w, int h)
//{
//	int sizen = w * h;
//	memcpy(outImg, inputImg, sizen);
//
//	//8邻域编码
//	//p3  p2  p1
//	//p4   p   p0
//	//p5  p6  p7
//	BYTE  list[8];
//
//	//图像边框像素值为0
//	for (int i = 0; i< h; i++)
//		for (int j = 0; j<w; j++)
//		{
//			int ij = i * w + j;
//
//			if (i == 0 || i == (h - 1) || j == 0 || j == (w - 1))
//				outImg[ij] = 0;
//		}
//
//	BYTE bdr1, bdr2, bdr4, bdr5;
//	int   b;
//
//	//循环标志
//	bool loop = true;
//
//	while (loop)
//	{
//		BYTE* img = outImg;
//		//第一个循环，取得前景轮廓，轮廓用2表示
//		for (int i = 1; i< h - 1; i++)
//		{
//			img += w;
//			for (int j = 1; j < w - 1; j++)
//			{
//				BYTE* p = img + j;
//
//				if (p[0] != 1)
//					continue;
//
//				FillNeighbor8(p, list, w);
//
//				//bdr1是2进制表示的p0...p6p7排列，10000011,p0=1,p6=p7=1
//				bdr1 = 0;
//				for (int k = 0; k<8; k++)
//				{
//					if (list[k] >= 1)
//						bdr1 |= 0x80 >> k;
//				}
//
//				//内部点;p0, p2, p4, p6都是为1, 非边界点，所以继续循环
//				//0xaa
//				//  0   1   0   
//				//  1         1
//				//  0   1    0
//				if ((bdr1 & 0xaa) == 0xaa)
//					continue;
//
//				//不是内部点，则是边界点(轮廓), 标记为2
//				p[0] = 2;
//
//				b = 0;
//
//				for (int k = 0; k <= 7; k++)
//				{
//					b += bdr1 & (0x80 >> k);
//				}
//				//在边界点中，等于1，则是端点，等于0，则是孤立点，此时标记3
//				if (b <= 1)
//					p[0] = 3;
//
//				//此条件说明p点是中间点，移去会引起断裂
//				// 0x70        0x7         0x88      0xc1        0x1c      0x22      0x82     0x1      0xa0     0x40     0x28    0x10       0xa      0x4
//				// 0 0 0     0  1  1     1  0   0    0   0   0    1  1  0    0   0   1  0  0  1  0 0 0    0  0  0   0 0 0    1  0  0   0  0  0  1  0  1   0 1 0
//				// 1    0     0      1     0       0    0        1    1      0    0        0  0      0  0    1    0      0   0    0    0      0   1      0  0     0    0    0
//				// 1 1 0     0  0  0     0  0   1    0   1   1    0  0  0    1   0   1  0  0  1  0 0 0    1  0  1   0 1 0    1  0  0   0  0  0  0  0  0   0 0 0
//				if ((bdr1 & 0x70) != 0 && (bdr1 & 0x7) != 0 && (bdr1 & 0x88) == 0)
//					p[0] = 3;
//				else if ((bdr1 && 0xc1) != 0 && (bdr1 & 0x1c) != 0 && (bdr1 & 0x22) == 0)
//					p[0] = 3;
//				else if ((bdr1 & 0x82) == 0 && (bdr1 & 0x1) != 0)
//					p[0] = 3;
//				else if ((bdr1 & 0xa0) == 0 && (bdr1 & 0x40) != 0)
//					p[0] = 3;
//				else if ((bdr1 & 0x28) == 0 && (bdr1 & 0x10) != 0)
//					p[0] = 3;
//				else if ((bdr1 & 0xa) == 0 && (bdr1 & 0x4) != 0)
//					p[0] = 3;
//			}
//		}
//
//		img = outImg;
//		for (int i = 1; i<h - 1; i++)
//		{
//			img += w;
//			for (int j = 1; j<w - 1; j++)
//			{
//				BYTE* p = img + j;
//
//				if (p[0] == 0)
//					continue;
//
//				FillNeighbor8(p, list, w);
//
//				bdr1 = bdr2 = 0;
//
//				//bdr1是2进制表示的当前点p的8邻域连通情况，hdr2是当前点周围轮廓点的连接情况
//				for (int k = 0; k <= 7; k++)
//				{
//					if (list[k] >= 1)
//						bdr1 |= 0x80 >> k;
//					if (list[k] >= 2)
//						bdr2 |= 0x80 >> k;
//				}
//
//				//相等，周围全是值为2的像素，继续
//				if (bdr1 == bdr2)
//				{
//					p[0] = 4;
//					continue;
//				}
//
//				//p0不为2，继续
//				if (p[0] != 2) continue;
//				//=4都是不可删除的轮廓点
//				//     0x80       0xa     0x40        0x1      0x30   0x6
//				//   0 0 0      1  0 1    0  0  0    0  0  0   0 0 0   0 1 1
//				//   0    0      0     0    0      0    0      1   1    0   0    0
//				//   0 0 1      0  0 0    0  1  0    0  0  0   1 0 0   0 0 0
//
//				if ((bdr2 & 0x80) != 0 && (bdr1 & 0xa) == 0 &&
//					(((bdr1 & 0x40) != 0 || (bdr1 & 0x1) != 0) && (bdr1 & 0x30) != 0 && (bdr1 & 0x6) != 0))
//				{
//					p[0] = 4;
//				}
//				else if ((bdr2 & 0x20) != 0 && (bdr1 & 0x2) == 0 &&
//					(((bdr1 & 0x10) != 0 || (bdr1 & 0x40) != 0) && (bdr1 & 0xc) != 0 && (bdr1 & 0x81) != 0))
//				{
//					p[0] = 4;
//				}
//				else if ((bdr2 & 0x8) != 0 && (bdr1 & 0x80) == 0 &&
//					(((bdr1 & 0x4) != 0 || (bdr1 & 0x10) != 0) && (bdr1 & 0x3) != 0 && (bdr1 & 0x60) != 0))
//				{
//					p[0] = 4;
//				}
//				else if ((bdr2 & 0x2) != 0 && (bdr1 & 0x20) == 0 &&
//					(((bdr1 & 0x1) != 0 || (bdr1 & 0x4) != 0) && (bdr1 & 0xc0) != 0 && (bdr1 & 0x18) != 0))
//				{
//					p[0] = 4;
//				}
//			}
//		}
//
//		img = outImg;
//		for (int i = 1; i<h - 1; i++)
//		{
//			img += w;
//			for (int j = 1; j<w - 1; j++)
//			{
//				BYTE* p = img + j;
//
//				if (p[0] != 2)
//					continue;
//
//				FillNeighbor8(p, list, w);
//
//				bdr4 = bdr5 = 0;
//				for (int k = 0; k <= 7; k++)
//				{
//					if (list[k] >= 4)
//						bdr4 |= 0x80 >> k;
//					if (list[k] >= 5)
//						bdr5 |= 0x80 >> k;
//				}
//				//值为4和5的像素
//				if ((bdr4 & 0x8) == 0)
//				{
//					p[0] = 5;
//					continue;
//				}
//				if ((bdr4 & 0x20) == 0 && bdr5 == 0)
//				{
//					p[0] = 5;
//					continue;
//				}
//
//			}
//		}
//
//		loop = false;
//
//		img = outImg;
//		for (int i = 1; i<h - 1; i++)
//		{
//			img += w;
//			for (int j = 1; j<w - 1; j++)
//			{
//				BYTE* p = img + j;
//				if (p[0] == 2 || p[0] == 5)
//				{
//					loop = true;
//					p[0] = 0;
//				}
//			}
//		}
//	}
//
//	for (int i = 0; i < sizen; i++)
//		outImg[i] *= 255;
//}
////Rosenfeld图像细化算法
//void RosenfeldThin(BYTE* inputImg, BYTE* outImg, int w, int h)
//{
//	int sizen = w * h;
//	memcpy(outImg, inputImg, sizen);
//
//	BYTE* tempImg = new BYTE[sizen];
//	memcpy(tempImg, inputImg, sizen);
//
//	//8邻域编码
//	//p3  p2  p1
//	//p4   p   p0
//	//p5  p6  p7
//	BYTE list[8];
//
//	int a[5] = { 0, -1, 1, 0, 0 };
//	int b[5] = { 0, 0, 0, 1, -1 };
//
//	BYTE  cond, n48, n26, n24, n46, n68, n82, n123, n345, n567, n781;
//
//	//循环标志
//	bool  loop = true;
//
//	while (loop)
//	{
//		loop = false;
//
//		for (int k = 1; k <= 4; k++)
//		{
//			for (int i = 1; i<h - 1; i++)
//			{
//				int ii = i + a[k];
//
//				for (int j = 1; j<w - 1; j++)
//				{
//					int ij = i * w + j;
//					BYTE* pos = outImg + ij;
//
//					if (!outImg[ij])
//						continue;
//
//					int jj = j + b[k];
//					int kk1 = ii * w + jj;
//
//					if (outImg[kk1])
//						continue;
//
//					FillNeighbor8(pos, list, w);
//
//					int nrnd = 0;
//					for (int k = 0; k < 8; k++)
//						nrnd += list[k];
//
//					if (nrnd <= 1)
//						continue;
//
//					cond = 0;
//					n48 = list[3] + list[7];
//					n26 = list[1] + list[5];
//					n24 = list[1] + list[3];
//					n46 = list[3] + list[5];
//					n68 = list[5] + list[7];
//					n82 = list[7] + list[1];
//					n123 = list[0] + list[1] + list[2];
//					n345 = list[2] + list[3] + list[4];
//					n567 = list[4] + list[5] + list[6];
//					n781 = list[6] + list[7] + list[0];
//
//					if (list[1] == 1 && n48 == 0 && n567>0)
//					{
//						if (!cond)
//							continue;
//						tempImg[ij] = 0;
//						loop = true;
//						continue;
//					}
//
//					if (list[5] == 1 && n48 == 0 && n123>0)
//					{
//						if (!cond)
//							continue;
//						tempImg[ij] = 0;
//						loop = true;
//						continue;
//					}
//
//					if (list[7] == 1 && n26 == 0 && n345>0)
//					{
//						if (!cond)
//							continue;
//						tempImg[ij] = 0;
//						loop = true;
//						continue;
//					}
//
//					if (list[3] == 1 && n26 == 0 && n781>0)
//					{
//						if (!cond)
//							continue;
//						tempImg[ij] = 0;
//						loop = true;
//						continue;
//					}
//
//					if (list[4] == 1 && n46 == 0)
//					{
//						if (!cond)
//							continue;
//						tempImg[ij] = 0;
//						loop = true;
//						continue;
//					}
//
//					if (list[6] == 1 && n68 == 0)
//					{
//						if (!cond)
//							continue;
//						tempImg[ij] = 0;
//						loop = true;
//						continue;
//					}
//
//					if (list[0] == 1 && n82 == 0)
//					{
//						if (!cond)
//							continue;
//						tempImg[ij] = 0;
//						loop = true;
//						continue;
//					}
//
//					if (list[2] == 1 && n24 == 0)
//					{
//						if (!cond)
//							continue;
//						tempImg[ij] = 0;
//						loop = true;
//						continue;
//					}
//
//					cond = 1;
//
//					tempImg[ij] = 0;
//
//					loop = true;
//				}
//			}
//
//			memcpy(outImg, tempImg, sizen);
//		}
//	}
//
//	delete[] tempImg;
//
//	for (int i = 0; i < sizen; i++)
//		outImg[i] *= 255;
//}
////BasedIndexTable图像细化算法
//void BasedIndexTableThin(BYTE* inputImg, BYTE* outImg, int w, int h)
//{
//	BYTE deletemark[256] = {
//		0,0,0,0,0,0,0,1,    0,0,1,1,0,0,1,1,
//		0,0,0,0,0,0,0,0,    0,0,1,1,1,0,1,1,
//		0,0,0,0,0,0,0,0,    1,0,0,0,1,0,1,1,
//		0,0,0,0,0,0,0,0,    1,0,1,1,1,0,1,1,
//		0,0,0,0,0,0,0,0,    0,0,0,0,0,0,0,0,
//		0,0,0,0,0,0,0,0,    0,0,0,0,0,0,0,0,
//		0,0,0,0,0,0,0,0,    1,0,0,0,1,0,1,1,
//		1,0,0,0,0,0,0,0,    1,0,1,1,1,0,1,1,
//		0,0,1,1,0,0,1,1,    0,0,0,1,0,0,1,1,
//		0,0,0,0,0,0,0,0,    0,0,0,1,0,0,1,1,
//		1,1,0,1,0,0,0,1,    0,0,0,0,0,0,0,0,
//		1,1,0,1,0,0,0,1,    1,1,0,0,1,0,0,0,
//		0,1,1,1,0,0,1,1,    0,0,0,1,0,0,1,1,
//		0,0,0,0,0,0,0,0,    0,0,0,0,0,1,1,1,
//		1,1,1,1,0,0,1,1,    1,1,0,0,1,1,0,0,
//		1,1,1,1,0,0,1,1,    1,1,0,0,1,1,0,0
//	};//IndexTable索引表，表示某像元的8领域的256种情况，1删除，0不删除
//
//	int sizen = w * h;
//	BYTE* tempImg = new BYTE[sizen];
//	memset(tempImg, 0, sizen);
//
//	//8领域编码
//	//p0  p1  p2
//	//p7   p   p3
//	//p6  p5  p4
//	BYTE list[8];
//
//	BYTE foreground = 1;//前景点
//	BYTE background = 1 - foreground;//背景点
//
//									 //循环标志
//	bool loop = true;
//
//	while (loop)
//	{
//		loop = false;
//
//		memset(tempImg, 0, sizen);
//
//		//首先求边缘点(并行)
//		BYTE* pmid = inputImg + w + 1;
//		BYTE* pmidtemp = tempImg + w + 1;
//
//		for (int i = 1; i < h - 1; i++)
//		{
//			for (int j = 1; j < w - 1; j++)
//			{
//				if (*pmid == background)//0，不考虑
//				{
//					pmid++;
//					pmidtemp++;
//					continue;
//				}
//
//				FillNeighbor8(pmid, list, w);
//
//				BYTE sum = 1;
//				for (int k = 0; k < 8; k++)
//					sum &= list[k];
//
//				if (sum == 0)
//				{
//					*pmidtemp = foreground;//边缘
//				}
//
//				pmid++;
//				pmidtemp++;
//			}
//
//			//移动到下一行的第2个点开始
//			pmid = pmid + 2;
//			pmidtemp = pmidtemp + 2;
//		}
//
//		//串行删除
//		pmid = inputImg + w + 1;
//		pmidtemp = tempImg + w + 1;
//
//		for (int i = 1; i < h - 1; i++)
//		{
//			for (int j = 1; j < w - 1; j++)
//			{
//				if (*pmidtemp == background)//1-边缘，0-中间点
//				{
//					pmid++;
//					pmidtemp++;
//					continue;
//				}
//
//				FillNeighbor8(pmid, list, w);
//
//				list[2] *= 2;
//				list[1] *= 4;
//				list[0] *= 8;
//				list[7] *= 16;
//				list[6] *= 32;
//				list[5] *= 64;
//				list[4] *= 128;
//
//				BYTE sum = 0;
//				for (int k = 0; k < 8; k++)
//					sum |= list[k];
//
//				if (deletemark[sum] == 1)
//				{
//					*pmid = background;
//					loop = true; //本次扫描进行了细化
//				}
//
//				pmid++;
//				pmidtemp++;
//			}
//
//			//移动到下一行的第2个点开始
//			pmid = pmid + 2;
//			pmidtemp = pmidtemp + 2;
//		}
//	}
//
//	delete[] tempImg;
//
//	for (int i = 0; i < sizen; i++)
//		outImg[i] = 255 * inputImg[i];
//}
////Morphology细化算法
//void MorphologyThin(BYTE* inputImg, BYTE* outImg, int w, int h)
//{
//	//inputImg:输入的图像
//	//img2: 输入图像的拷贝
//	//img3:erode后的图像
//	//img4:open操作的中间值
//	//img5:erode-open后的图像
//	//img6:作差后的图像
//	//outImg:输出的图像
//
//	int n = w * h;
//	BYTE* img2 = new BYTE[n];
//	BYTE* img3 = new BYTE[n];
//	BYTE* img4 = new BYTE[n];
//	BYTE* img5 = new BYTE[n];
//	BYTE* img6 = new BYTE[n];
//
//	memcpy(img2, inputImg, n);
//	memset(outImg, 0, n);
//
//	//loop flag
//	bool flag = true;
//	//erode flag
//	bool flag2 = true;
//
//	while (flag)
//	{
//		for (int i = 0; i<h; i++)
//			for (int j = 0; j < w; j++)
//			{
//				int ij = i * w + j;
//				if (i == 0 || j == 0 || i == h - 1 || j == w - 1)
//					img3[ij] = 0;
//				else
//				{
//					flag2 = true;
//					for (int r = i - 1; r <= i + 1; r++)
//						for (int s = j - 1; s <= j + 1; s++)
//						{
//
//							if (img2[r*w + j] != 1)
//								flag2 = false;
//						}
//				}
//
//				if (flag2)
//					img3[ij] = 1;
//				else
//					img3[ij] = 0;
//			}//img3 end
//
//		for (int i = 0; i<h; i++)
//			for (int j = 0; j < w; j++)
//			{
//				int ij = i * w + j;
//				if (i == 0 || j == 0 || i == h - 1 || j == w - 1)
//					img4[ij] = 0;
//				else
//				{
//					flag2 = true;
//					for (int r = i - 1; r <= i + 1; r++)
//						for (int s = j - 1; s <= j + 1; s++)
//						{
//							if (img3[r*w + s] != 1)
//								flag2 = false;
//						}
//
//					if (flag2)
//						img4[ij] = 1;
//					else
//						img4[ij] = 0;
//				}
//			}//img4 end
//
//		for (int i = 0; i<h; i++)
//			for (int j = 0; j < w; j++)
//			{
//				int ij = i * w + j;
//				if (i == 0 || j == 0 || i == h - 1 || j == w - 1)
//					img5[ij] = 0;
//				else
//				{
//					flag2 = true;
//					for (int r = i - 1; r <= i + 1; r++)
//						for (int s = j - 1; s <= j + 1; s++)
//						{
//							if (img4[r*w + s] != 1)
//								flag2 = false;
//						}
//
//					if (flag2)
//						img5[ij] = 1;
//					else
//						img5[ij] = 0;
//				}
//			}//img5 end
//
//			 //作差,等同于subtract函数
//		for (int i = 0; i<h; i++)
//			for (int j = 0; j < w; j++)
//			{
//				int ij = i * w + j;
//				img6[ij] = img3[ij] - img5[ij];
//			}//img6 end
//
//			 //并运算
//		for (int i = 0; i<h; i++)
//			for (int j = 0; j < w; j++)
//			{
//				int ij = i * w + j;
//				if (img6[ij] == 1)
//					outImg[ij] = 1;
//			}//img6 end
//
//		memcpy(img2, img3, n);
//
//		//判断循环标志
//		flag = false;
//		for (int i = 0; i<h; i++)
//			for (int j = 0; j < w; j++)
//			{
//				int ij = i * w + j;
//				if (img2[ij] == 1)
//					flag = true;
//			}//img6 end
//
//	}
//
//	for (int i = 0; i < n; i++)
//		outImg[i] *= 255;
//
//
//	delete[] img2;
//	delete[] img3;
//	delete[] img4;
//	delete[] img5;
//	delete[] img6;
//}
//
////Hilditch2图像细化算法
//int  DetectConnectivity(int* list)
//{
//	int count = list[6] - list[6] * list[7] * list[0];
//	count += list[0] - list[0] * list[1] * list[2];
//	count += list[2] - list[2] * list[3] * list[4];
//	count += list[4] - list[4] * list[5] * list[6];
//	return count;
//}
//void FillNeighbors(BYTE* p, int* list, int width, BYTE foreground)
//{
//	// list 存储的是补集，即前景点为0，背景点为1，以方便联结数的计算 
//
//	list[0] = p[1] == foreground ? 0 : 1;
//	list[1] = p[1 - width] == foreground ? 0 : 1;
//	list[2] = p[-width] == foreground ? 0 : 1;
//	list[3] = p[-1 - width] == foreground ? 0 : 1;
//	list[4] = p[-1] == foreground ? 0 : 1;
//	list[5] = p[-1 + width] == foreground ? 0 : 1;
//	list[6] = p[width] == foreground ? 0 : 1;
//	list[7] = p[1 + width] == foreground ? 0 : 1;
//}
//void HilditchThin(BYTE* inputImg, BYTE* outImg, int w, int h)
//{
//	int sizen = w * h;
//	memcpy(outImg, inputImg, sizen);
//
//	BYTE foreground = 1;//前景点为1
//	BYTE background = 1 - foreground;//背景点为0
//
//	bool* mask = new bool[sizen];
//	memset(mask, 0, sizen);
//
//	//8邻域编码
//	//  p3  p2  p1 
//	//  p4   p   p0 
//	//  p5  p6  p7 
//	int* list = new int[8];
//
//	bool loop = true;//循环标志
//
//	while (loop)
//	{
//		loop = false;
//
//		for (int i = 1; i < h - 1; i++)
//		{
//			for (int j = 1; j < w - 1; j++)
//			{
//				BYTE* p = outImg + i * w + j;
//
//				// 条件1：p 必须是前景点 
//				if (*p != foreground) continue;
//
//				// list 存储补集
//				FillNeighbors(p, list, w, foreground);
//
//				// 条件2：p0,p2,p4,p6 不皆为前景点 
//				if (list[0] == 0 && list[2] == 0 && list[4] == 0 && list[6] == 0)
//					continue;
//
//				// 条件3: p0~p7至少两个是前景点 
//				int count = 0;
//				for (int i = 0; i < 8; i++)
//				{
//					count += list[i];
//				}
//
//				if (count > 6) continue;
//
//				// 条件4：联结数等于1 
//				if (DetectConnectivity(list) != 1) continue;
//
//				// 条件5: 假设p2已标记删除，则令p2为背景，不改变p的联结数 
//				if (mask[(i - 1)*w + j])
//				{
//					list[2] = 1;
//					if (DetectConnectivity(list) != 1)
//						continue;
//					list[2] = 0;
//				}
//
//				// 条件6: 假设p4已标记删除，则令p4为背景，不改变p的联结数 
//				if (mask[i*w + j - 1])
//				{
//					list[4] = 1;
//					if (DetectConnectivity(list) != 1)
//						continue;
//				}
//				mask[i*w + j] = 1; // 标记删除 
//				loop = true;
//			}
//		}
//
//		//如果标记删除，则像元置0
//		for (int i = 0; i < sizen; i++)
//		{
//			if (mask[i])
//			{
//				outImg[i] = background;
//			}
//		}
//	}
//
//	delete[] list;
//	delete[] mask;
//
//	for (int i = 0; i < sizen; i++)
//		outImg[i] *= 255;
//}
//
//
////形态学边缘
//void FillNeighbor9(BYTE* p, BYTE* list, int w)
//{
//
//	list[0] = p[1];
//	list[1] = p[-w + 1];
//	list[2] = p[-w];
//	list[3] = p[-w - 1];
//	list[4] = p[-1];
//	list[5] = p[w - 1];
//	list[6] = p[w];
//	list[7] = p[w + 1];
//	list[8] = p[0];
//}
//void MorphologySharp(BYTE* inputImg, BYTE* outImg, int w, int h)
//{
//	int sizen = w * h;
//	memcpy(outImg, inputImg, sizen);
//
//	BYTE* tempImg = new BYTE[sizen];
//	memcpy(tempImg, inputImg, sizen);
//
//	//领域编码
//	BYTE list[9];
//
//	BYTE* pt = tempImg;
//	BYTE* po = outImg;
//	for (int i = 1; i<h - 1; i++)
//	{
//		for (int j = 1; j < w - 1; j++)
//		{
//			po = outImg + i * w + j;
//			pt = tempImg + i * w + j;
//			FillNeighbor9(pt, list, w);
//
//			BYTE min = 255;
//			for (int k = 0; k<9; k++)
//			{
//				min = (min >= list[k] ? list[k] : min);
//			}
//
//			(*po) = min;
//		}
//	}
//
//	//2*原图-腐蚀=锐化
//	for (int i = 0; i< sizen; i++)
//		outImg[i] = (BYTE)(2 * inputImg[i] - outImg[i]);
//
//	delete[] tempImg;
//}
//
