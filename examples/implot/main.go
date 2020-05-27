package main

import (
	"math"

	g "github.com/AllenDang/giu"
	"github.com/AllenDang/giu/imgui"
)

func loop() {
	plotdata := make([]float32, 0)
	x := float32(0)
	delta := float32(0.01)
	for len(plotdata) < 1000 {
		plotdata = append(plotdata, float32(math.Sin(float64(x))))
		x += delta
	}
	g.SingleWindow("hello world", g.Layout{
		g.Label("Hello world from giu"),
		g.Label("Simple sin(x) plot:"),
		g.Wrapper(func() {
			imgui.BeginChildV("container0", imgui.Vec2{640, 480}, true, 0)
			if imgui.BeginPlot("plot0", "x label", "y label", imgui.Vec2{640, 480}, 0, 0, 0, 0, 0) {
				imgui.PlotLineValues("plot0 label!", plotdata, 0)
				imgui.EndPlot()
			}
			imgui.EndChild()
		}),
		// g.PlotLines("testplot", plotdata),
		g.Label("sin(x) plot with overlay text, and size:"),
		// g.PlotLinesV("plot label", plotdata, 0, "overlay text", math.MaxFloat32, math.MaxFloat32, 500, 200),
	})
}

func main() {
	wnd := g.NewMasterWindow("Hello world", 700, 800, g.MasterWindowFlagsNotResizable, nil)
	wnd.Main(loop)
}
