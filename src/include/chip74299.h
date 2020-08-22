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
#ifndef CHIP74299_H
#define CHIP74299_H

class Chip74299 : public Chip
{
	Pin mS[2];		// mode select input 
	Pin mOE[2];		// 3-state output enable input (active LOW) 
	Pin mIO[8];		// parallel data input or 3-state parallel output (bus driver) 
	Pin mQ0,mQ7;	// serial output (standard output) 

	Pin mMR;			// asynchronous master reset input (active LOW) 

	Pin mDSR;		// serial data shift-right input 
	Pin mCP;			// clock input (LOW to HIGH, edge-triggered) 
	Pin mDSL;		// serial data shift-left input 

	unsigned char	mReg;
	int mTexture;
	netstates mOldClock;
public:
	Chip74299(); // Ctor

	virtual void render(int aChipId);
	virtual void update(float aTick);
};

#endif
