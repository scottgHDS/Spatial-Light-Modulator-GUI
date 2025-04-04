#pragma once
#include"ShowImgWidget.h"


//Shows what image is being transmitted to the SLM and transmits said image
class GrayFormMitWidget : public ShowImgWidget {

	Q_OBJECT;

public slots:
	void recieveDroppedImg(QString image_path);

public:
	GrayFormMitWidget(QWidget* parent);
	~GrayFormMitWidget();

private:
	void SLMformatTrans() override;
	void fill_widget(QString image_path) override;
	cv::Mat transformSize(cv::Mat original);

	unsigned char* SLMformatImg;
	cv::Mat original_image;

};
