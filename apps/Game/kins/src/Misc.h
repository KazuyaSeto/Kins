/**************************************************************************//**
	@file		Misc.h
	@brief		よく使う雑多な機能		定義ファイル	
	@author		K.Seto
	@date		2011-11-5
	@par		[説明]
				
*//***************************************************************************/

#ifndef _INCLUDE_MISC_H_
#define _INCLUDE_MISC_H_

namespace Misc {

	/**********************************************************************//**
		@brief		安全にポインタを開放する
		@param[out]	T * & p	開放するポインタの参照	
		@return		なし
		@note
		@par		
	*//***********************************************************************/
	template <typename T>
	inline void SafeDelete(T*& p){
		if(p != NULL) {
			delete (p);
			(p) = NULL;
		}
	}

	/**********************************************************************//**
		@brief		安全に配列を開放する
		@param[out]	T * & p	開放する配列の参照	
		@return		なし
		@note
		@par		
	*//***********************************************************************/
	template <typename T>
	inline void SafeDeleteArray(T*& p){
		if(p != NULL) {
			delete[] (p);
			(p) = NULL;
		}
	}

};

#endif //_INCLUDE_MISC_H_