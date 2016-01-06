/**************************************************************************//**
	@file		GameParent.cpp
	@brief		ゲームシーケンスの親クラス	実装ファイル	
	@author		K.Seto
	@date		2011-11-5
	@par		[説明]
				ゲームプレイのシーケンスを管理するシーケンスクラス
*//***************************************************************************/

#include "GameParent.h"
#include "Parent.h"
#include "Title.h"
#include "Game/Loading.h"
#include "Game/Play.h"
#include "Game/Clear.h"
#include "../Misc.h"
#include <iostream>
#include <string>

namespace Sequence {
	// コンストラクタ
	GameParent::GameParent(GameDifficulty gameDifficulty):
m_difficulty(gameDifficulty),returnTitle(false){
	switch (m_difficulty){
	case GAME_EASY:
		m_pChild = new GameSequence::Play(GameSequence::Play::DIFFICULTY_EASY);
		break;
	case GAME_NORMAL:
		m_pChild = new GameSequence::Play(GameSequence::Play::DIFFICULTY_NORMAL);
		break;
	case GAME_HARD:
		m_pChild = new GameSequence::Play(GameSequence::Play::DIFFICULTY_HARD);
		break;
	default:
		m_pChild = new GameSequence::Play(GameSequence::Play::DIFFICULTY_EASY);
		break;
	}
}

// デストラクタ
GameParent::~GameParent(){
	Misc::SafeDelete(m_pChild);
}

// 更新関数
Child* GameParent::Update(Parent* pParent){
	//同じ階層のシーケンス
	Child* pNext = this;
	if(returnTitle){
		pNext = new Title;
	}
	//子シーケンスの制御
	GameSequence::Child* pNextGemeSeuence = m_pChild->Update(this);
	if(m_pChild != pNextGemeSeuence){
		Misc::SafeDelete(m_pChild);
		m_pChild = pNextGemeSeuence;
	}
	return pNext;
}

// 描画関数
void GameParent::Draw(){
	m_pChild->Draw();
}

// タイトルに戻る
void GameParent::ReturnToTitle(){
	returnTitle = true;
}
};
