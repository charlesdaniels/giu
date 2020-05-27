#include "implot.h"
#include "implotWrapper.h"
#include "imguiWrappedHeader.h"
#include "imguiWrapper.h"
#include "WrapperConverter.h"

bool ipgBeginPlot(const char* title_id,
               const char* x_label,
               const char* y_label,
               const IggVec2* size,
               int flags,
               int x_flags,
               int y_flags,
               int y2_flags,
               int y3_flags) {

	Vec2Wrapper sizeArg(size);
	// ImPlot::BeginPlot(title_id, x_label, y_label, *sizeArg, flags, x_flags, y_flags, y2_flags, y3_flags);
	return ImPlot::BeginPlot(title_id);
}

void ipgEndPlot() {
	ImPlot::EndPlot();
}

void ipgPlotLineValues(const char* label_id, const float* values, int count, int offset, int stride) {
	ImPlot::PlotLine(label_id, values, count, offset, stride);
}

void ipgPlotLinePoints(const char* label_id, const float* xs, const float* ys, int count, int offset, int stride) {
	ImPlot::PlotLine(label_id, xs, ys, count, offset, stride);
}


void ipgPushStyleVarFloat(ImPlotStyleVar idx, float val) {
	ImPlot::PushStyleVar(idx, val);
}

void ipgPushStyleVarInt(ImPlotStyleVar idx, int val) {
	ImPlot::PushStyleVar(idx, val);
}

void ipgPopStyleVar(int count) {
	ImPlot::PopStyleVar(count);
}

