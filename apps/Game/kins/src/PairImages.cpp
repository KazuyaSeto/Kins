/**************************************************************************//**
	@file		PairImages.cpp
	@brief		ofImageポインタの二枚セットのデータクラス	実装ファイル			
	@author		K.Seto
	@date		2011-10-26 
	@par		[説明]
				画像クラスのポインタを保持しているだけデータクラス
				ポインタは外部から設定されるのでメモリを開放する必要はない。
*//***************************************************************************/

#include "PairImages.h"
// コントラクタ
PairImages::PairImages(ofImage* pFirstImage, ofImage* pSecondImage)
{
  m_pFirstImage = pFirstImage;
  m_pSecondImage = pSecondImage;
}

// デストラクタ
PairImages::~PairImages()
{
	// none
}

// 二枚の画像をセットする。
void PairImages::SetPairIamge(ofImage* m_pFirstImage, ofImage* m_pSecondImage){
  m_pFirstImage = m_pFirstImage;
  m_pSecondImage = m_pSecondImage;
}

// 一枚目の画像ポインタを返す
ofImage* PairImages::GetFirstImage(){
  return m_pFirstImage;
}

// 二枚目の画像ポインタを返す
ofImage* PairImages::GetSecondImage(){
  return m_pSecondImage;
}
