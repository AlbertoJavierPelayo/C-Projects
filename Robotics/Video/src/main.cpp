
#include <opencv2/core.hpp>   //VideoCapture
#include <opencv2/videoio.hpp> 
#include <opencv2/opencv.hpp>
#include <iostream>

const int cam_id = 0;          //Cámara video0
const int width = 640;
const int height = 480;
const int fps = 30;


int main()
{
    cv::VideoCapture input_video;   //Crea instancias con nombre input_video

    input_video.open(cam_id);         //Abre la cámara  (buscar en /dev ls = buscar video#)

    if (!input_video.isOpened())      //Asegura que la cámara se prenda
    {
        std::cout << "Cam not opened ... \n";
        return -1;                    //manda error
    }          

    input_video.set(cv::CAP_PROP_FRAME_WIDTH, width);   //Configura el tamaño de pixel y fps de cámara según la cámara
    input_video.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    input_video.set(cv::CAP_PROP_FPS, fps);

    std::cout << "Camera fps::: " << input_video.get(cv::CAP_PROP_FPS) << "\n";  //despliega fps

    cv::Mat input_frame;              //Se rea espacio para guardar imagen

    namedWindow("Video", cv::WINDOW_AUTOSIZE);

    while(1)
    {
        input_video.read(input_frame);  //Toma la foto siempre
        imshow("Video", input_frame);
        cv::waitKey(1);
    }
    
    input_video.release();           // Libera la cámara
    return 0;
}