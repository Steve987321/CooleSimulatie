#pragma once

namespace sim::ui
{
	// colors and styles 
	void decorations();

	void render_ui();

	constexpr const char* gridModes[] = { "density", "hsv", "velocity" };
	inline char selected_item_name[50] = "";
	inline int selected_item = -1;

}
