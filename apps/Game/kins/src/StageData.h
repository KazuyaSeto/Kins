﻿/**************************************************************************//**
	@file		StageData.cpp
	@brief		テキストファイルで保存されたステージデータをロードするクラス　定義ファイル
	@author		K.Seto
	@date		2011-10-24
	@par		[説明]
				stlのmapにステージのパラメータを読み込み、キーから各パラメータを取得する				
*//***************************************************************************/

#ifndef STAGE_DATE_LOADER_H
#define STAGE_DATE_LOADER_H

#include <map>
#include <vector>
#include <string>

/**********************************************************************//**
	@class		StageData
	@brief		テキストファイルからステージデータをロードするクラス
	@par		[説明]
*//***********************************************************************/
class StageData{
public:
	//////////////////////////////////////////////////////////////////////////
	// Public Function
	/**********************************************************************//**
		@brief		コンストラクタ
		@return		なし
		@note
		@par		辞書は作成しなバージョン
					あとでmakeDictionary()を呼び辞書を作成する必要がある。
	*//***********************************************************************/
	StageData();

	/**********************************************************************//**
		@brief		コンストラクタ
		@param[in]	std::string & filename	ファイル名
		@return		なし
		@note
		@par		インスタンスを作成すると同時にステージデータをロードする
	*//***********************************************************************/
	StageData(std::string& filename);


	/**********************************************************************//**
		@brief		デストラクタ
		@return		なし
		@note
		@par		
	*//***********************************************************************/
	virtual ~StageData();

	/**********************************************************************//**
		@brief		ステージファイルをロードする
		@param[in]	std::string & filename	ステージデータのファイル名
		@return		なし
		@note
		@par		
	*//***********************************************************************/
	void LoadStageData(std::string& filename);

	/**********************************************************************//**
		@brief		ステージデータを出力する
		@return		なし
		@note
		@par		端末にステージデータを出力する
	*//***********************************************************************/
	void PrintStageData();

	/**********************************************************************//**
		@brief		キーからintの数値を取得する
		@param[in]	std::string key	
		@return		キーに対応した数値
		@note
		@par		
	*//***********************************************************************/
	int GetIntValue(std::string key);


	/**********************************************************************//**
		@brief		キーからstring型の値を取得する
		@param[in]	std::string key	
		@return		キーに対応したstring型
		@note
		@par		
	*//***********************************************************************/
	std::string GetStringValue(std::string key);

	/**********************************************************************//**
		@brief		キー列の入っているベクターコンテナを取得する
		@return		なし
		@note
		@par		ステージデータのすべてのキーを取得したいときに使う
	*//***********************************************************************/
	std::vector<std::string> GetKeyVector() const;
private:
	/////////////////////////////////////////////////
	/// Private Function
	void _MakeStageDataFromStageFile( std::string &filename );

	//////////////////////////////////////////////////////////////////////////
	// Private Variable

	std::map<std::string, std::string> m_stageDataMap;
	std::vector<std::string> m_keyVector;
};

#endif