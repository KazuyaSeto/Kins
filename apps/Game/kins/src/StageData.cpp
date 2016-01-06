/**************************************************************************//**
	@file		StageData.cpp
	@brief		テキストファイルで保存されたステージデータをロードするクラス　実装ファイル
	@author		K.Seto
	@date		2011-10-24
	@par		[説明]
				stlのmapにステージのパラメータを読み込み、キーから各パラメータを取得する				
*//***************************************************************************/

#include <fstream>
#include <iostream>
#include <iterator>

#include "StageData.h"
#include "ofMain.h"

using namespace std;

// コンストラクタ
StageData::StageData(){}

// コンストラクタ
StageData::StageData(string& filename){
	_MakeStageDataFromStageFile(filename);
}

// デストラクタ
StageData::~StageData(){
	// none
}

// ステージデータをファイルから読み込む
void StageData::LoadStageData(string& filename){
	_MakeStageDataFromStageFile(filename);

}

// ステージデータを端末に出力する
void StageData::PrintStageData()
{
  // 要素を出力する
  map<string, string>::iterator it = m_stageDataMap.begin();
  while( it != m_stageDataMap.end() ){
    cout << it->first << ":" << it->second << endl;
    ++it;
  }
}

// キーからintの数値を取得する
int StageData::GetIntValue( std::string key )
{
  return ofToInt( m_stageDataMap[key] );
}

// キーからstring型の値を取得する
std::string StageData::GetStringValue( std::string key )
{
  return m_stageDataMap[key];
}

// キー列の入っているベクターコンテナを取得する
std::vector<std::string> StageData::GetKeyVector() const
{
  return m_keyVector;
}

// ファイルからステージデータを作成する
void StageData::_MakeStageDataFromStageFile( string &filename )
{
	// ファイルから辞書を作る。

	ifstream ifs( filename.c_str() );
	if (!ifs) {
		cout << "***error  入力ファイルを開けません\n";
		exit(1);
	}
	string key;
	string value;

	ifs >> key >> value;
	while(!ifs.eof()){
		m_stageDataMap.insert( map<string, string>::value_type( key, value ) ); // マップに要素を追加する
		m_keyVector.push_back( key );
		ifs >> key >> value;
	}
}
