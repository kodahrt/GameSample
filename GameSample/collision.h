/*========================================================================================


    Collision code [collision.h]										PYAE SONE THANT
                                                                        DATE:07/03/2025

------------------------------------------------------------------------------------------

=========================================================================================*/
#ifndef COLLISION_H
#define COLLISION_H

#include <DirectXMath.h>

struct Circle
{
    DirectX::XMFLOAT2 center;
    float radius;
};

struct Box
{
    DirectX::XMFLOAT2 center;
    float half_width;
    float half_height;
};

bool Collision_IsOverlapCircle(const Circle& a, const Circle& b);
bool Collision_IsOverlapBox(const Box& a, const Box& b);

#endif // BULLET_H
