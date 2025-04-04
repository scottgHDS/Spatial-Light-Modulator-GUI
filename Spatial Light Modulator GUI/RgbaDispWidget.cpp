#include "RgbaDispWidget.h"

//Creates a box to display the given Qimage
RgbaDispWidget::RgbaDispWidget(QWidget* parent = nullptr) :ShowImgWidget(parent)
{
	//Setting specific text in place of placeholder text from base class
	showImgTitleLayout->setText("What is being sent to SLM");
	//making sure there is a 10 pixel gap between the end of the GUI and the widget
	showImgLayout->setContentsMargins(0, 0, 10, 0);
	//Make sure the widget is no short than its minimum height
	setMinimumHeight(RGBAWidgetH);
}


//This overload of fill_widget converts the RGBA hollogramImage to the RGB and displays it on the widget
void RgbaDispWidget::fill_widget(QImage hollogramImage) {

	//Convert RGBA QImage to the RGB QImage
	QImage rgbHollogramImage = rgbaToRgb(hollogramImage);//old 
	//QImage rgbHollogramImage = hollogramImage; // new 

	//Sets the QImage to a QPixMap at scale, and sets the Widget display to the pixmap 
	QPixmap patternPix = QPixmap::fromImage(hollogramImage.scaled(RGBAWidgetW, RGBAWidgetH, Qt::KeepAspectRatio));
	imgBoxLayout->setPixmap(patternPix);

	//Send hollogramImage to the fourier
	emit imageForFT(hollogramImage);
}

//Place holder for the fill_widget virtual function in the base class
void RgbaDispWidget::fill_widget(QString qstring)
{
}

//Converts an RGBA QImage to RGB QImage
QImage RgbaDispWidget::rgbaToRgb(QImage rgbaImage)
{
	//Use QTwidgets method to make an RGB888 QImage the same dimensions as the RGBA8888 QImage
	QImage rgbImage(rgbaImage.width(), rgbaImage.height(), QImage::Format_RGB888);

	//sets the RGB values of the RGBA image to the RGB QImage at the appropriate pixel location
	for (int y = 0; y < rgbaImage.height(); ++y) {
		for (int x = 0; x < rgbaImage.width(); ++x) {
			QRgb rgbaPixel = rgbaImage.pixel(x, y);
			QRgb rgbPixel = qRgb(qRed(rgbaPixel), qGreen(rgbaPixel), qBlue(rgbaPixel));
			rgbImage.setPixel(x, y, rgbPixel);
		}
	}

	return rgbImage;
}







