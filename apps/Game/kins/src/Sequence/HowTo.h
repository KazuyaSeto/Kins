/**************************************************************************//**
	@file		HowTo.h
	@brief		ゲーム内の説明書を表示するシーケンスクラス　定義ファイル	
	@author		K.Seto
	@date		2011-11-4
	@par		[説明]
				Childクラスを継承したシーケンスクラス
				ゲーム内の説明書を表示する。
*//***************************************************************************/

#ifndef INCLUDE_SEQUENCE_HOWTO_H
#define INCLUDE_SEQUENCE_HOWTO_H

#include "Child.h"
#include "ofMain.h"

/////////////////////////////////////////////////
/// Forward Declaration

class Mouse;
class Materials;
class ClickButton;
namespace Sequence{
	class Parent;

	/**********************************************************************//**
		@class		HowTo
		@brief		ゲーム内の説明書を表示するシーケンスクラス
		@par		[説明]
					
	*//***********************************************************************/
	class HowTo : public Child{
	public:
		// ページの状態
		enum Page{
			PAGE_TITLE_0,
			PAGE_CONTENTS_1,
			PAGE_PROLOAG_2,
			PAGE_MOKUTEKI_3,
			PAGE_ASOBIKATA_4,
			PAGE_GAMEN_5,
			PAGE_TOOLS_6,
			PAGE_TIPS_7,
			PAGE_SIYOU_8,
			PAGE_STAFF_9,
		};
		
		/**********************************************************************//**
			@brief		コンストラクタ
			@return		なし
			@note
			@par		
		*//***********************************************************************/
		HowTo();

		/**********************************************************************//**
			@brief		デストラクタ
			@return		なし
			@note
			@par		
		*//***********************************************************************/
		virtual ~HowTo();

		/**********************************************************************//**
			@brief		更新関数
			@param[in]	Parent * pParent	
			@return		なし
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
	private:
		/////////////////////////////////////////////////
		/// Private Function

		/**********************************************************************//**
			@brief		BGMを再生する
			@return		なし
			@note
			@par		m_pMaterialsの初期化が事前に必要
		*//***********************************************************************/
		void _PlayBgm();

		/**********************************************************************//**
			@brief		ページを切り替える
			@param[in]	Page backPage	前のページ
			@param[in]	Page nextPage	次のページ
			@return		なし
			@note
			@par		
		*//***********************************************************************/
		void _ChangePage(Page backPage, Page nextPage);

		/**********************************************************************//**
			@brief		画像を切り替える
			@return		なし
			@note
			@par		ページの状態に応じて表示される画像を切り替える
		*//***********************************************************************/
		void _ChangeImage();

		/**********************************************************************//**
			@brief		Nextボタンが押されたかどうか？
			@retval		true	押された
			@retval		false	押されない
			@note
			@par		
		*//***********************************************************************/
		const bool _IsClickedNextButton() const;

		/**********************************************************************//**
			@brief		Backボタンが押されたどうか？
			@retval		true	押された
			@retval		false	押されない
			@note
			@par		
		*//***********************************************************************/
		const bool _IsClickedBackButton() const;

		/**********************************************************************//**
			@brief		Titleボタンが押されたどうか？
			@retval		true	押された
			@retval		false	押されない
			@note
			@par
		*//***********************************************************************/
		const bool _IsClickedTitleButton() const;

		/////////////////////////////////////////////////
		/// Private Variable
		Mouse* m_pMouse;
		Materials* m_pMaterials;
		Page m_page;
		ClickButton* m_pNextButton;
		ClickButton* m_pBackButton;
		ClickButton* m_pTitleButton;
		ofImage pageImage;
	};
};

#endif // HOWTO_H
