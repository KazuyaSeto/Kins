﻿/**************************************************************************//**
	@file		Child.h
	@brief		ゲームプレイシーケンスのインターフェイスクラス　定義ファイル	
	@author		K.Seto
	@date		2011-11-6
	@par		[説明]
				ゲームプレイシーケンスクラスのインターフェイスを規定する。
				更新、描画のインターフェイスを持つ。
*//***************************************************************************/

#ifndef INCLUDE_SEQUENCE_GAME_CHILD_H
#define INCLUDE_SEQUENCE_GAME_CHILD_H

namespace Sequence{
	class GameParent;
	namespace GameSequence{
		/**********************************************************************//**
			@class		Child
			@brief		ゲームプレイシーケンスのインターフェイスクラス
			@par		[説明]
		*//***********************************************************************/
		class Child{
		public:
			/**********************************************************************//**
				@brief		更新関数
				@param[in]	GameParent *	pGameParent
				@return		次のゲームプレイシーケンスのポインタ
				@note
				@par		
			*//***********************************************************************/
			virtual Child* Update(GameParent* pGameParent) = 0;

			/**********************************************************************//**
				@brief		描画関数
				@return		なし
				@note
				@par		
			*//***********************************************************************/
			virtual void Draw() = 0;

			/**********************************************************************//**
				@brief		デストラクタ
				@return		なし
				@note
				@par		デフォルトはなにもしない
			*//***********************************************************************/
			virtual ~Child(){}
		};
	};
};

#endif