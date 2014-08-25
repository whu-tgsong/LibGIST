/* Lear's GIST implementation, version 1.1, (c) INRIA 2009, Licence: PSFL */

#include <vector>
#include <opencv2/opencv.hpp>

#include "libgist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
using namespace cv;

static color_image_t *load_ppm(const char *fname)
{
    Mat src = imread(fname);

    src.convertTo(src, CV_32F);
    vector<Mat> bgr;
    split(src, bgr);

    color_image_t *img = color_image_new(src.cols, src.rows);
    memcpy(img->c1, bgr[2].data, src.cols * src.rows * sizeof(float));
    memcpy(img->c2, bgr[1].data, src.cols * src.rows * sizeof(float));
    memcpy(img->c3, bgr[0].data, src.cols * src.rows * sizeof(float));

    return img;
}


static void usage(void)
{
    fprintf(stderr, "compute_gist options... [infilename]\n"
            "infile is a PPM raw file\n"
            "options:\n"
            "[-nblocks nb] use a grid of nb*nb cells (default 4)\n"
            "[-orientationsPerScale o_1,..,o_n] use n scales and compute o_i orientations for scale i\n"
            );

    exit(1);
}



int main(int argc, char* args[])
{
    const char *infilename = "/dev/stdin";
    int nblocks = 4;
    int n_scale = 3;
    int orientations_per_scale[] = {8, 8, 4};

    while (*++args) {
        const char *a = *args;

        if (!strcmp(a, "-h")) usage();
        else if (!strcmp(a, "-nblocks")) {
            if (!sscanf(*++args, "%d", &nblocks)) {
                fprintf(stderr, "could not parse %s argument", a);
                usage();
            }
        } else if (!strcmp(a, "-orientationsPerScale")) {
            char *c;
            n_scale = 0;
            for (c = strtok(*++args, ","); c; c = strtok(NULL, ",")) {
                if (!sscanf(c, "%d", &orientations_per_scale[n_scale++])) {
                    fprintf(stderr, "could not parse %s argument", a);
                    usage();
                }
            }
        } else {
            infilename = a;
        }
    }

    color_image_t *im = load_ppm(infilename);

    float *desc = color_gist_scaletab(im, nblocks, n_scale, orientations_per_scale);

    int i;

    int descsize = 0;
    // compute descriptor size
    for (i = 0; i < n_scale; i++)
        descsize += nblocks*nblocks*orientations_per_scale[i];

    descsize *= 3; // color

    // print descriptor
    for (i = 0; i < descsize; i++)
        printf("%.4f ", desc[i]);

    printf("\n");

    free(desc);

    color_image_delete(im);

    return 0;
}