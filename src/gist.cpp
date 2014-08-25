#include "gist.h"
#include "clany/timer.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace clany;

void Gist::extract(const Mat& src, vector<float>& result,
                   int nblocks, int n_scale, const int* n_orientations)
{
    GistImage img(src);

    // Compute gist descriptor
    float* desc;
    if (src.channels() == 3) {
        desc = color_gist_scaletab(img, nblocks, n_scale, n_orientations);
    }

    if (src.channels() == 1) {
        desc = bw_gist_scaletab(img, nblocks, n_scale, n_orientations);
    }

    // Compute descriptor size
    int descsize = 0;
    for (int i = 0; i < n_scale; i++) {
        descsize += nblocks * nblocks * n_orientations[i];
    }
    descsize *= src.channels();

    // Copy to result
    result.resize(descsize);
    memcpy(result.data(), desc, sizeof(float) * descsize);

    free(desc);
}
