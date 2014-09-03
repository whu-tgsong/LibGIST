#include <iostream>
#include <iomanip>
#include <opencv2/opencv.hpp>

#include "standalone_image.h"
#include "gist.h"

using namespace std;
using namespace cv;
using namespace clany;

const GISTParams DEFAULT_PARAMS {256, 256, 4, 3, {8, 8, 4}};


int main(int argc, char* args[])
{
    string file_name;
    Mat src = imread(file_name);
    if (src.empty()) {
        cerr << "No input image!" << endl;
        exit(1);
    }

    vector<float> result;
    GIST gist_ext(DEFAULT_PARAMS);
    gist_ext.extract(src, result);

    for (const auto & val : result) {
        cout << fixed << setprecision(4) << val << " ";
    }
    cout << endl;

    return 0;
}