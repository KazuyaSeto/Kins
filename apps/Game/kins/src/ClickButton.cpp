/**************************************************************************//**
	@file		ClickButton.cpp
	@brief		マウスクリックに反応するボタンクラス 実装ファイル	
	@author		K.Seto
	@date		2011-10-24
	@par		[説明]
				ボタンの描画とボタンのマウスクリックを検知する。
				ボタンの状態にはマウスに操作に反応しないロック状態と
				マウス操作に反応するアンロック状態がある。
*//***************************************************************************/

#include "ClickButton.h"
#include "Mouse.h"
#include "Materials.h"
#include "ColorDefinitions.h"

#include <iostream>


namespace {
	// ボタンの長方形の中に入っているどうかを判定
	bool InaRectContaining(	int posX, int posY,
							int rectPosX, int rectPosY,
							int rectWidth, int rectHeight){
		int x = posX - rectPosX;
		int y = posY - rectPosY;
		if( 0 < x && x < rectWidth ){
			if( 0 < y && y < rectHeight){
				return true;
			}
		}
		return false;
	}
}

using namespace std;

// コンストラクタ
ClickButton::ClickButton(	int posX,
							int posY,
							int width,
							int height,
							std::string label):
	m_posX(posX),
	m_posY(posY),
	m_width(width),
	m_height(height),
	m_label(label),
	m_hiddenState(false),
	m_lockedState(false),
	m_rolloverState(false),
	m_clickedState(false)
{
	m_pMouse = Mouse::Instance();
	m_motionTween.SetTarget(0,0,1);
	m_pMaterials = Materials::Instance();
	m_pSSizeFont = m_pMaterials->GetSSizeFont();
}

// デストラクタ
ClickButton::~ClickButton()
{
	// none
}

// 更新関数
void ClickButton::Update(){
	// mvはボタンをスムーズに動かすための座標を返すので毎回updateする。
	if( m_hiddenState == false ){
		m_motionTween.Update();
		if( m_motionTween.IsFinished() ){
			m_lockedState = false;
		}
	}
	// ロックされているときは反応しない
	if( m_lockedState == false ){
		// マウスオーバーの状態変化
		if( InaRectContaining(	m_pMouse->GetPosX(),
								m_pMouse->GetPosY(),
								m_posX+m_motionTween.GetCurrentPosX(),
								m_posY+m_motionTween.GetCurrentPosY(),
								m_width,
								m_height) ){
			m_rolloverState = true;
		}else{
			m_rolloverState = false;
		}
		// クリックされた時の状態変化
		if( m_rolloverState && m_pMouse->IsReleased() ){
			m_clickedState = true;
		}else{
			m_clickedState = false;
		}
	}
}

// 描画関数
void ClickButton::Draw(){
	// 表示状態
	if( m_hiddenState == false ){
		ofPushMatrix();
		ofPushStyle();
		ofSetRectMode(OF_RECTMODE_CORNER);
		int x = 0;
		int y = 0;
		if( IsOpened() ){
			x = m_posX + m_motionTween.GetCurrentPosX();
			y = m_posY + m_motionTween.GetCurrentPosY();
		}else{
			x = m_posX;
			y = m_posY;
		}
		// 通常表示
		if(!m_rolloverState && !m_clickedState){
			ofSetHexColor(GameColor::GRAY);
			ofRect( x, y , m_width, m_height);
		}
		// クリック状態の表示
		if(m_rolloverState && m_clickedState){
			ofSetHexColor(GameColor::PINK);
			ofRect( x,  y, m_width, m_height);
		}
		// マウスオーバーの表示
		if(m_rolloverState && !m_clickedState){
			ofSetHexColor(GameColor::LIGHTGRAY);
			ofRect( x,  y, m_width, m_height);
		}

		ofSetHexColor(GameColor::BLACK);
		m_pSSizeFont->drawString(	m_label,
									x+(m_width-m_pSSizeFont->stringWidth(m_label))*0.5,
									y+(m_height+m_pSSizeFont->stringHeight(m_label))*0.5);
		ofPopStyle();
		ofPopMatrix();
	}
}

// ボタンの座標を設定
void ClickButton::SetPos( int x, int y){
	m_posX = x; m_posY = y;
}

// ボタンのX座標を取得
int ClickButton::GetPosX() const {
	return m_posX;
}

// ボタンのY座標を取得
int ClickButton::GetPosY() const {
	return m_posY;
}

// オープン状態時のボタンの座標を設定
void ClickButton::SetOpenedPos(int x, int y){ m_motionTween.SetTarget(x-m_posX, y-m_posY, 10); }

// ボタンをオープン状態にする
void ClickButton::Open(){
	m_hiddenState = false;
}

// ボタンがオープン状態なら真を返す
bool ClickButton::IsOpened(){
	if(!m_hiddenState && !m_lockedState){
		return true;
	}
	return false;
}

// ボタンをクローズ状態にする
void ClickButton::Close(){
	m_hiddenState = true;
	m_lockedState = true;
	m_motionTween.Reset();
}

// ボタンがクローズ状態なら真を返す
bool ClickButton::IsClosed(){
	if(m_hiddenState && m_lockedState){
		return true;
	}
	return false;
}

// ボタンを非表示状態にする
void ClickButton::Hide(){
	m_hiddenState = true;
}

// ボタンを表示状態にする
void ClickButton::Unhide(){
	m_hiddenState = false;
}

// ボタンをロック状態にする
void ClickButton::lock(){
	m_lockedState = true;
}

// ボタンをアンロック状態する
void ClickButton::Unlock(){
	m_lockedState = false;
}

// ボタンがクリックされたとき、真を返す
bool ClickButton::IsClicked(){
	return m_clickedState;
}
