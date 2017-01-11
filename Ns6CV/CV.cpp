#pragma once

#include "stdafx.h"
#include <opencv2\opencv.hpp>

using namespace cv;

class CV
{
public:
	String fileName;
	String dirName;

	Mat image;
	Mat pattern;

	int removeLightMethod = 0;

	double thresholdThresh = 20;
	double thresholdMaxval = 255;
	int thresholdMethod = 0;

	int erosionSize = 4;

	void setFileName(String dir, String filename)
	{
		dirName = dir;
		fileName = filename;
	}

	int readImage()
	{
		image = imread(fileName + ".jpg", IMREAD_GRAYSCALE);

		if (image.empty())
		{
			return -1;
		}

		return 0;
	}

	int viewImage()
	{
		namedWindow("Display window", WINDOW_AUTOSIZE);
		imshow("Display window", image);

		return 0;
	}

	int proccedImage(bool saveStep = false, String itr = "")
	{
		/*if (image.empty())
		{
			return -1;
		}

		Mat pattern = this->calculateLightPattern(image);
		if (saveStep) this->saveFile(pattern, "_1_pattern" + itr);

		Mat img = this->removeLight(image, pattern, this->removeLightMethod);
		if (saveStep) this->saveFile(img, "_2_remove_light" + itr);

		Mat img_thr = this->calculateThreshold(
			img, 
			this->thresholdThresh, 
			this->thresholdMaxval, 
			this->thresholdMethod
		);
		if (saveStep) this->saveFile(img_thr, "_3_threshold");

		Mat img_thr = img;

		Mat img_ers = this->removeErosion(img_thr, this->erosionSize);
		if (saveStep) this->saveFile(img_ers, "_4_erosion" + itr);
		*/
		return 0;
	}

	int saveImage(String postfix)
	{
		return saveFile(image, "_" + postfix);
	}

	String StringFromCString(CString str)
	{
		CT2CA pszConvertedAnsiString(str);
		std::string strStd(pszConvertedAnsiString);

		return String(strStd);
	}


	int saveFile(Mat img, String postfix)
	{
		if (img.empty())
		{
			return -1;
		}

		imwrite(this->fileName + postfix + ".jpg", img);

		return 0;
	}

	void calculateLightPattern()
	{
		blur(image, pattern, Size(image.cols / 3, image.cols / 3));
	}

	void removeLight(int method)
	{
		Mat aux;

		if (method == 1)
		{
			Mat img32, pattern32;
			image.convertTo(img32, CV_32F);
			pattern.convertTo(pattern32, CV_32F);
			aux = 1 - (img32 / pattern32);
			aux = aux * 255;
			aux.convertTo(aux, CV_8U);
		}
		else
		{
			aux = pattern - image;
		}

		image = aux;
	}

	void calculateThreshold(double thresh, double maxval, int method)
	{
		Mat thr;

		if (method == 2)
		{
			threshold(image, thr, thresh, maxval, THRESH_BINARY_INV); 
		}
		else
		{
			threshold(image, thr, thresh, maxval, THRESH_BINARY);
		}

		image = thr;
	}

	void removeErosion(int erosion_size)
	{
		Mat erd;
		Mat erode_element = getStructuringElement(
			MORPH_ELLIPSE,
			Size(2 * erosion_size + 1, 2 * erosion_size + 1),
			Point(erosion_size, erosion_size)
		);

		erode(image, erd, Mat());
		//dilate(erd, erd, erode_element);

		image = erd;
	}
};
