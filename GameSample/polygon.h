/*==============================================================================

   polygon.h [polygon.h]
														 Author : LCH
														 Date   : 2025/05/15
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef POLYGON_H
#define POLYGON_H

#include <d3d11.h>

void Polygon_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
void Polygon_Finalize(void);
void Polygon_Draw(void);


unsigned int Direct3D_GetBackBufferWidth();
unsigned int Direct3D_GetBackBufferHeight();

#endif // POLYGON_H
