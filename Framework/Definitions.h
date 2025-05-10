#pragma once

#define Delete(x)\
{\
	if (x != nullptr)\
	{\
		delete (x);\
		(x) = nullptr;\
	}\
}
