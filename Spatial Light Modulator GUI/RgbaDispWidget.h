#pragma once
#include"ShowImgWidget.h"

#define RGBAWidgetH 225
#define RGBAWidgetW 200


//This widget displays the image in RGBA8888 format 
class RgbaDispWidget : public ShowImgWidget {
	Q_OBJECT

public slots:
	void fill_widget(QImage hollogramImage);

signals:
	void imageForFT(QImage slmImage);

public:
	RgbaDispWidget(QWidget* parent);

private:
	void fill_widget(QString qstring) override;
	QImage rgbaToRgb(QImage rgbaImage);

};
