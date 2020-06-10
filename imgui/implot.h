// MIT License

// Copyright (c) 2020 Evan Pezent

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// ImPlot v0.2 WIP

#pragma once
#include "imgui.h"
#include "implotFlags.h"


// Double precision version of ImVec2 used by ImPlot. Extensible by end users.
struct ImPlotPoint {
    double x, y;
    ImPlotPoint()  { x = y = 0.0; }
    ImPlotPoint(double _x, double _y) { x = _x; y = _y; }
    double  operator[] (size_t idx) const { return (&x)[idx]; }
    double& operator[] (size_t idx)       { return (&x)[idx]; }
#ifdef IMPLOT_POINT_CLASS_EXTRA
    IMPLOT_POINT_CLASS_EXTRA     // Define additional constructors and implicit cast operators in imconfig.h to convert back and forth between your math types and ImPlotPoint.
#endif
};

// A range defined by a min/max value. Used for plot axes ranges.
struct ImPlotRange {
    double Min, Max;
    ImPlotRange();
    bool Contains(double value) const;
    double Size() const;
};

// Combination of two ranges for X and Y axes.
struct ImPlotLimits {
    ImPlotRange X, Y;
    ImPlotLimits();
    bool Contains(const ImPlotPoint& p) const;
    bool Contains(double x, double y) const;
};

// Plot style structure
struct ImPlotStyle {
    float        LineWeight;              // = 1, line weight in pixels
    ImPlotMarker Marker;                  // = ImPlotMarker_None, marker specification
    float        MarkerSize;              // = 4, marker size in pixels (roughly the marker's "radius")
    float        MarkerWeight;            // = 1, outline weight of markers in pixels
    float        ErrorBarSize;            // = 5, error bar whisker width in pixels
    float        ErrorBarWeight;          // = 1.5, error bar whisker weight in pixels
    float        DigitalBitHeight;        // = 8, digital channels bit height (at y = 1.0f) in pixels
    float        DigitalBitGap;           // = 4, digital channels bit padding gap in pixels
    ImVec4       Colors[ImPlotCol_COUNT]; // array of plot specific colors
    ImPlotStyle();
};

//-----------------------------------------------------------------------------
// Begin/End Plot
//-----------------------------------------------------------------------------

namespace ImPlot {

// Starts a 2D plotting context. If this function returns true, EndPlot() must
// be called, e.g. "if (BeginPlot(...)) { ... EndPlot(); }"". #title_id must
// be unique. If you need to avoid ID collisions or don't want to display a
// title in the plot, use double hashes (e.g. "MyPlot##Hidden"). If #x_label
// and/or #y_label are provided, axes labels will be displayed.
bool BeginPlot(const char* title_id,
               const char* x_label      = NULL,
               const char* y_label      = NULL,
               const ImVec2& size       = ImVec2(-1,0),
               ImPlotFlags flags        = ImPlotFlags_Default,
               ImPlotAxisFlags x_flags  = ImPlotAxisFlags_Default,
               ImPlotAxisFlags y_flags  = ImPlotAxisFlags_Default,
               ImPlotAxisFlags y2_flags = ImPlotAxisFlags_Auxiliary,
               ImPlotAxisFlags y3_flags = ImPlotAxisFlags_Auxiliary);
// Only call EndPlot() if BeginPlot() returns true! Typically called at the end
// of an if statement conditioned on BeginPlot().
void EndPlot();

//-----------------------------------------------------------------------------
// Plot Items (single precision data)
//-----------------------------------------------------------------------------

// Plots a standard 2D line plot.
void PlotLine(const char* label_id, const float* values, int count, int offset = 0, int stride = sizeof(float));
void PlotLine(const char* label_id, const double* values, int count, int offset = 0, int stride = sizeof(double));
void PlotLine(const char* label_id, const float* xs, const float* ys, int count, int offset = 0, int stride = sizeof(float));
void PlotLine(const char* label_id, const double* xs, const double* ys, int count, int offset = 0, int stride = sizeof(double));
void PlotLine(const char* label_id, const ImVec2* data, int count, int offset = 0);
void PlotLine(const char* label_id, const ImPlotPoint* data, int count, int offset = 0);
void PlotLine(const char* label_id, ImPlotPoint (*getter)(void* data, int idx), void* data, int count, int offset = 0);

// Plots a standard 2D scatter plot.
void PlotScatter(const char* label_id, const float* values, int count, int offset = 0, int stride = sizeof(float));
void PlotScatter(const char* label_id, const double* values, int count, int offset = 0, int stride = sizeof(double));
void PlotScatter(const char* label_id, const float* xs, const float* ys, int count, int offset = 0, int stride = sizeof(float));
void PlotScatter(const char* label_id, const double* xs, const double* ys, int count, int offset = 0, int stride = sizeof(double));
void PlotScatter(const char* label_id, const ImVec2* data, int count, int offset = 0);
void PlotScatter(const char* label_id, const ImPlotPoint* data, int count, int offset = 0);
void PlotScatter(const char* label_id, ImPlotPoint (*getter)(void* data, int idx), void* data, int count, int offset = 0);

// Plots a vertical bar graph.
void PlotBars(const char* label_id, const float* values, int count, float width = 0.67f, float shift = 0, int offset = 0, int stride = sizeof(float));
void PlotBars(const char* label_id, const double* values, int count, double width = 0.67f, double shift = 0, int offset = 0, int stride = sizeof(double));
void PlotBars(const char* label_id, const float* xs, const float* ys, int count, float width, int offset = 0, int stride = sizeof(float));
void PlotBars(const char* label_id, const double* xs, const double* ys, int count, double width, int offset = 0, int stride = sizeof(double));
void PlotBars(const char* label_id, ImPlotPoint (*getter)(void* data, int idx), void* data, int count, double width, int offset = 0);

// Plots a horizontal bar graph.
void PlotBarsH(const char* label_id, const float* values, int count, float height = 0.67f, float shift = 0, int offset = 0, int stride = sizeof(float));
void PlotBarsH(const char* label_id, const double* values, int count, double height = 0.67f, double shift = 0, int offset = 0, int stride = sizeof(double));
void PlotBarsH(const char* label_id, const float* xs, const float* ys, int count, float height,  int offset = 0, int stride = sizeof(float));
void PlotBarsH(const char* label_id, const double* xs, const double* ys, int count, double height,  int offset = 0, int stride = sizeof(double));
void PlotBarsH(const char* label_id, ImPlotPoint (*getter)(void* data, int idx), void* data, int count, double height,  int offset = 0);

// Plots vertical error bar. The label_id should match the label_id of the associated line or bar plot.
void PlotErrorBars(const char* label_id, const float* xs, const float* ys, const float* err, int count, int offset = 0, int stride = sizeof(float));
void PlotErrorBars(const char* label_id, const double* xs, const double* ys, const double* err, int count, int offset = 0, int stride = sizeof(double));
void PlotErrorBars(const char* label_id, const float* xs, const float* ys, const float* neg, const float* pos, int count, int offset = 0, int stride = sizeof(float));
void PlotErrorBars(const char* label_id, const double* xs, const double* ys, const double* neg, const double* pos, int count, int offset = 0, int stride = sizeof(double));

// Plots horizontal error bars. The label_id should match the label_id of the associated line or bar plot.
void PlotErrorBarsH(const char* label_id, const float* xs, const float* ys, const float* err, int count, int offset = 0, int stride = sizeof(float));
void PlotErrorBarsH(const char* label_id, const double* xs, const double* ys, const double* err, int count, int offset = 0, int stride = sizeof(double));
void PlotErrorBarsH(const char* label_id, const float* xs, const float* ys, const float* neg, const float* pos, int count, int offset = 0, int stride = sizeof(float));
void PlotErrorBarsH(const char* label_id, const double* xs, const double* ys, const double* neg, const double* pos, int count, int offset = 0, int stride = sizeof(double));

// Plots a pie chart. If the sum of values > 1 or normalize is true, each value will be normalized. Center and radius are in plot coordinates.
void PlotPieChart(const char** label_ids, const float* values, int count, float x, float y, float radius, bool normalize = false, const char* label_fmt = "%.1f", float angle0 = 90);
void PlotPieChart(const char** label_ids, const double* values, int count, double x, double y, double radius, bool normalize = false, const char* label_fmt = "%.1f", double angle0 = 90);

// Plots a 2D heatmap chart. Values are expected to be in row-major order. label_fmt can be set to NULL for no labels.
void PlotHeatmap(const char* label_id, const float* values, int rows, int cols, float scale_min, float scale_max, const char* label_fmt = "%.1f", const ImPlotPoint& bounds_min = ImPlotPoint(0,0), const ImPlotPoint& bounds_max = ImPlotPoint(1,1));
void PlotHeatmap(const char* label_id, const double* values, int rows, int cols, double scale_min, double scale_max, const char* label_fmt = "%.1f", const ImPlotPoint& bounds_min = ImPlotPoint(0,0), const ImPlotPoint& bounds_max = ImPlotPoint(1,1));

// Plots digital data.
void PlotDigital(const char* label_id, const float* xs, const float* ys, int count, int offset = 0, int stride = sizeof(float));
void PlotDigital(const char* label_id, const double* xs, const double* ys, int count, int offset = 0, int stride = sizeof(double));
void PlotDigital(const char* label_id, ImPlotPoint (*getter)(void* data, int idx), void* data, int count, int offset = 0);

// Plots a text label at point x,y.
void PlotText(const char* text, float x, float y, bool vertical = false, const ImVec2& pixel_offset = ImVec2(0,0));
void PlotText(const char* text, double x, double y, bool vertical = false, const ImVec2& pixel_offset = ImVec2(0,0));

//-----------------------------------------------------------------------------
// Plot Queries
//-----------------------------------------------------------------------------

// Returns true if the plot area in the current or most recent plot is hovered.
bool IsPlotHovered();
// Returns the mouse position in x,y coordinates of the current or most recent plot. A negative y_axis uses the current value of SetPlotYAxis (0 initially).
ImPlotPoint GetPlotMousePos(int y_axis = -1);
// Returns the current or most recent plot axis range. A negative y_axis uses the current value of SetPlotYAxis (0 initially).
ImPlotLimits GetPlotLimits(int y_axis = -1);
// Returns true if the current or most recent plot is being queried.
bool IsPlotQueried();
// Returns the current or most recent plot query bounds.
ImPlotLimits GetPlotQuery(int y_axis = -1);

//-----------------------------------------------------------------------------
// Plot Styling
//-----------------------------------------------------------------------------

// Provides access to plot style structure for permanant modifications to colors, sizes, etc.
ImPlotStyle& GetStyle();

// Temporarily modify a plot color. Don't forget to call PopStyleColor!
void PushStyleColor(ImPlotCol idx, ImU32 col);
// Temporarily modify a plot color. Don't forget to call PopStyleColor!
void PushStyleColor(ImPlotCol idx, const ImVec4& col);
// Undo temporary color modification.
void PopStyleColor(int count = 1);

// Temporarily modify a style variable of float type. Don't forget to call PopStyleVar!
void PushStyleVar(ImPlotStyleVar idx, float val);
// Temporarily modify a style variable of int type. Don't forget to call PopStyleVar!
void PushStyleVar(ImPlotStyleVar idx, int val);
// Undo temporary style modification.
void PopStyleVar(int count = 1);

// Switch to one of the built-in colormaps. If samples is greater than 1, the map will be linearly resampled.
void SetColormap(ImPlotColormap colormap, int samples = 0);
// Sets a custom colormap.
void SetColormap(const ImVec4* colors, int num_colors);
// Returns the size of the current colormap
int GetColormapSize();
// Returns a color from the Color map given an index > 0 (modulo will be performed)
ImVec4 GetColormapColor(int index);
// Linearly interpolates a color from the current colormap given t between 0 and 1.
ImVec4 LerpColormap(float t);

//-----------------------------------------------------------------------------
// Plot Utils
//-----------------------------------------------------------------------------

// Set the axes range limits of the next plot. Call right before BeginPlot(). If ImGuiCond_Always is used, the axes limits will be locked.
void SetNextPlotLimits(double x_min, double x_max, double y_min, double y_max, ImGuiCond cond = ImGuiCond_Once);
// Set the X axis range limits of the next plot. Call right before BeginPlot(). If ImGuiCond_Always is used, the X axis limits will be locked.
void SetNextPlotLimitsX(double x_min, double x_max, ImGuiCond cond = ImGuiCond_Once);
// Set the Y axis range limits of the next plot. Call right before BeginPlot(). If ImGuiCond_Always is used, the Y axis limits will be locked.
void SetNextPlotLimitsY(double y_min, double y_max, ImGuiCond cond = ImGuiCond_Once, int y_axis = 0);

// Set the X axis ticks and optionally the labels for the next plot.
void SetNextPlotTicksX(const double* values, int n_ticks, const char** labels = NULL, bool show_default = false);
void SetNextPlotTicksX(double x_min, double x_max, int n_ticks, const char** labels = NULL, bool show_default = false);
// Set the Y axis ticks and optionally the labels for the next plot.
void SetNextPlotTicksY(const double* values, int n_ticks, const char** labels = NULL, bool show_default = false, int y_axis = 0);
void SetNextPlotTicksY(double y_min, double y_max, int n_ticks, const char** labels = NULL, bool show_default = false, int y_axis = 0);

// Select which Y axis will be used for subsequent plot elements. The default is '0', or the first (left) Y axis.
void SetPlotYAxis(int y_axis);

// Get the current Plot position (top-left) in pixels.
ImVec2 GetPlotPos();
// Get the curent Plot size in pixels.
ImVec2 GetPlotSize();

// Convert pixels to a position in the current plot's coordinate system. A negative y_axis uses the current value of SetPlotYAxis (0 initially).
ImPlotPoint PixelsToPlot(const ImVec2& pix, int y_axis = -1);
// Convert a position in the current plot's coordinate system to pixels. A negative y_axis uses the current value of SetPlotYAxis (0 initially).
ImVec2 PlotToPixels(const ImPlotPoint& plt, int y_axis = -1);

// Renders a vertical color scale using the current color map
void ShowColormapScale(double scale_min, double scale_max, float height);

// Push clip rect for rendering to current plot area.
void PushPlotClipRect();
// Pop plot clip rect.
void PopPlotClipRect();

//-----------------------------------------------------------------------------
// Demo
//-----------------------------------------------------------------------------

// Shows the ImPlot demo. Add implot_demo.cpp to your sources!
void ShowDemoWindow(bool* p_open = NULL);

}  // namespace ImPlot
