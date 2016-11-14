#include <iostream>
#include "opencv2/opencv.hpp"

using std::cout;
using std::cerr;
using std::endl;
using namespace cv;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cerr << "input image required" << endl;
        cerr << "ex: " << argv[0] << " image.png" << endl;

        return 1;
    }

    Mat image = imread(argv[1], IMREAD_COLOR);
    imshow("Original Image", image);

    Mat gaussImage;
    GaussianBlur(image, gaussImage, Size(5, 5), 5);
    imshow("Gaussian Blurred Image", gaussImage);

    Mat medianImage;
    medianBlur(image, medianImage, 5);
    imshow("Median Blurred Image", medianImage);

    Mat bilaImage;
    bilateralFilter(image, bilaImage, 5, 120, 120);
    imshow("Bilateral Blurred Image", bilaImage);

    cout << "Press any key to continue" << endl;
    waitKey(0);

    destroyAllWindows();

    return 0;
}
