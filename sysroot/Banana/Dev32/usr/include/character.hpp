//
//  rectangle.hpp
//  GUI
//
//  Created by Alex Boxall on 22/2/20.
//  Copyright © 2020 Alex Boxall. All rights reserved.
//

#ifndef character_hpp
#define character_hpp

#include "gdo.hpp"
#define MAX_CACHED_FONTS 4

struct FONTDATA1
{
	char chr;
	uint8_t font[14];
	uint8_t size;
};

struct FONTDATA2
{
	char signature[16];
	struct FONTDATA1 FONTD[256];
};

class ICharacter
{
private:
protected:


public:
	int width = 0;
	int height = 0;
	uint8_t* buffer;
	bool valid = false;

	ICharacter();
	~ICharacter();
};

class Font
{
private:
protected:
	bool valid = false;
	bool traditional;

	uint16_t Fonts[256][14];
	uint8_t FontWidths[256];

	struct CachedCharacter
	{
		ICharacter character;
		uint32_t unicode;
		int size;
		uint64_t age = 0;
	};

	CachedCharacter cachedChars[256];

public:
	char filepath[256];

	Font(const char* name);
	Font();
	ICharacter get(uint32_t unicode, int size);
};

extern Font cachedFonts[MAX_CACHED_FONTS];
Font* getFontFromName(const char* name);

class Character: public GDO
{
private:
protected:
	virtual void paint();

	uint32_t bgCol;
	ICharacter ichar;
	bool hidden = false;

public:
	int getWidth();
	int getHeight();
	void show();
	void hide();

	void set(Font* fnt, int x, int y, uint32_t unicode, int size, uint32_t col);
	
	Character(Font* fnt, int x, int y, uint32_t unicode, int size, GDO* parent_, uint32_t colour = 0, const char* debugName = "Unnamed Rectangle");
};


#endif /* rectangle_hpp */
