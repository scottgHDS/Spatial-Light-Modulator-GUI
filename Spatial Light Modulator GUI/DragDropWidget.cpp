#include"DragDropWidget.h"

//Constructor which creates Widget within the parent widget
DragDropWidget:: DragDropWidget(QWidget* parent) : QWidget(parent) {
       
        //Allow Widget to accept dropped images
        setAcceptDrops(true);

        //Setting size of widget box
        setMinimumSize(DDwidgetW, DDwidgetH);


        //Vertical layout to hold image and title
        QVBoxLayout* DDLayout = new QVBoxLayout(this);

        //Create and fill title Label
        QLabel* DDTitleLayout = new QLabel("Drag Image Below",this);
        DDLayout->setAlignment(Qt::AlignTop);
        DDTitleLayout->setAlignment(Qt::AlignCenter);
        DDTitleLayout->setStyleSheet("margin: 0px; padding: 0px;");

        //Adding title to Vertical Layout
        DDLayout->addWidget(DDTitleLayout);
        DDLayout->setSpacing(1); //set spacing between title and box 
        DDLayout->setContentsMargins(10, 0, 0, 0);//10 pixels from left boarder
        
        //Widget will align its image in its center and have a boarder
        dragBoxLabel = new QLabel(this);
        dragBoxLabel->setAlignment(Qt::AlignCenter);
        dragBoxLabel->setStyleSheet("border: 2px solid black;");
        dragBoxLabel->setMinimumHeight(DDwidgetH);
        
        //connect box Widget to vertical layout
        DDLayout->addWidget(dragBoxLabel);

 }


//Handles how Widget responds to a dragged image entering the screen
void DragDropWidget:: dragEnterEvent(QDragEnterEvent* event) {

    //Will only accept the image itself if it has a location within the computer    
    if (event->mimeData()->hasUrls()) {
            event->acceptProposedAction();
        }
    }


//Once image is dropped within square, image is saved and 
void DragDropWidget:: dropEvent(QDropEvent* event) {
        //QMimeData object created to transfer the data from the dropped images
        const QMimeData* mimeData = event->mimeData();

        //Only accept the Image data if mimeData has a URL within the computer
        if (mimeData->hasUrls()) {
            QStringList filePaths;
            if (checkImageType(mimeData)) return;
            
            //collects each image location of dragged images
            for (const QUrl& url : mimeData->urls()) {
                filePaths.append(url.toLocalFile());
            }

            // Multiple images can be dragged at once, but the
            // code assumes the first file dropped is the image file
            QString imagePath = filePaths.first();

            //Loads image
            QImage image(imagePath);

            //If image load is successful 
            if (!image.isNull()) {

                bool SuccesfulSave;

                // Scale image into a pixel map that will fit in the widget window
                QPixmap droppedImg = QPixmap::fromImage(image.scaled(DDwidgetH, DDwidgetW+10,Qt::KeepAspectRatio));

                //Show pixel map on image
                dragBoxLabel->setPixmap(droppedImg);

                //Records the image's file name
                QString imageName = QFileInfo(imagePath).fileName();

                //Gets current directory path
                QDir dir(QCoreApplication::applicationDirPath());

                //Saves the image in the current_image folder within the project
                QString save_path = dir.absolutePath() + "/current_image/" + imageName; 
                SuccesfulSave=image.save(save_path);

                //If current_image folder is not within the current directory trying saving one layer above
                if (SuccesfulSave == false) {
                    dir.cdUp();
                    save_path = dir.absolutePath() + "/current_image/" + imageName;
                    SuccesfulSave = image.save(save_path);
                }

                //If it is not one layer above, try one more time 2 layers above
                if (SuccesfulSave == false) {
                    dir.cdUp();
                    save_path = dir.absolutePath() + "/current_image/" + imageName;
                    SuccesfulSave = image.save(save_path);
                }

                //If current_image is not on any of the three levels, stop the code and explain the user the issue
                if (SuccesfulSave == false) {
                    QMessageBox::critical(this, "Error", "There is no current_image folder within 0-2 layer above the executable, check the README.");
                    return;
                }

                //Emits the save_path QString to all connected Q style slots
                emit ImageDroppedName(save_path);
            }
        }
    }

int DragDropWidget:: checkImageType(const QMimeData* mimeData)
{
    QStringList filePaths;

    // collects each image location of dragged images
    for (const QUrl& url : mimeData->urls()) {
        QString filePath = url.toLocalFile();

        // Check if file has a valid extension before proceeding
        QString extension = QFileInfo(filePath).suffix().toLower();
        if (extension == "bmp" || extension == "jpg" || extension == "jpeg" || extension == "png" ||
            extension == "ppm" || extension == "xbm" || extension == "xpm") {
            filePaths.append(filePath);
            return 0;
        }
        else {
            // Display error message to user
            QMessageBox::critical(this, "Error", "Invalid file type. Only BMP, JPG, JPEG, PNG, PPM, XBM, and XPM are allowed.");
            return 1;
        }
    }

}
