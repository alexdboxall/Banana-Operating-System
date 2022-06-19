
#include "Userlink.hpp"
#include "NFrame.hpp"

NWindow* userlinkCreateWindow(UserCommandArg::CreateWindow* args)
{
	NWindow* win = new NWindow(args->x, args->y, args->w, args->h, args->name, args->flags);
	return win;
}

uint64_t userlinkAddChild(NFrame* frame, UserCommandArg::AddChild* args)
{
	((NFrame*)args->parent)->addChild(frame);
}

NFrame* userlinkGetDesktop()
{
	extern NDesktopWindow* desktopWindow;
	return desktopWindow;
}

uint64_t userlinkGetCoordinates(NFrame* frame, UserCommandArg::Coordinates* args)
{
	args->absX = frame->getAbsX();
	args->absY = frame->getAbsY();
	args->x = frame->getX();
	args->y = frame->getY();
	args->w = frame->getWidth();
	args->h = frame->getHeight();
	return 0;
}

uint64_t userlinkSetCoordinates(NFrame* frame, UserCommandArg::Coordinates* args)
{
	if (args->setAll || args->setX) frame->setX(args->x);
	if (args->setAll || args->setY) frame->setY(args->y);
	if (args->setAll || args->setW) frame->setWidth(args->w);
	if (args->setAll || args->setH) frame->setHeight(args->h);

	args->absX = frame->getAbsX();
	args->absY = frame->getAbsY();
	args->x = frame->getX();
	args->y = frame->getY();
	args->w = frame->getWidth();
	args->h = frame->getHeight();

	return 0;
}

uint64_t userlinkFullscreen(NFrame* frame, UserCommandArg::Fullscreen* args)
{
	extern Screen screen;

	if (args->set) {
		if (args->state && !frame->isFullscreen()) frame->toggleFullscreen(screen);
		if (!args->state && frame->isFullscreen()) frame->toggleFullscreen(screen);
		
	} else if (args->toggle) {
		frame->toggleFullscreen(screen);
	}

	args->state = frame->isFullscreen();
	return 0;
}

uint64_t userlinkHide(NFrame* frame, UserCommandArg::Hide* args)
{
	extern Screen screen;

	if (args->set) {
		frame->hide(args->state);
	}

	args->state = frame->isHidden();
	args->stateOverall = frame->isHiddenOverall();

	return 0;
}

uint64_t userlinkRaise(NFrame* frame)
{
	frame->raise();
	return 0;
}

uint64_t userlinkInvalidate(NFrame* frame)
{
	frame->tryInvalidate();
	return 0;
}

uint64_t usermodeLinkHandler(UserCommand command, NFrame* frame, void* arg)
{
	switch (command) {
	case UserCommand::CreateWindow:
		return (uint64_t) userlinkCreateWindow((UserCommandArg::CreateWindow*) arg);

	case UserCommand::AddChild:
		return (uint64_t) userlinkAddChild(frame, (UserCommandArg::AddChild*) arg);

	case UserCommand::GetDesktop:
		return (uint64_t) userlinkGetDesktop();

	case UserCommand::GetCoordinates:
		return (uint64_t) userlinkGetCoordinates(frame, (UserCommandArg::Coordinates*) arg);

	case UserCommand::SetCoordinates:
		return (uint64_t) userlinkSetCoordinates(frame, (UserCommandArg::Coordinates*) arg);

	case UserCommand::Fullscreen:
		return (uint64_t) userlinkFullscreen(frame, (UserCommandArg::Fullscreen*) arg);

	case UserCommand::Hide:
		return (uint64_t) userlinkHide(frame, (UserCommandArg::Hide*) arg);

	case UserCommand::Raise:
		return (uint64_t) userlinkRaise(frame);

	case UserCommand::Invalidate:
		return (uint64_t) userlinkInvalidate(frame);

	default:
		return -1;
	}
}