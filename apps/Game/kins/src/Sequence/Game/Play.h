/**************************************************************************//**
	@file		Play.h
	@brief		ゲームプレイシーケンスのプレイクラス　定義ファイル
	@author		K.Seto
	@date		2011-11-6
	@par		[説明]

*//***************************************************************************/

#ifndef INCLUDE_SEQUENCE_GAME_PLAY_H
#define INCLUDE_SEQUENCE_GAME_PLAY_H

#include "Child.h"
#include "ofMain.h"

/////////////////////////////////////////////////
/// Forward Declaration
class Game;
class ClickButton;
class Mouse;
class Materials;
class Clear;

namespace Sequence{
	class GameParent;
	namespace GameSequence{
		/**********************************************************************//**
			@class		Play
			@brief		ゲームプレイクラス
			@par		[説明]
		*//***********************************************************************/
		class Play : public Child{
		public:
			// 難易度の状態
			enum Difficulty{
				DIFFICULTY_EASY,
				DIFFICULTY_NORMAL,
				DIFFICULTY_HARD
			};

			// ステージの状態
			enum Stage{
				STAGE_FIRST,
				STAGE_SECOND,
				STAGE_THIRD,
				STAGE_GAME_OVER
			};
			/////////////////////////////////////////////////
			/// Public Function

			/**********************************************************************//**
				@brief		コンストラクタ
				@param[in]	Difficulty difficulty	難易度	
				@return		なし
				@note
				@par		
			*//***********************************************************************/
			Play(Difficulty difficulty);

			/**********************************************************************//**
				@brief		デストラクタ
				@return		なし
				@note
				@par		
			*//***********************************************************************/
			virtual ~Play();

			/**********************************************************************//**
				@brief		更新関数
				@param[in]	GameParent * pGameparent	
				@return		なし
				@note
				@par		
			*//***********************************************************************/
			Child* Update(GameParent* pGameparent);


			/**********************************************************************//**
				@brief		描画関数
				@return		なし
				@note
				@par		
			*//***********************************************************************/
			void Draw();
		private:
			/////////////////////////////////////////////////
			/// Private Function
			/**********************************************************************//**
				@brief		難易度を表す文字列を取得する
				@return		現在の何度を表す文字列
				@note
				@par		Gameクラスの実体を作成するときに使用する
			*//***********************************************************************/
			string _GetDifficultyString() const;

			/**********************************************************************//**
				@brief		ステージを表す文字列を取得する
				@return		現在のステージを表す文字列
				@note
				@par		Gameクラスの実体を作成するときに使用する
			*//***********************************************************************/
			string _GetStageString() const;
				
			/**********************************************************************//**
				@brief		次のステージの値を返す
				@param[in]	Play::Stage stage	ステージを表す列挙形
				@return		次のステージの列挙型の値
				@note
				@par		
			*//***********************************************************************/
			Stage _GetNextStage(Stage stage) const;

			/////////////////////////////////////////////////
			/// Private Variable

			Difficulty m_difficulty;
			Stage m_stage;
			Materials* m_pMaterials;
			Mouse* m_pMouse;
			Game* m_pGame;
			ofSoundPlayer m_bgm;
		};
	};
};


#endif
