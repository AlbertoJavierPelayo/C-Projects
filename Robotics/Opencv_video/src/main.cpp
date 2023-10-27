#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


const int cam_id = 0;
const int width = 640;
const int height = 480;
const int fps = 30;

const char* Window_name = "Images Filters";

const char* trackbar_name = "FILTER TRYPE:\n 0. Default 1. Threshold 2.Log 3. Smoothing 4. Kernel 5. Edge 6. color Segmentation";
const int trackbar_max_value = 6;

const char* threshold_name = "0. Binary 1. Binary INverted 2 . TRuncate 3. To Zero 4. To Zero Inv";
const int threshold_max_value = 4;

const char*threshold_value_name = "Threshold Value";
const int threshold_value_max_value=255;
 
const char* smoothing_name = "0. Homogeneous 1. Gaussian 2. Median";
const int smoothing_max_value = 2;




void smoothing(cv::Mat& src, cv::Mat&dst, int type);

int main()
{
    cv::VideoCapture input_video;
    int trackbar_value = 0;
    int threshold_filter = 0;
    int threshold_value=125;
    int smoothing_value=0;



    int highH =179;
    int highS =255;
    int highV =255;

    int lowH =0;
    int lowS =0;
    int lowV =0;


    input_video.open(cam_id); //open video
    if(!input_video.isOpened())
    {
        std::cout<<"Cam not opened ...\n";
        return -1;

    }
    input_video.set(cv::CAP_PROP_FRAME_WIDTH, width);//Ancho de la imagen
    input_video.set(cv::CAP_PROP_FRAME_HEIGHT, height);//ALto de la imagen
    input_video.set(cv::CAP_PROP_FPS,fps);//Setear los frames por segundo
    
    std::cout<<"camera fps::  "<<input_video.get(cv::CAP_PROP_FPS)<<"\n";

    cv::Mat input_frame;
    cv::Mat output_frame;
    cv::namedWindow(Window_name,cv::WINDOW_AUTOSIZE);
    cv::createTrackbar(trackbar_name, Window_name, &trackbar_value, trackbar_max_value);
    cv::createTrackbar(threshold_name, Window_name, &threshold_filter, threshold_max_value);
    cv::createTrackbar(threshold_value_name, Window_name, &threshold_value, threshold_value_max_value);
    cv::createTrackbar(smoothing_name, Window_name, &smoothing_value, smoothing_max_value);
    cv::createTrackbar("LowH", Window_name, &lowH, 179);
    cv::createTrackbar("Lows", Window_name, &lowS, 255);
    cv::createTrackbar("Lowv", Window_name, &lowV, 255);

    cv::createTrackbar("HighH", Window_name, &highH, 179);
    cv::createTrackbar("HighS", Window_name, &highS, 255);
    cv::createTrackbar("HighV", Window_name, &highV, 255);


    while(1)
    {
        input_video.read(input_frame);
        
        


        if(trackbar_value==0)
        {
            output_frame=input_frame;
        }
        if(trackbar_value==1)
        {
            cvtColor(input_frame, output_frame, cv::COLOR_BGR2GRAY);
            threshold(output_frame,output_frame,threshold_value,threshold_value_max_value,threshold_filter);
        }
        if(trackbar_value==2)
        {
            input_frame.convertTo(output_frame, CV_32F);
            output_frame =output_frame+1;
            cv::log(output_frame,output_frame);
            cv::convertScaleAbs(output_frame,output_frame);
            cv::normalize(output_frame, output_frame,0,255,cv::NORM_MINMAX);
        }
        if(trackbar_value==3)
        {
            smoothing(input_frame,output_frame,smoothing_value);
        }
        if(trackbar_value ==4)
        {
            cv::Mat kernel = (cv::Mat_<char>(3,3)<< 0, -1, 0,
                                                    -1,20,-1,
                                                    0,-1,0);
            filter2D(input_frame, output_frame, input_frame.depth(),kernel);
        }
        if(trackbar_value==5)
        {
            cv::Mat dst;
            GaussianBlur(input_frame,dst,cv::Size(3,3),0,0);
            cvtColor(dst,dst,cv::COLOR_BGR2GRAY);
            Laplacian(dst,output_frame,CV_16S,3,1,0,cv::BORDER_DEFAULT);
            cv::convertScaleAbs(output_frame,output_frame);
        }
        if(trackbar_value==6)
        {
            cv::Mat imgHSV;
            cvtColor(input_frame,imgHSV,cv::COLOR_BGR2HSV);
            inRange(imgHSV,cv::Scalar(lowH, lowS, lowV),cv::Scalar(highH, highS, highV), output_frame);
        }

        imshow(Window_name,output_frame);
        cv::waitKey(1);

    }
    

    input_video.release();

    return 0;
}

void smoothing(cv::Mat& src, cv::Mat&dst, int type)
{
    
    if(type==0)
    {
        int kernel_size=7*3;
        blur(src,dst,cv::Size(kernel_size,kernel_size),cv::Point(-1,-1));

    }
    if(type==1)
    {
        int kernel_size=7*3;
        GaussianBlur(src,dst,cv::Size(kernel_size,kernel_size),0,0);
    }
    if(type==2)
    {
        int kernel_size=7*3;
        medianBlur(src,dst,kernel_size);

    }
    
}