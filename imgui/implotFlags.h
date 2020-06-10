#ifndef IMPLOT_FLAGS_H
#define IMPLOT_FLAGS_H

#ifdef __cplusplus
extern "C"
{
#endif


//-----------------------------------------------------------------------------
// Basic types and flags
//-----------------------------------------------------------------------------

typedef int ImPlotFlags;
typedef int ImPlotAxisFlags;
typedef int ImPlotCol;
typedef int ImPlotStyleVar;
typedef int ImPlotMarker;
typedef int ImPlotColormap;

// Options for plots.
enum ImPlotFlags_ {
    ImPlotFlags_MousePos    = 1 << 0,  // the mouse position, in plot coordinates, will be displayed in the bottom-right
    ImPlotFlags_Legend      = 1 << 1,  // a legend will be displayed in the top-left
    ImPlotFlags_Highlight   = 1 << 2,  // plot items will be highlighted when their legend entry is hovered
    ImPlotFlags_BoxSelect   = 1 << 3,  // the user will be able to box-select with right-mouse
    ImPlotFlags_Query       = 1 << 4,  // the user will be able to draw query rects with middle-mouse
    ImPlotFlags_ContextMenu = 1 << 5,  // the user will be able to open a context menu with double-right click
    ImPlotFlags_Crosshairs  = 1 << 6,  // the default mouse cursor will be replaced with a crosshair when hovered
    ImPlotFlags_CullData    = 1 << 7,  // plot data outside the plot area will be culled from rendering
    ImPlotFlags_AntiAliased = 1 << 8,  // lines and fills will be anti-aliased (not recommended)
    ImPlotFlags_NoChild     = 1 << 9,  // a child window region will not be used to capture mouse scroll (can boost performance for single ImGui window applications)
    ImPlotFlags_YAxis2      = 1 << 10, // enable a 2nd y axis
    ImPlotFlags_YAxis3      = 1 << 11, // enable a 3rd y axis
    ImPlotFlags_Default     = ImPlotFlags_MousePos | ImPlotFlags_Legend | ImPlotFlags_Highlight | ImPlotFlags_BoxSelect | ImPlotFlags_ContextMenu | ImPlotFlags_CullData
};

// Options for plot axes (X and Y).
enum ImPlotAxisFlags_ {
    ImPlotAxisFlags_GridLines  = 1 << 0, // grid lines will be displayed
    ImPlotAxisFlags_TickMarks  = 1 << 1, // tick marks will be displayed for each grid line
    ImPlotAxisFlags_TickLabels = 1 << 2, // text labels will be displayed for each grid line
    ImPlotAxisFlags_Invert     = 1 << 3, // the axis will be inverted
    ImPlotAxisFlags_LockMin    = 1 << 4, // the axis minimum value will be locked when panning/zooming
    ImPlotAxisFlags_LockMax    = 1 << 5, // the axis maximum value will be locked when panning/zooming
    ImPlotAxisFlags_Adaptive   = 1 << 6, // grid divisions will adapt to the current pixel size the axis
    ImPlotAxisFlags_LogScale   = 1 << 7, // a logartithmic (base 10) axis scale will be used
    ImPlotAxisFlags_Scientific = 1 << 8, // scientific notation will be used for tick labels if displayed (WIP, not very good yet)
    ImPlotAxisFlags_Default    = ImPlotAxisFlags_GridLines | ImPlotAxisFlags_TickMarks | ImPlotAxisFlags_TickLabels | ImPlotAxisFlags_Adaptive,
    ImPlotAxisFlags_Auxiliary  = ImPlotAxisFlags_Default & ~ImPlotAxisFlags_GridLines,
};

// Plot styling colors.
enum ImPlotCol_ {
    ImPlotCol_Line,          // plot line/outline color (defaults to next unused color in current colormap)
    ImPlotCol_Fill,          // plot fill color for bars (defaults to the current line color)
    ImPlotCol_MarkerOutline, // marker outline color (defaults to the current line color)
    ImPlotCol_MarkerFill,    // marker fill color (defaults to the current line color)
    ImPlotCol_ErrorBar,      // error bar color (defaults to ImGuiCol_Text)
    ImPlotCol_FrameBg,       // plot frame background color (defaults to ImGuiCol_FrameBg)
    ImPlotCol_PlotBg,        // plot area background color (defaults to ImGuiCol_WindowBg)
    ImPlotCol_PlotBorder,    // plot area border color (defaults to ImGuiCol_Text)
    ImPlotCol_XAxis,         // x-axis grid/label color (defaults to 25% ImGuiCol_Text)
    ImPlotCol_YAxis,         // y-axis grid/label color (defaults to 25% ImGuiCol_Text)
    ImPlotCol_YAxis2,        // 2nd y-axis grid/label color (defaults to 25% ImGuiCol_Text)
    ImPlotCol_YAxis3,        // 3rd y-axis grid/label color (defaults to 25% ImGuiCol_Text)
    ImPlotCol_Selection,     // box-selection color (defaults to yellow)
    ImPlotCol_Query,         // box-query color (defaults to green)
    ImPlotCol_COUNT
};

// Plot styling variables.
enum ImPlotStyleVar_ {
    ImPlotStyleVar_LineWeight,       // float, line weight in pixels
    ImPlotStyleVar_Marker,           // int,   marker specification
    ImPlotStyleVar_MarkerSize,       // float, marker size in pixels (roughly the marker's "radius")
    ImPlotStyleVar_MarkerWeight,     // float, outline weight of markers in pixels
    ImPlotStyleVar_ErrorBarSize,     // float, error bar whisker width in pixels
    ImPlotStyleVar_ErrorBarWeight,   // float, error bar whisker weight in pixels
    ImPlotStyleVar_DigitalBitHeight, // float, digital channels bit height (at 1) in pixels
    ImPlotStyleVar_DigitalBitGap,    // float, digital channels bit padding gap in pixels
    ImPlotStyleVar_COUNT
};

// Marker specifications. You can combine this with binary OR, e.g. ImPlotMarker_Circle | ImPlotMarker_Cross.
enum ImPlotMarker_ {
    ImPlotMarker_None        = 1 << 0,  // no marker
    ImPlotMarker_Circle      = 1 << 1,  // a circle marker will be rendered at each point
    ImPlotMarker_Square      = 1 << 2,  // a square maker will be rendered at each point
    ImPlotMarker_Diamond     = 1 << 3,  // a diamond marker will be rendered at each point
    ImPlotMarker_Up          = 1 << 4,  // an upward-pointing triangle marker will up rendered at each point
    ImPlotMarker_Down        = 1 << 5,  // an downward-pointing triangle marker will up rendered at each point
    ImPlotMarker_Left        = 1 << 6,  // an leftward-pointing triangle marker will up rendered at each point
    ImPlotMarker_Right       = 1 << 7,  // an rightward-pointing triangle marker will up rendered at each point
    ImPlotMarker_Cross       = 1 << 8,  // a cross marker will be rendered at each point (not filled)
    ImPlotMarker_Plus        = 1 << 9,  // a plus marker will be rendered at each point (not filled)
    ImPlotMarker_Asterisk    = 1 << 10, // a asterisk marker will be rendered at each point (not filled)
};

// Built-in colormaps
enum ImPlotColormap_ {
    ImPlotColormap_Default  = 0, // ImPlot default colormap         (n=10)
    ImPlotColormap_Dark     = 1, // a.k.a. matplotlib "Set1"        (n=9)
    ImPlotColormap_Pastel   = 2, // a.k.a. matplotlib "Pastel1"     (n=9)
    ImPlotColormap_Paired   = 3, // a.k.a. matplotlib "Paired"      (n=12)
    ImPlotColormap_Viridis  = 4, // a.k.a. matplotlib "viridis"     (n=11)
    ImPlotColormap_Plasma   = 5, // a.k.a. matplotlib "plasma"      (n=11)
    ImPlotColormap_Hot      = 6, // a.k.a. matplotlib/MATLAB "hot"  (n=11)
    ImPlotColormap_Cool     = 7, // a.k.a. matplotlib/MATLAB "cool" (n=11)
    ImPlotColormap_Pink     = 8, // a.k.a. matplotlib/MATLAB "pink" (n=11)
    ImPlotColormap_Jet      = 9, // a.k.a. MATLAB "jet"             (n=11)
    ImPlotColormap_COUNT
};


#ifdef __cplusplus
}
#endif

#endif /* IMPLOT_FLAGS_H */

