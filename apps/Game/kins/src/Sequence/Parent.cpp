/**************************************************************************//**
	@file		Parent.cpp
	@brief		シーケンス制御の親クラス	実装ファイル	
	@author		K.Seto
	@date		2011-11-5
	@par		[説明]
				シーケンス制御の親クラス
				シーケンスが移動した場合前のシーケンスのメモリを開放する
*//***************************************************************************/

#include "Parent.h"

#include "Title.h"
#include "GameParent.h"
#include "../Materials.h"
#include "../Misc.h"

#include <iostream>

namespace Sequence {

		// コンストラクタ
	Parent::Parent():
		m_pChild( 0 ),
		mNext( SEQ_NONE ){
			m_pChild = new Title;
	}

	// デストラクタ
	Parent::~Parent(){
		Misc::SafeDelete(m_pChild);
	}

	// 更新関数
	void Parent::Update(){
		Child* pNext = m_pChild->Update(this);

		if(m_pChild != pNext){
			Misc::SafeDelete(m_pChild);
			m_pChild = pNext;
		}
	}

	// 描画関数
	void Parent::Draw(){
		m_pChild->Draw();
	}

};
