/**************************************************************************//**
	@file		ToolBox.cpp
	@brief		ゲーム内メニューツールボックスクラス 実装ファイル
	@author		K.Seto
	@date		2011-10-22
	@par		[説明]
				ツールボックスクラス
				選択ツールの状態とツールボックスの描画を管理するクラス。
				選択されたツールの状態を管理する。
*//***************************************************************************/


#include "ToolBox.h"
#include "Mouse.h"
#include "Materials.h"
#include "ColorDefinitions.h"

#include <iostream>

// コンストラクタ
ToolBox::ToolBox(int posx, int posy, int width, int height):
m_posX( posx ),
	m_posY( posy ),
	m_width(width),
	m_height(height),
	m_buttonWidth(m_width/3),
	m_buttonHeight(m_height/3)
{
	// 初期化する
	m_pMouse = Mouse::Instance();
	m_pMaterials = Materials::Instance();
	m_imagePinset.loadImage("pinset.png");
	m_imageLoupe.loadImage("loupe.png");
	m_imageAir.loadImage("air.png");
	// 現在のツールを表す。
	m_toolState = TOOL_NONE;
	m_pMsizeFont = m_pMaterials->GetMSizeFont();
}

// デストラクタ
ToolBox::~ToolBox()
{
	// none
}

// 更新関数
void ToolBox::Update(){
	if(m_pMouse->IsPressed()){
		int x = m_posX;
		int y = m_posY;
		// ツールボタンが押されたかをチェックする
		if( _IsIncludedInRect(x, y+m_pMsizeFont->getLineHeight(), m_buttonWidth, m_buttonHeight) ){
			m_toolState = TOOL_PINSET;
		}else if( _IsIncludedInRect( x+m_buttonWidth, y+m_pMsizeFont->getLineHeight(), m_buttonWidth, m_buttonHeight ) ){
			m_toolState = TOOL_LOUPE;
		}else if( _IsIncludedInRect( x+m_buttonWidth*2, y+m_pMsizeFont->getLineHeight(), m_buttonWidth, m_buttonHeight) ){
			m_toolState = TOOL_AIR;
		}
	}
}

// 描画関数
void ToolBox::Draw(){
	ofPushMatrix();
	ofPushStyle();
	ofSetHexColor(GameColor::BLACK);

	m_pMsizeFont->drawString("TOOLBOX", m_posX, m_posY + m_pMsizeFont->getLineHeight()/2 + 5.0);

	ofNoFill();
	ofRect( m_posX, m_posY, m_width, m_pMsizeFont->getLineHeight() );

	// ツールボックスのボタンの位置を設定
	int buttonPosX = m_posX;
	int buttonPosY = m_posY + m_pMsizeFont->getLineHeight();

	// ピンセットボタンの表示
	if( m_toolState == TOOL_PINSET ){
		_SelectedButtonDraw(buttonPosX, buttonPosY, m_imagePinset);
	}else{
		_UnSelectedButtonDraw(buttonPosX, buttonPosY, m_imagePinset);
	}

	// ルーペボタンの表示
	if( m_toolState == TOOL_LOUPE ){
		_SelectedButtonDraw(buttonPosX+m_buttonWidth, buttonPosY, m_imageLoupe);
	}else{
		_UnSelectedButtonDraw(buttonPosX+m_buttonWidth, buttonPosY, m_imageLoupe);
	}

	// エアーブラシボタンの表示
	if( m_toolState == TOOL_AIR ){
		_SelectedButtonDraw(buttonPosX+m_buttonWidth*2, buttonPosY, m_imageAir);
	}else{
		_UnSelectedButtonDraw(buttonPosX+m_buttonWidth*2, buttonPosY, m_imageAir);
	}

	ofFill();
	ofPopStyle();
	ofPopMatrix();
}

// マウスポインタの座標が指定した短形に含まれているかチェックする
bool ToolBox::_IsIncludedInRect(int x, int y, int w, int h){
	x = m_pMouse->GetPosX()-x;
	y = m_pMouse->GetPosY()-y;
	if( 0 < x && x < w ){
		if( 0 < y && y < h){
			return true;
		}
	}
	return false;
}


// 選択されているツールの列挙型を返すを返す
ToolBox::TOOL_STATE ToolBox::GetToolState() const{
	return m_toolState;
}
// 選択されているツールがピンセットならば真を返す
bool ToolBox::IsPinset() const{
	if( m_toolState == TOOL_PINSET ){
		return true;
	}else{
		return false;
	}
}
// 選択されているツールがルーペならば真を返す
bool ToolBox::IsLoupe() const{
	if( m_toolState == TOOL_LOUPE ){
		return true;
	}else{
		return false;
	}
}
// 選択されているツールがエアならば真を返す
bool ToolBox::IsAir() const{
	if( m_toolState == TOOL_AIR ){
		return true;
	}else{
		return false;
	}
}
// ツールが選択されていな場合は真を返す
bool ToolBox::IsNone() const{
	if( m_toolState == TOOL_NONE ){
		return true;
	}else{
		return false;
	}
}
// ツールを選択する。
void ToolBox::SetToolState( TOOL_STATE tool){
	m_toolState = tool;
}

// 非選択のボタンを描画する
void ToolBox::_UnSelectedButtonDraw( int buttonPosX, int buttonPosY, ofImage& image )
{
	ofPushStyle();
	ofSetHexColor(GameColor::WHITE);
	image.draw(buttonPosX, buttonPosY, m_buttonWidth, m_buttonHeight);
	ofSetHexColor(GameColor::BLACK);
	ofRect(buttonPosX, buttonPosY, m_buttonWidth, m_buttonHeight);
	ofNoFill();
	ofPopStyle();
}
// 選択されたボタンを描画する
void ToolBox::_SelectedButtonDraw( int buttonPosX, int buttonPosY, ofImage& image )
{
	ofPushStyle();
	ofFill();
	ofSetHexColor(GameColor::GREEN);
	ofRect(buttonPosX, buttonPosY, m_buttonWidth, m_buttonHeight);
	image.draw(buttonPosX, buttonPosY, m_buttonWidth, m_buttonHeight);
	ofNoFill();
	ofSetHexColor(GameColor::BLACK);
	ofRect(buttonPosX, buttonPosY, m_buttonWidth, m_buttonHeight);
	ofPopStyle();
}


