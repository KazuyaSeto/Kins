/**************************************************************************//**
	@file		GameParent.h
	@brief		ゲームシーケンスの親クラス	定義ファイル
	@author		K.Seto
	@date		2011-11-4
	@par		[説明]
				ゲームプレイのシーケンスを管理するシーケンスクラス

*//***************************************************************************/

#ifndef INCLUDE_SEQUENCE_GAMEPARENT_H
#define INCLUDE_SEQUENCE_GAMEPARENT_H

#include "Child.h"
#include "Game/Child.h"

namespace Sequence{
	/**********************************************************************//**
		@class		GameParent
		@brief		ゲームシーケンスクラス
		@par		[説明]
					ゲームプレイのシーケンスを管理するシーケンスクラス
	*//***********************************************************************/
	class GameParent : public Child{
	public:
		enum GameSequenceID{
			GAME_SEQ_LOADING,
			GAME_SEQ_PLAY,
			GAME_SEQ_MENU,
			GAME_SEQ_CLEAR,
			GAME_SEQ_RETURN_TO_TITLE,
			GAME_SEQ_NONE
		};
		// ゲームの難易度
		enum GameDifficulty{
			GAME_EASY,
			GAME_NORMAL,
			GAME_HARD
		};
		/////////////////////////////////////////////////
		/// Public Function

		/**********************************************************************//**
			@brief		コンストラクタ
			@param[in]	GameDifficulty gameDifficulty	ゲームの難易度	
			@return		なし
			@note
			@par		ゲームの難易度を引数にとり、各難易度のゲームを開始する。
		*//***********************************************************************/
		GameParent(GameDifficulty gameDifficulty);

		/**********************************************************************//**
			@brief		デストラクタ
			@return		なし
			@note
			@par		
		*//***********************************************************************/
		virtual ~GameParent();

		/**********************************************************************//**
			@brief		更新関数
			@param[in]	Parent * pParent	親クラスのポインタ
			@return		更新後のシーケンスポインタ
			@note
			@par		
		*//***********************************************************************/
		Child* Update( Parent* pParent );

		/**********************************************************************//**
			@brief		描画関数
			@return		なし
			@note
			@par		
		*//***********************************************************************/
		void Draw();

		/**********************************************************************//**
			@brief		タイトルに戻る
			@return		なし
			@note
			@par		
		*//***********************************************************************/
		void ReturnToTitle();
	private:
		/////////////////////////////////////////////////
		/// Private Function

		GameDifficulty m_difficulty;
		GameSequence::Child* m_pChild;
		bool returnTitle;
	};
};
#endif
