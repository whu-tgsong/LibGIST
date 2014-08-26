#ifndef GIST_H
#define GIST_H

#include <array>
#include <vector>
#include <opencv2/opencv.hpp>
#include "clany/clany_macros.h"
#include "libgist.h"

_CLANY_BEGIN
class Gist {
public:
    Gist(const cv::Mat& src) : img(src) {}

    void extract(vector<float>& result, int n_blocks, int n_scale, vector<int> n_orientations) const {
        extract(img, result, n_blocks, n_scale, n_orientations.data());
    }

    void extract(vector<float>& result, int n_blocks, int n_scale,
                 const int* n_orientations) const {
        extract(img, result, n_blocks, n_scale, n_orientations);
    }

    static
    void extract(const cv::Mat& src, vector<float>& result,
                 int n_blocks, int n_scale, const int* n_orientations);

private:
    cv::Mat img;
};
_CLANY_END

#endif // GIST_H
