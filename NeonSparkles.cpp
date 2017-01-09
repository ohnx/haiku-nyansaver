/* 
 * The MIT License (MIT)
 * 
 * Copyright 2016, Adrien Destugues
 * Copyright 2017, Jessica Hamilton
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

#include "NeonSparkles.h"

#include <math.h>
#include <stdlib.h>

#include <Alignment.h>
#include <Bitmap.h>
#include <CheckBox.h>
#include <TextView.h>
#include <LayoutBuilder.h>
#include <Region.h>
#include <Slider.h>
#include <String.h>
#include <Window.h>

#define ARRAY_SIZE(a) \
	(sizeof(a) / sizeof(a[0]))

static const BString kName = "Neon Sparkles";
static const BString kAuthor = "Adrien Destugues, Jessica Hamilton";

extern "C" BScreenSaver*
instantiate_screen_saver(BMessage* msg, image_id id)
{
	return new NeonSparkles(msg, id);
}


NeonSparkles::NeonSparkles(BMessage* archive, image_id id)
	:
	BScreenSaver(archive, id)
{
	fSpots = 22;
	fParticles = 250;
	fSpotSize = 5;
}


NeonSparkles::~NeonSparkles()
{
}


void NeonSparkles::StartConfig(BView* view)
{
	// TODO
}


status_t NeonSparkles::StartSaver(BView* view, bool prev)
{
	srandom(time(NULL));

	BRect rect = view->Bounds();
	fWidth = (int) rect.Width() + 1;
	fHeight = (int) rect.Height() + 1;

	fBackBitmap = new(std::nothrow) BBitmap(rect, B_RGB32, true);
	if (fBackBitmap == NULL)
		return B_ERROR;

	if (fBackBitmap->IsValid()) {
		fBackView = new(std::nothrow) BView(rect, 0, B_FOLLOW_NONE, B_WILL_DRAW);
		if (fBackView == NULL) {
			delete fBackBitmap;
			fBackBitmap = NULL;
			return B_ERROR;
		}

		fBackBitmap->AddChild(fBackView);
		memset(fBackBitmap->Bits(), 0, fBackBitmap->BitsLength());
	} else {
		delete fBackBitmap;
		fBackBitmap = NULL;
		return B_ERROR;
	}

	fLocker.Lock();

	if (fBackBitmap->Lock()) {
		fBackView->SetDrawingMode(B_OP_ALPHA);
		fBackView->SetLineMode(B_ROUND_CAP, B_ROUND_JOIN);
		fBackView->SetFlags(view->Flags() | B_SUBPIXEL_PRECISE);

		fBackView->SetLowColor(make_color(0, 0, 0, 255));
		fBackView->SetViewColor(make_color(0, 0, 0, 255));
		_Restart(fBackView);
		fBackView->Sync();
		fBackBitmap->Unlock();
	}

	fLocker.Unlock();

	return B_OK;
}


rgb_color somecolor() {
  // pick some random good color

	static const rgb_color goodcolor[] = {
		{ 0, 0, 255, 128 },
		{ 0, 255, 255, 128 },
		{ 255, 0, 255, 128 },
		//{ 255, 255, 255, 128 },
		//{ 128, 128, 128, 128 },
		{ 0, 255, 0, 128 },
		{ 255, 0, 0, 128 },
		{ 255, 255, 0, 128 },
#if 0
		{ 0x00, 0x00, 0x00, 56 }, { 0x00, 0x00, 0x00, 56 },
		{ 0x00, 0x00, 0x00, 56 }, { 0x00, 0x00, 0x00, 56 },
		{ 0x00, 0x00, 0x00, 56 }, { 0x00, 0x00, 0x00, 56 },
		{ 0x00, 0x00, 0x00, 56 }, { 0x00, 0x00, 0x00, 56 },
		{ 0x00, 0x00, 0x00, 56 }, { 0x00, 0x00, 0x00, 56 },
		{ 0x00, 0x00, 0x00, 56 }, { 0x00, 0x00, 0x00, 56 },
		{ 0x00, 0x00, 0x00, 56 }, { 0x00, 0x00, 0x00, 56 },
		{ 0x00, 0x00, 0x00, 56 }, { 0x00, 0x00, 0x00, 56 },
		{ 0x00, 0x00, 0x00, 56 }, { 0x00, 0x00, 0x00, 56 },
		{ 0x6B, 0x65, 0x56, 56 }, { 0xA0, 0x9C, 0x84, 56 },
		{ 0x90, 0x8B, 0x7C, 56 }, { 0x79, 0x74, 0x6E, 56 },
		{ 0x75, 0x5D, 0x35, 56 }, { 0x93, 0x73, 0x43, 56 },
		{ 0x9c, 0x6B, 0x4B, 56 }, { 0xAB, 0x82, 0x59, 56 },
		{ 0xAA, 0x8A, 0x61, 56 }, { 0x57, 0x83, 0x75, 56 },
		{ 0xF0, 0xF6, 0xF2, 56 }, { 0xD0, 0xE0, 0xE5, 56 },
		{ 0xD7, 0xE5, 0xEC, 56 }, { 0xD3, 0xDF, 0xEA, 56 },
		{ 0xC2, 0xD7, 0xE7, 56 }, { 0xA5, 0xC6, 0xE3, 56 },
		{ 0xA6, 0xCB, 0xE6, 56 }, { 0xAD, 0xCB, 0xE5, 56 },
		{ 0x77, 0x83, 0x9D, 56 }, { 0xD9, 0xD9, 0xB9, 56 },
		{ 0xA9, 0xA9, 0x78, 56 }, { 0x72, 0x7B, 0x5B, 56 },
		{ 0x6B, 0x7C, 0x4B, 56 }, { 0x54, 0x6D, 0x3E, 56 },
		{ 0x47, 0x47, 0x2E, 56 }, { 0x72, 0x7B, 0x52, 56 },
		{ 0x89, 0x8A, 0x6A, 56 }, { 0x91, 0x92, 0x72, 56 },
		{ 0xAC, 0x62, 0x3B, 56 }, { 0xCB, 0x6A, 0x33, 56 },
		{ 0x9D, 0x5C, 0x30, 56 }, { 0x84, 0x3F, 0x2B, 56 },
		{ 0x65, 0x2c, 0x2a, 56 }, { 0x7e, 0x37, 0x2b, 56 },
		{ 0x40, 0x32, 0x29, 56 }, { 0x47, 0x39, 0x2b, 56 },
		{ 0x3D, 0x26, 0x26, 56 }, { 0x36, 0x2c, 0x26, 56 },
		{ 0x57, 0x39, 0x2c, 56 }, { 0x99, 0x8a, 0x72, 56 },
		{ 0x86, 0x4d, 0x36, 56 }, { 0x54, 0x47, 0x32, 56 }
#endif
	};

  return goodcolor[random() % ARRAY_SIZE(goodcolor)];
}


// OBJECTS ------------------------------------------------------------
class City {
public:
  float x, y;
  BPoint path[0x201];
  int count = 0;
  int other;
  float vx, vy;
  rgb_color myc;

  void Draw(BView* view) {
  	view->SetDrawingMode(B_OP_OVER);
  	path[count++] = BPoint(x, y);
  	int beginning = max_c(0, count - 32);
	// colour underneath
	view->SetPenSize(5.0 / 2.0);
	view->BeginLineArray(32);
	for (int i = beginning; i < count - 1; ++i) {
		view->AddLine(path[i], path[i + 1], myc);
	}
	view->EndLineArray();
	// white on top
	view->SetPenSize(5.0 / 3.0);
	view->BeginLineArray(32);
	for (int i = beginning; i < count - 1; ++i) {
		view->AddLine(path[i], path[i + 1], make_color(255, 255, 255, 255));
	}
	view->EndLineArray();
  }
};

static const int kMaxCities = 64;
City cities[kMaxCities];

void NeonSparkles::_Move(City* city, BView* view) {
    city->vx += (cities[city->other].x-city->x)/view->Bounds().Width();
    city->vy += (cities[city->other].y-city->y)/view->Bounds().Height();

	city->vx *= 0.986;
	city->vy *= 0.979;

	if (random() < RAND_MAX / 100)
		city->other = random() % fSpots;

    city->x+=city->vx / 2;
    city->y+=city->vy / 2;
    if (city->x > 0 && city->x < view->Bounds().Width())
		city->x += city->vx;
    if (city->y > 0 && city->y < view->Bounds().Height())
		city->y += city->vy;
    int delta = fSpotSize * 8;
    if (city->x < -delta || city->x > view->Bounds().Width() + delta) {
		city->vx = -city->vx;
		city->y = random() % (int)view->Bounds().Height();
    }
    if (city->y < -delta || city->y > view->Bounds().Height() + delta) {
		city->vy = -city->vy;
		city->x = random() % (int)view->Bounds().Width();
    }

    city->Draw(view);
}


void NeonSparkles::_Restart(BView* view)
{
	float tinc = 2 * M_PI / fSpots;

	float r = random();
	r /= RAND_MAX;
	r /= 2; // in range 0.0 - 0.5
	r -= 0.25;
	int x = r * (float)fWidth;
	int y = r * (float)fHeight;
	x = (fWidth / 2) + x;
	y = (fHeight / 2) + y;

	for (int t = 0; t < fSpots; t++)
	{
		cities[t].x = x;
		cities[t].y = y;
		cities[t].path[0] = BPoint(x, y);
		cities[t].count = 1;
		cities[t].vx = (1+random() % 11)*sin(tinc*t);
		cities[t].vy = (1+random() % 11)*cos(tinc*t);
		cities[t].myc = somecolor();
		do {
			cities[t].other = random() % fSpots;
		} while(cities[t].other == t);
	}
}


float citydistance(int a, int b) {
  if (a!=b) {
    // calculate and return distance between cities
    float dx = cities[b].x-cities[a].x;
    float dy = cities[b].y-cities[a].y;
    float d = sqrt(dx*dx+dy*dy);
    return d;
  } else {
    return 0.0;
  }
}


void NeonSparkles::Draw(BView* view, int32 frame)
{
	fLocker.Lock();

	if (fBackView) {
		if (fBackBitmap->Lock()) {
			if ((frame & 0x1FF) == 0)
				_Restart(fBackView);

			fBackView->SetDrawingMode(B_OP_ALPHA);
			rgb_color c = fBackView->LowColor();
			fBackView->SetLowColor(make_color(0, 0, 0, 1));
			fBackView->FillRect(view->Bounds(), B_SOLID_LOW);
			fBackView->SetLowColor(c);


			fBackView->SetDrawingMode(B_OP_BLEND);
			fBackView->SetPenSize(1.5);
			fBackView->BeginLineArray(fParticles * 5);
			for (int n = 0; n < fParticles; n++)
			{
				int a = random() % fSpots; // int rand
				int b = 0;
				int tr = 0;
				do
				{
					b = random() % fSpots; // int rand
					tr ++;
				}
				while (tr < 100 && citydistance(a,b) < (fWidth * fHeight) / (10 * (fWidth + fHeight)));

				if (tr >= 100)
					continue;

				int r = random();
				float t = r * M_PI / RAND_MAX; // float rand
				float dx = sin(t)*(cities[b].x-cities[a].x)+cities[a].x;
				float dy = sin(t)*(cities[b].y-cities[a].y)+cities[a].y;

				// noise
				dx += random() * 1.5 / RAND_MAX - 1.5;
				dy += random() * 1.5 / RAND_MAX - 1.5;

				rgb_color c = mix_color(cities[b].myc, cities[a].myc, 128);
				c.alpha = 16;
				rgb_color c1 = rgb_color(c);
				rgb_color c2 = rgb_color(c);
				c1.alpha = 8;
				c2.alpha = 4;
				if (n & 1) {
					c1 = make_color(0, 0, 0, 255);
					c2 = make_color(0, 0, 0, 127);
				}

				fBackView->AddLine(BPoint(dx-2.5, dy-2.5), BPoint(dx, dy), c1);
				fBackView->AddLine(BPoint(dx+2.5, dy-2.5), BPoint(dx, dy), c2);
				fBackView->AddLine(BPoint(dx, dy), BPoint(dx, dy), c);
				fBackView->AddLine(BPoint(dx,dy), BPoint(dx+2.5, dy+2.5), c2);
				fBackView->AddLine(BPoint(dx,dy), BPoint(dx-2.5, dy+2.5), c1);
			}
			fBackView->EndLineArray();

			// move cities
			fBackView->SetPenSize(fSpotSize / 3);
			for (int c = 0; c < fSpots; c++) {
				_Move(&cities[c], fBackView);
			}

			fBackView->Sync();
			fBackBitmap->Unlock();
		}
		
		view->DrawBitmap(fBackBitmap, BPoint(0, 0));
	}

	fLocker.Unlock();
}


void NeonSparkles::MessageReceived(BMessage* msg)
{
	switch (msg->what) {
	default:
		BHandler::MessageReceived(msg);
	}
}


status_t NeonSparkles::SaveState(BMessage* into) const
{
	return B_OK;
}
