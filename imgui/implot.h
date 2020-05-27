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

// A range defined by a min/max value. Used for plot axes ranges.
struct ImPlotRange {
    float Min, Max;
    ImPlotRange();
    bool Contains(float value) const;
    float Size() const;
};

// Combination of two ranges for X and Y axes.
struct ImPlotLimits {
    ImPlotRange X, Y;
    ImPlotLimits();
    bool Contains(const ImVec2& p) const;
    ImVec2 Size() const;
};

// Plot style structure
struct ImPlotStyle {
    float    LineWeight;              // = 1, line weight in pixels
    ImPlotMarker Marker;              // = ImPlotMarker_None, marker specification
    float    MarkerSize;              // = 4, marker size in pixels (roughly the marker's "radius")
    float    MarkerWeight;            // = 1, outline weight of markers in pixels
    float    ErrorBarSize;            // = 5, error bar whisker width in pixels
    float    ErrorBarWeight;          // = 1.5, error bar whisker weight in pixels
    float    DigitalBitHeight;        // = 8, digital channels bit height (at y = 1.0f) in pixels
    float    DigitalBitGap;           // = 4, digital channels bit padding gap in pixels
    ImVec4   Colors[ImPlotCol_COUNT]; // array of plot specific colors
    ImPlotStyle();
};

//-----------------------------------------------------------------------------
// Core API
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
// Plot Items
//-----------------------------------------------------------------------------

// Plots a standard 2D line plot.
void PlotLine(const char* label_id, const float* values, int count, int offset = 0, int stride = sizeof(float));
void PlotLine(const char* label_id, const float* xs, const float* ys, int count, int offset = 0, int stride = sizeof(float));
void PlotLine(const char* label_id, const ImVec2* data, int count, int offset = 0);
void PlotLine(const char* label_id, ImVec2 (*getter)(void* data, int idx), void* data, int count, int offset = 0);
// Plots a standard 2D scatter plot.
void PlotScatter(const char* label_id, const float* values, int count, int offset = 0, int stride = sizeof(float));
void PlotScatter(const char* label_id, const float* xs, const float* ys, int count, int offset = 0, int stride = sizeof(float));
void PlotScatter(const char* label_id, const ImVec2* data, int count, int offset = 0);
void PlotScatter(const char* label_id, ImVec2 (*getter)(void* data, int idx), void* data, int count, int offset = 0);
// Plots a vertical bar graph.
void PlotBars(const char* label_id, const float* values, int count, float width = 0.67f, float shift = 0, int offset = 0, int stride = sizeof(float));
void PlotBars(const char* label_id, const float* xs, const float* ys, int count, float width, int offset = 0, int stride = sizeof(float));
void PlotBars(const char* label_id, ImVec2 (*getter)(void* data, int idx), void* data, int count, float width, int offset = 0);
// Plots a horizontal bar graph.
void PlotBarsH(const char* label_id, const float* values, int count, float height = 0.67f, float shift = 0, int offset = 0, int stride = sizeof(float));
void PlotBarsH(const char* label_id, const float* xs, const float* ys, int count, float height,  int offset = 0, int stride = sizeof(float));
void PlotBarsH(const char* label_id, ImVec2 (*getter)(void* data, int idx), void* data, int count, float height,  int offset = 0);
// Plots vertical error bar.
void PlotErrorBars(const char* label_id, const float* xs, const float* ys, const float* err, int count, int offset = 0, int stride = sizeof(float));
void PlotErrorBars(const char* label_id, const float* xs, const float* ys, const float* neg, const float* pos, int count, int offset = 0, int stride = sizeof(float));
void PlotErrorBars(const char* label_id, ImVec4 (*getter)(void* data, int idx), void* data, int count, int offset = 0);
// Plots a pie chart. If the sum of values > 1, each value will be normalized. Center and radius are in plot coordinates.
void PlotPieChart(const char** label_ids, float* values, int count, const ImVec2& center, float radius, bool show_percents = true, float angle0 = 90);
// Plots digital data.
void PlotDigital(const char* label_id, const float* xs, const float* ys, int count, int offset = 0, int stride = sizeof(float));
void PlotDigital(const char* label_id, ImVec2 (*getter)(void* data, int idx), void* data, int count, int offset = 0);
// Plots a text label at point x,y.
void PlotText(const char* text, float x, float y, bool vertical = false, const ImVec2& pixel_offset = ImVec2(0,0));

//-----------------------------------------------------------------------------
// Plot Queries
//-----------------------------------------------------------------------------

/// Returns true if the plot area in the current or most recent plot is hovered.
bool IsPlotHovered();
/// Returns the mouse position in x,y coordinates of the current or most recent plot. A negative y_axis uses the current value of SetPlotYAxis (0 initially).
ImVec2 GetPlotMousePos(int y_axis = -1);
/// Returns the current or most recent plot axis range. A negative y_axis uses the current value of SetPlotYAxis (0 initially).
ImPlotLimits GetPlotLimits(int y_axis = -1);
/// Returns true if the current or most recent plot is being queried.
bool IsPlotQueried();
/// Returns the current or most recent plot query bounds.
ImPlotLimits GetPlotQuery(int y_axis = -1);

//-----------------------------------------------------------------------------
// Plot Styling
//-----------------------------------------------------------------------------

// Provides access to plot style structure for permanant modifications to colors, sizes, etc.
ImPlotStyle& GetStyle();

// Sets the color palette to be used for plot items.
void SetPalette(const ImVec4* colors, int num_colors);
// Restores the default ImPlot color map.
void RestorePalette();

// Temporarily modify a plot color.
void PushStyleColor(ImPlotCol idx, ImU32 col);
// Temporarily modify a plot color.
void PushStyleColor(ImPlotCol idx, const ImVec4& col);
// Undo temporary color modification.
void PopStyleColor(int count = 1);

// Temporarily modify a style variable of float type.
void PushStyleVar(ImPlotStyleVar idx, float val);
// Temporarily modify a style variable of int type.
void PushStyleVar(ImPlotStyleVar idx, int val);
// Undo temporary style modification.
void PopStyleVar(int count = 1);

//-----------------------------------------------------------------------------
// Plot Utils
//-----------------------------------------------------------------------------

/// Set the axes range limits of the next plot. Call right before BeginPlot(). If ImGuiCond_Always is used, the axes limits will be locked.
void SetNextPlotLimits(float x_min, float x_max, float y_min, float y_max, ImGuiCond cond = ImGuiCond_Once);
/// Set the X axis range limits of the next plot. Call right before BeginPlot(). If ImGuiCond_Always is used, the axis limits will be locked.
void SetNextPlotLimitsX(float x_min, float x_max, ImGuiCond cond = ImGuiCond_Once);
/// Set the Y axis range limits of the next plot. Call right before BeginPlot(). If ImGuiCond_Always is used, the axis limits will be locked.
void SetNextPlotLimitsY(float y_min, float y_max, ImGuiCond cond = ImGuiCond_Once, int y_axis = 0);

/// Select which Y axis will be used for subsequent plot elements. The default is '0', or the first Y axis.
void SetPlotYAxis(int y_axis);

// Get the current Plot position (top-left) in pixels.
ImVec2 GetPlotPos();
// Get the curent Plot size in pixels.
ImVec2 GetPlotSize();

// Convert pixels to a position in the current plot's coordinate system. A negative y_axis uses the current value of SetPlotYAxis (0 initially).
ImVec2 PixelsToPlot(const ImVec2& pix, int y_axis = -1);
// Convert a position in the current plot's coordinate system to pixels. A negative y_axis uses the current value of SetPlotYAxis (0 initially).
ImVec2 PlotToPixels(const ImVec2& plt, int y_axis = -1);

// Push clip rect for rendering to current plot area
void PushPlotClipRect();
// Pop plot clip rect
void PopPlotClipRect();

//-----------------------------------------------------------------------------
// Demo
//-----------------------------------------------------------------------------

// Shows the ImPlot demo. Add implot_demo.cpp to your sources!
void ShowDemoWindow(bool* p_open = NULL);

}  // namespace ImPlot
