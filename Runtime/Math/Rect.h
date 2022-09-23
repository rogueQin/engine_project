#pragma once

namespace Engine {
	template<typename T>
	class Rect{
	public:
		T mLeft;
		T mBottom;
		T mWidth;
		T mHeight;

		Rect() mLeft(0), mBottom(0), mWidth(0), mHeight(0){}
		Rect(T _left, T _bottom, T _width, T _height): mLeft(_left), mBottom(_bottom), mWidth(_width), mHeight(_height) {}

		inline T GetRight() { return mLeft + mWidth; }
		inline T GetTop() { return mBottom + mHeight; }
		void Set(T _x, T _y, T _width, T _height) 
		{
			mLeft = _x;
			mBottom = _y;
			mWidth = _width;
			mHeight = _height;
		}
	};
}
