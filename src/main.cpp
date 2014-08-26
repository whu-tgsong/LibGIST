/* Lear's GIST implementation, version 1.1, (c) INRIA 2009, Licence: PSFL */

#include <iostream>
#include <iomanip>
#include <vector>
#include <opencv2/opencv.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "standalone_image.h"
#include "gist.h"

using namespace std;
using namespace cv;
using namespace clany;

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

    Mat src = imread(infilename);

    vector<float> result;
    Gist::extract(src, result, nblocks, n_scale, orientations_per_scale);

    for (const auto & val : result) {
        cout << fixed << setprecision(4) << val << " ";
    }
    cout << endl;

    return 0;
}
