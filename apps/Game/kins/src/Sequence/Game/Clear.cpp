/**************************************************************************//**
	@file		Clear.cpp
	@brief		�Q�[���v���C�V�[�P���X�̃N���A��ʂ̃N���X�@�����t�@�C��
	@author		K.Seto
	@date		2011-11-6
	@par		[����]
				
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
	// �摜�t�@�C���̃p�X
	const static char* IMAGE_FILE_PATH_PAGE1 = "ending/end_1.png";
	const static char* IMAGE_FILE_PATH_PAGE2 = "ending/end_2.png";
	const static char* IMAGE_FILE_PATH_PAGE3 = "ending/end_3.png";
	const static char* IMAGE_FILE_PATH_PAGE4 = "ending/end_4.png";
	// �{�^���̃��x��
	const static char* NEXT_BUTTON_STRING = "Next";
	const static char* TITLE_BUTTON_STRING = "Return To Title";
	// �{�^���̍���
	const static int BUTTON_HEIGHT = 30;
	// �{�^���̕�
	const static int NEXT_BUTTON_WIDTH = 50;
	const static int TITLE_BUTTON_HEIGHT = 150;
	
}

namespace Sequence {
	namespace GameSequence {
		// �R���X�g���N�^
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

		// �f�X�g���N�^
		Clear::~Clear(){
			Misc::SafeDelete(m_pNextButton);
			Misc::SafeDelete(m_pTitleButton);
		}

		// �X�V�֐�
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

		// �`��֐�
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

		// �y�[�W�؂�ւ�
		void Clear::_ChangePage(Page in_page){
			m_page = in_page;
			_ChangeImage();
		}

		// �摜�؂�ւ�
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

		// Next�{�^���������ꂽ���ǂ����H
		bool Clear::_IsClickedNextButton() const{
			return m_pNextButton->IsClicked();
		}

		// Title�{�^���������ꂽ���ǂ����H
		bool Clear::_IsClickedRerturnButton() const{
			return m_pTitleButton->IsClicked();
		}

		// BGM���Đ�����
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