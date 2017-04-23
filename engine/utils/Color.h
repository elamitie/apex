#pragma once

#include "../imgui/imgui.h"

// WIP

class Color {
public:
    int r, g, b, a;

public:
    Color() {};
    Color(int r, int g, int b, int a = 255) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    inline ImVec4& CreateIMColor() {
        ImVec4 color = ImColor(r, g, b, a);
        return color;
    }

	inline void Normalize()
	{
		this->r /= 255;
		this->g /= 255;
		this->b /= 255;
		this->a /= 255;
	}
};