/**************************************************************************//**
	@file		Misc.h
	@brief		�悭�g���G���ȋ@�\		��`�t�@�C��	
	@author		K.Seto
	@date		2011-11-5
	@par		[����]
				
*//***************************************************************************/

#ifndef _INCLUDE_MISC_H_
#define _INCLUDE_MISC_H_

namespace Misc {

	/**********************************************************************//**
		@brief		���S�Ƀ|�C���^���J������
		@param[out]	T * & p	�J������|�C���^�̎Q��	
		@return		�Ȃ�
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
		@brief		���S�ɔz����J������
		@param[out]	T * & p	�J������z��̎Q��	
		@return		�Ȃ�
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