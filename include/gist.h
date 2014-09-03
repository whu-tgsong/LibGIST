#ifndef GIST_H
#define GIST_H

#include <opencv2/core/core.hpp>
#include "clany/clany_macros.h"
#include "libgist.h"

_CLANY_BEGIN
struct GISTParams {
    int width;
    int height;
    int blocks;
    int scale;
    vector<int> orients;
};

class GIST {
public:
#if __cplusplus >= 201103L
    GIST() = default;
#endif
    GIST(const GISTParams& gist_params) : params(gist_params) {}

    void setParams(const GISTParams& gist_params) {
        params = gist_params;
    }

    void extract(const cv::Mat& src, vector<float>& result) const {
        extract(src, result, params.blocks, params.scale, params.orients.data());
    }

    void extract(const cv::Mat& src, vector<float>& result,
                 int n_blocks, int n_scale, const int* n_orientations) const;

private:
#if __cplusplus >= 201103L
    GISTParams params {256, 256, 4, 3, {8, 8, 4}};
#else
    GISTParams params;
#endif
};
_CLANY_END

#endif // GIST_H
