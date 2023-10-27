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

const char* trackbar_name = "FILTER TRYPE:\n 0. Default 1. Otsu";
const int trackbar_max_value = 1;

const char* screenshot_name = "0. Default 1. Screenshot";
const int screenshot_max_value = 1;



std::vector<uchar> getHistogram(cv::Mat image);
std::vector<double> getProb(std::vector<uchar> histogram,int cols, int rows);
std::vector<double> getSigma(std::vector<double> Prob);
void Otsu_binarization(cv::Mat &input_image, cv:: Mat &output_image);


int main(int argc, char **argv)
{
    cv::VideoCapture input_video;
    int trackbar_value = 0;
    int screenshot_value = 0;
    input_video.open(cam_id); //open video
    if(!input_video.isOpened())
    {
        std::cout<<"Cam not opened ...\n";
        return -1;

    }
    input_video.set(cv::CAP_PROP_FRAME_WIDTH, width);//Ancho de la imagen
    input_video.set(cv::CAP_PROP_FRAME_HEIGHT, height);//ALto de la imagen
    input_video.set(cv::CAP_PROP_FPS,fps);//Setear los frames por segundo
    
    cv::Mat input_frame;
    cv::Mat output_frame;
    cv::namedWindow(Window_name,cv::WINDOW_AUTOSIZE);
    
    cv::createTrackbar(trackbar_name, Window_name, &trackbar_value, trackbar_max_value);
    cv::createTrackbar(screenshot_name, Window_name, &screenshot_value, screenshot_max_value);

    while(1)
    {
        input_video.read(input_frame);
        
        


        if(trackbar_value==0)
        {
            output_frame=input_frame;
        }
        if(trackbar_value==1)
        {
            //output_frame=input_frame;
            Otsu_binarization(input_frame,output_frame);
            
        }
        if(screenshot_value==1)
        {
            imwrite( "../data/OtsuFilter.jpg", output_frame);
        }

        imshow(Window_name,output_frame);
        cv::waitKey(1);
        

    }
    

    input_video.release();

    return 0;
}

std::vector<uchar> getHistogram(cv::Mat image)
{
    //*
    
    std::vector<uchar> histogram(256,0);
    int rows = image.rows;
    int cols = image.cols;
    uchar *pixelPtr = (uchar*)image.data;

    for (int irows = 0; irows < rows; irows++)
    {
        for (int icols = 0; icols <cols; icols++)
        {
            histogram[pixelPtr[irows*cols + icols]]++;
            //std::cout<<pixelPtr[irows*cols + icols]<<"\n";
        }
    }
    return histogram;
   

}

std::vector<double> getProb(std::vector<uchar> histogram,int cols, int rows)
{
    std::vector<double> Prob(256,0);


    for (int idx =0; idx<256; idx++)
    {
        Prob[idx] = (double)histogram[idx]/(cols*rows);
    }

    return Prob;
}

std::vector<double> getSigma(std::vector<double> Prob)
{
    std::vector<double> Sigma(256,0);
    for (int idx=0; idx<256; idx++)
    {
        double W_0 = 0;
        double U_0 = 0;
        double W_1 = 0;
        double U_1 = 0;

        for (int idy = 0; idy < idx;idy++) 
        {
            W_0+=Prob[idy];
        }
        for (int idy = idx+1; idy < 256;idy++)
        {
            W_1+= 1-Prob[idy];
        } 
   
        for (int idy = 0; idy < idx;idy++) 
        {
            U_0+=idy*Prob[idy];
        }
        if(W_0>0) 
        {
            U_0=U_0/W_0;
        }
        for (int idy = idx+1; idy < 256; idy++) 
        {
            U_1 = idy*Prob[idy];
        }
        if(W_1>0) 
        {
            U_1 = U_1/W_1;
        }

        Sigma[idx]=(W_0*W_1)*((U_0*U_1)*(U_0*U_1));
    }
    return Sigma;
}

void Otsu_binarization(cv::Mat &input_image, cv:: Mat &output_image)
{
    cv::Mat image_gray;
    cvtColor(input_image,image_gray,cv::COLOR_BGR2GRAY);
    int rows = image_gray.rows;
    int cols = image_gray.cols;

    int in_rows = input_image.rows;
    int in_cols = input_image.cols;

    std::vector<uchar> histogram= getHistogram(image_gray);

    std::vector<double> prob =getProb(histogram,in_cols,in_rows);

    std::vector<double> Sigma=getSigma(prob);

    double max = 0;
    for (auto& idy:Sigma) 
    {
        if(idy>max) 
        {
            max=idy;
        }
    }

    uchar *pixelPtrGray = (uchar*)image_gray.data;
    for (int irows = 0; irows < rows; irows++)
    {
        for (int icols = 0; icols < cols; icols++)
        {
            uchar k = image_gray.at<uchar> (irows, icols);
            if (k>max)
            {
                pixelPtrGray[irows*cols + icols] = 255;
            }
            else
            {
                pixelPtrGray[irows*cols + icols] = 0;
            }
        }
    }
    output_image = image_gray;
}
