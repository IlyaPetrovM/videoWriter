#include <iostream>	// for standard I/O
#include <string>   // for strings

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/videoio/videoio.hpp>  // Video write
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace std;
using namespace cv;

static void help()
{
    cout
        << "------------------------------------------------------------------------------" << endl
        << "This program writes video files."                                               << endl
        << "Usage:"                                                                         << endl
        << "./video-write {inputvideoName.ext|cam} outputVideo.ext [--show]"<< endl  
        << "For example: ./video-write input.avi output.avi"                                << endl
        << "------------------------------------------------------------------------------" << endl
        << endl;
}
     // int fourcc;
//  fourcc = CV_FOURCC('X','V','I','D');
//  fourcc = CV_FOURCC('P','I','M','1');
//  fourcc = CV_FOURCC('M','J','P','G');
 int fourcc = CV_FOURCC('M', 'P', '4', '2');
//  fourcc = CV_FOURCC('D', 'I', 'V', '3');
//  fourcc = CV_FOURCC('D', 'I', 'V', 'X');
//  fourcc = CV_FOURCC('U', '2', '6', '3');
//  fourcc = CV_FOURCC('I', '2', '6', '3');
//  fourcc = CV_FOURCC('F', 'L', 'V', '1');
 // int fourcc = 0;

int main(int argc, char *argv[])
{
    help();
    string source;
    VideoCapture capture;
    if(argc<=2){
        return -1;
    }
    source = argv[1];
    string outputName(argv[2]);
    bool showStream=false;
    if(argc==4){
        string s(argv[3]);
        if(s=="--show") showStream=true;
    }
    if(source=="cam"){
        capture.open(0);
    }else{
        capture.open(source);
    }
    if(capture.isOpened()){
        Size S = Size((int) capture.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
                  (int) capture.get(CV_CAP_PROP_FRAME_HEIGHT));
        VideoWriter outputVideo(outputName, fourcc, capture.get(CAP_PROP_FPS), S, true);  
        if (!outputVideo.isOpened())
        {
            cout  << "Could not open the output video for write: " << source << endl;
            return -1;
        }

        Mat frame,frame1;
        cout << "Started writing" << endl;
        for(;;) //Show the image captured in the window and repeat
        {
            capture >> frame;              // read
            if (frame.empty()) break;         // check if at end
            frame1 = frame.clone();
            outputVideo << frame1;

            if(showStream)imshow("Window",frame1);
            int c = waitKey(10);
            if( c == 27 || c == 'q' || c == 'Q' )break;
        }
        cout << "Finished writing" << endl;
    }
    cout << "program ends" << endl;

    return 0;
}
