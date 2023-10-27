#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdio.h>
#include <iostream>


cv::Mat customGray(cv::Mat image);

int main(int argc, char **argv)
{
    if(argc !=2)
    {
        std::cout<<"usage: ./gay <Image>\n";
        return -1;
    }
    cv::Mat image;
    image=imread(argv[1],cv::IMREAD_COLOR);
    if(!image.data)
    {
        std::cout<<"No image data\n";
        return -1;
    }
    cv::Mat gray;
    gray=customGray(image);
    imwrite( "../Gray_Image.jpg", gray);
    namedWindow("Display Window",cv::WINDOW_AUTOSIZE);
    imshow("Display Window",gray);
    cv::waitKey(0);
    return 0;
}

cv::Mat customGray(cv::Mat image)
{
    int height = image.rows;
    int width = image.cols;
    int channels = image.channels();

    std::cout << "(" << width << "," <<height<<","<<channels<<")\n";

    int rows = image.rows;
    int cols = image.cols;

    cv::Mat gray(image.rows, image.cols, CV_8UC1);

    //safe method
    /*
    for (int irows=0;irows<rows;irows++)
    {
        for(int icols=0;icols<cols;icols++)
        {
            //data type
            cv::Vec3b colors = image.at<cv::Vec3b>(irows,icols);
            //RGB
            uchar blue = colors.val[0];
            uchar green = colors.val[1];
            uchar red = colors.val[2];

            //obteniendo la magnitud
            double gray_value = 0.2*blue + 0.7*green+0.1*red;

            gray.at<uchar>(irows,icols) = char(gray_value);


        }


    }*/

    //iterator method
    uchar *pixelPtr = (uchar*)image.data;
    uchar *pixelPtrGray = (uchar*)gray.data;
    for (int irows=0;irows<rows;irows++)
    {
        for(int icols=0;icols<cols;icols++)
        {
            uchar blue = pixelPtr[irows*cols*channels + icols*channels +0];
            uchar green = pixelPtr[irows*cols*channels + icols*channels +1];
            uchar red = pixelPtr[irows*cols*channels + icols*channels +2];
            double gray_value = 0.2*blue + 0.7*green+0.1*red;

            pixelPtrGray[irows*cols + icols] = gray_value;

        }
    }

    return gray;
}