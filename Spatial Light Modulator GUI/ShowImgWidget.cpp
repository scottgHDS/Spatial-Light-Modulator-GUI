#include"ShowImgWidget.h"


ShowImgWidget::ShowImgWidget(QWidget* parent)
{
	height = Get_Height();
	width = Get_Width();

	//Setting size of widget box
	setMinimumSize(SIwidgetW, SIwidgetH);

	//Vertical layout to hold image and title
	showImgLayout = new QVBoxLayout(this);

	//Create and fill title label
	showImgTitleLayout = new QLabel("Place Holder Text", this);
	showImgLayout->setAlignment(Qt::AlignTop);
	showImgTitleLayout->setAlignment(Qt::AlignCenter);
	showImgTitleLayout->setStyleSheet("margin: 0px; padding: 0px;");

	//Adding title to Vertical Layout
	showImgLayout->addWidget(showImgTitleLayout);
	showImgLayout->setSpacing(1);//set spacing between title and box
	showImgLayout->setContentsMargins(0, 0, 0, 0);

	//Widget will align ts image in its center and have a boarder
	imgBoxLayout = new QLabel(this);
	imgBoxLayout->setAlignment(Qt::AlignCenter);
	imgBoxLayout->setStyleSheet("border: 2px solid black;");
	imgBoxLayout->setMinimumHeight(SIwidgetH);

	//connect box Widget to vertical layout
	showImgLayout->addWidget(imgBoxLayout);

}

//This virtual function is not a pure virtual function most of the subclass widgets also transmit the image to the SLM but not all
void ShowImgWidget::SLMformatTrans()
{
}


//Gives all subclasses the ability to convert a RGB opencv Mat to a 3 byte RGB QImage
QImage ShowImgWidget::mat2Qimage(cv::Mat mat)
{
	//Converts the Mat object to the 24-bit RGB color format of QImage
	QImage qimage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
	return qimage;


}
