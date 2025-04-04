#pragma once
#include"ShowImgWidget.h"

#define RGBAWidgetH 225
#define RGBAWidgetW 200


//This widget both displays the image in RGBA8888 format and transmit it to the SLM
class RgbMitwidget : public ShowImgWidget {
	Q_OBJECT

public slots:
	void recieveHologramPattern(QImage image_path);

signals:
	void imageForFT(QImage slmImage);

public:
	RgbMitwidget(QWidget* parent);
	~RgbMitwidget();

private:
	void SLMformatTrans(QImage image);
	void fill_widget(QString qstring) override;
	void fill_widget(QImage hollogramImage);
	QImage rgbaToRgb(QImage rgbaImage);

	unsigned char* SLMformatImg; 

	//for testing purposes with grayscale
	cv::Mat QImageToCvMat(const QImage& image);
	void SLMformatTransGray(cv::Mat grayimage);

	unsigned char* SLMformatG;
};
