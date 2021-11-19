#include "window.h"
#include "context.h"

uint8_t readByte(uint8_t* code, int* ip)
{
	uint8_t b = *((uint8_t*) (code + *ip));
	*ip = (*ip) + 1;
	return b;
}

uint16_t readWord(uint8_t* code, int* ip)
{
	uint16_t b = *((uint16_t*) (code + *ip));
	*ip = (*ip) + 2;
	return b;
}

void debugwrite(char* t);
void debugwritestrhx(char* t, uint32_t hx);

uint16_t readCalcWord(uint8_t* code, int* ip, uint16_t* vars)
{
	uint16_t word = readWord(code, ip);
	if (word >= 0xFF00) {
		if (word <= 0xFF0F) {
			return vars[word - 0xFF00];
		} else {
			debugwrite("BAD WORD SUPPLEID TO readCalcWord");
			while (1);
		}

	} else {
		return word;
	}
}

uint32_t readDword(uint8_t* code, int* ip)
{
	uint32_t b = *((uint32_t*) (code + *ip));
	*ip = (*ip) + 4;
	return b;
}


void scriptParse(uint8_t* code, Window* win)
{
	Context* ctxt = win->context;
	uint16_t vars[16];
	vars[0] = win->width;
	vars[1] = win->height;
	vars[2] = win->x;
	vars[3] = win->y;
	for (int i = 4; i < 16; ++i) {
		vars[i] = 0;
	}

	int ip = 0;
	while (1) {
		uint8_t op = readByte(code, &ip);

		switch (op) {
		case OP_FILL_RECT:
		case OP_DRAW_RECT:
		{
			uint16_t x = readCalcWord(code, &ip, vars);
			uint16_t y = readCalcWord(code, &ip, vars);
			uint16_t w = readCalcWord(code, &ip, vars);
			uint16_t h = readCalcWord(code, &ip, vars);
			uint32_t col = readDword(code, &ip);

			if (op == OP_DRAW_RECT) {
				Context_draw_rect(ctxt, x, y, w, h, col);
			} else {
				Context_fill_rect(ctxt, x, y, w, h, col);
			}
			break;
		}

		case OP_HORZ_LINE:
		case OP_VERT_LINE:
		{
			uint16_t x = readCalcWord(code, &ip, vars);
			uint16_t y = readCalcWord(code, &ip, vars);
			uint16_t l = readWord(code, &ip);
			uint32_t col = readDword(code, &ip);
			if (op == OP_HORZ_LINE) {
				Context_horizontal_line(ctxt, x, y, l, col);
			} else {
				Context_vertical_line(ctxt, x, y, l, col);
			}
			break;
		}

		case OP_DRAW_TEXT:
		{
			uint16_t x = readCalcWord(code, &ip, vars);
			uint16_t y = readCalcWord(code, &ip, vars);
			uint32_t col = readDword(code, &ip);
			uint32_t flags = readDword(code, &ip);
			uint16_t len = readWord(code, &ip);

			Context_draw_text(ctxt, code + ip, x, y, col, flags);
			ip += len;
			break;
		}

		case OP_DRAW_BITMAP:
		{
			uint16_t x = readCalcWord(code, &ip, vars);
			uint16_t y = readCalcWord(code, &ip, vars);
			uint16_t w = readCalcWord(code, &ip, vars);
			uint16_t h = readCalcWord(code, &ip, vars);
			uint32_t len = readDword(code, &ip);

			Context_draw_bitmap(ctxt, code + ip, x, y, w, h);
			ip += len;
			break;
		}

		case OP_VARIABLE:
		case OP_VARIABLE2:
		{
			uint8_t flags = readByte(code, &ip);
			uint16_t value;
			if (op == OP_VARIABLE2) {
				value = readCalcWord(code, &ip, vars);
			} else {
				value = readWord(code, &ip);
			}

			uint8_t var = flags & 0xF;
			op = flags >> 4;

			if (op == OP_VARIABLE_REG) {
				uint8_t reg2 = value & 0xF;
				op = (value >> 4) & 0xF;
				value = vars[reg2];
			}

			if (op == OP_VARIABLE_SET) {
				vars[var] = value;

			} else if (op == OP_VARIABLE_ADD) {
				vars[var] += value;

			} else if (op == OP_VARIABLE_SUB) {
				vars[var] -= value;
			
			} else if (op == OP_VARIABLE_MUL) {
				vars[var] *= value;

			} else if (op == OP_VARIABLE_DIV) {
				if (value == 0) {
					vars[var] = 0;
				} else {
					vars[var] /= value;
				}

			} else if (op == OP_VARIABLE_AND) {
				vars[var] &= value;

			} else if (op == OP_VARIABLE_OR) {
				vars[var] |= value;

			} else if (op == OP_VARIABLE_XOR) {
				vars[var] ^= value;

			} else if (op == OP_VARIABLE_SHL) {
				vars[var] <<= value;

			} else if (op == OP_VARIABLE_SHR) {
				vars[var] >>= value;

			} else if (op == OP_VARIABLE_MOD) {
				if (value == 0) {
					vars[var] = 0;
				} else {
					vars[var] %= value;
				}
			} else if (op == OP_VARIABLE_NOT) {
				vars[var] = !vars[var];

			} else if (op == OP_VARIABLE_NEG) {
				vars[var] = -vars[var];

			} else if (op == OP_VARIABLE_SLIDE) {
				if (var == 0) {
					vars[0] = vars[15];
				} else {
					vars[var] = vars[var - 1];
				}
			}

			break;
		}

		case OP_DEFAULT_VARS:
		{
			vars[0] = ctxt->width;
			vars[1] = ctxt->height;
			vars[2] = ctxt->translate_x;
			vars[3] = ctxt->translate_y;
			break;
		}

		case OP_END:
		{
			return;
		}

		default:
			return;
		}
	}
}