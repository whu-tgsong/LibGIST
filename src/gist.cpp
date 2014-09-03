#include <memory>
#include "gist.h"

using namespace std;
using namespace cv;
using namespace clany;

namespace {
using DescPtr     = unique_ptr<float, void(*)(void*)>;
using ColorImgPtr = unique_ptr<color_image_t, void(*)(color_image_t*)>;
using GrayImgPtr  = unique_ptr<image_t, void(*)(image_t*)>;

class GISTImage {
public:
    GISTImage(const cv::Mat& src) {
        cv::Mat src_f;
        src.convertTo(src_f, CV_32F);

        if (src.channels() == 1) {
            gray_img.reset(image_new(src.cols, src.rows));
            memcpy(gray_img->data, src_f.data, src.cols * src.rows * sizeof(float));
        } else {
            vector<cv::Mat> bgr;
            cv::split(src_f, bgr);

            color_img.reset(color_image_new(src.cols, src.rows));
            memcpy(color_img->c1, bgr[2].data, src.cols * src.rows * sizeof(float));
            memcpy(color_img->c2, bgr[1].data, src.cols * src.rows * sizeof(float));
            memcpy(color_img->c3, bgr[0].data, src.cols * src.rows * sizeof(float));
        }
    }

    operator color_image_t* () {
        return color_img.get();
    }

    operator image_t* () {
        return gray_img.get();
    }

private:
    ColorImgPtr color_img {nullptr, &color_image_delete};
    GrayImgPtr  gray_img  {nullptr, &image_delete};
};
} // Unnamed namespace


//////////////////////////////////////////////////////////////////////////
void GIST::extract(const Mat& src, vector<float>& result,
                   int nblocks, int n_scale, const int* n_orientations) const
{
    assert(!src.empty() && src.channels() == 1 || src.channels() == 3);

    // Scale and crop image


    GISTImage img(src);

    // Compute gist descriptor
    DescPtr desc(nullptr, &free);

    if (src.channels() == 1) {
        desc.reset(bw_gist_scaletab(img, nblocks, n_scale, n_orientations));
    } else {
        desc.reset(color_gist_scaletab(img, nblocks, n_scale, n_orientations));
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