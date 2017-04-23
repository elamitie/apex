#pragma once

#include "../utils/Math.h"

class Mouse {
public:
	static bool LeftDown();
	static bool LeftPressed();
	static bool LeftReleased();

	static glm::vec2 GetPosition();
	static glm::vec2 DeltaPosition();
	static glm::vec2 GetScrollOffset();

	static void Update();

	// Hardware only functions that need to be global no touch plz
	static void SetPosition(const glm::vec2& position);
	static void SetLeft(bool val);
	static void SetScrollOffset(const glm::vec2& scroll);

private:
	static bool mLeft;
	static bool mLeftPrev;
	static bool mLeftNext;

	static glm::vec2 mScrollOffset;
	static glm::vec2 mPosition;
	static glm::vec2 mPrevPosition;
	static glm::vec2 mNextPosition;
};