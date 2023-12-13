#pragma once
#include "DrawingSurface.h"
#include "FilterPoints.h"
// This class is modified from ExampleFilterPointClasses' FilterPointsScaling class, after understanding the source code,
// I modified and deleted some unnecessary methods
class ZoomingFilter : public FilterPoints
{
public:

	ZoomingFilter(int xFactor, int yFactor, FilterPoints* pNextFilter = nullptr)
		: pNextFilter(pNextFilter), xStretch(1), yStretch(1), xCompress(1), yCompress(1)
	{
		setStretch(xFactor, yFactor);
	}

	virtual bool filter(DrawingSurface* surface, int& xVirtual, int& yVirtual, unsigned int& uiColour) override
	{
		handleXthenY(surface, xVirtual, yVirtual, uiColour);
		return false; 
	}

	// Calculate real from virtual position - apply the stretch then any following filter
	virtual int filterConvertVirtualToRealXPosition(int xVirtual) override
	{
		if (xStretch > 1)
		{
			if (pNextFilter)
				return pNextFilter->filterConvertVirtualToRealXPosition(xVirtual * xStretch);
			else
				return xVirtual * xStretch;
		}
		else
		{
			if (pNextFilter)
				return pNextFilter->filterConvertVirtualToRealXPosition(xVirtual / xCompress);
			else
				return xVirtual / xCompress;
		}
	}

	// Calculate real from virtual position - apply the stretch then any following filter
	virtual int filterConvertVirtualToRealYPosition(int yVirtual) override
	{
		if (yStretch > 1)
		{
			if (pNextFilter)
				return pNextFilter->filterConvertVirtualToRealYPosition(yVirtual * yStretch);
			else
				return yVirtual * yStretch;
		}
		else
		{
			if (pNextFilter)
				return pNextFilter->filterConvertVirtualToRealYPosition(yVirtual / xCompress);
			else
				return yVirtual / yCompress;
		}
	}

	// These convert from a clicked location to a virtual pixel position in a surface
	virtual int filterConvertRealToVirtualXPosition(int xReal) override
	{
		// Apply other filter first if it exists (since we are reversing the order we used for virtual to real)
		if (pNextFilter)
			xReal = pNextFilter->filterConvertRealToVirtualXPosition(xReal);
		// Other filter has now been applied so we can try to reverse the effect of THIS filter...
		if (xStretch > 1)
			return xReal / xStretch;
		else
			return xReal * xCompress;
	}

	// These convert from a clicked location to a virtual pixel position in a surface
	virtual int filterConvertRealToVirtualYPosition(int yReal) override
	{
		// Apply other filter first if it exists (since we are reversing the order we used for virtual to real)
		if (pNextFilter)
			yReal = pNextFilter->filterConvertRealToVirtualYPosition(yReal);
		// Other filter has now been applied so we can try to reverse the effect of THIS filter...
		if (yStretch > 1)
			return yReal / yStretch;
		else
			return yReal * yCompress;
	}

	void stretchX() { if (xCompress > 1) --xCompress; else ++xStretch; }
	void stretchY() { if (yCompress > 1) --yCompress; else ++yStretch; }
	void compressX() { if (xStretch > 1) --xStretch; else ++xCompress; }
	void compressY() { if (yStretch > 1) --yStretch; else ++yCompress; }

	void compress() { compressX(); compressY(); }
	void stretch() { stretchX(); stretchY(); }

	/* Set stretch/compress x and y dimensions independently:
	Positive: Stretch by this factor
	zero: leave unscaled
	Negative: Compress by this factor
	*/
	void setStretch(int xFactor, int yFactor)
	{
		if (xFactor == 0) { xStretch = 1; xCompress = 1; }
		else if (xFactor < 0) { xStretch = 1; xCompress = 1 - xFactor; }
		else if (xFactor > 0) { xStretch = 1 + xFactor; xCompress = 1; }
		if (yFactor == 0) { yStretch = 1; yCompress = 1; }
		else if (yFactor < 0) { yStretch = 1; yCompress = 1 - yFactor; }
		else if (yFactor > 0) { yStretch = 1 + yFactor; yCompress = 1; }
	}

	// Get a floating point zoom level for current x zoom
	float getZoomX()
	{
		int v1 = xStretch; if (v1 < 1) v1 = 1;
		int v2 = xCompress; if (v2 < 1) v2 = 1;
		return (float)v1 / (float)v2;
	}

	// Get a floating point zoom level for current y zoom
	float getZoomY()
	{
		int v1 = yStretch; if (v1 < 1) v1 = 1;
		int v2 = yCompress; if (v2 < 1) v2 = 1;
		return (float)v1 / (float)v2;
	}


private:
	FilterPoints* pNextFilter;
	int xStretch, yStretch, xCompress, yCompress;

	void handleXthenY(DrawingSurface* surface, int xVirtual, int yVirtual, unsigned int& uiColour)
	{
		if (xStretch > 1) // Stretch it!
		{
			xVirtual *= xStretch; // First multiply the point coordinates
			for (int i = 0; i < xStretch; i++)
				handleY(surface, xVirtual + i, yVirtual, uiColour);
		}
		else // Shrinking, so just convert the pixel values and skip some
		{
			xVirtual /= xCompress; // Shrink the coordinate by this amount
			handleY(surface, xVirtual, yVirtual, uiColour);
		}
	}

	void handleY(DrawingSurface* surface, int xVirtual, int yVirtual, unsigned int& uiColour)
	{
		if (yStretch > 1) // Stretch it!
		{
			yVirtual *= yStretch; // First multiply the point coordinates
			for (int i = 0; i < yStretch; i++)
			{
				// If no following filter, or filter permits it, then colour the pixel
				int yTest = yVirtual + i; // Need to be able to pass in by reference...
				if ((pNextFilter == nullptr) || pNextFilter->filter(surface, xVirtual, yTest, uiColour))
					surface->rawSetPixel(xVirtual, yTest, uiColour); // Colour this pixel now
			}
		}
		else
		{
			yVirtual /= yCompress; // Shrink the coordinate by this amount
			if ((pNextFilter == nullptr) || pNextFilter->filter(surface, xVirtual, yVirtual, uiColour))
				surface->rawSetPixel(xVirtual, yVirtual, uiColour); // Colour this pixel now
		}
	}
};







// Filter to mask out all drawing outside of the specified region
class ZoomTranslator : public FilterPoints
{
public:
	ZoomTranslator(int xModifier, int yModifier, FilterPoints* pNextFilter = nullptr)
		: xModifier(xModifier), yModifier(yModifier), pNextFilter(pNextFilter)
	{
	}

	virtual bool filter(DrawingSurface* surface, int& xVirtual, int& yVirtual, unsigned int& uiColour) override
	{
		xVirtual += xModifier;
		yVirtual += yModifier;
		return (pNextFilter == nullptr) || pNextFilter->filter(surface, xVirtual, yVirtual, uiColour);
	}

	// This first convert the position, then apply any following filter if desired.
	virtual int filterConvertVirtualToRealXPosition(int xVirtual) override
	{
		// Apply other filter first if it exists (since we are reversing drawing order)
		if (pNextFilter)
			return pNextFilter->filterConvertVirtualToRealXPosition(xVirtual + xModifier);
		return xVirtual + xModifier;
	}

	// This first convert the position, then apply any following filter if desired.
	virtual int filterConvertVirtualToRealYPosition(int yVirtual) override
	{
		// Apply other filter first if it exists (since we are reversing drawing order)
		if (pNextFilter)
			return pNextFilter->filterConvertVirtualToRealYPosition(yVirtual + yModifier);
		return yVirtual + yModifier;
	}

	// These convert from a clicked location to a virtual pixel position in a surface. First apply any additional filter then modify the result.
	virtual int filterConvertRealToVirtualXPosition(int x) override
	{
		// Apply other filter first if it exists (since we are reversing drawing order)
		if (pNextFilter)
			x = pNextFilter->filterConvertRealToVirtualXPosition(x);
		return x - xModifier;
	}

	// These convert from a clicked location to a virtual pixel position in a surface
	virtual int filterConvertRealToVirtualYPosition(int y) override
	{
		// Apply other filter first if it exists (since we are reversing drawing order)
		if (pNextFilter)
			y = pNextFilter->filterConvertRealToVirtualYPosition(y);
		return y - yModifier;
	}

	// Change the offset used for drawing
	void setOffset(int offsetX, int offsetY)
	{
		xModifier = offsetX;
		yModifier = offsetY;
	}

	int getXOffset() { return xModifier; }
	int getYOffset() { return yModifier; }

	// Change the offset used for drawing
	void changeOffset(int offsetXIncrement, int offsetYIncrement)
	{
		xModifier += offsetXIncrement;
		yModifier += offsetYIncrement;
	}

private:
	int xModifier, yModifier;
	FilterPoints* pNextFilter;
};