#pragma once

// api
#ifdef ENGINE_IS_EXPORT
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif