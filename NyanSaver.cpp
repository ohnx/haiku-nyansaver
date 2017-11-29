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
	if (frame == 0) { 
		view->SetLowColor(0, 0, 0); 
		view->FillRect(view->Bounds(), B_SOLID_LOW); 
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
