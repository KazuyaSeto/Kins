﻿/**************************************************************************//**
	@file		Application.h
	@brief		openFramworksアプリケーションクラス　定義ファイル
	@author		K.Seto
	@date		2011-10-29
	@par		[説明]
				ofBaseAppを継承してopenFrameworksのアプリケーションクラスを作成する。
				アプリケーションの初期化、更新、描画を行う。
				またマウスやキー入力のイベントはこのクラスで受け取る。
*//***************************************************************************/

#ifndef _INCLUDE_APPLICATION_H
#define _INCLUDE_APPLICATION_H

#include "ofMain.h"
#include "Sequence/Parent.h"

/////////////////////////////////////////////////
/// Forward Declaration

class Mouse;
class Materials;
class Sequence::Parent;

/**********************************************************************//**
	@class		Application
	@brief		openFrameworksアプリケーションクラス
	@par		[説明]
				ofBaseAppを継承し、各メンバ関数をオーバーロードするのが
				openFrameworksアプリケーションの基本的な作成の仕方である。
*//***********************************************************************/
class Application : public ofBaseApp
{
public:
	/**********************************************************************//**
		@brief		初期化関数
		@return		なし
		@note
		@par		アプリケーションの初期化
					アプリケーションの起動時に呼ばれる。
	*//***********************************************************************/
	void setup();

	/**********************************************************************//**
		@brief		更新関数
		@return		なし
		@note
		@par		アプリケーションの更新、毎フレーム呼ばれる。
	*//***********************************************************************/
	void update();


	/**********************************************************************//**
		@brief		描画関数
		@return		なし
		@note
		@par		アプリケーションの描画、毎フレーム呼ばれる
	*//***********************************************************************/
	void draw();


	/**********************************************************************//**
		@brief		キープレスのイベントハンドラ
		@param[in]	int key		押されたキー
		@return		なし
		@note
		@par		キーボードの押したときに呼ばれるイベントハンドラ
					ofBaseAppのメンバ関数のオーバーロード
	*//***********************************************************************/
	void keyPressed(int key);


	/**********************************************************************//**
		@brief		キーリリースのイベントハンドラ
		@param[in]	int key		離されたキー
		@return		なし
		@note
		@par		キーボードを離したときに呼ばれるイベントハンドラ
					ofBaseAppのメンバ関数のオーバーロード
	*//***********************************************************************/
	void keyReleased(int key);

	/**********************************************************************//**
		@brief		マウスの移動のイベントハンドラ
		@param[in]	int x	マウスのX座標
		@param[in]	int y	マウスのY座標
		@return		なし
		@note
		@par		マウスが移動したときに処理されるイベントハンドラ
					ofBaseAppのメンバ関数のオーバーロード

	*//***********************************************************************/
	void mouseMoved(int x, int y );

	/**********************************************************************//**
		@brief		マウスドラッグ時に呼ばれるイベントハンドラ
		@param[in]	int x		マウスのX座標
		@param[in]	int y		マウスのY座標
		@param[in]	int button	押されているマウスボタン
		@return		なし
		@note
		@par		マウスがドラックされたときに呼ばれるイベントハンドラ
					ofBaseAppのメンバ関数のオーバーロード					
	*//***********************************************************************/
	void mouseDragged(int x, int y, int button);

	/**********************************************************************//**
		@brief		マウスプレス時に呼ばれるイベントハンドラ
		@param[in]	int x			マウスのX座標
		@param[in]	int y			マウスのY座標
		@param[in]	int button		押されたマウスボタン
		@return		なし
		@note
		@par		マウスがプレスされたときに呼ばれるイベントハンドラ
					ofBaseAppのメンバ関数のオーバーロード				
	*//***********************************************************************/
	void mousePressed(int x, int y, int button);

	/**********************************************************************//**
		@brief		マウスリリース時に呼ばれるイベントハンドラ
		@param[in]	int x			マウスのX座標
		@param[in]	int y			マウスのY座標
		@param[in]	int button		離されたマウスボタン
		@return		なし
		@note
		@par		マウスがリリースされたとき呼ばれるイベントハンドラ
					ofBaseAppのメンバ関数のオーバーロード									
	*//***********************************************************************/
	void mouseReleased(int x, int y, int button);

	/**********************************************************************//**
		@brief		ウィンドウリサイズ時に呼ばれるイベントハンドラ
		@param[in]	int w	現在のウィンドウ幅
		@param[in]	int h	現在のウィンドウ高さ
		@return		なし
		@note
		@par		ofBaseAppのメンバ関数のオーバーロード	
	*//***********************************************************************/
	void windowResized(int w, int h);

	/**********************************************************************//**
		@brief		終了処理
		@return		なし
		@note
		@par		ウィンドウが閉じられれて終了されたときに呼ばれるイベントハンドラ
	*//***********************************************************************/
	void exit();

private:
	//////////////////////////////////////////////////////////////////////////
	// Private Variable

	Sequence::Parent* m_pParent;
	Mouse* m_pMouse;
	Materials* m_pMaterials;
};

#endif //_INCLUDE_APPLICATION_H