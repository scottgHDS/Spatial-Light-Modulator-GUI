#pragma once
#include<qboxlayout.h>
#include<qapplication.h>
#include<qlabel.h>
#include<qpixmap.h>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>
#include"Blink_C_wrapper.h"
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/imgproc/imgproc.hpp>


#define SIwidgetW 200
#define SIwidgetH 200

//This base class is used to give each widget that is mainly used for displaying and possibly transmitting an image the SLM
//	a format for the widget architecture aswell as some quality of life functions/variables
class ShowImgWidget : public QWidget {
	Q_OBJECT

public:
	ShowImgWidget(QWidget* parent = nullptr);
	
public slots: 
	virtual void fill_widget(QString image_path) = 0;

protected:
	virtual void SLMformatTrans();
	QImage mat2Qimage(cv::Mat mat);
	int height, width;

	cv::Mat resized_image;
	QLabel* showImgTitleLayout;
	QLabel* imgBoxLayout; 
	QVBoxLayout* showImgLayout;

};