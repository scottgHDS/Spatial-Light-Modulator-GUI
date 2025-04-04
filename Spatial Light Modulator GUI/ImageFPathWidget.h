#pragma once
#include"ShowImgWidget.h"

//This widget show an image given a file path
class ImageFPathWidget : public ShowImgWidget {
	Q_OBJECT

public:
	ImageFPathWidget(QWidget* parent = nullptr);

public slots: 
	void PathSelected(QString ImageFPath);

private:
	void fill_widget(QString image_path) override;

};