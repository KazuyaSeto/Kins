/********************ｓ******************************************************//**
	@file		Mouse.cpp
	@brief		openFrameworks用マウスマネージャクラス 実装ファイル		
	@author		K.Seto
	@date		2011-10-22 
	@par		[説明]
				シングルトンクラス
				ヘッダを読み込んでシングルトンクラスのポインタを取得すればマウスの状態を取得できる。
*//***************************************************************************/

#include "Mouse.h"
#include "Misc.h"

#include <iostream>

namespace {
	// openFrameworksのマウスボタンの値
	static int OF_MOUSE_BUTTON_LEFT = 0;
	static int OF_MOUSE_BUTTON_CENTER = 1;
	static int OF_MOUSE_BUTTON_RIGHT = 2;
};

// inctance()内の条件式のために初期化
Mouse* Mouse::m_pInstance = 0;

// マウスマネージャのインスタンスを取得
Mouse* Mouse::Instance(){
	// インスタンスがなければインスタンスを作る
	if(!m_pInstance){
		m_pInstance = new Mouse();
	}
	return m_pInstance;
}

// マウスマネージャーのインスタンスを破棄
void Mouse::Destroy()
{
	// インスタンスがあればメモリを開放
	if(!m_pInstance){
		delete m_pInstance;
		m_pInstance = 0;
	}
}

// マウスの状態を状態を更新する
void Mouse::Update(){
	if(m_buttonState == NONE ){
		; // pass
	} else if(m_buttonState == DRAGGED){
		; //pass
	} else if(m_buttonState == PRESSED){
		// プレスした瞬間にドラッグに
		m_buttonState = DRAGGED;
	}else if(m_buttonState == RELEASED){
		// リリースした次の瞬間に何もしていない状態に
		m_buttonState = NONE;
	}
}

// マウスの座標を設定
void Mouse::SetPos(int x, int y){
	m_posX = x;
	m_posY = y;
}

// マウスボタンの状態をドラッグ状態に設定
void Mouse::SetDraggedPos(int x, int y, int button){
	m_draggedPosX = x;
	m_draggedPosY = y;
	m_posX = x;
	m_posY = y;
	m_buttonState = DRAGGED;
}

// マウスボタンを状態をプレス状態に設定
void Mouse::SetPressedPos(int x, int y, int button){
	m_pressedPosX = x;
	m_pressedPosY = y;
	m_buttonState = PRESSED;
}

// マウスボタンの状態をリリース状態に設定
void Mouse::SetReleasedPos(int x, int y, int button){
	m_releasedPosX = x;
	m_releasedPosY = y;
	m_buttonState = RELEASED;
}

// マウスボタンの状態を設定
void Mouse::SetButton(int button){
	if(button == OF_MOUSE_BUTTON_LEFT){
		m_button = BUTTON_LEFT;
	}
	if(button == OF_MOUSE_BUTTON_CENTER){
		m_button = BUTTON_CENTER;
	}
	if(button == OF_MOUSE_BUTTON_RIGHT){
		m_button = BUTTON_RIGHT;
	}
}

// マウスのX座標を取得
int Mouse::GetPosX() const{
	return m_posX;
}

// マウスのY座標を取得
int Mouse::GetPosY() const{
	return m_posY;
}

// マウスボタンのドラッグのX座標を取得 
int Mouse::GetDraggedPosX() const
{
	return m_draggedPosX;
}

// マウスボタンのドラッグのY座標を取得
int Mouse::GetDraggedPosY() const{
	return m_draggedPosY;
}

// マウスボタンのプレスのX座標を取得
int Mouse::GetPressedPosX() const{
	return m_pressedPosX;
}

// マウスボタンのプレスのY座標を取得
int Mouse::GetPressedPosY() const{
	return m_pressedPosY;
}

// マウスボタンのリリースのX座標を取得
int Mouse::GetReleasedPosX() const{
	return m_releasedPosX;
}

// マウスボタンのリリースのY座標を取得
int Mouse::GetReleasedPosY() const{
	return m_releasedPosY;
}

// マウスボタンの状態がドラッグ状態かどうか？
bool Mouse::IsDragged() const{
	if(m_buttonState == DRAGGED){
		return true;
	}
	return false;
}

// マウスボタンの状態がプレス状態かどうか？
bool Mouse::IsPressed() const{
	if(m_buttonState == PRESSED){
		return true;
	}
	return false;
}

// マウスボタンの状態がリリース状態かどうか？
bool Mouse::IsReleased() const{
	if(m_buttonState == RELEASED){
		return true;
	}
	return false;
}

// マウスボタンの状態が左ボタンかどうか？
bool Mouse::Left() const{
	return (m_button == BUTTON_LEFT) ? true : false;
}

// マウスボタンの状態がセンターボタンかどうか？
bool Mouse::Center() const{
	return (m_button == BUTTON_CENTER) ? true : false;
}

// マウスボタンの状態が右ボタンかどうか？
bool Mouse::Right() const{
	return (m_button == BUTTON_RIGHT) ? true : false;
}

// コンストラクタ
Mouse::Mouse():
m_posX(0),
	m_posY(0),
	m_draggedPosX(0),
	m_draggedPosY(0),
	m_pressedPosX(0),
	m_pressedPosY(0),
	m_releasedPosX(0),
	m_releasedPosY(0),
	m_buttonState(NONE){
}

// デストラクタ
Mouse::~Mouse(){
	delete m_pInstance;
}
