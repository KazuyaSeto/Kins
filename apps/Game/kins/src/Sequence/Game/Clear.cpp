/**************************************************************************//**
	@file		Clear.cpp
	@brief		ゲームプレイシーケンスのクリア画面のクラス　実装ファイル
	@author		K.Seto
	@date		2011-11-6
	@par		[説明]
				
*//***************************************************************************/


#include "Clear.h"
#include "../GameParent.h"
#include "../../ClickButton.h"
#include "../../Materials.h"
#include "../../Mouse.h"
#include "../../Misc.h"

#include <iostream>
#include <cassert>

namespace {
	// 画像ファイルのパス
	const static char* IMAGE_FILE_PATH_PAGE1 = "ending/end_1.png";
	const static char* IMAGE_FILE_PATH_PAGE2 = "ending/end_2.png";
	const static char* IMAGE_FILE_PATH_PAGE3 = "ending/end_3.png";
	const static char* IMAGE_FILE_PATH_PAGE4 = "ending/end_4.png";
	// ボタンのラベル
	const static char* NEXT_BUTTON_STRING = "Next";
	const static char* TITLE_BUTTON_STRING = "Return To Title";
	// ボタンの高さ
	const static int BUTTON_HEIGHT = 30;
	// ボタンの幅
	const static int NEXT_BUTTON_WIDTH = 50;
	const static int TITLE_BUTTON_HEIGHT = 150;
	
}

namespace Sequence {
	namespace GameSequence {
		// コンストラクタ
		Clear::Clear(){
			m_pMouse = Mouse::Instance();
			m_pMaterials = Materials::Instance();
			_PlayBgm();


			m_pNextButton = new ClickButton(	ofGetWidth()-NEXT_BUTTON_WIDTH,
												0,
												NEXT_BUTTON_WIDTH,
												BUTTON_HEIGHT,
												NEXT_BUTTON_STRING);

			m_pTitleButton = new ClickButton(	0,
												ofGetHeight()-BUTTON_HEIGHT,
												TITLE_BUTTON_HEIGHT,
												BUTTON_HEIGHT,
												TITLE_BUTTON_STRING);

			m_pageImage.loadImage(IMAGE_FILE_PATH_PAGE1);
			m_page = PAGE_1;
		}

		// デストラクタ
		Clear::~Clear(){
			Misc::SafeDelete(m_pNextButton);
			Misc::SafeDelete(m_pTitleButton);
		}

		// 更新関数
		Child* Clear::Update(Sequence::GameParent* pParent){
			m_pNextButton->Update();
			m_pTitleButton->Update();
			if( m_pTitleButton->IsClicked() ){
				pParent->ReturnToTitle();
			}

			if( _IsClickedNextButton() ){
				switch (m_page){
				case PAGE_1:
					_ChangePage(PAGE_2);
					break;
				case PAGE_2:
					_ChangePage(PAGE_3);
					break;
				case PAGE_3:
					_ChangePage(PAGE_4);
					break;
				default:
					break;
				}
			}


			return this;
		}

		// 描画関数
		void Clear::Draw(){
			ofPushStyle();
			switch (m_page){
			case PAGE_4:
				m_pageImage.draw(0,0);
				break;
			default:
				m_pageImage.draw(0,0);
				m_pNextButton->Draw();
				break;
			}
			m_pTitleButton->Draw();
			ofPopStyle();
		}

		// ページ切り替え
		void Clear::_ChangePage(Page in_page){
			m_page = in_page;
			_ChangeImage();
		}

		// 画像切り替え
		void Clear::_ChangeImage(){
			switch (m_page){
			case PAGE_1:
				m_pageImage.loadImage(IMAGE_FILE_PATH_PAGE1);
				break;
			case PAGE_2:
				m_pageImage.loadImage(IMAGE_FILE_PATH_PAGE2);
				break;
			case PAGE_3:
				m_pageImage.loadImage(IMAGE_FILE_PATH_PAGE3);
				break;
			case PAGE_4:
				m_pageImage.loadImage(IMAGE_FILE_PATH_PAGE4);
				break;
			default:
				assert(false);
				break;
			}
		}

		// Nextボタンが押されたかどうか？
		bool Clear::_IsClickedNextButton() const{
			return m_pNextButton->IsClicked();
		}

		// Titleボタンが押されたかどうか？
		bool Clear::_IsClickedRerturnButton() const{
			return m_pTitleButton->IsClicked();
		}

		// BGMを再生する
		void Clear::_PlayBgm()const{
			ofSoundPlayer* pTitleBgm = m_pMaterials->GetSoundTitle();
			ofSoundPlayer* pPlayBgm = m_pMaterials->GetSoundPlay();
			ofSoundPlayer* pEndingBgm = m_pMaterials->GetSoundEnd();
			if( pTitleBgm->getIsPlaying()){ pTitleBgm->stop(); }
			if( pPlayBgm->getIsPlaying() ){ pPlayBgm->stop(); }
			if( !pEndingBgm->getIsPlaying() ){ pEndingBgm->play(); }
		}

	};
};