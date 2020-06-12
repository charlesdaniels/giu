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
	return ImPlot::BeginPlot(title_id, x_label, y_label, *sizeArg, flags, x_flags, y_flags, y2_flags, y3_flags);
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

void ipgPlotScatterValues(const char* label_id, const float* values, int count, int offset, int stride) {
	ImPlot::PlotScatter(label_id, values, count, offset, stride);
}

void ipgPlotScatterPoints(const char* label_id, const float* xs, const float* ys, int count, int offset, int stride) {
	ImPlot::PlotScatter(label_id, xs, ys, count, offset, stride);
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

void ipgSetNextPlotLimits(float x_min, float x_max, float y_min, float y_max, int cond) {
	ImPlot::SetNextPlotLimits(x_min, x_max, y_min, y_max, cond);
}

void ipgPushStyleColor(int idx, IggVec4 const *col) {
	Vec4Wrapper colArg(col);
	ImPlot::PushStyleColor(idx, *colArg);
}

void ipgPopStyleColor(int count) {
	ImPlot::PopStyleColor(count);
}

void ipgSetNextPlotTicksXValues(const double* values, int n_ticks, const char** labels, bool show_default) {
	ImPlot::SetNextPlotTicksX(values, n_ticks, labels, show_default);
}

void ipgSetNextPlotTicksXRange(double x_min, double x_max, int n_ticks, const char** labels, bool show_default) {
	ImPlot::SetNextPlotTicksX(x_min, x_max, n_ticks, labels, show_default);

}

void ipgSetNextPlotTicksYValues(const double* values, int n_ticks, const char** labels, bool show_default, int y_axis) {
	ImPlot::SetNextPlotTicksY(values, n_ticks, labels, show_default, y_axis);
}

void ipgSetNextPlotTicksYRange(double x_min, double x_max, int n_ticks, const char** labels, bool show_default, int y_axis) {
	ImPlot::SetNextPlotTicksY(x_min, x_max, n_ticks, labels, show_default, y_axis);

}
