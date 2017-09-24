#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <ctime>

using namespace std;
double fgamma(float pixel,float ngamma){
    double re = (pow((pixel/255.0),ngamma)*255.0);
    return re;
}

int main(int argc, char *argv[])
{
    unsigned t0, t1,t2,t3;
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
   cv::imshow("real",img);
   t0=clock();
   cv::Mat newTmp1;
   img.convertTo(newTmp1, CV_32F);
   newTmp1 = newTmp1/255;
   cv::pow(newTmp1,ngamma,newTmp1);
   newTmp1 *=255;
   newTmp1.convertTo(newTmp1,img.depth());
   cv::imshow("Mat Completo",newTmp1);
   t1=clock();
   double time = (double(t1-t0)/CLOCKS_PER_SEC);
   cout << "Mat completo: " << time << endl;
   t2=clock();
   cv::Mat dst = img;
   cv::Mat_<cv::Vec3b> _I = dst;
   int i,j;
   for(i=0;i< img.rows;i++){
       for(j=0;j<img.cols;j++){
           _I(i,j)[0]=fgamma(_I(i,j)[0],ngamma);
           _I(i,j)[1]=fgamma(_I(i,j)[1],ngamma);
           _I(i,j)[2]=fgamma(_I(i,j)[2],ngamma);
       }
   }
    dst = _I;
    cv::imshow("pixel por pixel",dst);
    t3=clock();
    double time1 = (double(t3-t2)/CLOCKS_PER_SEC);
    cout << "Pixel por pixel: " << time1 << endl;
    cv::waitKey(0);
    return 0;
}
