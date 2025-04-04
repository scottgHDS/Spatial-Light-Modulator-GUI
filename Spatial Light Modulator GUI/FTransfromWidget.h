#pragma once
#include<qwidget.h>
#include<qapplication.h>
#include<qgridlayout.h>
#include<opencv2/opencv.hpp>
#include"Blink_C_wrapper.h"
#include<qlabel.h>


#define FTwidgetW 200
#define FTwidgetH 200

//This Widget calculates and displays both the LogMagnitude and Phase Spectrum of an image
class FTransformWidget : public QWidget {
	Q_OBJECT

public:
	FTransformWidget( QWidget* parent = nullptr);

public slots:
	void ImageDropped(QString image_path);
	void ImageDroppedImg(QImage qimage);

private:
	void displaySpectra();
	void Ftransform(cv::Mat formatted_image);
	void CreateSpectrumWidget(QLabel* widgetTitleLabel, QVBoxLayout* SpetraLayout, QLabel* BoxLabel);
	QImage F32matToQImage(const cv::Mat & src, cv::Mat& temp);
	cv::Mat dft_shift(cv::Mat image);
	cv::Mat Qimage2Smatrgba(QImage &qimage);


	int height, width; 
	cv::Mat Phase;
	cv::Mat logMag;
	QLabel* phaseLabel;
	QLabel* magnitudeLabel;



};

