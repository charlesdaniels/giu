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

void ipgPlot(const char* label_id, const float* values, int count, int offset, int stride) {
	ImPlot::Plot(label_id, values, count, offset, stride);
}
