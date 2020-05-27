package imgui

// #cgo CXXFLAGS: -std=c++11
// #include "implotWrapper.h"
import "C"

func BeginPlot(title_id, x_label, y_label string, size Vec2, flags, x_flags, y_flags, y2_flags, y3_flags int) bool {
	title_idArg, title_idFin := wrapString(title_id)
	defer title_idFin()
	x_labelArg, x_labelFin := wrapString(x_label)
	defer x_labelFin()
	y_labelArg, y_labelFin := wrapString(y_label)
	defer y_labelFin()
	sizeArg, _ := size.wrapped()

	res := C.ipgBeginPlot(title_idArg, x_labelArg, y_labelArg, sizeArg, C.int(flags), C.int(x_flags), C.int(y_flags), C.int(y2_flags), C.int(y3_flags))

	return bool(res)
}

func EndPlot() {
	C.ipgEndPlot()
}

// The stride is always 4, because this is sizeof(float32).
const implotStride = 4

func PlotLineValues(label_id string, values []float32, offset int) {
	label_idArg, label_idFin := wrapString(label_id)
	defer label_idFin()
	valuesArray := make([]C.float, len(values))
	for i, value := range values {
		valuesArray[i] = C.float(value)
	}

	C.ipgPlotLineValues(label_idArg, &valuesArray[0], C.int(len(values)), C.int(offset), implotStride)
}
