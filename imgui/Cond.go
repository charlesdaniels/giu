package imgui

const (
	ImGuiCond_Always       int = 1 << 0 // Set the variable
	ImGuiCond_Once         int = 1 << 1 // Set the variable once per runtime session (only the first call with succeed)
	ImGuiCond_FirstUseEver int = 1 << 2 // Set the variable if the object/window has no persistently saved data (no entry in .ini file)
	ImGuiCond_Appearing    int = 1 << 3 // Set the variable if the object/window is appearing after being hidden/inactive (or the first time)
)
