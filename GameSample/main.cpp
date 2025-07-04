﻿/*========================================================================================


    MAIN CPP												LCH
                                                            DATE:06/06/2005

------------------------------------------------------------------------------------------

=========================================================================================*/
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "game_window.h"
#include "direct3d.h"
#include "shader.h"
#include "sprite.h"
#include "texture.h"
#include "sprite_anim.h"
#include "debug_text.h"
#include <sstream>
#include "system_timer.h"
#include "polygon.h"
#include <cmath>
#include <DirectXMath.h>
#include "key_logger.h"
#include "mouse.h"
#include "game.h"
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")

using namespace DirectX;
/*-------------------------------------------------------------------------------
    メイン
・-------------------------------------------------------------------------------*/

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    (void)hPrevInstance;
    (void)lpCmdLine;

    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hr)) return -1;

    // DPI スケーリング
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    HWND hWnd = GameWindow_Create(hInstance);

    SystemTimer_Initialize();
    Keyboard_Initialize();
	KeyLogger_Initialize();
	Mouse_Initialize(hWnd);

    Direct3D_Initialize(hWnd);
    Shader_Initialize(Direct3D_GetDevice(), Direct3D_GetDeviceContext());
    Texture_Initialize(Direct3D_GetDevice(), Direct3D_GetDeviceContext());
    Sprite_Initialize(Direct3D_GetDevice(), Direct3D_GetDeviceContext());
    SpriteAnim_Initialize();
	Polygon_Initialize(Direct3D_GetDevice(), Direct3D_GetDeviceContext());
    

    hal::DebugText dt(Direct3D_GetDevice(), Direct3D_GetDeviceContext(),
        L"consolab_ascii_512.png", Direct3D_GetBackBufferWidth(), Direct3D_GetBackBufferHeight(),
        0.0f, 0.0f, 
        0, 0, 
        0.0f, 16.0f);

	Game_Initialize();

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    //Frame setting 実行フレイム
    double exec_last_time = SystemTimer_GetTime();
    double fps_last_time = exec_last_time;
    double current_time = 0.0;
    ULONG frame_count = 0;
    double fps = 0.0;


    MSG msg = {};
    float x = 0.0f;  // Initialize x
	float y = 256.0f; // Initialize y (starting verical position)
	float angle = 0.0f; // Initialize angle
    float runman_x = 512.0f;
    float runman_speed = -2.0f; // 每幀移動速度
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            current_time = SystemTimer_GetTime();//システム時刻を取得
            double elapsed_time = current_time - fps_last_time; //fps計測用の経過時間を計算

            if (elapsed_time >= 1.0)//1秒ごとに計測
            {
                fps = frame_count / elapsed_time;
                fps_last_time = current_time;//FPSを測定した時刻を保存
                frame_count = 0;//カウントをクリア
            }

            // 1/60秒ごとに実行
            elapsed_time = current_time - exec_last_time;
            if (elapsed_time >= (1.0 / 60.0)) {
               //if (true) {
                exec_last_time = current_time;//処理した時刻を保存
				KeyLogger_Update(); // Update keyboard state

				Game_Update(elapsed_time); // Update game logic

				SpriteAnim_Update(elapsed_time); // Update sprite animations

                
                // ゲームの描画
                Direct3D_Clear();

                Sprite_Begin();

    //            runman_x += runman_speed; // 向左跑
    //            if (runman_x < -128.0f) runman_x = 1980.0f;

    //            SpriteAnim_Draw(pid05, ms.x, ms.y, 128.0f, 128.0f);

				//angle += elapsed_time; // Update angle based on elapsed time
    //            Sprite_Draw(texid_coco, x, y, 256.0f, 256.0f, 0, 0, 32 , 32, angle);

    //            float ky = sinf(angle) * 50.0f + 64.0f;
				//// angle += 0.05f; // 角度を更新
				//Sprite_Draw(texid_girl, 256.0f, ky, 64.0f, 64.0f);
    //            Polygon_Draw();

				Game_Draw(); // Draw game content

#if defined(DEBUG) || defined(_DEBUG)
                std::stringstream ss;
                ss << "FPS:" << fps << std::endl;
                dt.SetText(ss.str().c_str());

                dt.Draw();
                dt.Clear();
#endif
                Direct3D_Present();

                frame_count++;
            }
        }
    }while (msg.message != WM_QUIT);

	Game_Finalize();
    SpriteAnim_Finalize();
    Sprite_Finalize();
    Texture_Finalize();
    Shader_Finalize();
    Direct3D_Finalize();
	Polygon_Finalize();
	Mouse_Finalize();

    CoUninitialize();
    return (int)msg.wParam;
}


