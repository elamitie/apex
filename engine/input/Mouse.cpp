#include "Mouse.h"

glm::vec2 Mouse::mPosition;
glm::vec2 Mouse::mPrevPosition;
glm::vec2 Mouse::mNextPosition;
glm::vec2 Mouse::mScrollOffset;
bool Mouse::mLeftPrev = false;
bool Mouse::mLeft = false;
bool Mouse::mLeftNext = false;

bool Mouse::LeftDown() {
	return mLeft;
}

bool Mouse::LeftPressed() {
	return mLeft && !mLeftPrev;
}

bool Mouse::LeftReleased() {
	return !mLeft && mLeftPrev;
}

glm::vec2 Mouse::GetPosition()
{
	return mPosition;
}

glm::vec2 Mouse::DeltaPosition()
{
	return mPosition - mPrevPosition;
}

glm::vec2 Mouse::GetScrollOffset()
{
	return mScrollOffset;
}

void Mouse::Update() {
	mLeftPrev = mLeft;
	mLeft = mLeftNext;

	mPrevPosition = mPosition;
	mPosition = mNextPosition;
}

void Mouse::SetPosition(const glm::vec2& position) {
	mNextPosition = position;
}

void Mouse::SetLeft(bool val) {
	mLeftNext = val;
}

void Mouse::SetScrollOffset(const glm::vec2& scroll) {
	mScrollOffset = scroll;
}