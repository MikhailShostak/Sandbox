#pragma once

SHADER_BUFFER_BEGIN(GlobalConstants)
SHADER_VARIABLE(float, g_Time)
SHADER_BUFFER_END()

inline SharedReference<GlobalConstants> g_GlobalConstants = CreateShared<GlobalConstants>();
