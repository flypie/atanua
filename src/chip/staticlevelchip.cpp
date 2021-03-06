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
#include "atanua.h"
#include "staticlevelchip.h"

StaticLevelChip::StaticLevelChip(int aLevel)
{
    mLevel = aLevel;
    set(0,0,2,2,NULL);
    mPin.push_back(&mOutputPin);
    if (aLevel)
    {
        mOutputPin.set(0.75, 1.5, this, "Output");
        mTexture = load_file_texture("data/vcc.png");
    }
    else
    {
        mOutputPin.set(0.75, 0, this, "Output");
        mTexture = load_file_texture("data/gnd.png");
    }
}

void StaticLevelChip::render(int aChipId)
{
	if (gBlackBackground)
	    drawtexturedrect(mTexture,mX,mY,mW,mH,0xffffffff);
	else
		drawtexturedrect(mTexture,mX,mY,mW,mH,0xff000000);
}

void StaticLevelChip::update(float aTick) 
{
    if (mLevel)
        mOutputPin.setState(PINSTATE_WRITE_HIGH);
    else
        mOutputPin.setState(PINSTATE_WRITE_LOW);
}    
