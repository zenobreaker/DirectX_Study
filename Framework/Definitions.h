#pragma once

#define MAX_KEY_COUNT 256

#define MAX_MODEL_TRANSFORMS 250
#define MAX_MODEL_KEYFRAMES 500

#define INSTANCE_SLOT_NUMBER 9
#define MAX_INSTANCE_COUNT 100

#define MAX_BILLBOARD_COUNT 100000
#define MAX_RENDER_LINE_COUNT 10000

#define MAX_LIGHT_COUNT 20
#define MAX_PROJECTOR_COUNT 5

///////////////////////////////////////////////////////////////////////////////

#define Super __super

#define Check(x) { assert((x) >= 0); }
#define Assert(x, message) { assert((x) && (message)); }

#define Delete(x)\
{\
	if (x != nullptr)\
	{\
		delete (x);\
		(x) = nullptr;\
	}\
}

#define DeleteArray(x)\
{\
	if (x != nullptr)\
	{\
		delete [] (x);\
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

#define CheckTrue(x) { if(x == true) return; }
#define CheckTrueResult(x, y) { if(x == true) return y; }

#define CheckFalse(x) { if(x == false) return;}
#define CheckFalseResult(x, y) { if(x == false) return y;}

#define CheckNull(x) { if(x == nullptr) return; }
#define CheckNullResult(x, y) { if(x == nullptr) return y;}


#define IA_POINTLIST() { CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST); }
#define IA_TRIANGLELIST() { CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); }
#define IA_TRIANGLESTRIP() { CD3D::Get()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); }