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

func PlotLineValues(label_id string, values []float32, offset int) {
	label_idArg, label_idFin := wrapString(label_id)
	defer label_idFin()
	valuesArray := make([]C.float, len(values))
	for i, value := range values {
		valuesArray[i] = C.float(value)
	}

	C.ipgPlotLineValues(label_idArg, &valuesArray[0], C.int(len(values)), C.int(offset), implotStride)
}

func PlotLinePoints(label_id string, xs, ys []float32, offset int) {
	label_idArg, label_idFin := wrapString(label_id)
	defer label_idFin()

	xsC := make([]C.float, len(xs))
	for i, value := range xs {
		xsC[i] = C.float(value)
	}

	ysC := make([]C.float, len(ys))
	for i, value := range ys {
		ysC[i] = C.float(value)
	}

	// silently choose the shorter of the two lists if they are mismatched
	//
	// XXX: maybe this should throw an error?
	l := len(xsC)
	if len(ysC) < l {
		l = len(ysC)
	}

	C.ipgPlotLinePoints(label_idArg, &xsC[0], &ysC[0], C.int(l), C.int(offset), implotStride)
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
