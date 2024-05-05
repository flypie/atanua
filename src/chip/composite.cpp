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
#include "composite.h"
#include "slidingaverage.h"

typedef union
{
	TexPixel RGBA;
	struct
	{
		unsigned char R;
		unsigned char G;
		unsigned char B;
		unsigned char A;
	} S;
} Pixy;

unsigned int Composite::mCompositeNId=0;

Composite::Composite(CType aSize)
{
	mSize=aSize;
	mPins=3;

	mInSyncCount=0;

	if(mSize==i480)
	{
		mxSize=640;
		mySize=525;
	}
	else
	{
		mxSize=768;
		mySize=625;
	}

	set(0,0,mxSize/16,mySize/16,NULL);

	mInputPin=new Pin[mPins];

	int i;
	for(i=0; i<mPins; i++)
	{
		mPin.push_back(&mInputPin[i]);
	}

	mPinDescription=new char* [mPins];

	float ypos=0.2;

	mPinDescription[0]=mystrdup("1");
	mInputPin[0].set(0,ypos,this,"Composite");
	mPinDescription[1]=mystrdup("2");
	mInputPin[1].set(0,2+ypos,this,"Sync");
	mPinDescription[2]=mystrdup("3");
	mInputPin[2].set(0,4+ypos,this,"Clk");


	snprintf(TextureName,32,"composite_base %d",Composite::mCompositeNId++);

	mBaseTexture=load_blank_texture(TextureName,1,mxSize,mySize);


	for(i=0; i<mPins; i++)
	{
		mInputPin[i].mReadOnly=1;
	}
	mScanX=0;
	mScanY=0;
	mInVSync=false;
	mInHSync=false;

	mLastClkState=NETSTATE_INVALID;

	mMaxX=100;
	mMaxY=100;

	mDirty=true;


}

Composite::~Composite()
{
	int i;

	if(mInputPin)
	{
		delete[] mInputPin;
		mInputPin=0;
	}

	for(i=0; i<mPins; i++)
	{
		delete[] mPinDescription[i];
	}
	mPins=0;

	if(mPinDescription)
	{
		delete[] mPinDescription;
		mPinDescription=0;
	}

	if(DeleteTextBitmap("composite_base"))
	{

	}
}


void Composite::render(int aChipId)
{
	unsigned char* RawBitMap;
	GLuint	FramebufferName;

	if(FindTextBitmap(TextureName,&RawBitMap,FramebufferName))
	{
		GLErrorTest();
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		glBindTexture(GL_TEXTURE_2D,mBaseTexture);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

		glEnable(GL_TEXTURE_2D);

		glColor4f(1,1,1,1);
		glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2f(0,0);
		glVertex2f(mX+0.25,mY);

		glTexCoord2f(0,(float)mMaxY/(float)mySize);
		glVertex2f(mX+0.25,mY+mH);

		glTexCoord2f((float)mMaxX/(float)mxSize,0);
		glVertex2f(mX+0.25+mW-0.5,mY);

		glTexCoord2f((float)mMaxX/(float)mxSize,(float)mMaxY/(float)mySize);
		glVertex2f(mX+0.25+mW-0.5,mY+mH);

		glEnd();
		glDisable(GL_TEXTURE_2D);
		GLErrorTest();
	}
}



void Composite::update(float aTick)
{
	unsigned char* RawBitMap;
	GLuint	FramebufferName;
	netstates	ClkState;

	Pixy	PixVal;

	if(mInputPin[DATA_PIN].mNet&&mInputPin[SYNC_PIN].mNet&&mInputPin[CLK_PIN].mNet)
	{
		ClkState=mInputPin[CLK_PIN].mNet->mState;

		if(ClkState!=mLastClkState)
		{
			mLastClkState=ClkState;

			if(ClkState==NETSTATE_LOW)
			{
				netstates SPin=mInputPin[SYNC_PIN].mNet->mState;
				netstates DPin=mInputPin[DATA_PIN].mNet->mState;

				if(
					SPin==NETSTATE_NC||SPin==NETSTATE_INVALID||
					DPin==NETSTATE_NC||DPin==NETSTATE_INVALID)
				{
				}
				else
				{
					if(FindTextBitmap(TextureName,&RawBitMap,FramebufferName))
					{

						if(SPin==NETSTATE_HIGH&&!mInHSync)
						{
							mInHSync=true;
							mScanX=0;
							mScanY++;
							if(mScanY>mMaxY)
							{
								mMaxY=mScanY;
							}
							mInSyncCount=0;

						}
						else if(SPin==NETSTATE_HIGH&&mInHSync)
						{
							mInSyncCount++;
							if(mInSyncCount>35&&!mInVSync)
							{
								mScanX=0;
								mScanY=0;
								mInVSync=true;
							}
							else if(mInSyncCount>35&&mInVSync)
							{
								if(mScanX>=mMaxX)
								{
									mScanX=0;
									mScanY++;
								}
							}
						}
						else if(SPin==NETSTATE_LOW&&mInHSync)
						{
							mInHSync=false;
							if(mInVSync)
							{
								mInVSync=false;
								mScanX=0;
								mScanY++;
							}

							PixVal.RGBA=0xFFFF0000;
						}
						else
						{
							//				mScanX++;
						}

						if(mInVSync)
						{
							PixVal.RGBA=0xFF0000FF;
						}
						else if(mInHSync)
						{
							PixVal.RGBA=0xFF00FF00;
						}
						else
						{
							if(DPin==NETSTATE_HIGH)
							{
								PixVal.RGBA=0xFFFFFFFF;
							}
							else
							{
								PixVal.RGBA=0xFF000000;
							}
						}

						int MMode;

						glGetIntegerv(GL_MATRIX_MODE,&MMode);

						// set rendering destination to FBO
						glBindFramebuffer(GL_FRAMEBUFFER,FramebufferName);
						GLErrorTest();

						glPushMatrix();
						GLErrorTest();

						glClearColor(0.5f,0.5f,0.5f,1.0f);
						GLErrorTest();

						glViewport(0,0,mxSize,mySize);
						GLErrorTest();

						glMatrixMode(GL_PROJECTION);
						GLErrorTest();
						glLoadIdentity();
						GLErrorTest();

						gluOrtho2D(0,mxSize,0,mySize);
						GLErrorTest();

						if(DPin==NETSTATE_HIGH)
						{
							glColor4f(1,1,1,1);
						}
						else
						{
							glColor4f(0,0,0,1);
						}

						glColor4f(PixVal.S.R,PixVal.S.G,PixVal.S.B,PixVal.S.A);

						glShadeModel(GL_SMOOTH);
						GLErrorTest();
						glBegin(GL_TRIANGLE_STRIP);

						glVertex2f(mScanX,mScanY);
						glVertex2f(mScanX+1,mScanY+1);
						glVertex2f(mScanX+1,mScanY);
						glVertex2f(mScanX,mScanY+1);

						glEnd();

						glMatrixMode(MMode);
						GLErrorTest();

						glPopMatrix();
						GLErrorTest();

						// unbind FBO
						glBindFramebuffer(GL_FRAMEBUFFER,0);
						GLErrorTest();
					}

					mScanX++;
					if(mScanX>mMaxX)
					{
						mMaxX=mScanX;
					}
				}
			}
		}
	}
}
