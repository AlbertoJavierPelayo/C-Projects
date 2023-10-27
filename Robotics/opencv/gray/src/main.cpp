// ENcontrar documentacion docs.opencv.org
// En este archivo es donde se programarà la pràctica

void safe_gray(cv::Mat &src, cv::Mat &dst);

#include <iostream>     // cout
#include <opencv2/opencv.hpp>   // cv:mat
        // argc #params, argv ?params
int main(int argc, char** argv)
{
    //argc numero de parametros
    // argv contenido esta variable es un arreglo
    // Si entra a ese if significa que no hay una imagen para leer, por lo que hay un error (1)
    if(argc != 2)
    {
        std::cout <<"usage: ./img_gray <Image_Path>\n";
        return 1;
    }

    cv::Mat image;
    // EL segundo calor de argv es la imagen

    image = imread(argv[1], cv::IMREAD_COLOR);
    if(!image.data == 0)
    {
        std::cout <<"No valid data\n";
        return 1;
    }
    // SI se llego a este punto significa que todo salio bien y que hay una imagen en image

    // Crear nueva imageno
    cv::Mat image_gray;

    // Metodo para cambiar la imagen a otro color, en este caso a gris
    cvtColor(image, image_gray, cv::COLOR_BGR2GRAY);   // imagen a convertir, donde se guardara, de que a que color
    
    // Guardar la imagen nueva
    imwrite("result.jpg", image_gray);   // (nombre de la imagen a guardar, imagen a guardar)
   
    // Crear ventana para mostrar el resultado
    // namedWindow -> Comando para crear ventana
    namedWindow("Gray", cv::WINDOW_AUTOSIZE);     // (identificador de la ventada, tamanio

    // MOstrar imagen
    imshow("Gray", image_gray); // (identificador, imagen a mostrar)

    // Metodo para que opencv espere cierto tiempo

    waitKey(0);     // Se espera 1/t milisegundos; Si se ingresa un 0 espera hasta que el usuario cierre la ventana manualmente

    
    return 0;
}


// imagen rgb, imagen donde se guardara en gris
void safe_gray(cv::Mat &src, cv::Mat &dst)
{
    int rows = src.rows();
    int cols = src.cols();
    int channels = src.depth();

    cv::Mat gray(rows, cols, 1, CV_UC1C);

    for(int id_cols = 0; id_cols < cols; id_cols++)
    {
        for(int id_rows = 0; id_rows < cols; id_rows++)
        {
            cv::Vec3b pval = src.at<cv::Vec3b> (id_rows, id_cols);
            uchar result = 0.2*pval.val[0] + 0.6*pval.val[1] + 0.2-pval.val[2];
            gray.at<uchar>(id_rows, id_cols) = results;
        }
    }
    dst = gray;
}