
#include <stdio.h>
#include <stdlib.h>

#include <uwsbe/krnllink.h>

int main (int argc, char *argv[])
{
	Window* win = wsbeCreateWindow(40, 40, 80 * 8 + 10, 25 + 16 * 25 + 10, WIN_TOPLEVELWIN | WIN_NORESIZING);
	wsbeSetWindowTitle(win, "Console");

	WsbeScript script = wsbeNewScript();
	wsbeBufferDrawRect(&script, 0, 0, WSBE_MATH_WIDTH_DEREF, WSBE_MATH_HEIGHT_DEREF, WIN_BGCOLOR);
	wsbeBufferDrawRect(&script, 5, 30, 80 * 8, 25 * 16, 0);
	wsbeSetRepaintScript(win, script);

	wsbeAddWindow(wsbeDesktopWindow(), win);
	wsbePaintWindow(win);

	while (1) {
		;
	}

	return 0;
}