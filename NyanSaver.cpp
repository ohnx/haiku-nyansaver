/* 
 * The MIT License (MIT)
 * 
 * Copyright 2016, Adrien Destugues
 * Copyright 2017, Jessica Hamilton
 * Copyright 2017, Mason
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "NyanSaver.h"

static const BString kName = "NyanSaver";
static const BString kAuthor = "Adrien Destugues, Jessica Hamilton, Mason X";
static rgb_color rainbow[] = {{255,18,17,0},{255,168,11,0},{255,255,0,0},{74,255,12,0},{15,174,255,0},{118,68,255,0}};
static rgb_color background = {15, 77, 143};
static int offset = 0;


extern "C" BScreenSaver*
instantiate_screen_saver(BMessage* msg, image_id id)
{
	return new NyanSaver(msg, id);
}


NyanSaver::NyanSaver(BMessage* archive, image_id id)
	:
	BScreenSaver(archive, id)
{
}


NyanSaver::~NyanSaver()
{
}


void NyanSaver::StartConfig(BView* view)
{
}


status_t NyanSaver::StartSaver(BView* view, bool prev)
{
	return B_OK;
}

void NyanSaver::Draw(BView* view, int32 frame)
{
	int i, j;
	BRect *myRect = new BRect();
	int SCALE = 8;
	int sWidth = (int)(view->Bounds().Width());
	int sHeight = (int)(view->Bounds().Height());
	int xtopleft = sWidth/2 - 35*(SCALE/2), ytopleft = sHeight/2 - 20*(SCALE/2);

	if (frame == 0) {
		/* background */
		view->SetLowColor(background);
		view->FillRect(view->Bounds(), B_SOLID_LOW);

		/* nyan head */
		for (i = 10; i < 35; i++) { // x
			for (j = 0; j < 20; j++) { // y
				myRect->Set(xtopleft+i*SCALE, ytopleft+j*SCALE, xtopleft+i*SCALE + SCALE, ytopleft+j*SCALE + SCALE);
				view->SetLowColor(nyancat[j*35+i]);
				view->FillRect(*myRect, B_SOLID_LOW);
			}
		}
	}

	if (!(frame % 30)) {
		/* clear old */
		myRect->Set(0, ytopleft, xtopleft+10*SCALE, ytopleft + SCALE*20);
		view->SetLowColor(background);
		view->FillRect(*myRect, B_SOLID_LOW);

        /* rainbow */
		for (i = 0; i < xtopleft+(7*SCALE); i++) { // x
			for (j = 0; j < 6; j++) { // y
				myRect->Set(i, ytopleft+j*SCALE*3+offset*SCALE, i + SCALE, ytopleft+j*SCALE*3+offset*SCALE + SCALE*3);
				view->SetLowColor(rainbow[j]);
				view->FillRect(*myRect, B_SOLID_LOW);
			}
			if (i % (9*SCALE) == 0) {
				offset = !offset;
			}
		}

		if (offset) {
			// nyan butt
			for (i = 0; i < 10; i++) { // x
				for (j = 0; j < 20; j++) { // y
					if (!(background.red == nyanbutt1[j*10+i].red && background.green == nyanbutt1[j*10+i].green && background.blue == nyanbutt1[j*10+i].blue)) {
						myRect->Set(xtopleft+i*SCALE, ytopleft+j*SCALE, xtopleft+i*SCALE + SCALE, ytopleft+j*SCALE + SCALE);
						view->SetLowColor(nyanbutt1[j*10+i]);
						view->FillRect(*myRect, B_SOLID_LOW);
					}
				}
			}
		} else {
			/* nyan butt other version */
			for (i = 0; i < 10; i++) { // x
				for (j = 0; j < 20; j++) { // y
					if (!(background.red == nyancat[j*35+i].red && background.green == nyancat[j*35+i].green && background.blue == nyancat[j*35+i].blue)) {
						myRect->Set(xtopleft+i*SCALE, ytopleft+j*SCALE, xtopleft+i*SCALE + SCALE, ytopleft+j*SCALE + SCALE);
						view->SetLowColor(nyancat[j*35+i]);
						view->FillRect(*myRect, B_SOLID_LOW);
					}
				}
			}
		}
	}
}


void NyanSaver::MessageReceived(BMessage* msg)
{
	switch (msg->what) {
	default:
		BHandler::MessageReceived(msg);
	}
}


status_t NyanSaver::SaveState(BMessage* into) const
{
	return B_OK;
}
