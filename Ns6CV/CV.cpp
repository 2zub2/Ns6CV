#pragma once

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include "settingsTV.h"

using namespace cv;

class CV
{
public:
	String fileName;
	String fileDir;
	String fileExt;

	String settingFileName;

	String savePostfix;

	Mat image;
	Mat pattern;

	bool removeLightActive = true;
	bool removeLightSave = false;
	char removeLightMethod = 0;

	double thresholdThresh = 20;
	double thresholdMaxval = 255;
	int thresholdMethod = 0;

	int erosionSize = 4;



	void setFileName(String file)
	{
		fileDir = file.substr(0, file.find_last_of('\\'));
		fileName = file.substr(file.find_last_of('\\'), file.length());
		fileName = fileName.substr(0, fileName.length() - 4);
		fileExt = file.substr(file.find_last_of('.'), file.length());
	}



	int readSettings(String settingFileName)
	{
		SCL::settingsTV sclSettings;
		bool fileSettingVersionDifferent = false;
		string importErrStr;
		SCL::SettingsImportType importType = SCL::IMPORT_ALL;
		SCL::SettingsImportErrType irc = sclSettings.importSettingsFromFile(
			settingFileName,
			importType,
			fileSettingVersionDifferent,
			importErrStr,
			NULL
		);
		if (irc != SCL::SIRC_SUCCESS)
		{
			return -1;
		}
		
		sclSettings.getBoolSetting("LightPatten", "active",);

		return 0;
	}



	int prepareSettingsTemplate()
	{
		SCL::setting_initializer pgmInitialSettings[] =
		{
			{ "LightPattern",	"active",	ST_BOOL,	"TRUE",		"удалить свет по шаблону"	},
			{ "LightPattern",	"save",		ST_BOOL,	"FALSE",	"удалить свет по шаблону"	},
			{ "LightPattern",	"method",	ST_UI8,		"0",		"метод удаления (1 или 2)"	},
		};

		uint32_t numSettings =
			sizeof(pgmInitialSettings) / sizeof(SCL::setting_initializer);

		SCL::settingsTV sclSettings;
		uint32_t rc = sclSettings.init(numSettings, pgmInitialSettings);

		if (rc != 0) 
		{
			return -1;
		}

		SCL::SettingsExportErrType erc = sclSettings.saveSettingsToFile("template.cfg", true);
		if (erc != SCL::SERC_SUCCESS)
		{
			return -1;
		}

		return 0;
	}
	

	int readImage()
	{
		image = imread(fileDir + fileName + fileExt, IMREAD_GRAYSCALE);

		if (image.empty())
		{
			return -1;
		}

		return 0;
	}

	int viewImage()
	{
		namedWindow("Display window", WINDOW_AUTOSIZE);

		if (image.empty())
		{
			return -1;
		}

		imshow("Display window", image);

		return 0;
	}

	int saveImage()
	{
		if (image.empty())
		{
			return -1;
		}

		imwrite(fileDir + fileName + '_' + savePostfix + fileExt, image);

		return 0;
	}


	int proccedImage(bool saveStep = false, String itr = "")
	{

		return 0;
	}

protected:

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
