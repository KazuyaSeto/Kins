/**************************************************************************//**
	@file		HowTo.cpp
	@brief		ゲーム内の説明書を表示するシーケンスクラス　実装ファイル	
	@author		K.Seto
	@date		2011-11-4
	@par		[説明]
	Childクラスを継承したシーケンスクラス
	ゲーム内の説明書を表示する。
*//***************************************************************************/
#include "HowTo.h"

#include "Parent.h"
#include "Child.h"
#include "Title.h"
#include "../Mouse.h"
#include "../Materials.h"
#include "../ClickButton.h"
#include "../Misc.h"

#include <iostream>


namespace {
	// ボタンに表示する文字列
	static const char* BUTTON_STRING_NEXT = "Next";
	static const char* BUTTON_STRING_BACK = "Back";
	static const char* BUTTON_STRING_RETURN_TO_TITLE = "Return To Title";

	static const int CLICK_BUTTON_WIDTH = 50;
	static const int CLICK_BUTTON_HEIGHT = 30;

	// nextButtonのパラメータ
	static const int NEXT_BUTTON_POSX = 640-CLICK_BUTTON_WIDTH;
	static const int NEXT_BUTTON_POSY = 0;

	// backButtonのパラメータ
	static const int BACK_BUTTON_POSX = 0;
	static const int BACK_BUTTON_POSY = 0;

	// returnTitleButtonのパラメータ
	static const int TITLE_BUTTON_POSX = 0;
	static const int TITLE_BUTTON_POSY = 480-CLICK_BUTTON_HEIGHT;
	static const int TITLE_BUTTON_WIDHT =150;

	// 画像ファイルパス
	static const char* IMAGE_FILE_PATH_TITLE_0 = "howto/omote.png";
	static const char* IMAGE_FILE_PATH_CONTENTS_1 = "howto/contents.png";
	static const char* IMAGE_FILE_PATH_PROLOAG_2 = "howto/prolorg.png";
	static const char* IMAGE_FILE_PATH_MOKUTEKI_3 = "howto/mokuteki.png";
	static const char* IMAGE_FILE_PATH_ASOBIKATA_4 = "howto/asobikata.png";
	static const char* IMAGE_FILE_PATH_GAMEN_5 = "howto/gamen.png";
	static const char* IMAGE_FILE_PATH_TOOLS_6 = "howto/tools.png";
	static const char* IMAGE_FILE_PATH_TIPS_7 = "howto/Tips.png";
	static const char* IMAGE_FILE_PATH_SIYOU_8 = "howto/siyouzyou.png";
	static const char* IMAGE_FILE_PATH_PAGE_STAFF_9 = "howto/staff.png";
}

namespace Sequence {
	/////////////////////////////////////////////////
	/// Public Function

	// コンストラクタ
	HowTo::HowTo(){
		// シングルトンのマテリアルクラスからデータを引っ張ってきて初期化
		m_pMouse = Mouse::Instance();
		m_pMaterials = Materials::Instance();
		_PlayBgm();


		m_pNextButton = new ClickButton(NEXT_BUTTON_POSX,
										NEXT_BUTTON_POSY,
										CLICK_BUTTON_WIDTH,
										CLICK_BUTTON_HEIGHT,
										BUTTON_STRING_NEXT);

		m_pBackButton = new ClickButton(BACK_BUTTON_POSX,
										BACK_BUTTON_POSY,
										CLICK_BUTTON_WIDTH,
										CLICK_BUTTON_HEIGHT,
										BUTTON_STRING_BACK);

		m_pTitleButton = new ClickButton(	TITLE_BUTTON_POSX,
											TITLE_BUTTON_POSY,
											TITLE_BUTTON_WIDHT,
											CLICK_BUTTON_HEIGHT,
											BUTTON_STRING_RETURN_TO_TITLE);
		m_page = PAGE_TITLE_0;
		pageImage.loadImage(IMAGE_FILE_PATH_TITLE_0);


	}

	// デストラクタ
	HowTo::~HowTo(){
		// ボタンのインスタンスを開放
		using namespace Misc;
		SafeDelete(m_pNextButton);
		SafeDelete(m_pBackButton);
		SafeDelete(m_pTitleButton);
	}

	// 更新関数
	Child* HowTo::Update(Parent* parent){

		m_pTitleButton->Update();

		Child* pNext = this;
		if(m_pTitleButton->IsClicked()){
			pNext = new Title;
		}

		m_pNextButton->Update();
		m_pBackButton->Update();

		if(_IsClickedNextButton() || _IsClickedBackButton()){
			switch (m_page){
			case PAGE_TITLE_0:
				if(_IsClickedNextButton()){
					m_page = PAGE_CONTENTS_1;
					_ChangeImage();
				}
				break;
			case PAGE_CONTENTS_1:
				_ChangePage(PAGE_TITLE_0, PAGE_PROLOAG_2);
				break;
			case PAGE_PROLOAG_2:
				_ChangePage(PAGE_CONTENTS_1, PAGE_MOKUTEKI_3);
				break;
			case PAGE_MOKUTEKI_3:
				_ChangePage(PAGE_PROLOAG_2, PAGE_ASOBIKATA_4);
				break;
			case PAGE_ASOBIKATA_4:
				_ChangePage(PAGE_MOKUTEKI_3, PAGE_GAMEN_5);
				break;
			case PAGE_GAMEN_5:
				_ChangePage(PAGE_ASOBIKATA_4, PAGE_TOOLS_6);
				break;
			case PAGE_TOOLS_6:
				_ChangePage(PAGE_GAMEN_5, PAGE_TIPS_7);
				break;
			case PAGE_TIPS_7:
				_ChangePage(PAGE_TOOLS_6, PAGE_SIYOU_8);
				break;
			case PAGE_SIYOU_8:
				_ChangePage(PAGE_TIPS_7, PAGE_STAFF_9);
				break;
			case PAGE_STAFF_9:
				if(_IsClickedBackButton()){
					m_page = PAGE_SIYOU_8;
					_ChangeImage();
				}
				break;
			default:
				break;
			}
		}

		return pNext;
	}

	// 描画関数
	void HowTo::Draw(){
		ofPushMatrix();
		ofPushStyle();

		pageImage.draw(0,0);
		m_pNextButton->Draw();
		m_pBackButton->Draw();
		m_pTitleButton->Draw();

		ofPopStyle();
		ofPopMatrix();
	}

	/////////////////////////////////////////////////
	/// Private Function

	// ページを切り替え
	void HowTo::_ChangePage(Page backPage, Page nextPage){
		if(_IsClickedBackButton()){
			m_page = backPage;
		}else if(_IsClickedNextButton()){
			m_page = nextPage;
		}
		_ChangeImage();
	}

	// BGMを再生する
	void HowTo::_PlayBgm()
	{
		ofSoundPlayer* pTitleBgm = m_pMaterials->GetSoundTitle();
		ofSoundPlayer* pPlayBgm = m_pMaterials->GetSoundPlay();
		ofSoundPlayer* pEndingBgm = m_pMaterials->GetSoundEnd();
		if(!pTitleBgm->getIsPlaying()){ pTitleBgm->play(); }
		if( pPlayBgm->getIsPlaying() ){ pPlayBgm->stop(); }
		if( pEndingBgm->getIsPlaying() ){ pEndingBgm->stop(); }
	}

	// ページに応じて画像を切り替え
	void HowTo::_ChangeImage(){
		switch (m_page){
		case PAGE_TITLE_0:
			pageImage.loadImage(IMAGE_FILE_PATH_TITLE_0);
			break;
		case PAGE_CONTENTS_1:
			pageImage.loadImage(IMAGE_FILE_PATH_CONTENTS_1);
			break;
		case PAGE_PROLOAG_2:
			pageImage.loadImage(IMAGE_FILE_PATH_PROLOAG_2);
			break;
		case PAGE_MOKUTEKI_3:
			pageImage.loadImage(IMAGE_FILE_PATH_MOKUTEKI_3);
			break;
		case PAGE_ASOBIKATA_4:
			pageImage.loadImage(IMAGE_FILE_PATH_ASOBIKATA_4);
			break;
		case PAGE_GAMEN_5:
			pageImage.loadImage(IMAGE_FILE_PATH_GAMEN_5);
			break;
		case PAGE_TOOLS_6:
			pageImage.loadImage(IMAGE_FILE_PATH_TOOLS_6);
			break;
		case PAGE_TIPS_7:
			pageImage.loadImage(IMAGE_FILE_PATH_TIPS_7);
			break;
		case PAGE_SIYOU_8:
			pageImage.loadImage(IMAGE_FILE_PATH_SIYOU_8);
			break;
		case PAGE_STAFF_9:
			pageImage.loadImage(IMAGE_FILE_PATH_PAGE_STAFF_9);
			break;
		}
	}

	// Nextボタンが押されたかどうか？
	const bool HowTo::_IsClickedNextButton() const{
		return m_pNextButton->IsClicked();
	}

	// Backボタンが押されたかどうか？
	const bool HowTo::_IsClickedBackButton() const{
		return m_pBackButton->IsClicked();
	}

	// Titleボタンが押されたかどうか？
	const bool HowTo::_IsClickedTitleButton() const{
		return m_pTitleButton->IsClicked();
	}
};