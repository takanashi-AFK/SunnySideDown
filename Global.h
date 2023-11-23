#pragma once

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}

#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}
