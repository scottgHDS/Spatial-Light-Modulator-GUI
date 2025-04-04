#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include<string>
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QWidget>
#include<filesystem>
#include"ImageGen.h"
#include"Blink_C_wrapper.h"
#include"stdafx.h"

#define maxFocalPnts 1000
#define SobelWidgetW 425
#define SobelWidgetH 225

//This widget uses Sobel Edge detection to create an edge image that it then converts into a Hollogram pattern and writes it to the SLM
//  it creates 3 sliders which control the Sobel Edge detection and displays the results to the user
class SobelEdgeWidget : public QWidget {
    Q_OBJECT

public:
    SobelEdgeWidget(QWidget* parent = nullptr);
    ~SobelEdgeWidget();

signals:
    void holoPattern(QImage pattern);
    void image_loaded();
    void edgeImage(QImage pattern);

 public slots:
     void updateImage();
     void loadImage(QString imagePath);
     void createHologram(QImage qimage);

private:
    QSlider* xSlider;
    QSlider* ySlider;
    QSlider* ksizeSlider;
    QLabel* inputLabel;
    QLabel* outputLabel;
    cv::Mat imageFromPath;
    int  width, height, depth;
    unsigned char* WFC;
    unsigned char* hologramArray;

    float* X_spots;
    float* Y_spots;
    float* Z_spots;
    float* I_spots;
    int num_spots = 0;

    QImage array2Qimage();
    QImage mat2Qimage(cv::Mat mat);
    void CreateImageWidget(QLabel* widgetTitleLabel, QVBoxLayout* SpetraLayout, QLabel* BoxLabel);
    void loadWFC();
    void refreshHologramArray();
    void generateArrays(QImage);
};


