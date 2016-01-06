/**************************************************************************//**
	@file		Kin.cpp
	@brief		ゲーム中表示される菌のクラス　実装ファイル
	@author		K.Seto
	@date		2011-10-24
	@par		[説明]
				菌の座標や状態を管理する。
*//***************************************************************************/

#include "kin.h"

#include "kinManager.h"
#include "PairImages.h"
#include "Materials.h"
#include "Mouse.h"
#include "ColorDefinitions.h"

#include <cmath>

using namespace std;

namespace {
	// 菌状態別の状態が変化するまでのフレーム数
	static const int STATE_CHANGE_TIME_STOP = 27;
	static const int STATE_CHANGE_TIME_MOVE = 21;

	// 菌状態別の画像が切り替わるまでのフレーム数
	static const int IMAGE_CHANGE_TIME_MOVE = 5;
	static const int IMAGE_CHANGE_TIME_PICUP = 2;

	// メインウィンドウの位置、サイズ
	static const int MAIN_AREA_POSX = 0;
	static const int MAIN_ARIA_POSY = 0;
	static const int MAIN_AREA_WIDTH = 480;
	static const int MAIN_AREA_HEIGHT = 480;

	// シャーレの位置、サイズ
	static const int SCHALE_AREA_POSX = 480;
	static const int SCHALE_AREA_POSY = 320;
	static const int SCHALE_AREA_WIDHT = 160;
	static const int SCHALE_AREA_HEIGHT = 160;
}

// メインウィンドウの中に入っているチェック
bool InTheWindow(int posX, int posY){
	if(MAIN_AREA_POSX < posX && posX < MAIN_AREA_POSX + MAIN_AREA_WIDTH ){
		if( MAIN_ARIA_POSY < posY && posY < MAIN_ARIA_POSY + MAIN_AREA_HEIGHT ){
			return true;
		}
	}
	return false;
}

// シャーレの中に入っているかをチェック
bool InTheSchale(int posX, int posY){
	if(SCHALE_AREA_POSX < posX && posX < SCHALE_AREA_POSX + SCHALE_AREA_WIDHT ){
		if( SCHALE_AREA_POSY < posY && posY < SCHALE_AREA_POSY + SCHALE_AREA_HEIGHT ){
			return true;
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
// Public Function

// コンストラクタ
Kin::Kin(int posX, int posY, int width, int height,const string& name,const KinManager* pKinManager ):
m_posX(posX),m_posY(posY),m_width(width),m_height(height), m_name(name),m_pKinmanager(pKinManager),m_imageChange(true)
{
	m_imageCount = 0;
	m_moveCount = 0;
	m_stateCount = 0;
	m_id = id;
	++id;
	Materials* pMaterials = Materials::Instance();
	m_pPairImage = pMaterials->GetKinPairImageByKey(m_name);
	m_pMouse = Mouse::Instance();
	m_state = move;
	m_upDownState = upDownNeutral;
	m_leftRightState = leftRightNeutral;
}

// デストラクタ
Kin::~Kin()
{
	// none
}

// 更新関数
void Kin::Update()
{
	switch (m_state){
	case stop:
		_ChangeState( STATE_CHANGE_TIME_STOP );
		break;
	case move:
		_Move(1,1);
		_ImageChange( IMAGE_CHANGE_TIME_MOVE );
		_ChangeState( STATE_CHANGE_TIME_MOVE );
		break;
	case picUp:

		_ImageChange( IMAGE_CHANGE_TIME_PICUP );
		SetPos(m_pMouse->GetPosX()-m_width/2, m_pMouse->GetPosY()-m_height/2);
		if(m_pMouse->IsReleased()){
			if(InTheSchale(m_posX, m_posY) && m_pKinmanager->IsTargetName(m_name)){
				SetState(schale);
			}else if(InTheWindow(m_posX, m_posY)){
				SetState(stop);
			}
		}
		break;
	case air:
		_Move(1,10);
		SetState(stop);
		break;
	case schale:
		break;
	default:
		break;
	}
}

// 描画関数
void Kin::Draw()
{
	ofPushMatrix();
	ofPushStyle();

	_ImageDraw();

	ofPopStyle();
	ofPopMatrix();
}

// 座標を設定
void Kin::SetPos(int x, int y){
	m_posX = x;
	m_posY = y;
}

// X座標を取得
int Kin::PosX() const{
	return m_posX;
}

// Y座標を取得
int Kin::PosY() const{
	return m_posY;
}


bool Kin::IsMouseOver() const{
	int x = m_pMouse->GetPosX() - m_posX;
	int y = m_pMouse->GetPosY() - m_posY;
	if(2 < x && x < m_width-2){
		if( 2 < y && y < m_height-2){
			return true;
		}
	}
	return false;
}

void Kin::SetState(STATE in_state){
	m_state = in_state;
}

bool Kin::IsState(STATE in_state){
	if(m_state == in_state){
		return true;
	}
	return false;
}

bool Kin::IsName( const std::string& name )
{
	if( m_name == name){
		return true;
	}
	return false;
}

void Kin::_Move(int frame, int distance){

	if(m_moveCount > frame){
		// 上下移動の処理
		if(m_upDownState == up && m_posY > 0){
			m_posY -= distance;
		}else if(m_upDownState == down && m_posY < MAIN_AREA_POSX + MAIN_AREA_HEIGHT - m_height){
			m_posY += distance;
		}
		// 左右移動の処理
		if(m_leftRightState == left && m_posX > 0 ){
			m_posX -= distance;
		}else if(m_leftRightState == right && m_posX < MAIN_AREA_POSX + MAIN_AREA_HEIGHT - m_width){
			m_posX += distance;
		}
		
		m_moveCount = 0;
	}else {
		++m_moveCount;
	}
}

void Kin::_ChangeState(int frame){
	if(m_stateCount > frame){
		float dice = ofRandom(0.0, 2.0);
		if(dice <= 1){
			m_state = stop;
		}
		if(dice > 1){
			m_state = move;
			_ChangeMovingState();
		}
		m_stateCount = 0;
	}else{
		++m_stateCount;
	}
}

void Kin::_ChangeMovingState(){
	float dice = ofRandom(0.0, 3.0);
	if(dice < 1.0){
		m_upDownState = up;
	}else if(dice < 2.0){
		m_upDownState = upDownNeutral;
	}else{
		m_upDownState = down;
	}
	dice = ofRandom(0.0, 3.0);
	if(dice < 1.0){
		m_leftRightState = right;
	}else if(dice < 2.0){
		m_leftRightState = leftRightNeutral;
	}else{
		m_leftRightState = left;
	}
}

void Kin::_ImageDraw(){
	ofPushStyle();

	if(m_state == schale){ofSetHexColor(GameColor::PINK);}
	if(m_imageChange){
		m_pPairImage->GetFirstImage()->draw(m_posX,m_posY);
	}else {
		m_pPairImage->GetSecondImage()->draw(m_posX,m_posY);
	}
	ofPopStyle();
}

void Kin::_ImageChange(int frame){
	++m_imageCount;
	if(m_imageCount > frame){
		m_imageChange = !m_imageChange;
		m_imageCount = 0;
	}
}

