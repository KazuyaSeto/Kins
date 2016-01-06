﻿/**************************************************************************//**
	@file		Kin.h
	@brief		ゲーム中表示される菌のクラス　定義ファイル
	@author		K.Seto
	@date		2011-10-25
	@par		[説明]
				菌の座標や状態を管理する。
*//***************************************************************************/

// 菌のクラス、
// 状態 

#ifndef INCLUDE_KIN_H
#define INCLUDE_KIN_H

#include "ofMain.h"
#include <string>

namespace{
	static int id = 0; //<! 菌の固有IDを与える
}

//////////////////////////////////////////////////////////////////////////
// Forward Declaration
class KinManager;
class PairImages;
class Mouse;

/**********************************************************************//**
	@class		Kin
	@brief		画像やサウンドなどを一括で読み込んで素材として保持しているクラス
	@par		[説明]
				以下状態の概要
				STOP showcase内にいるときの状態
				MOVE showcase内にいるときの状態、動き回る
				PICUP クリックされて持ち上げられている時の状態
				SCHALE schale内の状態で動かない
*//***********************************************************************/
class Kin
{
public:
	// 菌の状態、主にこれによって更新、描画の制御がされる
	enum STATE{
		stop,	//<! 止まっている
		move,	//<! 動いている
		picUp,	//<! 摘まれている
		air,	//<! エアーブラシで吹かれている
		schale	//<! シャーレに入っている
	};

	// 菌の斜めへの移動も可能にするために
	// 上下と左右の状態をもつ。
	// 上下の移動状態
	enum MOVE_UP_DOWN{
		up,					//<! 上に移動する状態
		upDownNeutral,		//<! ニュートラル状態
		down				//<! 下に移動する状態
	};
	// 左右の移動状態
	enum MOVE_LEFT_RIGHT{
		right,
		leftRightNeutral,
		left
	};


	/**********************************************************************//**
		@brief		コンストラクタ
		@param[in]	posX			座標X
		@param[in]	posY			座標Y
		@param[in]	width			幅
		@param[in]	height			高さ
		@param[in]	name			菌の名前
		@param[in]	pKinManager		菌マネージャのポインタ
		@return		なし
		@note
		@par		
	*//***********************************************************************/
	Kin(int posX, int posY, int width, int height ,const std::string& name, const KinManager* pKinManager);


	/**********************************************************************//**
		@brief		デストラクタ
		@return		なし
		@note
		@par		
	*//***********************************************************************/
	virtual ~Kin();

	/**********************************************************************//**
		@brief		更新関数
		@return		なし
		@note
		@par		
	*//***********************************************************************/
	void Update();

	/**********************************************************************//**
		@brief		描画関数
		@return		なし
		@note
		@par		
	*//***********************************************************************/
	void Draw();

	/**********************************************************************//**
		@brief		座標を設定する
		@param[in]	int x	X座標
		@param[in]	int y	Y座標
		@return		なし
		@note
		@par		
	*//***********************************************************************/
	void SetPos(int x, int y);


	/**********************************************************************//**
		@brief		X座標を取得する
		@return		X座標
		@note
		@par		
	*//***********************************************************************/
	int PosX() const;


	/**********************************************************************//**
		@brief		Y座標を取得する
		@return		Y座標
		@note
		@par		
	*//***********************************************************************/
	int PosY() const;

	/**********************************************************************//**
		@brief		マウスーオーバーしていれば真を返す
		@retval		true	マウスオーバーしている
		@note		false	マウスオーバーしていない
		@par		
	*//***********************************************************************/
	bool IsMouseOver() const;

	/**********************************************************************//**
		@brief		菌の状態を設定する
		@param[in]	STATE in_state	設定する状態
		@return		なし
		@note
		@par		
	*//***********************************************************************/
	void SetState(STATE in_state);

	// ---- IsState( STATE ) ----
	// 引数のSTATEと菌のSTATEを比較して同じであれば真を返す
	/**********************************************************************//**
		@brief		
		@param[in]	STATE in_state	
		@return		
		@note
		@par		
	*//***********************************************************************/
	bool IsState(STATE in_state);

	/**********************************************************************//**
		@brief		引数の名前と菌の名前を比較して同じであれば真を返す
		@param[in]	const std::string & name	名前	
		@retval		true	名前が同じである
		@retval		false	名前が同じでない
		@note
		@par		
	*//***********************************************************************/
	bool IsName(const std::string& name);
private:
	//////////////////////////////////////////////////////////////////////////
	// Private Function
	/**********************************************************************//**
		@brief		菌の画像を描画する
		@return		なし
		@note
		@par		
	*//***********************************************************************/
	void _ImageDraw();

	/**********************************************************************//**
		@brief		指定フレーム数以上であれば菌の画像を切り替える
		@param[in]	int frame	フレーム数
		@return		なし
		@note
		@par		菌の画像は二枚セットであるので指定したフレーム数に応じて切り替える。
	*//***********************************************************************/
	void _ImageChange(int frame);

	/**********************************************************************//**
		@brief		指定のフレーム数を超えたら指定距離移動する
		@param[in]	int frame		指定のフレーム数
		@param[in]	int distance	指定の距離
		@return		なし
		@note
		@par		
	*//***********************************************************************/
	
	void _Move(int frame, int distance);
	/**********************************************************************//**
		@brief		指定フレーム数超えたら菌の画像を切り替える
		@param[in]	int frame	指定のフレーム数
		@return		なし
		@note
		@par		
	*//***********************************************************************/
	void _ChangeState(int frame);

	/**********************************************************************//**
		@brief		菌の移動の状態を切り替える
		@return		なし
		@note
		@par		
	*//***********************************************************************/
	void _ChangeMovingState();

	//////////////////////////////////////////////////////////////////////////
	// Private Variable
	int m_id;				//<! 菌のID
	int m_posX;				//<! 座標X
	int m_posY;				//<! 座標Y
	int m_width;			//<! 幅
	int m_height;			//<! 高さ
	int m_imageCount;		//<! イメージが変わるまでのフレーム数
	int m_moveCount;		//<! 移動方向が変わるまでのフレーム数
	int m_stateCount;		//<! 菌の状態が変わるまでのフレーム数
	STATE m_state;			//<! 菌の状態
	MOVE_UP_DOWN m_upDownState;			//<! 上下の移動方向の状態
	MOVE_LEFT_RIGHT m_leftRightState;	//<! 左右の移動方向の状態
	const KinManager* m_pKinmanager;	//<! 菌マネージャへのポインタ
	Mouse* m_pMouse;					//<! マウスインスタンスへのポインタ
	PairImages* m_pPairImage;			//<! 画像データのポインタ
	bool m_imageChange;					//<! 菌のイメージを変化させるかどうかのフラグ
	std::string m_name;					//<! 菌の名前
};

#endif // INCLUDE_KIN_H