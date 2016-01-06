﻿/**************************************************************************//**
	@file		kinManager.h
	@brief		ゲームで使用される菌を管理するクラス	定義ファイル
	@author		K.Seto
	@date		2011-10-24 
	@par		[説明]
				ステージファイルを読み取って出現すべき菌を生成管理する。
				ひとつのステージで捕獲すべき菌の種類は最大でも３種類である。
				その３種類をそれぞれターゲットA、ターゲットB、ターゲットCと呼ぶ。
				
*//***************************************************************************/

#ifndef INCLUDE_KIN_MANAGER_H
#define INCLUDE_KIN_MANAGER_H

#include <vector>
#include <string>

/////////////////////////////////////////////////
/// Forward Declaration

class Game;
class Kin;
class Mouse;
class PairImages;


class KinManager
{
    public:
		//////////////////////////////////////////////////////////////////////////
		///	Public Function
        /**********************************************************************//**
        	@brief		コンストラクタ
        	@param[in]	pGame	ゲームクラスにアクセスするポインタ
        	@param[in]	stage	ステージ名
        	@return		なし
        	@note
        	@par		
        *//***********************************************************************/
        KinManager(const Game* pGame, const std::string& stage);

        /**********************************************************************//**
        	@brief		デストラクタ
        	@return		なし
        	@note
        	@par		
        *//***********************************************************************/
        virtual ~KinManager();

        /**********************************************************************//**
        	@brief		更新関数
        	@return		なし		
        	@note
        	@par		
        *//***********************************************************************/
        void Update();

        /**********************************************************************//**
        	@brief		描画
        	@return		なし
        	@note
        	@par		菌をすべて描画する
        *//***********************************************************************/
        void Draw();

		/**********************************************************************//**
			@brief		ステージクリアの条件を満たしていることを返す。
			@retval		true	ステージクリアしている
			@retval		false	ステージクリアしていない
			@note
			@par		
		*//***********************************************************************/
		bool IsStageClear() const;

        /**********************************************************************//**
        	@brief		ターゲットの種類の数を返す
        	@return		ターゲットの種類の数
        	@note		
        	@par		
        *//***********************************************************************/
		int GetNumberOfTypesOfTarget() const;

        /**********************************************************************//**
        	@brief		ターゲットAのPairImagesを取得する
        	@return		ターゲットAのPairImages
        	@note
        	@par		
        *//***********************************************************************/
        PairImages* GetPairImagesTargetA();

        /**********************************************************************//**
        	@brief		ターゲットAの目的捕獲数を返す
        	@return		ターゲットAの目的捕獲数
        	@note
        	@par		
        *//***********************************************************************/
		int GetNumberOfTargetA() const;

        /**********************************************************************//**
			@brief		ターゲットBのPairImagesを取得する
			@return		ターゲットBのPairImages	
        	@note
        	@par		
        *//***********************************************************************/
        PairImages* GetPairImagesTargetB();

        /**********************************************************************//**
        	@brief		ターゲットBの目的捕獲数を返す
        	@return		ターゲットBの目的捕獲数
        	@note
        	@par		
        *//***********************************************************************/
		int GetNumberOfTargetB() const;

        /**********************************************************************//**
			@brief		ターゲットCのPairImagesを取得する
			@return		ターゲットCのPairImages	
        	@note
        	@par		
        *//***********************************************************************/        
		PairImages* GetPairImagesTargetC();

		/**********************************************************************//**
        	@brief		ターゲットCの目的捕獲数を返す
        	@return		ターゲットCの目的捕獲数
        	@note
        	@par		
        *//***********************************************************************/
		int GetNumberOfTargetC() const;

		/**********************************************************************//**
			@brief		nameがターゲットの菌の種類の名前であれば真を返す
			@param[in]	const std::string & name	判定する菌の名前
			@retval		true	nameはターゲットである
			@retval		false	nameはターゲットでない
			@note
			@par		
		*//***********************************************************************/
		bool IsTargetName(const std::string& name) const;

		/**********************************************************************//**
			@brief		捕獲された（シャーレの中にいる）菌の数を返す
			@return		捕獲された菌の数
			@note
			@par		
		*//***********************************************************************/
		int GetNumberOfKinInShale() const;

		/**********************************************************************//**
			@brief		捕獲された（シャーレの中にいる）ターゲットAの数を返す
			@return		捕獲されたターゲットA
			@note
			@par		
		*//***********************************************************************/
		int GetNumberOfTargetAInSchale() const;


		/**********************************************************************//**
			@brief		捕獲された（シャーレの中にいる）ターゲットBの数を返す
			@return		捕獲されたターゲットB
			@note
			@par		
		*//***********************************************************************/
		int GetNumberOfTargetBInSchale() const;

		/**********************************************************************//**
			@brief		捕獲された（シャーレの中にいる）ターゲットCの数を返す
			@return		捕獲されたターゲットC
			@note
			@par		
		*//***********************************************************************/
		int GetNumberOfTargetCInSchale() const;
    private:
		//////////////////////////////////////////////////////////////////////////
		///	Private Function
		/**********************************************************************//**
			@brief		ターゲットAがクリア条件の捕獲数を満たしていれば真を返す
			@retval		true	ターゲットAはクリア条件を満たしている
			@retval		false	ターゲットAはクリア条件を満たしていない
			@note
			@par		
		*//***********************************************************************/
		bool _IsClearTargetA() const;

		/**********************************************************************//**
			@brief		ターゲットBがクリア条件の捕獲数を満たしていれば真を返す
			@retval		true	ターゲットBはクリア条件を満たしている
			@retval		false	ターゲットBはクリア条件を満たしていない
			@note
			@par		
		*//***********************************************************************/
		bool _IsClearTargetB() const;

		/**********************************************************************//**
			@brief		ターゲットCがクリア条件の捕獲数を満たしていれば真を返す
			@retval		true	ターゲットCはクリア条件を満たしている
			@retval		false	ターゲットCはクリア条件を満たしていない
			@note
			@par		
		*//***********************************************************************/
		bool _IsClearTargetC() const;

		//////////////////////////////////////////////////////////////////////////
		/// Private Variable
		const Game* m_pGame;					//<! ゲームクラスへアクセスするポインタ
		Mouse* m_pMouse;						//<! マウスのインスタンスへのポインタ
		std::vector<Kin*> mKinVector;			//<! 生成した菌を格納するベクターコンテナ
		int m_targetNum;							//<! ターゲットの種類
		std::string m_targetAName;				//<! ターゲットAの名前
		PairImages* m_pTargetAPairImage;		//<! ターゲットAの画像ペア
		int m_targetANum;						//<! ターゲットAの数
		std::string m_targetBName;				//<! ターゲットBの名前
		PairImages* m_pTargetBPairImage;		//<! ターゲットBの画像ペア
		int m_targetBNum;						//<! ターゲットBの数
		std::string m_targetCName;				//<! ターゲットCの名前
		PairImages* m_pTargetCPairImage;		//<! ターゲットCの画像ペア
		int m_targetCNum;						//<! ターゲットCの数

};

#endif // KINMANAGER_H