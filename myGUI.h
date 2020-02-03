#ifndef MY_GUI_H
#define MY_GUI_H


// GLUTヘッダファイルのインクルード
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


// 物体の回転のための変数
extern GLdouble     turn;
extern int     movable;
extern GLdouble   theta;
extern float   velocity;
// カメラの回転のための変数
extern float   camera_yaw; // Ｙ軸を中心とする回転角度
extern float   camera_pitch; // Ｘ軸を中心とする回転角度
extern float   camera_roll; // Ｘ軸を中心とする回転角度
extern float   camera_distance; // 中心からカメラの距離

// マウスのドラッグのための変数
extern int     drag_mouse_l; // 左ボタンがドラッグ中かどうかのフラグ（1:ドラッグ中, 0:非ドラッグ中）
extern int     drag_mouse_m; // 中ボタンがドラッグ中かどうかのフラグ（1:ドラッグ中, 0:非ドラッグ中）
extern int     drag_mouse_r; // 右ボタンがドラッグ中かどうかのフラグ（1:ドラッグ中, 0:非ドラッグ中）
extern int     last_mouse_x;
extern int     last_mouse_y; // 最後に記録されたマウスカーソルの座標

// ウィンドウのサイズ
extern int     win_width;
extern int     win_height;

// glut_my_mouse.c
extern void  motion( int mx, int my );
extern void  mouse( int button, int state, int mx, int my );

// glut_my_key.c
extern void key(unsigned char c, int x, int y);

#endif /* MY_GUI_H */
