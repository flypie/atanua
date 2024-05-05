/*
Atanua Real-Time Logic Simulator
Copyright (c) 2008-2014 Jari Komppa

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/
#ifndef Composite_H
#define Composite_H

class SlidingAverage;



class Composite : public Chip
{
public:

    typedef enum
    {
        i480,
        i576
    } CType;

private:

    CType mSize;        // Grid size (n x n)

    int mPins;
    Pin *mInputPin;   // Chip's input pins
	char **mPinDescription;
#define DATA_PIN	0
#define SYNC_PIN	1
#define CLK_PIN		2


    int mBaseTexture; // Chip's base texture
	int mLitTexture;  // Chip's lit texture

    int mxSize;        // Grid size (n x n)
    int mySize;        // Grid size (n x n)


    int mInSyncCount;

    int mScanX;
    int mScanY;

    bool mInVSync;
    bool mInHSync;

    netstates mLastClkState;

    int mMaxX;
    int mMaxY;

    char    TextureName[32];

    static unsigned int mCompositeNId;

public:
    Composite(CType atype);
	virtual ~Composite();

    virtual void render(int aChipId);
    virtual void update(float aTick);
	virtual int isUselessInBox() { return 1; }
};

#endif
