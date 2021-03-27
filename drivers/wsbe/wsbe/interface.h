#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "window.h"
#include "desktop.h"
#include "context.h"
#include "user.h"

#ifdef __cplusplus
extern "C" {
#endif

	void interfaceSetup();

	Desktop* getDesktop();
	Window* createWindow(int x, int y, int w, int h, int flags);
	void addWindow(Window* parent, Window* child);
	void raiseWindow(Window* window);
	void setWindowTitle(Window* window, char* title);
	Context* getWindowContext(Window* window);
	
	void dispatchMessage(Window* window, Message msg);
	int getMessage(Window* window, Message* msg);
	int guiDefaultProc(Window* window, Message msg);
	Message blankMessage();

#ifdef __cplusplus
}
#endif

#endif