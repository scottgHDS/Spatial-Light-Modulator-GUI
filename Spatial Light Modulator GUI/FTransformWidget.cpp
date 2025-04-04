#include "FTransfromWidget.h"


//Constructor which creates two boxes, one to display the Log Magnitude 
// Spectrum and one to display the Phase Spectrum
FTransformWidget::FTransformWidget( QWidget* parent):QWidget(parent)
{	
	//Minimum size is set so that no box widgets get cut off
	setMinimumSize(2*FTwidgetW+25, FTwidgetH+30);
	
	//Saves size of output resolution 
	height = Get_Height();
	width = Get_Width();

	//This layout will hold both spectra
	QHBoxLayout* outerLayout = new QHBoxLayout(this);

	//This layout is the Log Mangintude Spectrum
	QVBoxLayout* magnitudeLayout = new QVBoxLayout();
	QLabel* magnitudeTitleLabel = new QLabel("Log Magnitude Spectrum", this);
	magnitudeLabel = new QLabel(this);
	CreateSpectrumWidget(magnitudeTitleLabel, magnitudeLayout,magnitudeLabel);
	outerLayout->addLayout(magnitudeLayout);

	//This layout is the Phase Spectrum
	QVBoxLayout* phaseLayout = new QVBoxLayout();
	QLabel* phaseTitleLabel = new QLabel("Phase Spectrum", this);
	phaseLabel = new QLabel(this);
	CreateSpectrumWidget(phaseTitleLabel, phaseLayout,phaseLabel);
	outerLayout->addLayout(phaseLayout);


}


//This creates a titles, framed box for each spectrum to fill
void FTransformWidget::CreateSpectrumWidget(QLabel* widgetTitleLabel, QVBoxLayout* SpetraLayout,QLabel* BoxLabel) {
	
	//Makes the title use as little blank space between them as possible
	SpetraLayout->setAlignment(Qt::AlignTop);

	//The title is centered and has a 0 px margin to what is around it
	widgetTitleLabel->setAlignment(Qt::AlignCenter);
	widgetTitleLabel->setStyleSheet("margin: 0px; padding: 0px;");

	//Add title to the Spectrum Widget
	SpetraLayout->addWidget(widgetTitleLabel);

	//Puts a slight gap between title and image but reduces all other margins 
	SpetraLayout->setSpacing(1); // set spacing between title and box
	SpetraLayout->setContentsMargins(0, 0, 0, 0); // set margin to 0

	//Image is centered within it's sublayout
	BoxLabel->setAlignment(Qt::AlignCenter);
	BoxLabel->setStyleSheet("border: 2px solid black;");

	//This Height and Width is set so that when the images are resized later, they are consistent with their borders
	//and are not cut-off
	BoxLabel->setMinimumHeight(FTwidgetH);
	BoxLabel->setMidLineWidth(FTwidgetW);

	//Add the image to the Spectrum widget
	SpetraLayout->addWidget(BoxLabel);

}


//calculates the log magnitude and phase spectra of a given opencv Mat object image
void FTransformWidget::Ftransform(cv::Mat formattedImage)
{
	cv::Mat complexImage;
	cv::Mat padded;
	cv::Mat Magni;

	//creates these sizes are used for padding of the images for the speed of the fourier transform and avoid artifacts
	int m = cv::getOptimalDFTSize(formattedImage.rows);
	int n = cv::getOptimalDFTSize(formattedImage.cols);

	//create a version of the image to avoid having peridotical artifacts in the result
	cv::copyMakeBorder(formattedImage, padded, 0, m - formattedImage.rows, 0, n - formattedImage.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

	//create an a 2 element array of Mat objects one being the image in float and the second being an exmpty complex domain
	cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32FC1) };

	//merge the 2 element array into an array of complex values
	cv::merge(planes, 2, complexImage);

	//preform the discrete fourier transform and store the result in the same variable
	cv::dft(complexImage, complexImage);

	//splits the real and imaginary parts back into a 2 element array of Mats
	cv::split(complexImage, planes);

	//stores magnitude domain image
	cv::magnitude(planes[0], planes[1], Magni);

	//stores phase domain image (true 
	cv::phase(planes[0], planes[1], Phase);
	
	//This makes the image clearer by not having DC frequency overshadow all other frequencies and the patterns they create
	cv::log(Magni + 1e-10, logMag);

	//normalize results so that the distinction between different frequencies are easier to see
	cv::normalize(Phase, Phase, 0, 1, cv::NORM_MINMAX);
	cv::normalize(logMag, logMag, 0, 1, cv::NORM_MINMAX);

	//Swaps the 1rst/3rd regions, and the 2nd/4rth regions of the spectra, so that the DC frequency is centered
	Phase = dft_shift(Phase);
	logMag = dft_shift(logMag);

}


//Receives and image, calculates the fourier spectra, and shows it to the user
//This slot is for Mode1 and Mode 2 which have an original image that is trasmitted throughout the software
void FTransformWidget::ImageDropped(QString image_path)
{
	//Read the image into a opencvMat object in a grayscale format
	cv::Mat image = cv::imread(image_path.toStdString(), cv::IMREAD_GRAYSCALE);

	//Calculate the log mangnitude and phase spectra of the given image
	Ftransform(image);

	//Does all conversion from Mat to Qpixmap and sets it to the respective spectrum label
	displaySpectra();
}


//Receives and image, calculates the fourier spectra, and shows it to the user
//This slot is for Mode 3 which emits the hologram image instead of the original image throughout the software
void FTransformWidget::ImageDroppedImg(QImage qimage)
{
	//converts the Qimage into a RGBA mat image
	cv::Mat image = Qimage2Smatrgba(qimage);

	//Calculate the log mangnitude and phase spectra of the given image
	Ftransform(image);

	//Does all conversion from Mat to Qpixmap and sets it to the respective spectrum label
	displaySpectra();

}


//Does all conversion from Mat to Qpixmap and sets it to the respective spectrum label
void FTransformWidget::displaySpectra()
{
//these unsized Mat's are used to fill a 8 bit conversion of their 32Floating point spectrum mats
cv::Mat temp_M, temp_P;

//Convert each spectrum into a Qimage
QImage Magni_Q = F32matToQImage(logMag, temp_M);
QImage Phase_Q = F32matToQImage(Phase, temp_P);

//Sclae each Q image so that it can fit within it's display widget
QImage Magni_Q_scaled = Magni_Q.scaled(200, 200, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
QImage Phase_Q_scaled = Phase_Q.scaled(200, 200, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

//Create pixel maps of each image so that they can be displayed on the GUI
QPixmap magni = QPixmap::fromImage(Magni_Q_scaled);
QPixmap phase = QPixmap::fromImage(Phase_Q_scaled);

//Set both spectrum's image display to their respective pixel maps
magnitudeLabel->setPixmap(magni);
phaseLabel->setPixmap(phase);
}



//Converts a Qimage  of the RGBA colorspace into a Opencv Mat grayscale image
cv::Mat FTransformWidget::Qimage2Smatrgba(QImage &qimage) 
{
	// Create a new Mat with the same dimensions and number of channels as the input image as RGBA
	cv::Mat mat(qimage.height(), qimage.width(), CV_8UC4, const_cast<uchar*>(qimage.bits()), qimage.bytesPerLine());

	//converts RGBA mat into a grayscale mat
	cv::cvtColor(mat, mat, cv::COLOR_RGBA2GRAY);

	return mat;
}


//converts a float 32bit opencv Mat image into a Qimage
QImage FTransformWidget::F32matToQImage(const cv::Mat& src, cv::Mat& temp)
{
	// Convert CV_32F to CV_8U
	src.convertTo(temp, CV_8U, 255.0);

	// Create QImage from CV_8U Mat
	QImage dest((const uchar*)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_Grayscale8);

	return dest;
}


//Swaps the 1rst/3rd regions, and the 2nd/4rth regions of a spectrum, so that the DC frequency is centered
//This needs to be done because the FFT (faster fourier transform) calculates the spectrum such that the zero order 
//is at the corners
cv::Mat FTransformWidget::dft_shift(cv::Mat image)
{
	//This clone is used so that quadrants can be written to it without overwriting the original data
	cv::Mat image_clone = image.clone();

	// Divide the image into four quadrants
	cv::Rect firstQuadrant(image.cols / 2, 0, image.cols / 2, image.rows / 2);
	cv::Rect secondQuadrant(0, 0, image.cols / 2, image.rows / 2);
	cv::Rect thirdQuadrant(0, image.rows / 2, image.cols / 2, image.rows / 2);
	cv::Rect fourthQuadrant(image.cols / 2, image.rows / 2, image.cols / 2, image.rows / 2);

	//Swap first and third quadrant
	image(thirdQuadrant).copyTo(image_clone(firstQuadrant));
	image(firstQuadrant).copyTo(image_clone(thirdQuadrant));

	//Swap second and fourth quadrant
	image(secondQuadrant).copyTo(image_clone(fourthQuadrant));
	image(fourthQuadrant).copyTo(image_clone(secondQuadrant));

	return image_clone;
}

