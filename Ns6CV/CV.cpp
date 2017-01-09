#include "stdafx.h"
#include <opencv2\opencv.hpp>

using namespace cv;

class CV
{
public:
	String fileName;

	Mat image;

	int removeLightMethod = 0;

	double thresholdThresh = 20;
	double thresholdMaxval = 255;
	int thresholdMethod = 0;

	int erosionSize = 4;

	int readImage()
	{
		image = imread(fileName + ".jpg", IMREAD_GRAYSCALE);

		if (image.empty())
		{
			return -1;
		}

		return 0;
	}

	int proccedImage(bool saveStep = false, String itr = "")
	{
		if (image.empty())
		{
			return -1;
		}

		Mat pattern = this->calculateLightPattern(image);
		if (saveStep) this->saveFile(pattern, "_1_pattern" + itr);

		Mat img = this->removeLight(image, pattern, this->removeLightMethod);
		if (saveStep) this->saveFile(img, "_2_remove_light" + itr);

		/*Mat img_thr = this->calculateThreshold(
			img, 
			this->thresholdThresh, 
			this->thresholdMaxval, 
			this->thresholdMethod
		);
		if (saveStep) this->saveFile(img_thr, "_3_threshold");*/

		Mat img_thr = img;

		Mat img_ers = this->removeErosion(img_thr, this->erosionSize);
		if (saveStep) this->saveFile(img_ers, "_4_erosion" + itr);

		return 0;
	}

	int saveImage()
	{
		return this->saveFile(this->image, "_result");
	}

protected:
	int saveFile(Mat img, String postfix)
	{
		if (img.empty())
		{
			return -1;
		}

		imwrite(this->fileName + postfix + ".jpg", img);

		return 0;
	}

	Mat calculateLightPattern(Mat img)
	{
		Mat pattern;
		blur(img, pattern, Size(img.cols / 3, img.cols / 3));
		return pattern;
	}

	Mat removeLight(Mat img, Mat pattern, int method)
	{
		Mat aux;

		if (method == 1)
		{
			Mat img32, pattern32;
			img.convertTo(img32, CV_32F);
			pattern.convertTo(pattern32, CV_32F);
			aux = 1 - (img32 / pattern32);
			aux = aux * 255;
			aux.convertTo(aux, CV_8U);
		}
		else
		{
			aux = pattern - img;
		}

		return aux;
	}

	Mat calculateThreshold(Mat img, double thresh, double maxval, int method)
	{
		Mat thr;

		if (method == 2)
		{
			threshold(img, thr, thresh, maxval, THRESH_BINARY_INV); 
		}
		else
		{
			threshold(img, thr, thresh, maxval, THRESH_BINARY);
		}

		return thr;
	}

	Mat removeErosion(Mat img, int erosion_size)
	{
		Mat erd;
		Mat erode_element = getStructuringElement(
			MORPH_ELLIPSE,
			Size(2 * erosion_size + 1, 2 * erosion_size + 1),
			Point(erosion_size, erosion_size)
		);

		erode(img, erd, erode_element);
		dilate(erd, erd, erode_element);

		return erd;
	}
};
