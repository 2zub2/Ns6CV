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

	SCL::settingsTV sclSettings;1

	// remove light
	unsigned char	removeLightActive = 1;
	unsigned char	removeLightSave = 1;
	unsigned char	removeLightMethod = 0;

	// calc threshold
	unsigned char	calcThresholdActive = 1;
	unsigned char	calcThresholdSave = 1;
	unsigned char	calcThresholdMethod = 0;
	double			calcThresholdThresh = 30;

	// calc erode and dilate
	unsigned char	calcErodeActive = 1;
	unsigned char	calcDilateActive = 1;
	unsigned char	calcErodeDilateSave = 1;
	unsigned char	calcErodeDilateSize = 1;


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


		// remove light
		sclSettings.getUI8Setting("1LightPattern", "active", removeLightActive);
		sclSettings.getUI8Setting("1LightPattern", "save", removeLightSave);
		sclSettings.getUI8Setting("1LightPattern", "method", removeLightMethod);

		// calc threshold
		sclSettings.getUI8Setting("2Threshold", "active", calcThresholdActive);
		sclSettings.getUI8Setting("2Threshold", "save", calcThresholdSave);
		sclSettings.getUI8Setting("2Threshold", "method", calcThresholdMethod);
		sclSettings.getDblSetting("2Threshold", "thresh", calcThresholdThresh);

		// calc erode and dilate
		sclSettings.getUI8Setting("3ErodeDilate", "active_erode", calcErodeActive);
		sclSettings.getUI8Setting("3ErodeDilate", "active_dilate", calcDilateActive);
		sclSettings.getUI8Setting("3ErodeDilate", "save", calcErodeDilateSave);
		sclSettings.getUI8Setting("3ErodeDilate", "size", calcErodeDilateSize);

		return 0;
	}



	int prepareSettingsTemplate()
	{
		SCL::setting_initializer pgmInitialSettings[] =
		{
			// remove light
			{ "1LightPattern",	"active",			ST_UI8,		"1",		"выполнять"					},
			{ "1LightPattern",	"save",				ST_UI8,		"1",		"сохранять результат"		},
			{ "1LightPattern",	"method",			ST_UI8,		"1",		"метод удаления (1 или 2)"	},
			// calc threshold
			{ "2Threshold",		"active",			ST_UI8,		"1",		"выполнять"					},
			{ "2Threshold",		"save",				ST_UI8,		"1",		"сохранять результат"		},
			{ "2Threshold",		"method",			ST_UI8,		"1",		"метод расчета (1 или 2)"	},
			{ "2Threshold",		"thresh",			ST_DBL,		"30",		"метод расчета (1 или 2)"	},
			// calc erode and dilate
			{ "3ErodeDilate",	"active_erode",		ST_UI8,		"1",		"выполнять erode"			},
			{ "3ErodeDilate",	"active_dilate",	ST_UI8,		"1",		"выполнять dilate"			},
			{ "3ErodeDilate",	"save",				ST_UI8,		"1",		"сохранять результат"		},
			{ "3ErodeDilate",	"size",				ST_UI8,		"1",		"размер эрозии"				},
		};

		uint32_t numSettings =
			sizeof(pgmInitialSettings) / sizeof(SCL::setting_initializer);

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



	int proccedImage()
	{
		// remove light
		if (removeLightActive)
		{
			removeLight(removeLightMethod);
			if (removeLightSave)
			{
				savePostfix = "1remove_light";
				saveImage();
			}
		}

		// calculate threshold
		if (calcThresholdActive)
		{
			calculateThreshold(calcThresholdThresh, 255, calcThresholdMethod);
			if (calcThresholdSave)
			{
				savePostfix = "2threshold";
				saveImage();
			}
		}

		// calc erode and dilate
		if (calcErodeActive)
		{
			calcErode(calcErodeDilateSize);
			if (calcErodeDilateSave)
			{
				savePostfix = "3erode";
				saveImage();
			}
		}

		if (calcDilateActive)
		{
			calcDilate(calcErodeDilateSize);
			if (calcErodeDilateSave)
			{
				savePostfix = "4dilate";
				saveImage();
			}
		}

		return 0;
	}

protected:
	Mat calculateLightPattern()
	{
		Mat pattern;
		blur(image, pattern, Size(image.cols / 3, image.cols / 3));
		return pattern;
	}



	void removeLight(int method)
	{
		Mat aux;

		Mat pattern = calculateLightPattern();

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

		if (method == 1)
		{
			threshold(image, thr, thresh, maxval, THRESH_BINARY_INV); 
		}
		else
		{
			threshold(image, thr, thresh, maxval, THRESH_BINARY);
		}

		image = thr;
	}



	void calcErode(int size)
	{
		Mat erd;
		Mat erode_element = getStructuringElement(
			MORPH_TOPHAT,
			Size(2 * size + 1, 2 * size + 1),
			Point(size, size)
		);

		erode(image, erd, erode_element);

		image = erd;
	}



	void calcDilate(int size)
	{
		Mat erd;
		Mat erode_element = getStructuringElement(
			MORPH_ELLIPSE,
			Size(2 * size + 1, 2 * size + 1),
			Point(size, size)
		);

		dilate(image, erd, erode_element);

		image = erd;
	}
};
