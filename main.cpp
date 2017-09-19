#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>

using namespace std;
double fgamma(float pixel,float ngamma){
    double re = (pow((pixel/255.0),ngamma)*255.0);
    return re;
}

int main(int argc, char *argv[])
{
    if(argc==1){
        cout << "no se encontro imagen" << endl;
        return 1;
    }
    cv::Mat img = cv::imread(argv[1],1);
    float ngamma=atof(argv[2]);
    if(img.empty()){
        cout << "Error al abrir imagen" << argv[1] << endl;
        return 1;
   }
   cv::Mat dst;
   cv::Mat_<cv::Vec3b> _I = img;
   int i,j;
   for(i=0;i< img.rows;i++){
       for(j=0;j<img.cols;j++){
           _I(i,j)[0]=fgamma(_I(i,j)[0],ngamma);
           _I(i,j)[1]=fgamma(_I(i,j)[1],ngamma);
           _I(i,j)[2]=fgamma(_I(i,j)[2],ngamma);
       }
   }
    dst = _I;
    cv::imshow("Input",dst);
    cv::waitKey(0);
    return 0;
}
