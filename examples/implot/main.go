package main

// This file is heavily based on the implot demo:
//
// https://github.com/epezent/implot/blob/master/implot_demo.cpp

import (
	"math"

	g "github.com/AllenDang/giu"
	"github.com/AllenDang/giu/imgui"
)

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
					// XXX: style?
					imgui.PlotLinePoints("sin(50*x)", xs1, ys1, 0)
					imgui.PushPlotStyleVarInt(imgui.ImPlotStyleVar_Marker, int(imgui.ImPlotMarker_Circle))
					imgui.PlotLinePoints("x^2", xs2, ys2, 0)
					imgui.PopPlotStyleVar(1)
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
