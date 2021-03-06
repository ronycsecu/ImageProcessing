#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include<iostream>

using namespace std;
using namespace cv;

int main ()
{

    Mat src, src_gray, dst1, dst2, dst;

    Mat kernel;
    Point anchor;
    double delta;
    int kernel_size =3;
    int scale = 1;
    int ddepth = CV_16S;
    int c;

    src = imread("lena.jpg", 1 );
    /// Convert the image to grayscale
    cvtColor( src, src_gray, CV_BGR2GRAY );
    imshow("Original Image", src_gray);


    /// Initialize arguments for the filter
    anchor = Point( 0, 0 );
    delta = 0;
    ddepth = -1;

    kernel_size= 3;
    kernel = (Mat_<float>(3,3) << 0, 1, 0, 1, -4, 1, 0, 1, 0);


    /// Apply filter
    filter2D(src, dst1, ddepth , kernel, anchor, delta, BORDER_DEFAULT );
    imshow( "Our Full Mask", dst1 );

    ///apply built in laplacian
    Mat abs_dst;
    Laplacian( src_gray, dst2, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( dst2, abs_dst );

    /// Show what you got
    imshow( "Built in Laplacian", abs_dst );

    int i, j, cnt =0;
    for(i=0; i<512; i++)
    {
        for(j=0; j<512; j++)
        {
            if((int)dst1.at<uchar>(i,j) != (int)dst2.at<uchar>(i,j))
                cnt++;
        }
    }

    if(cnt>0)
        cout << "Matrices are not same\n"<< cnt <<" elements are different" <<endl;
    else
        cout << "Matrices are the same" << endl;

    waitKey(0);
    destroyWindow("window");
    return 0;
}
