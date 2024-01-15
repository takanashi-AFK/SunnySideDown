#pragma once

const float WINDOW_WIDTH = 1280.0f;
const float WINDOW_HEIGHT = 720.0f;

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}

#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}
