
#include "Window.hpp"

#include <string.h>

inline __attribute__((always_inline)) uint64_t Window::performSystemCall(UserCommand cmd, void* arg)
{
	return SystemCall((size_t) SystemCallNumber::WSBE, (size_t) cmd, (size_t) krnlFrame, (size_t) arg);
}

Window::Window(int x, int y, int w, int h, const char* title, int flags)
{
	UserCommandArg::CreateWindow args;
	args.flags = flags;
	args.x = x;
	args.y = y;
	args.w = w;
	args.h = h;
	strcpy(args.name, title);

	krnlFrame = (void*) performSystemCall(UserCommand::CreateWindow, (void*) &args);
}

void Window::refreshCoordinates()
{
	UserCommandArg::Coordinates args;
	performSystemCall(UserCommand::GetCoordinates, (void*) &args);

	mostRecentAbsX = args.absX;
	mostRecentAbsY = args.absY;
	mostRecentX = args.x;
	mostRecentY = args.y;
	mostRecentW = args.w;
	mostRecentH = args.h;
}

void Window::setCoordinates(UserCommandArg::Coordinates args)
{
	performSystemCall(UserCommand::SetCoordinates, (void*) &args);

	mostRecentAbsX = args.absX;
	mostRecentAbsY = args.absY;
	mostRecentX = args.x;
	mostRecentY = args.y;
	mostRecentW = args.w;
	mostRecentH = args.h;
}

void Window::setPosition(int x, int y)
{
	UserCommandArg::Coordinates args;
	memset((void*) &args, 0, sizeof(args));
	args.x = x;
	args.y = y;
	args.setX = true;
	args.setY = true;
	setCoordinates(args);
}

void Window::setX(int x)
{
	UserCommandArg::Coordinates args;
	memset((void*) &args, 0, sizeof(args));
	args.x = x;
	args.setX = true;
	setCoordinates(args);
}

void Window::setY(int y)
{
	UserCommandArg::Coordinates args;
	memset((void*) &args, 0, sizeof(args));
	args.y = y;
	args.setY = true;
	setCoordinates(args);
}

void Window::setSize(int w, int h)
{
	UserCommandArg::Coordinates args;
	memset((void*) &args, 0, sizeof(args));
	args.w = w;
	args.h = h;
	args.setW = true;
	args.setH = true;
	setCoordinates(args);
}

void Window::setWidth(int w)
{
	UserCommandArg::Coordinates args;
	memset((void*) &args, 0, sizeof(args));
	args.w = w;
	args.setW = true;
	setCoordinates(args);
}

void Window::setHeight(int h)
{
	UserCommandArg::Coordinates args;
	memset((void*) &args, 0, sizeof(args));
	args.h = h;
	args.setH = true;
	setCoordinates(args);
}

int Window::getX(bool update)
{
	if (update) refreshCoordinates();
	return mostRecentX;
}

int Window::getY(bool update)
{
	if (update) refreshCoordinates();
	return mostRecentY;
}

int Window::getWidth(bool update)
{
	if (update) refreshCoordinates();
	return mostRecentW;
}

int Window::getHeight(bool update)
{
	if (update) refreshCoordinates();
	return mostRecentH;
}

void Window::invalidate()
{
	performSystemCall(UserCommand::Invalidate, nullptr);
}

void Window::setParentAsDesktop()
{
	UserCommandArg::AddChild args;
	args.parent = (void*) performSystemCall(UserCommand::GetDesktop, nullptr);
	performSystemCall(UserCommand::AddChild, &args);
}

void Window::setParent(Window* window)
{
	UserCommandArg::AddChild args;
	args.parent = window->krnlFrame;
	performSystemCall(UserCommand::AddChild, &args);
}

void Window::setFullscreen(bool state)
{
	UserCommandArg::Fullscreen args;
	args.set = true;
	args.state = state;
	args.toggle = false;
	performSystemCall(UserCommand::Fullscreen, &args);
}

void Window::toggleFullscreen()
{
	UserCommandArg::Fullscreen args;
	args.set = false;
	args.state = false;
	args.toggle = true;
	performSystemCall(UserCommand::Fullscreen, &args);
}

bool Window::isFullscreen()
{
	UserCommandArg::Fullscreen args;
	args.set = false;
	args.toggle = false;
	performSystemCall(UserCommand::Fullscreen, &args);
	return args.state;
}

void Window::hide(bool state)
{
	UserCommandArg::Hide args;
	args.set = true;
	args.state = state;
	performSystemCall(UserCommand::Hide, &args);
}

void Window::unhide()
{
	hide(false);
}

bool Window::isHidden()
{
	UserCommandArg::Hide args;
	args.set = false;
	performSystemCall(UserCommand::Hide, &args);
	return args.state;
}

void Window::raise()
{
	performSystemCall(UserCommand::Raise, nullptr);
}