#pragma once

#include "imguiWrapperTypes.h"
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

void ipgPlot(const char* label_id, const float* values, int count, int offset, int stride);

#ifdef __cplusplus
}
#endif
