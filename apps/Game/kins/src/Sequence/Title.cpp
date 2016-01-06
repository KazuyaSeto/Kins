/**************************************************************************//**
	@file		Title.cpp
	@brief		タイトルのシーケンスクラス		実装ファイル	
	@author		K.Seto
	@date		2011-11-5
	@par		[説明]
				ゲームのタイトル画面のシーケンス
				格難易度のゲームプレイやゲームないの説明書のシーケンスに移動するボタンを表示する。			
*//***************************************************************************/
#include "Title.h"

#include "Parent.h"
#include "Child.h"
#include "GameParent.h"
#include "HowTo.h"
#include "../Mouse.h"
#include "../Materials.h"
#include "../ClickButton.h"
#include "../Misc.h"

#include <iostream>

namespace {
	// ボタン配置に関する定数
	static const int BUTTON_WIDTH = 78;
	static const int BUTTON_HEIGHT = 28;
	static const int BUTTON_HEIGHT_INTERVAL = BUTTON_HEIGHT + 2;
	static const int BUTTON_WIDTH_INTERVAL = BUTTON_WIDTH + 2;
	static const int BUTTON_POSX = 20;
	static const int BUTTON_POSY = 360;

	static const char* BUTTON_STRING_GAME = "Game";
	static const char* BUTTON_STRING_EAZY = "Eazy";
	static const char* BUTTON_STRING_NORMAL = "Normal";
	static const char* BUTTON_STRING_HARD = "Hard";
	static const char* BUTTON_STRING_HOWTO = "HowTo";
}

using namespace std;

namespace Sequence {
	/////////////////////////////////////////////////
	/// Public Function
	// コンストラクタ
	Title::Title(){
		// マテリアルクラスからデータを引っ張ってきて初期化
		m_pMouse = Mouse::Instance();
		m_pMaterials = Materials::Instance();

		_PlayBgm();

		m_titleImage.loadImage("titleImage.png");

		_InitializeButtons();
	}

	// デストラクタ
	Title::~Title(){
		_FinalizeButtons();

	}

	// 更新関数
	Child* Title::Update(Parent* pParent){

		// 素材データの更新
		m_pMaterials->Update();

		_UpdateButtons();

		// 次のシーケンスポインタを返す
		return _GetNextSequence();
	}

	// 描画関数
	void Title::Draw(){
		ofPushMatrix();
		ofPushStyle();

		// 背景画像を表示
		m_titleImage.draw(0,0);

		_DrawButtons();

		ofPopStyle();
		ofPopMatrix();
	}

	/////////////////////////////////////////////////
	/// Private Function

	// BGMを再生する
	void Title::_PlayBgm()
	{
		// BGMの再生、ほかのシーケンスのBGMはストップ
		ofSoundPlayer* pTitleBgm = m_pMaterials->GetSoundTitle();
		ofSoundPlayer* pPlayBgm = m_pMaterials->GetSoundPlay();
		ofSoundPlayer* pEndingBgm = m_pMaterials->GetSoundEnd();

		if(!pTitleBgm->getIsPlaying()){
			pTitleBgm->play();
		}
		if( pPlayBgm->getIsPlaying() ){
			pPlayBgm->stop();
		}
		if( pEndingBgm->getIsPlaying() ){
			pEndingBgm->stop();
		}
	}
	
	// タイトルメニューに表示されtるボタンを初期化する
	void Title::_InitializeButtons()
	{
		// ボタンの初期化
		m_pClickButtonGame = new ClickButton(	BUTTON_POSX,
												BUTTON_POSY,
												BUTTON_WIDTH,
												BUTTON_HEIGHT,
												BUTTON_STRING_GAME);
		// ゲームボタンの座標を取得
		const int clickButtonGamePosX = m_pClickButtonGame->GetPosX();
		const int clickButtonGamePosY = m_pClickButtonGame->GetPosY();
		// 
		m_pClickButtonEasy = new ClickButton(	clickButtonGamePosX,
												clickButtonGamePosY,
												BUTTON_WIDTH,
												BUTTON_HEIGHT,
												BUTTON_STRING_EAZY);
		m_pClickButtonEasy->Close();
		m_pClickButtonEasy->SetOpenedPos(clickButtonGamePosX+BUTTON_WIDTH_INTERVAL, clickButtonGamePosY);

		m_pClickButtonNormal = new ClickButton(	clickButtonGamePosX,
												clickButtonGamePosY,
												BUTTON_WIDTH,
												BUTTON_HEIGHT,
												BUTTON_STRING_NORMAL);
		m_pClickButtonNormal->Close();
		m_pClickButtonNormal->SetOpenedPos(clickButtonGamePosX+BUTTON_WIDTH_INTERVAL*2, clickButtonGamePosY);

		m_pClickButtonHard = new ClickButton(	clickButtonGamePosX,
												clickButtonGamePosY,
												BUTTON_WIDTH,
												BUTTON_HEIGHT,
												BUTTON_STRING_HARD);
		m_pClickButtonHard->Close();

		m_pClickButtonHard->SetOpenedPos(clickButtonGamePosX+BUTTON_WIDTH_INTERVAL*3,clickButtonGamePosY);
		m_pClickButtonHowto = new ClickButton(	BUTTON_POSX,
												BUTTON_POSY + BUTTON_HEIGHT_INTERVAL,
												BUTTON_WIDTH,
												BUTTON_HEIGHT,
												BUTTON_STRING_HOWTO);
	}

	// 確保したボタンのインスタンスを開放
	void Title::_FinalizeButtons()
	{
		using namespace Misc;
		SafeDelete(m_pClickButtonGame);
		SafeDelete(m_pClickButtonEasy);
		SafeDelete(m_pClickButtonNormal);
		SafeDelete(m_pClickButtonHard);
		SafeDelete(m_pClickButtonHowto);
	}

	// ボタンの更新を行う
	void Title::_UpdateButtons()
	{
		// ボタンの更新
		m_pClickButtonGame->Update();
		if(m_pClickButtonGame->IsClicked()){
			m_pClickButtonGame->lock();

			m_pClickButtonEasy->Open();
			m_pClickButtonNormal->Open();
			m_pClickButtonHard->Open();
		}
		m_pClickButtonEasy->Update();
		m_pClickButtonNormal->Update();
		m_pClickButtonHard->Update();
		m_pClickButtonHowto->Update();
	}

	// ボタンの描画関数
	void Title::_DrawButtons()
	{
		// ボタンの表示
		m_pClickButtonGame->Draw();
		m_pClickButtonEasy->Draw();
		m_pClickButtonNormal->Draw();
		m_pClickButtonHard->Draw();
		m_pClickButtonHowto->Draw();
	}

	// 次のシーケンスのポインタを取得する
	Child* Title::_GetNextSequence()
	{
		// シーケンスの移動処理
		if( m_pClickButtonEasy->IsClicked() ){
			return  new GameParent(GameParent::GAME_EASY);
		}else if( m_pClickButtonNormal->IsClicked() ){
			return new GameParent(GameParent::GAME_NORMAL);
		}else if( m_pClickButtonHard->IsClicked() ){
			return new GameParent(GameParent::GAME_HARD);
		}else if( m_pClickButtonHowto->IsClicked() ){
			return  new HowTo;
		}
		return this;
	}

};

