﻿/**************************************************************************//**
	@file		Clear.h
	@brief		ゲームプレイシーケンスのクリア画面のクラス　定義ファイル
	@author		K.Seto
	@date		2011-11-6
	@par		[説明]
				
*//***************************************************************************/
#ifndef INCLUDE_SEQUENCE_GAME_CLEAR_H
#define INCLUDE_SEQUENCE_GAME_CLEAR_H

#include "Child.h"
#include "ofMain.h"

#include <string>

/////////////////////////////////////////////////
/// Forward Declaration

class Sequence::GameSequence::Child;
class ClickButton;
class Mouse;
class Materials;

namespace Sequence{
	class GameParent;
	namespace GameSequence{
		/**********************************************************************//**
			@class		Clear
			@brief		ゲームプレイシーケンスのクリア画面のクラス
			@par		[説明]
						ゲームクリア画面は紙芝居のような処理を行う
						Nextボタンが押された次のページの画像を読み込み、表示する
		*//***********************************************************************/
		class Clear : public Child{
		public:
			enum Page{
				PAGE_1,
				PAGE_2,
				PAGE_3,
				PAGE_4
			};
			/////////////////////////////////////////////////
			/// Private Function

			/**********************************************************************//**
				@brief		コンストラクタ
				@return		なし
				@note
				@par		
			*//***********************************************************************/
			Clear();

			/**********************************************************************//**
				@brief		デストラクタ		
				@return		なし
				@note
				@par		
			*//***********************************************************************/
			virtual ~Clear();

			/**********************************************************************//**
				@brief		更新関数
				@param[in]	GameParent * pParent	ゲームプレイシーケンス親クラスのポインタ	
				@return		次のゲームプレイシーケンスのポインタ
				@note
				@par		
			*//***********************************************************************/
			Child* Update(GameParent* pParent);

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
				@brief		ページを切り替える
				@param[in]	Page nextPage	次のページ
				@return		なし
				@note
				@par		
			*//***********************************************************************/
			void _ChangePage(Page nextPage);

			/**********************************************************************//**
				@brief		画像を切り替える
				@return		なし
				@note
				@par		
			*//***********************************************************************/
			void _ChangeImage();

			/**********************************************************************//**
				@brief		Nextボタンが押されたかどうか？
				@retval		true	押された
				@retval		false	押されていない
				@note
				@par		
			*//***********************************************************************/
			bool _IsClickedNextButton() const;

			/**********************************************************************//**
				@brief		Titleボタンが押されたかどうか？
				@retval		true	押された
				@retval		false	押されていない
				@note
				@par		
			*//***********************************************************************/
			bool _IsClickedRerturnButton() const;

			/**********************************************************************//**
				@brief		BGMを再生する
				@return		なし
				@note
				@par		
			*//***********************************************************************/
			void _PlayBgm() const;

			/////////////////////////////////////////////////
			/// Private Variable
			Page m_page;
			ClickButton* m_pNextButton;
			ClickButton* m_pTitleButton;
			Materials* m_pMaterials;
			Mouse* m_pMouse;
			ofImage m_pageImage;
		};
	};
};


#endif
