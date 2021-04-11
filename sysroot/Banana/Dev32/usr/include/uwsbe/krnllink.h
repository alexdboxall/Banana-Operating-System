#ifdef __cplusplus
extern "C" {
#endif

	struct List;
	struct Context;
	typedef struct List List;
	typedef struct Context Context;

#include <stdint.h>
#include <stdbool.h>

#define _USER_WSBE_WANT_KEYBRD_
#include "D:/Users/Alex/Desktop/Banana/kernel/hal/keybrd.hpp"
#undef _USER_WSBE_WANT_KEYBRD_

#include "D:/Users/Alex/Desktop/Banana/drivers/wsbe/wsbe/user.h"

	typedef struct WsbeScript
	{
		uint8_t* data;
		int length;
		int maxLength;

	} WsbeScript;

	Window* wsbeCreateWindow(int x, int y, int w, int h, int flags);
	void wsbeSetWindowTitle(Window* window, const char* title);
	void wsbePaintWindow(Window* window);
	void wsbeAddWindow(Window* parent, Window* child);
	Window* wsbeDesktopWindow();
	void wsbeSetRepaintScript(Window* window, WsbeScript script);

	WsbeScript wsbeNewScript();
	WsbeScript wsbeNewScriptWithSize(int size);
	void wsbeDeleteScript(WsbeScript script);

	int wsbeGetMessage(Window* window, Message* msg);

	uint32_t* wsbeParseTGA(uint8_t* ptr, int size, int* widthOut, int* heightOut, int* sizeOut);
	uint32_t* wsbeParseTGAFromFile(char* filename, int* widthOut, int* heightOut, int* sizeOut);

#define WSBE_MATH_WIDTH_VAR		0
#define WSBE_MATH_HEIGHT_VAR	1
#define WSBE_MATH_X_VAR			2
#define WSBE_MATH_Y_VAR			3

#define WSBE_MATH_WIDTH_DEREF	0xFF00
#define WSBE_MATH_HEIGHT_DEREF	0xFF01
#define WSBE_MATH_X_DEREF		0xFF02
#define WSBE_MATH_Y_DEREF		0xFF03

	void wsbeGetTextBoundingBox(char* text, int flags, int* widthOut, int* heightOut);

	uint16_t wsbeMathVariableDereference(int num);
	void wsbeBufferMath(WsbeScript* script, char oper, int dest, int src);
	void wsbeBufferMathImm(WsbeScript* script, char oper, int dest, uint16_t imm);
	void wsbeBufferMathImmCanDeref(WsbeScript* script, char oper, int dest, uint16_t imm);
	void wsbeBufferDrawRect(WsbeScript* script, int x, int y, int w, int h, uint32_t colour);
	void wsbeBufferFillRect(WsbeScript* script, int x, int y, int w, int h, uint32_t colour);
	void wsbeBufferDrawText(WsbeScript* script, int x, int y, char* text, uint32_t colour);
	void wsbeBufferDrawTextWithFlags(WsbeScript* script, int x, int y, char* text, uint32_t colour, int flags);
	void wsbeBufferDrawBitmap(WsbeScript* script, int x, int y, int w, int h, uint32_t* data, int datalen);
	void wsbeBufferDrawTGAFromFile(WsbeScript* script, char* file, int x, int y);

#ifdef __cplusplus
}
#endif