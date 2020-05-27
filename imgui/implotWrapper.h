#pragma once

#include "imguiWrapperTypes.h"
#include "implotFlags.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

// we use the "ipg" prefix for "implot go", and to avoid potential name
// collision with "igg" functions.

bool ipgBeginPlot(const char* title_id,
               const char* x_label,
               const char* y_label,
               const IggVec2* size,
               int flags,
               int x_flags,
               int y_flags,
               int y2_flags,
               int y3_flags);

void ipgEndPlot();

void ipgPlotLineValues(const char* label_id, const float* values, int count, int offset, int stride);

void ipgPlotLinePoints(const char* label_id, const float* xs, const float* ys, int count, int offset, int stride);

void ipgPushStyleVarFloat(ImPlotStyleVar idx, float val);

void ipgPushStyleVarInt(ImPlotStyleVar idx, int val);

void ipgPopStyleVar(int);

#ifdef __cplusplus
}
#endif
