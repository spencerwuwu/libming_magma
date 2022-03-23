#ifndef ZTRIM_H
#define ZTRIM_H
#include <libztrim.h>
#endif


#ifndef __C2MAN__
#include <string.h>
#include <stdlib.h>
#endif

#include "font_util.h"
#include "blocks/block.h"
#include "libming.h"

typedef struct
{
  char* name;
  SWFFont font;
} Ming_fontListStruct;
static Ming_fontListStruct *Ming_fontList = NULL;

static int Ming_numFonts = 0;

SWFFont
Ming_getFont(const char* name)
{
#ifndef ZTRIM_DONT_INSTR
ztrim_fInstrument(475);
#endif
  int i;

  for ( i = 0; i < Ming_numFonts; ++i )
  {
    if ( strcmp(Ming_fontList[i].name, name) == 0 )
      return Ming_fontList[i].font;
  }

  return NULL;
}


SWFFont
Ming_loadFont(const char* path, const char* name)
{
#ifndef ZTRIM_DONT_INSTR
ztrim_fInstrument(476);
#endif
  SWFFont font = newSWFFont_fromFile(path);

  if ( font == NULL )
    return NULL;

  Ming_fontList = (Ming_fontListStruct*)realloc(Ming_fontList,
			  (Ming_numFonts + 1) * sizeof(*Ming_fontList));

  Ming_fontList[Ming_numFonts].name = strdup(name);
  Ming_fontList[Ming_numFonts].font = font;
  ++Ming_numFonts;

  return font;
}


void
Ming_cleanupFonts()
{
#ifndef ZTRIM_DONT_INSTR
ztrim_fInstrument(477);
#endif
  int i;

  for ( i = 0; i < Ming_numFonts; ++i )
  {
    free(Ming_fontList[i].name);
    destroySWFFont(Ming_fontList[i].font);
  }

  if ( Ming_fontList != NULL )
    free(Ming_fontList);
}
