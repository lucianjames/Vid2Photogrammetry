#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/types_c.h>

//gist.github.com/EyalAr/3940636

using namespace cv;

void helloWorld(){
    //create a gui window:
    namedWindow("Output",1);
    //initialize a 120X350 matrix of black pixels:
    Mat output = Mat::zeros( 120, 350, CV_8UC3 );
    //write text on the matrix:
    putText(output,
            "Hello World :)",
            cvPoint(15,70),
            FONT_HERSHEY_PLAIN,
            3,
            cvScalar(0,255,0),
            4);
    //display the image:
    imshow("Output", output);
    //wait for the user to press any key:
    waitKey(0);
}