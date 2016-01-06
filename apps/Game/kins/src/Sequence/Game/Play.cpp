/**************************************************************************//**
	@file		Play.cpp
	@brief		ゲームプレイシーケンスのプレイクラス　実装ファイル	
	@author		K.Seto
	@date		2011-11-6
	@par		[説明]
				
*//***************************************************************************/
#include "Play.h"

#include "../GameParent.h"
#include "Clear.h"

#include "../../ClickButton.h"
#include "../../Materials.h"
#include "../../Mouse.h"
#include "../../Game.h"
#include "../../Misc.h"

#include <iostream>
#include <string>
#include "ofMain.h"

namespace Sequence {
	namespace GameSequence {

		// コンストラクタ
		Play::Play(Difficulty difficulty):
	m_difficulty(difficulty){
		Materials* pMaterials = Materials::Instance();
		m_pMouse = Mouse::Instance();
		pMaterials = Materials::Instance();

		ofSoundPlayer* pTitleBgm = pMaterials->GetSoundTitle();
		ofSoundPlayer* pPlayBgm = pMaterials->GetSoundPlay();
		ofSoundPlayer* pEndingBgm = pMaterials->GetSoundEnd();
		if(!pPlayBgm->getIsPlaying()){
			pPlayBgm->play();
		}

		if( pTitleBgm->getIsPlaying() ){
			pTitleBgm->stop();
		}
		if( pEndingBgm->getIsPlaying() ){
			pEndingBgm->stop();
		}

		// 難易度を指定してゲームクラスを作成
		switch (m_difficulty){
		case DIFFICULTY_EASY:
			m_pGame = new Game("EasyFirst");
			break;
		case DIFFICULTY_NORMAL:
			m_pGame = new Game("NormalFirst");
			break;
		case DIFFICULTY_HARD:
			m_pGame = new Game("HardFirst");
			break;
		default:
			m_pGame = new Game("EasyFirst");
			break;
		}
		m_stage = STAGE_FIRST;

	}

	// デストラクタ
	Play::~Play(){
		Misc::SafeDelete(m_pGame);
	}

	// 更新関数
	Child* Play::Update( Sequence::GameParent* gameParent ){
		Child* pNext = this;

		if(m_stage == STAGE_GAME_OVER){
			pNext = new Clear();
			m_bgm.stop();
		}

		m_pMaterials->Update();
		m_pGame->Update();

		if(m_pGame->IsNextStage()){

			string difficulty;
			string stage;

			// 次のステージへ
			m_stage = _GetNextStage(m_stage);

			difficulty = _GetDifficultyString();
			
			stage = _GetStageString();


			if(m_stage == STAGE_GAME_OVER){

			}else{
				Misc::SafeDelete(m_pGame);
				m_pGame = new Game(difficulty + stage);
			}
		}
		// タイトルに戻る
		if(m_pGame->IsPressedReturnToTitleButton()){
			gameParent->ReturnToTitle();
			m_bgm.stop();
		}
		return pNext;
	}

	// 描画関数
	void Play::Draw(){
		m_pGame->Draw();
	}

	// 難易度のストリングを取得する
	std::string Play::_GetDifficultyString() const
	{
		// 難易度別のstringを作る
		switch (m_difficulty){
		case DIFFICULTY_EASY:
			return "Easy";
			break;
		case DIFFICULTY_NORMAL:
			return "Normal";
			break;
		case DIFFICULTY_HARD:
			return "Hard";
			break;
		default:
			return "Easy";
			break;
		}
	}

	// 今のステージのステージ名を取得する
	std::string Play::_GetStageString() const
	{
		// ステージ別のstringを作る
		switch (m_stage){
		case STAGE_FIRST:
			return "First";
		case STAGE_SECOND:
			return "Second";
		case STAGE_THIRD:
			return "Third";
			break;
		case STAGE_GAME_OVER:
			return "GameOver";
		default:
			return "First";
		}
	}

	// 次のステージを返す
	Play::Stage Play::_GetNextStage(Play::Stage stage) const
	{
		switch (m_stage){
		case STAGE_FIRST:
			return STAGE_SECOND;
		case STAGE_SECOND:
			return STAGE_THIRD;
		case STAGE_THIRD:
			return STAGE_GAME_OVER;
			break;
		case STAGE_GAME_OVER:
			return STAGE_GAME_OVER;
		default:
			return STAGE_GAME_OVER;
		}
	}
	};
};
