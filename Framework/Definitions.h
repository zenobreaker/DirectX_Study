#pragma once

#define Check(x) { assert((x) >= 0); }
#define Assert(x, message) { assert((x)>= 0 && (message)); }

#define Delete(x)\
{\
	if (x != nullptr)\
	{\
		delete (x);\
		(x) = nullptr;\
	}\
}


#define Release(x)\
{\
	if (x != nullptr)\
	{\
		x->Release();\
		(x) = nullptr;\
	}\
}