package main

// This file is intended to test the low-level bindings of implot into GIU's
// version of imgui-go. You should not use this style of interacting with
// implot unless there is functionality you need which GIU does not expose.
//
// Go check out ../plotting if you would like to learn how to use GIU's
// plotting widgets.
//
// This file is intended to be, as closely as possible, a transliteration of
// implot's demo file:
//
// https://github.com/epezent/implot/blob/master/implot_demo.cpp

import (
	"math"
	"math/rand"

	g "github.com/AllenDang/giu"
	"github.com/AllenDang/giu/imgui"
)

func randomrange(lower, upper float32) float32 {
	return rand.Float32()*(upper-lower) + lower
}

func loop() {
	g.SingleWindow("ImPlot Binding Demo", g.Layout{
		g.Wrapper(func() {
			imgui.Text("ImPlot GoLang Bindings says hello")

			if imgui.CollapsingHeader("Line Plots") {
				xs1 := make([]float32, 1001)
				ys1 := make([]float32, len(xs1))
				for i, _ := range xs1 {
					xs1[i] = float32(i) * 0.001
					ys1[i] = 0.5 + 0.5*float32(math.Sin(50*float64(xs1[i])))
				}

				xs2 := make([]float32, 11)
				ys2 := make([]float32, len(xs1))
				for i, _ := range xs2 {
					xs2[i] = float32(i) * 0.1
					ys2[i] = xs2[i] * xs2[i]
				}

				if (imgui.BeginPlot("Line Plot", "x", "f(x)", imgui.Vec2{-1, 0}, int(imgui.ImPlotFlags_Default), int(imgui.ImPlotAxisFlags_Default), int(imgui.ImPlotAxisFlags_Default), int(imgui.ImPlotAxisFlags_Auxiliary), int(imgui.ImPlotAxisFlags_Auxiliary))) {
					imgui.PlotLinePoints("sin(50*x)", xs1, ys1, 0)
					imgui.PushPlotStyleVarInt(imgui.ImPlotStyleVar_Marker, int(imgui.ImPlotMarker_Circle))
					imgui.PlotLinePoints("x^2", xs2, ys2, 0)
					imgui.PopPlotStyleVar(1)
					imgui.EndPlot()
				}
			}

			if imgui.CollapsingHeader("Filled Plots") {
				xs1 := make([]float32, 101)
				ys1 := make([]float32, 101)
				ys2 := make([]float32, 101)
				ys3 := make([]float32, 101)

				rand.Seed(4) // chosen by fair dice roll. Guaranteed to be random.

				for i, _ := range xs1 {
					xs1[i] = float32(i)
					ys1[i] = randomrange(400, 450)
					ys2[i] = randomrange(275, 350)
					ys3[i] = randomrange(150, 225)
				}

				imgui.SetNextPlotLimits(0, 100, 0, 500, imgui.ImGuiCond_Once)

				if (imgui.BeginPlot("Stock Prices", "Days", "Price", imgui.Vec2{-1, 0}, int(imgui.ImPlotFlags_Default), int(imgui.ImPlotAxisFlags_Default), int(imgui.ImPlotAxisFlags_Default), int(imgui.ImPlotAxisFlags_Auxiliary), int(imgui.ImPlotAxisFlags_Auxiliary))) {
					imgui.PushPlotStyleColor(imgui.ImPlotCol_Line, imgui.Vec4{1, 1, 0, 1})
					imgui.PushPlotStyleColor(imgui.ImPlotCol_Fill, imgui.Vec4{1, 1, 0, 0.25})
					imgui.PlotLinePoints("Stock 1", xs1, ys1, 0)
					imgui.PopPlotStyleColor(2)

					imgui.PushPlotStyleColor(imgui.ImPlotCol_Line, imgui.Vec4{1, 0, 1, 1})
					imgui.PushPlotStyleColor(imgui.ImPlotCol_Fill, imgui.Vec4{1, 0, 1, 0.25})
					imgui.PlotLinePoints("Stock 2", xs1, ys2, 0)
					imgui.PopPlotStyleColor(2)

					imgui.PushPlotStyleColor(imgui.ImPlotCol_Line, imgui.Vec4{1, 0, 0, 1})
					imgui.PushPlotStyleColor(imgui.ImPlotCol_Fill, imgui.Vec4{1, 0, 0, 0.25})
					imgui.PlotLinePoints("Stock 3", xs1, ys3, 0)
					imgui.PopPlotStyleColor(2)

					imgui.EndPlot()
				}

			}

			if imgui.CollapsingHeader("Scatter Plots") {
				rand.Seed(4)

				xs1 := make([]float32, 100)
				ys1 := make([]float32, 100)

				for i, _ := range xs1 {
					xs1[i] = float32(i) * 0.01
					ys1[i] = xs1[i] + 0.1*randomrange(0, 1)
				}

				xs2 := make([]float32, 50)
				ys2 := make([]float32, 50)

				for i, _ := range xs2 {
					xs2[i] = 0.25 + 0.2*randomrange(0, 1)
					ys2[i] = 0.75 + 0.2*randomrange(0, 1)
				}

				if (imgui.BeginPlot("Scatter Plot", "", "", imgui.Vec2{-1, 0}, int(imgui.ImPlotFlags_Default), int(imgui.ImPlotAxisFlags_Default), int(imgui.ImPlotAxisFlags_Default), int(imgui.ImPlotAxisFlags_Auxiliary), int(imgui.ImPlotAxisFlags_Auxiliary))) {

					imgui.PlotScatterPoints("Data 1", xs1, ys1, 0)
					imgui.PushPlotStyleVarInt(imgui.ImPlotStyleVar_MarkerSize, 6)
					imgui.PushPlotStyleVarInt(imgui.ImPlotStyleVar_Marker, int(imgui.ImPlotMarker_Square))
					imgui.PushPlotStyleColor(imgui.ImPlotCol_MarkerFill, imgui.Vec4{1, 0, 0, 0.25})
					imgui.PushPlotStyleColor(imgui.ImPlotCol_MarkerOutline, imgui.Vec4{0, 0, 0, 0})
					imgui.PlotScatterPoints("Data 2", xs2, ys2, 0)
					imgui.PopPlotStyleColor(2)
					imgui.PopPlotStyleVar(2)
					imgui.EndPlot()

				}

			}

		}),
	})
}

func main() {
	wnd := g.NewMasterWindow("Hello world", 700, 800, g.MasterWindowFlagsNotResizable, nil)
	wnd.Main(loop)
}
