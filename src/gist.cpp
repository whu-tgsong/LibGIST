#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>
#include "gist.h"
#include "clany/timer.hpp"

using namespace std;
using namespace cv;
using namespace clany;

namespace {
class GistImage {
public:
    GistImage(const cv::Mat& src) {
        cv::Mat src_f;
        src.convertTo(src_f, CV_32F);

        if (src.channels() == 3) {
            vector<cv::Mat> bgr;
            cv::split(src_f, bgr);

            color_img = color_image_new(src.cols, src.rows);
            memcpy(color_img->c1, bgr[2].data, src.cols * src.rows * sizeof(float));
            memcpy(color_img->c2, bgr[1].data, src.cols * src.rows * sizeof(float));
            memcpy(color_img->c3, bgr[0].data, src.cols * src.rows * sizeof(float));
        }

        if (src.channels() == 1) {
            gray_img = image_new(src.cols, src.rows);
            memcpy(gray_img->data, src_f.data, src.cols * src.rows * sizeof(float));
        }
    }

    ~GistImage() {
        if (color_img) color_image_delete(color_img);
        if (gray_img) image_delete(gray_img);
    }

    operator color_image_t* () {
        return color_img;
    }

    operator image_t* () {
        return gray_img;
    }

private:
    color_image_t *color_img = nullptr;
    image_t* gray_img = nullptr;
};

using GistDesc = unique_ptr<float, void(*)(void*)>;
}   // Unamed namespace

void Gist::extract(const Mat& src, vector<float>& result,
                   int nblocks, int n_scale, const int* n_orientations)
{
    assert(!src.empty());
    assert(src.channels() == 3 || src.channels() == 1);

    GistImage img(src);

    // Compute gist descriptor
    GistDesc desc(nullptr, &free);

    if (src.channels() == 3) {
        desc.reset(color_gist_scaletab(img, nblocks, n_scale, n_orientations));
    } else {
        desc.reset(bw_gist_scaletab(img, nblocks, n_scale, n_orientations));
    }

    // Compute descriptor size
    int descsize = 0;
    for (int i = 0; i < n_scale; i++) {
        descsize += nblocks * nblocks * n_orientations[i];
    }
    descsize *= src.channels();

    // Copy to result
    result.resize(descsize);
    memcpy(result.data(), desc.get(), sizeof(float) * descsize);
}
