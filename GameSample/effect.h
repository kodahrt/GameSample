#ifndef EFFECT_H
#define EFFECT_H
// /*========================================================================================
//
//     Effect code [effect.h]											   LEE CHEE HOW
//                                                                         DATE:07/03/2025
//
// ------------------------------------------------------------------------------------------

// =========================================================================================*/
#include <DirectXMath.h>

void Effect_Initialize();
void Effect_Finalize();
void Effect_Update(double elapsed_time);
void Effect_Draw();
void Effect_Create(const DirectX::XMFLOAT2& position, int typeId);


#endif // EFFECT_H
