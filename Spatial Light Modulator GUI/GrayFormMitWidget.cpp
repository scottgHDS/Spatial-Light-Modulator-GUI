#include "GrayFormMitWidget.h"


//NOTE:
// the reason the transformed image is not sent to the FT widget is because the padding
// added in this transform will cause more padding to be created in the FT widget causing
// innacurate spectra to be calculated

GrayFormMitWidget::GrayFormMitWidget(QWidget* parent = nullptr) :ShowImgWidget(parent)
{
	//this the size of the eventual image that will be sent to the SLM based on the SLM dimensions
	int imgSize = height*width;

	//Allocate memory for the image to be sent to the SLM
	SLMformatImg = new unsigned char[imgSize];
	memset(SLMformatImg, 0, imgSize);

	//Sets the title of the Image and instructs it to have a 10 pix margin to its right
	showImgTitleLayout->setText("What is being sent to SLM");
	showImgLayout->setContentsMargins(0, 0, 10, 0);
}


GrayFormMitWidget::~GrayFormMitWidget()
{
	//releases memory reserved for the image that will be transmitted to the SLM
	delete[] SLMformatImg;
}


//Transforms the openCV mat image into a an array of the correct format for the SLM
void GrayFormMitWidget::SLMformatTrans()
{
	unsigned char pixelValue;
	cv::Mat flipped;
	
	//corrects for the effect of the light leaving the SLM and flipping itself
	//cv::flip(original_image, flipped, 0);
	flipped = original_image;

	//pixel by pixel takes each value from the Mat object and allocates that to memory within
	// the predefined array
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			pixelValue = flipped.at<unsigned char>(h, w);
			SLMformatImg[h * width + w] = pixelValue;
		}
	}

}


//converts the image at the given path to a grayscale image of the the SLM's screen dimensions
// while still maintaing original aspect ratio
void GrayFormMitWidget::fill_widget(QString image_path) {

	cv::Mat rgbimg;

	//convert Qstring to std::string for opencv to load the image
	std::string pathStr = image_path.toStdString();

	//reads the dropped image in grayscale 8-bit
	cv::Mat temp_original = cv::imread(pathStr.c_str(), 0);

	//resize and/or pad image for SLM transmission
	original_image = transformSize(temp_original);

	//converting the grayscale image into
	cv::cvtColor(original_image, rgbimg, cv::COLOR_GRAY2RGB);
;

	//Create QImage from the processed image
	QImage qImage = mat2Qimage(rgbimg);
	

	//rescales and converts the QImage of what is being sent to the SLM into a pixel map
	QPixmap droppedImg = QPixmap::fromImage(qImage.scaled(SIwidgetH, SIwidgetW,Qt::KeepAspectRatio));
	
	//Sets the pixel map of the image that will be transmitted to the widgets display
	imgBoxLayout->setPixmap(droppedImg);

}


//This slot receives the image path of the dropped image, converts it so that it can be transmited
// then transmitts said transformed iamge
void GrayFormMitWidget::recieveDroppedImg(QString image_path)
{
	//Fills the widget's display with what will be transmitted to the SLM
	fill_widget(image_path);

	//converts the above generated imge into an array that the SLM can be transmitted to
	SLMformatTrans();

	//writes to the SLM the image via a pointer
	Write_image(SLMformatImg, true);
	
}


cv::Mat GrayFormMitWidget::transformSize(cv::Mat original) {
	// Get the dimensions of the SLM display
	int slmWidth = Get_Width();
	int slmHeight = Get_Height();

	// Get the dimensions of the original image
	int originalWidth = original.cols;
	int originalHeight = original.rows;

	// Calculate the aspect ratios of the SLM and the original image
	double slmAspectRatio = (double)slmWidth / slmHeight;
	double originalAspectRatio = (double)originalWidth / originalHeight;

	// Calculate the new dimensions of the input image to fit within the SLM display
	int newWidth, newHeight;
	if (originalAspectRatio >= slmAspectRatio) {
		// Input image is wider than the SLM display
		newWidth = slmWidth;
		newHeight = static_cast<int>(slmWidth / originalAspectRatio);
	}
	else {
		// Input image is taller than the SLM display
		newHeight = slmHeight;
		newWidth = static_cast<int>(slmHeight * originalAspectRatio);
	}

	// Resize the input image to the new dimensions while maintaining its aspect ratio
	cv::Mat resizedOriginal;
	cv::resize(original, resizedOriginal, cv::Size(newWidth, newHeight));

	// Create a blank image the size of the SLM display
	cv::Mat endImage = cv::Mat::zeros(cv::Size(slmWidth, slmHeight), CV_8UC1);

	// Set all pixels to white
	endImage.setTo(cv::Scalar::all(255));

	// Calculate the region of interest to copy the resized input image to
	int startX = (slmWidth - newWidth) / 2;
	int startY = (slmHeight - newHeight) / 2;
	cv::Rect roi(startX, startY, newWidth, newHeight);

	// Copy the resized input image to the region of interest in the blank image
	resizedOriginal.copyTo(endImage(roi));

	// Return the resized input image on a blank background the size of the SLM's display
	return endImage;
}

