#ifndef PLOT_HPP
#define PLOT_HPP

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cstdio>
#include "common.hpp"

namespace seismath {

typedef struct PlotParameters {
    std::string title = "2D Array";
    std::string xlabel = "X-Axis";
    std::string ylabel = "Y-Axis";
    std::string cblabel = "Intensity";
    size_t width = 800;
    size_t height = 600;
} params;

template <typename T>
void plot1D(const std::vector<T>& arr, const params& plotParams = params()) {

    FILE* gnuplotPipe = popen("gnuplot -persist", "w");
    if (!gnuplotPipe) {
        throw std::runtime_error("Could not open pipe to Gnuplot.");
    }

    fprintf(gnuplotPipe, "set term qt size %zu,%zu\n", plotParams.width, plotParams.height);
    fprintf(gnuplotPipe, "set title '%s' font ',18'\n", plotParams.title.c_str());
    fprintf(gnuplotPipe, "set xlabel '%s' font ',14'\n", plotParams.xlabel.c_str());
    fprintf(gnuplotPipe, "set ylabel '%s' font ',14'\n", plotParams.ylabel.c_str());
    fprintf(gnuplotPipe, "unset key\n");

    fprintf(gnuplotPipe, "plot '-' with lines\n");

    size_t x = 0;
    for (const auto& val : arr) {
        fprintf(gnuplotPipe, "%zu %f\n", x++, static_cast<double>(val));
    }

    fprintf(gnuplotPipe, "e\n");
    fflush(gnuplotPipe);
    fprintf(gnuplotPipe, "pause mouse close\n");

    pclose(gnuplotPipe);
}

static void setupGnuplot(FILE* gnuplotPipe, const params& plotParams) {
    fprintf(gnuplotPipe, "set term qt size %zu,%zu\n", plotParams.width, plotParams.height);
    fprintf(gnuplotPipe, "set title '%s'\n", plotParams.title.c_str());
    fprintf(gnuplotPipe, "unset key\n");
    fprintf(gnuplotPipe, "set view map\n");
    fprintf(gnuplotPipe, "unset surface\n");
    fprintf(gnuplotPipe, "set pm3d interpolate 0,0\n");
    fprintf(gnuplotPipe, "set pm3d map\n");

    fprintf(gnuplotPipe,
        "set palette defined (\\\n"
        "    0     0      0    0.5,\\\n"
        "    0.15  0      0    1,\\\n"
        "    0.35  0      0.5  1,\\\n"
        "    0.65  1      1    0,\\\n"
        "    0.85  1      0    0,\\\n"
        "    1     0.5    0    0)\n"
    );

    fprintf(gnuplotPipe, "set colorbox\n");
    fprintf(gnuplotPipe, "set xlabel '%s'\n", plotParams.xlabel.c_str());
    fprintf(gnuplotPipe, "set ylabel '%s'\n", plotParams.ylabel.c_str());
    fprintf(gnuplotPipe, "set cblabel '%s'\n", plotParams.cblabel.c_str());
    fprintf(gnuplotPipe, "set size ratio 0\n");
    fprintf(gnuplotPipe, "set lmargin at screen 0.1\n");
    fprintf(gnuplotPipe, "set rmargin at screen 0.9\n");
    fprintf(gnuplotPipe, "set tmargin at screen 0.9\n");
    fprintf(gnuplotPipe, "set bmargin at screen 0.1\n");
}

template <typename T>
void plot2D(const std::vector<std::vector<T>>& array, const params& plotParams = params()) {
    size_t rows = array.size();
    size_t cols = array[0].size();

    FILE* gnuplotPipe = popen("gnuplot -persist", "w");
    if (!gnuplotPipe) {
        throw std::runtime_error("Could not open pipe to Gnuplot.");
    }

    setupGnuplot(gnuplotPipe, plotParams);

    fprintf(gnuplotPipe, "set xrange [0:%zu]\n", cols);
    fprintf(gnuplotPipe, "set yrange [%zu:0]\n", rows);
    fprintf(gnuplotPipe, "splot '-' matrix with image\n");

    for (size_t i = rows; i-- > 0;) {
        for (size_t j = 0; j < cols; ++j) {
            std::ostringstream oss;
            oss << array[i][j];
            fprintf(gnuplotPipe, "%s ", oss.str().c_str());
        }
        fprintf(gnuplotPipe, "\n");
    }

    fprintf(gnuplotPipe, "\n");
    fprintf(gnuplotPipe, "e\n");
    fprintf(gnuplotPipe, "e\n");
    fflush(gnuplotPipe);
    fprintf(gnuplotPipe, "pause mouse close\n");

    pclose(gnuplotPipe);
}

template <typename T>
void plotFlattened2D(const std::vector<T>& array, size_t rows, size_t cols, const params& plotParams = params()) {
    if (array.size() != rows * cols) {
        throw std::invalid_argument("Flattened array size does not match the specified dimensions.");
    }

    FILE* gnuplotPipe = popen("gnuplot -persist", "w");
    if (!gnuplotPipe) {
        throw std::runtime_error("Could not open pipe to Gnuplot.");
    }

    setupGnuplot(gnuplotPipe, plotParams);

    fprintf(gnuplotPipe, "set xrange [0:%zu]\n", cols);
    fprintf(gnuplotPipe, "set yrange [%zu:0]\n", rows);
    fprintf(gnuplotPipe, "splot '-' matrix with image\n");

    for (size_t i = rows; i-- > 0;) {
        for (size_t j = 0; j < cols; ++j) {
            std::ostringstream oss;
            oss << array[i * cols + j];
            fprintf(gnuplotPipe, "%s ", oss.str().c_str());
        }
        fprintf(gnuplotPipe, "\n");
    }

    fprintf(gnuplotPipe, "\n");
    fprintf(gnuplotPipe, "e\n");
    fprintf(gnuplotPipe, "e\n");
    fflush(gnuplotPipe);
    fprintf(gnuplotPipe, "pause mouse close\n");

    pclose(gnuplotPipe);
}

} // namespace seismath

#endif // PLOT_HPP

