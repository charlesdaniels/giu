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

// Options for plots
type ImPlotFlags int

const (
	ImPlotFlags_MousePos    ImPlotFlags = C.ImPlotFlags_MousePos
	ImPlotFlags_Legend      ImPlotFlags = C.ImPlotFlags_Legend
	ImPlotFlags_Highlight   ImPlotFlags = C.ImPlotFlags_Highlight
	ImPlotFlags_BoxSelect   ImPlotFlags = C.ImPlotFlags_BoxSelect
	ImPlotFlags_Query       ImPlotFlags = C.ImPlotFlags_Query
	ImPlotFlags_ContextMenu ImPlotFlags = C.ImPlotFlags_ContextMenu
	ImPlotFlags_Crosshairs  ImPlotFlags = C.ImPlotFlags_Crosshairs
	ImPlotFlags_CullData    ImPlotFlags = C.ImPlotFlags_CullData
	ImPlotFlags_AntiAliased ImPlotFlags = C.ImPlotFlags_AntiAliased
	ImPlotFlags_NoChild     ImPlotFlags = C.ImPlotFlags_NoChild
	ImPlotFlags_YAxis2      ImPlotFlags = C.ImPlotFlags_YAxis2
	ImPlotFlags_YAxis3      ImPlotFlags = C.ImPlotFlags_YAxis3
	ImPlotFlags_Default     ImPlotFlags = C.ImPlotFlags_Default
)

// Options for plot axes (X and Y)
type ImPlotAxisFlags = int

const (
	ImPlotAxisFlags_GridLines  ImPlotAxisFlags = C.ImPlotAxisFlags_GridLines
	ImPlotAxisFlags_TickMarks  ImPlotAxisFlags = C.ImPlotAxisFlags_TickMarks
	ImPlotAxisFlags_TickLabels ImPlotAxisFlags = C.ImPlotAxisFlags_TickLabels
	ImPlotAxisFlags_Invert     ImPlotAxisFlags = C.ImPlotAxisFlags_Invert
	ImPlotAxisFlags_LockMin    ImPlotAxisFlags = C.ImPlotAxisFlags_LockMin
	ImPlotAxisFlags_LockMax    ImPlotAxisFlags = C.ImPlotAxisFlags_LockMax
	ImPlotAxisFlags_Adaptive   ImPlotAxisFlags = C.ImPlotAxisFlags_Adaptive
	ImPlotAxisFlags_LogScale   ImPlotAxisFlags = C.ImPlotAxisFlags_LogScale
	ImPlotAxisFlags_Scientific ImPlotAxisFlags = C.ImPlotAxisFlags_Scientific
	ImPlotAxisFlags_Default    ImPlotAxisFlags = C.ImPlotAxisFlags_Default
	ImPlotAxisFlags_Auxiliary  ImPlotAxisFlags = C.ImPlotAxisFlags_Auxiliary
)

// Plot styling colors
type ImPlotCol int

const (
	ImPlotCol_Line          ImPlotCol = C.ImPlotCol_Line
	ImPlotCol_Fill          ImPlotCol = C.ImPlotCol_Fill
	ImPlotCol_MarkerOutline ImPlotCol = C.ImPlotCol_MarkerOutline
	ImPlotCol_MarkerFill    ImPlotCol = C.ImPlotCol_MarkerFill
	ImPlotCol_ErrorBar      ImPlotCol = C.ImPlotCol_ErrorBar
	ImPlotCol_FrameBg       ImPlotCol = C.ImPlotCol_FrameBg
	ImPlotCol_PlotBg        ImPlotCol = C.ImPlotCol_PlotBg
	ImPlotCol_PlotBorder    ImPlotCol = C.ImPlotCol_PlotBorder
	ImPlotCol_XAxis         ImPlotCol = C.ImPlotCol_XAxis
	ImPlotCol_YAxis         ImPlotCol = C.ImPlotCol_YAxis
	ImPlotCol_YAxis2        ImPlotCol = C.ImPlotCol_YAxis2
	ImPlotCol_YAxis3        ImPlotCol = C.ImPlotCol_YAxis3
	ImPlotCol_Selection     ImPlotCol = C.ImPlotCol_Selection
	ImPlotCol_Query         ImPlotCol = C.ImPlotCol_Query
	ImPlotCol_COUNT         ImPlotCol = C.ImPlotCol_COUNT
)

// Plot styling variables
type ImPlotStyleVar int

const (
	ImPlotStyleVar_LineWeight       ImPlotStyleVar = C.ImPlotStyleVar_LineWeight
	ImPlotStyleVar_Marker           ImPlotStyleVar = C.ImPlotStyleVar_Marker
	ImPlotStyleVar_MarkerSize       ImPlotStyleVar = C.ImPlotStyleVar_MarkerSize
	ImPlotStyleVar_MarkerWeight     ImPlotStyleVar = C.ImPlotStyleVar_MarkerWeight
	ImPlotStyleVar_ErrorBarSize     ImPlotStyleVar = C.ImPlotStyleVar_ErrorBarSize
	ImPlotStyleVar_ErrorBarWeight   ImPlotStyleVar = C.ImPlotStyleVar_ErrorBarWeight
	ImPlotStyleVar_DigitalBitHeight ImPlotStyleVar = C.ImPlotStyleVar_DigitalBitHeight
	ImPlotStyleVar_DigitalBitGap    ImPlotStyleVar = C.ImPlotStyleVar_DigitalBitGap
	ImPlotStyleVar_COUNT            ImPlotStyleVar = C.ImPlotStyleVar_COUNT
)

// Marker specification
type ImPlotMarker int

const (
	ImPlotMarker_None     ImPlotMarker = C.ImPlotMarker_None
	ImPlotMarker_Circle   ImPlotMarker = C.ImPlotMarker_Circle
	ImPlotMarker_Square   ImPlotMarker = C.ImPlotMarker_Square
	ImPlotMarker_Diamond  ImPlotMarker = C.ImPlotMarker_Diamond
	ImPlotMarker_Up       ImPlotMarker = C.ImPlotMarker_Up
	ImPlotMarker_Down     ImPlotMarker = C.ImPlotMarker_Down
	ImPlotMarker_Left     ImPlotMarker = C.ImPlotMarker_Left
	ImPlotMarker_Right    ImPlotMarker = C.ImPlotMarker_Right
	ImPlotMarker_Cross    ImPlotMarker = C.ImPlotMarker_Cross
	ImPlotMarker_Plus     ImPlotMarker = C.ImPlotMarker_Plus
	ImPlotMarker_Asterisk ImPlotMarker = C.ImPlotMarker_Asterisk
)

func float2float(vals []float32) []C.float {
	res := make([]C.float, len(vals))
	for i, value := range vals {
		res[i] = C.float(value)
	}

	return res
}

func float2floatPtr(vals []float32) *C.float {
	arr := float2float(vals)
	return &arr[0]
}

func PlotLineValues(label_id string, values []float32, offset int) {
	label_idArg, label_idFin := wrapString(label_id)
	defer label_idFin()

	C.ipgPlotLineValues(label_idArg, float2floatPtr(values), C.int(len(values)), C.int(offset), implotStride)
}

func PlotLinePoints(label_id string, xs, ys []float32, offset int) {
	label_idArg, label_idFin := wrapString(label_id)
	defer label_idFin()

	// silently choose the shorter of the two lists if they are mismatched
	//
	// XXX: maybe this should throw an error?
	l := len(xs)
	if len(ys) < l {
		l = len(ys)
	}

	C.ipgPlotLinePoints(label_idArg, float2floatPtr(xs), float2floatPtr(ys), C.int(l), C.int(offset), implotStride)
}

func PlotScatterValues(label_id string, values []float32, offset int) {
	label_idArg, label_idFin := wrapString(label_id)
	defer label_idFin()

	C.ipgPlotScatterValues(label_idArg, float2floatPtr(values), C.int(len(values)), C.int(offset), implotStride)
}

func PlotScatterPoints(label_id string, xs, ys []float32, offset int) {
	label_idArg, label_idFin := wrapString(label_id)
	defer label_idFin()

	// silently choose the shorter of the two lists if they are mismatched
	//
	// XXX: maybe this should throw an error?
	l := len(xs)
	if len(ys) < l {
		l = len(ys)
	}

	C.ipgPlotScatterPoints(label_idArg, float2floatPtr(xs), float2floatPtr(ys), C.int(l), C.int(offset), implotStride)
}

func PushPlotStyleVarFloat(idx ImPlotStyleVar, val float32) {
	C.ipgPushStyleVarFloat(C.int(idx), C.float(val))
}

func PushPlotStyleVarInt(idx ImPlotStyleVar, val int) {
	C.ipgPushStyleVarInt(C.int(idx), C.int(val))
}

func PopPlotStyleVar(count int) {
	C.ipgPopStyleVar(C.int(count))
}

func SetNextPlotLimits(x_min, x_max, y_min, y_max float32, cond int) {
	C.ipgSetNextPlotLimits(C.float(x_min), C.float(x_max), C.float(y_min), C.float(y_max), C.int(cond))
}

func PushPlotStyleColor(idx ImPlotCol, col Vec4) {
	colWrapped, _ := col.wrapped()
	C.ipgPushStyleColor(C.int(idx), colWrapped)
}

func PopPlotStyleColor(count int) {
	C.ipgPopStyleColor(C.int(count))
}

func SetNextPlotTicksXValues(values []float32, n_ticks int, labels []string, show_default bool) {
	labelCount := len(items)
	Clabels := make([]*C.char, labelCount)
	for i, label := range labels {
		labelArg, labelDeleter := wrapString(label)
		defer labelDeleter()
		labels[i] = labelArg
	}

	valuesCount := len(values)
	valuesArray := make([]C.float, valuesCount)
	for i, value := range values {
		valuesArray[i] = C.float(value)
	}

	C.ipgSetNextPlotTicksXValues(valuesArray, C.int(n_ticks), Clabels, C.bool(show_default))
}

func SetNextPlotTicksXRange(x_min, x_max float32, n_ticks int, labels []string, show_default bool) {
	labelCount := len(labels)
	Clabels := make([]*C.char, labelCount)
	for i, label := range labels {
		labelArg, labelDeleter := wrapString(label)
		defer labelDeleter()
		labels[i] = labelArg
	}

	C.ipgSetNextPlotTicksXValues(C.double(x_min), C.double(x_max), C.int(n_ticks), Clabels, C.bool(show_default))
}

func SetNextPlotTicksYValues(values []float32, n_ticks int, labels []string, show_default bool, y_axis int) {
	labelCount := len(labels)
	Clabels := make([]*C.char, labelCount)
	for i, label := range labels {
		labelArg, labelDeleter := wrapString(label)
		defer labelDeleter()
		labels[i] = labelArg
	}

	valuesCount := len(values)
	valuesArray := make([]C.float, valuesCount)
	for i, value := range values {
		valuesArray[i] = C.float(value)
	}

	C.ipgSetNextPlotTicksYValues(valuesArray, C.int(n_ticks), Clabels, C.bool(show_default))
}

func SetNextPlotTicksYRange(y_min, y_max float32, n_ticks int, labels []string, show_default bool, y_axis int) {
	labelCount := len(labels)
	Clabels := make([]*C.char, labelCount)
	for i, label := range labels {
		labelArg, labelDeleter := wrapString(label)
		defer labelDeleter()
		labels[i] = labelArg
	}

	C.ipgSetNextPlotTicksYValues(C.double(y_min), C.double(y_max), C.int(n_ticks), Clabels, C.bool(show_default))
}
