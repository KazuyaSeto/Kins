/**************************************************************************//**
	@file		MotionTween.cpp
	@brief		初期位置から目的位置までの座標を補間するクラス 実装ファイル		
	@author		K.Seto
	@date		2011-10-22
	@par		[説明]
				モーショントゥイーンクラス
				初期位置と目的地と速度（フレーム数）を指定すると
				その経過フレーム数に応じた座標を補完してその値を返す機能を持つ。
				オブジェクトの位置をスムーズに移動させたいときに使う。
*//***************************************************************************/

#include "MotionTween.h"

#include <iostream>

using namespace std;

// コンストラクタ
MotionTween::MotionTween():
	m_posX(0),
	m_posY(0),
	m_targetPosX(0),
	m_targetPosY(0)
{

}

// デストラクタ
MotionTween::~MotionTween()
{
	//none
}

// 更新関数
void MotionTween::Update(){
	// 到着時のフレーム数以下の場合、経過フレーム数を増やす
	if(m_currentFrame < m_targetFrame){
		m_currentFrame++;
	}
}

// 目的地に到着したらしたら真を返す。
bool MotionTween::IsFinished()const{
	if(m_currentFrame == m_targetFrame){
		return true;
	}
	return false;
}

// 目的地をセットする。
void MotionTween::SetTarget(int targetPosX, int targetPosY, int targetFrame){
	// 現在の座標を初期化
	m_posX = 0;
	m_posY = 0;
	// 目的地を設定
	m_targetPosX = targetPosX;
	m_targetPosY = targetPosY;

	// 到着時のフレーム数が０の場合はゼロ除算を避けるために１に設定
	if(targetFrame == 0){
		m_targetFrame = 1;
	}else{
		m_targetFrame = targetFrame;
	}
	// 経過フレーム数を初期化
	m_currentFrame = 0;
}

// 経過したフレームを0に戻す。
void MotionTween::Reset(){
	m_currentFrame = 0;
}

// 現在のX座標を返す。
int MotionTween::GetCurrentPosX()const{
	float tmp = static_cast<float>(m_targetPosX*m_currentFrame)/m_targetFrame;
	return static_cast<int>(tmp);
}

// 現在のY座標を返す。
int MotionTween::GetCurrentPosY()const{
	float tmp = static_cast<float>(m_targetPosY*m_currentFrame)/m_targetFrame;
	return static_cast<int>(tmp);
}
