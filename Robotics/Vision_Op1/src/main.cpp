#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdio.h>
#include <iostream>



cv::Mat piramidal_reducir(int level, cv::Mat image);
cv::Mat piramidal_extendida(int level, cv::Mat image);

void Save_img(std::string name, std::string path, cv::Mat image);



int main(int argc, char **argv)
{
    if(argc !=2)
    {
        std::cout<<"usage: ./Vision_Op1 <Image>\n";
        return -1;
    }
    cv::Mat image;
    image=imread(argv[1],cv::IMREAD_COLOR);
    if(!image.data)
    {
        std::cout<<"No image data\n";
        return -1;
    }
    cv::Mat P_reducida;
    P_reducida=piramidal_reducir(5,image);
    Save_img("Reducida.jpg","../data/",P_reducida);

    cv::Mat P_extendida;
    P_extendida=piramidal_extendida(3,image);
    Save_img("Extendida.jpg","../data/",P_extendida);

    return 0;
}


void Save_img(std::string name, std::string path, cv::Mat image)
{
    std::string pathname = path+name;
    cv::imwrite( pathname, image);
    std::cout<<"Imagen: "<<pathname<<" guardada correctamente"<<"\n";
    namedWindow(name,cv::WINDOW_AUTOSIZE);
    imshow(name,image);
    cv::waitKey(0);
}



cv::Mat piramidal_reducir(int level, cv::Mat image)
{
    
    int rows = image.rows;
    int cols = image.cols;
    int channels = image.channels();
   
    int final_rows = rows/2;
    int final_cols = cols/2;

    //std::cout<<cols<<"\n";
    //std::cout<<rows<<"\n";

    cv::Mat final_image(final_rows, final_cols, CV_8UC3);
    
    uchar *pixelPtr = (uchar*)image.data;
    uchar *pixelPtrFinal = (uchar*)final_image.data;
    if(level<=0)
    {
        std::cout<<"ERROR NIVEL: Favor de introducir un valor entero a partir de 1"<<"\n";
        return image;
    }
    else{
        //reducimos la imagen
        for (int irows=0;irows<final_rows;irows++)
        {
            for(int icols=0;icols<final_cols;icols++)
            {
                for (int ichannel=0;ichannel<channels;ichannel++)
                {
                    //std::cout<<"ro "<<irows<<" col "<<icols<<" ch "<<ichannel<<" ";
                    //std::cout<<"aux "<<irows*cols*channels + icols*channels + ichannel<<" mirror "<<(irows*2)*cols*channels + (icols*2)*channels + ichannel<<"\n";
                    pixelPtrFinal[irows*final_cols*channels + icols*channels + ichannel] = pixelPtr[(irows*2)*cols*channels + (icols*2)*channels + ichannel];
                }
            }
        }   
        
        if(level==1)
        {
            return final_image;
        }
        else
        {
            return piramidal_reducir(level-1,final_image);
        }
    }
    
}

cv::Mat piramidal_extendida(int level, cv::Mat image)
{
    
    int rows = image.rows;
    int cols = image.cols;
    int channels = image.channels();
   
    int final_rows = rows*2;
    int final_cols = cols*2;

    //std::cout<<final_cols<<"\n";
    //std::cout<<final_rows<<"\n";

    cv::Mat final_image(final_rows, final_cols, CV_8UC3);
    
    uchar *pixelPtr = (uchar*)image.data;
    uchar *pixelPtrFinal = (uchar*)final_image.data;
    if(level<=0)
    {
        std::cout<<"ERROR NIVEL: Favor de introducir un valor entero a partir de 1"<<"\n";
        return image;
    }
    else{
        //ampliamos la imagen
        for (int irows=0;irows<final_rows;irows+=2)
        {
            for(int icols=0;icols<final_cols;icols+=2)
            {
                for (int ichannel=0;ichannel<channels;ichannel++)
                {
                    //std::cout<<"ro "<<irows<<" col "<<icols<<" ch "<<ichannel<<" ";
                    //std::cout<<"aux "<<irows*cols*channels + icols*channels + ichannel<<" mirror "<<(irows*2)*cols*channels + (icols*2)*channels + ichannel<<"\n";
                    pixelPtrFinal[irows*final_cols*channels + icols*channels + ichannel] = pixelPtr[(irows/2)*cols*channels + (icols/2)*channels + ichannel];
                    pixelPtrFinal[irows*final_cols*channels + (icols+1)*channels + ichannel] = pixelPtr[(irows/2)*cols*channels + (icols/2)*channels + ichannel];
                    pixelPtrFinal[(irows+1)*final_cols*channels + icols*channels + ichannel] = pixelPtr[(irows/2)*cols*channels + (icols/2)*channels + ichannel];
                    pixelPtrFinal[(irows+1)*final_cols*channels + (icols+1)*channels + ichannel] = pixelPtr[(irows/2)*cols*channels + (icols/2)*channels + ichannel];
                }
            }
        }   
        
        if(level==1)
        {
            return final_image;
        }
        else
        {
            return piramidal_extendida(level-1,final_image);
        }
    }
    
}