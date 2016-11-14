#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    namedWindow("Video");
    VideoCapture vCap;

    if (argc < 2)
    {
        vCap.open(0);
    }
    else
    {
        vCap.open(argv[1]);
    }

    if (!vCap.isOpened())
    {
        cerr << "fail to open " << argv[1] << endl;
        return 1;
    }

    for (short i = 0; i < 100; ++i)
    {
        Mat frame;
        vCap >> frame;
        imshow("Video", frame);
    }

    destroyAllWindows();

    return 0;
}
