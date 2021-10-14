#ifndef _CONFIG_H
#define _CONFIG_H

#include "mcore/maths.h"

void config_init(void);
int config_get_int(const char *file, const char *name);
float config_get_float(const char *file, const char *name);
vec2 config_get_vec2(const char *file, const char *name);
vec3 config_get_vec3(const char *file, const char *name);
vec4 config_get_vec4(const char *file, const char *name);

#endif
