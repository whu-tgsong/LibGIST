#ifndef GIST_H
#define GIST_H

#include <vector>
#include <opencv2/opencv.hpp>
#include "clany/clany_macros.h"
#include "libgist.h"

_CLANY_BEGIN
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

class Gist {
public:
    Gist() = default;
    Gist(const cv::Mat& src);

    void extract(const cv::Mat& src, vector<float>& result,
                 int nblocks, int n_scale, const int* n_orientations);

private:

};
_CLANY_END

#endif // GIST_H
