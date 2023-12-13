#pragma once
#include "ExampleDragableObjects.h"
#include "ImagePixelMapping.h"

class MappableMaskImage :
    public MappableImageObject
{
public:
    MappableMaskImage(ImagePixelMapping* pMapping, int xStart, int yStart, BaseEngine* pEngine, std::string strURL, bool useTopLeftFor00 = true, bool bVisible = true):
        MappableImageObject(pMapping, xStart, yStart, pEngine, strURL, useTopLeftFor00, bVisible)
    {

    }
    void virtDraw() {
        if (isVisible())
        {
            // modify the function of "renderImageApplyingMapping" in SimpleImage.cpp
            // do not draw black background of the image
            int xStart = m_iCurrentScreenX + m_iStartDrawPosX;
            int yStart = m_iCurrentScreenY + m_iStartDrawPosY;
            int xMinOffset = 0;
            int xMaxOffset = m_iDrawWidth;
            int yMinOffset = 0;
            int yMaxOffset = m_iDrawHeight;

            int iLHS = getEngine()->convertClickedToVirtualPixelXPosition(0);
            int iTop = getEngine()->convertClickedToVirtualPixelYPosition(0);
            int iRHS = getEngine()->convertClickedToVirtualPixelXPosition(getEngine()->getWindowWidth());
            int iBottom = getEngine()->convertClickedToVirtualPixelYPosition(getEngine()->getWindowHeight());
            double dx, dy;
            int iPixel;
            //std::cout << "Draw from " << xMinOffset << " to " << xMaxOffset << std::endl;
            for (int iYOffset = yMinOffset; iYOffset < yMaxOffset; ++iYOffset)
            {
                for (int iXOffset = xMinOffset; iXOffset < xMaxOffset; ++iXOffset)
                {
                    dx = iXOffset;
                    dy = iYOffset;
                    if (m_pMapping->mapCoordinates(dx, dy, image))
                    { // It mapcoordinates returns false, do not draw the pixel
                        int iColour = 0xffffff & image.getTheData()->getRawPixelColour((int)(dx + 0.5), (int)(dy + 0.5));
                        if (m_pMapping->changePixelColour(m_iCurrentScreenX + m_iStartDrawPosX + iXOffset, m_iCurrentScreenY + m_iStartDrawPosY + iYOffset, iColour, getEngine()->getForegroundSurface()))
                        { // If changePixelColour returns false it means we should not draw the pixel
                            // do not draw the black colour
                            if (iColour == 0x000000) continue;
                            getEngine()->getForegroundSurface()->setPixel(m_iCurrentScreenX + m_iStartDrawPosX + iXOffset, m_iCurrentScreenY + m_iStartDrawPosY + iYOffset, iColour);
                        }
                    }
                }
            }
        }
    }
};

