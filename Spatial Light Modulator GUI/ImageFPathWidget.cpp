#include "ImageFPathWidget.h"



ImageFPathWidget::ImageFPathWidget(QWidget* parent) :ShowImgWidget(parent)
{	//Set title
	showImgTitleLayout->setText("Image from the path");

	//widget will be 10 pixels from the left
	showImgLayout->setContentsMargins(10, 0, 0, 0);

	//Minimum size prevents images from being cutoff
	setMinimumSize( SIwidgetW , SIwidgetH + 25);
}

void ImageFPathWidget::fill_widget(QString image_path)
{
	//Loads a QImage from a filepath
	QImage ImageFPath(image_path);

	//only loads the image if the image is valid
	if (!ImageFPath.isNull()) {
		
		//QImage is converted to a QPixmap and scaled to the Widget's display dimensions
		QPixmap loadedImg = QPixmap::fromImage(ImageFPath.scaled(SIwidgetW, SIwidgetH, Qt::KeepAspectRatio));

		//The pixel map covers the image display of the widget
		imgBoxLayout->setPixmap(loadedImg);
	}
}

//This slot recieves the image file path given by the FilePathWidget widget
void ImageFPathWidget::PathSelected(QString ImageFPath) {
	
	//uses the filepath to put an image in the widget's image display
	fill_widget(ImageFPath);
}