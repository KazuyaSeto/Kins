/**************************************************************************//**
	@file		KinManager.cpp
	@brief		ゲームで使用される菌を管理するクラス	実装ファイル
	@author		K.Seto
	@date		2011-11-1
	@par		[説明]
				ステージファイルを読み取って出現すべき菌を生成管理する。
				ひとつのステージで捕獲すべき菌の種類は最大でも３種類である。
				その３種類をそれぞれターゲットA、ターゲットB、ターゲットCと呼ぶ。
				
*//***************************************************************************/
#include "kinManager.h"
#include "Materials.h"
#include "Game.h"
#include "ToolBox.h"
#include "StageData.h"
#include "kin.h"
#include "Mouse.h"

#include <iostream>
#include <algorithm>

namespace {
	/**********************************************************************//**
		@brief		二つの点の距離が指定した距離以下であるかどうか？
		@param[in]	int x1			点１のX座標
		@param[in]	int y1			点１のY座標
		@param[in]	int x2			点２のX座標
		@param[in]	int y2			点２のY座標
		@param[in]	int distance	指定距離
		@retval		true			指定して距離以下である
		@retval		false			指定した距離以下でない
		@note
		@par		
	*//***********************************************************************/
	bool IsDistanceLessThan(int x1, int y1, int x2, int y2,int distance){
	  int x = x1 - x2;
	  int y = y1 - y2;
	  if(distance * distance > x*x + y*y){
		return true;
	  }
	  return false;
	}

	// ステージファイルの情報
	static const std::string STAGE_FILE_PATH("./data/stage/");
	static const std::string STAGE_FILE_EXTENTION(".ini");
	static const std::string KIN_LIST_FILE_NAME("KinList");

	static const int KIN_IMAGE_WIDTH = 24;
	static const int KIN_IMAGE_HEIGHT = 24;

}

using namespace std;

// コンストラクタ
KinManager::KinManager(const Game* pGame, const string& stage)
	:m_pGame(pGame)
{
   // ステージデータロード
   Materials* pMaterials = Materials::Instance();
   m_pMouse = Mouse::Instance();

   StageData stageDataLoader( STAGE_FILE_PATH + stage + STAGE_FILE_EXTENTION);
   StageData kinListLoader( STAGE_FILE_PATH + KIN_LIST_FILE_NAME + STAGE_FILE_EXTENTION);
   kinListLoader.PrintStageData();
   

   m_targetAName = stageDataLoader.GetStringValue("targetA");
   m_pTargetAPairImage = pMaterials->GetKinPairImageByKey(m_targetAName);
   m_targetANum = stageDataLoader.GetIntValue("targetANum");

   m_targetBName = stageDataLoader.GetStringValue("targetB");
   m_pTargetBPairImage = pMaterials->GetKinPairImageByKey(m_targetBName);
   m_targetBNum = stageDataLoader.GetIntValue("targetBNum");

   m_targetCName = stageDataLoader.GetStringValue("targetC");
   m_pTargetCPairImage = pMaterials->GetKinPairImageByKey(m_targetCName);
   m_targetCNum = stageDataLoader.GetIntValue("targetCNum");

   m_targetNum = stageDataLoader.GetIntValue("targetNum");

   int posx1 = stageDataLoader.GetIntValue("posx1");
   int posy1 = stageDataLoader.GetIntValue("posy1");
   int posx2 = stageDataLoader.GetIntValue("posx2");
   int posy2 = stageDataLoader.GetIntValue("posy2");
   int posx3 = stageDataLoader.GetIntValue("posx3");
   int posy3 = stageDataLoader.GetIntValue("posy3");
   vector<string> key = kinListLoader.GetKeyVector();
   for(int i = 0; i < key.size() ; i++){
     for(int j = 0; j < stageDataLoader.GetIntValue(key[i]); j++ ){
       float rand = ofRandom(0.0,static_cast<float>(m_targetNum));
       if(rand < 1.0){
         mKinVector.push_back( new Kin(posx1,posy1,KIN_IMAGE_WIDTH,KIN_IMAGE_HEIGHT, key[i],this ) );
       }else if( rand < 2.0){
         mKinVector.push_back( new Kin(posx2,posy2,KIN_IMAGE_WIDTH,KIN_IMAGE_HEIGHT, key[i],this ) );
       }else {
         mKinVector.push_back( new Kin(posx3,posy3,KIN_IMAGE_WIDTH,KIN_IMAGE_HEIGHT, key[i],this ) );
       }
     }
   }
   random_shuffle(mKinVector.begin(), mKinVector.end());
}


// デストラクタ
KinManager::~KinManager()
{
  for(int i = 0; i < mKinVector.size() ; i++){
    delete mKinVector[i];
    mKinVector[i] = 0;
  }
}



// 更新関数
void KinManager::Update(){
  for(int i=0; i < mKinVector.size(); i++){
     mKinVector[i]->Update();
  }
  if( m_pMouse->IsPressed() && ToolBox::TOOL_PINSET == m_pGame->GetToolBoxState()){
    for(int i=0; i < mKinVector.size(); i++){
      if( mKinVector[i]->IsMouseOver() ){
        if(!mKinVector[i]->IsState(Kin::schale)){
          mKinVector[i]->SetState(Kin::picUp);
        }
        break;
      }
    }
  }else if(m_pMouse->IsDragged() && ToolBox::TOOL_AIR == m_pGame->GetToolBoxState()){
    for(int i=0; i < mKinVector.size(); i++){
      if(!mKinVector[i]->IsState(Kin::schale) &&
         IsDistanceLessThan(m_pMouse->GetPosX(), m_pMouse->GetPosY(), mKinVector[i]->PosX(), mKinVector[i]->PosY(), 30)){
        mKinVector[i]->SetState(Kin::air);
      }
    }
  }
}
// 描画関数
void KinManager::Draw(){
  for(int i=mKinVector.size()-1; i >= 0; i--){
     mKinVector[i]->Draw();
  }
}

// ステージクリアの条件を満たしていることを返す。
bool KinManager::IsStageClear() const
{
	if( _IsClearTargetA() && _IsClearTargetB() && _IsClearTargetC() ){
		return true;
	}
	return false;
}

// ターゲットの種類の数を返す
int KinManager::GetNumberOfTypesOfTarget() const
{
  return m_targetNum;
}

// ターゲットAのPairImagesを取得する
PairImages* KinManager::GetPairImagesTargetA(){
  return m_pTargetAPairImage;
}

// ターゲットAの目的捕獲数を返す
int KinManager::GetNumberOfTargetA() const
{
  return m_targetANum;
}

// ターゲットBのPairImagesを取得する
PairImages* KinManager::GetPairImagesTargetB(){
  return m_pTargetBPairImage;
}

// ターゲットBの目的捕獲数を返す
int KinManager::GetNumberOfTargetB() const
{
  return m_targetBNum;
}

// ターゲットCのPairImagesを取得する
PairImages* KinManager::GetPairImagesTargetC(){
  return m_pTargetCPairImage;
}

// ターゲットCの目的捕獲数を返す
int KinManager::GetNumberOfTargetC() const
{
  return m_targetCNum;
}

// nameがターゲットの菌の種類の名前であれば真を返す
bool KinManager::IsTargetName( const std::string& name ) const
{
  if(name == m_targetAName ||
     name == m_targetBName ||
     name == m_targetCName){
    return true;
  }
  return false;
}

// シャーレにいる菌をカウントする
int KinManager::GetNumberOfKinInShale() const
{
  int count = 0;
  for(int i = 0; i < mKinVector.size();i++){
    if( mKinVector[i]->IsState(Kin::schale) ){ count++; }
  }
  return count;
}

// 捕獲された（シャーレの中にいる）ターゲットAの数を返す
int KinManager::GetNumberOfTargetAInSchale() const {
  int count = 0;
  for(int i = 0; i < mKinVector.size(); i++){
    if( mKinVector[i]->IsState(Kin::schale) ){
      if(mKinVector[i]->IsName(m_targetAName)){
        count++;
      }
    }
  }
  return count;
}

// ターゲットAがクリア条件の捕獲数を満たしていれば真を返す
bool KinManager::_IsClearTargetA() const {
  if( m_targetANum <= GetNumberOfTargetAInSchale() ){
    return true;
  }
  return false;
}

// 捕獲された（シャーレの中にいる）ターゲットBの数を返す
int KinManager::GetNumberOfTargetBInSchale() const {
  int count = 0;
  for(int i = 0; i < mKinVector.size(); i++){
    if( mKinVector[i]->IsState(Kin::schale) ){
      if(mKinVector[i]->IsName(m_targetBName)){
        count++;
      }
    }
  }
  return count;
}

// ターゲットBがクリア条件の捕獲数を満たしていれば真を返す
bool KinManager::_IsClearTargetB() const {
  if( m_targetBNum <= GetNumberOfTargetBInSchale() ){
    return true;
  }
  return false;
}

// 捕獲された（シャーレの中にいる）ターゲットCの数を返す
int KinManager::GetNumberOfTargetCInSchale() const {
  int count = 0;
  for(int i = 0; i < mKinVector.size(); i++){
    if( mKinVector[i]->IsState(Kin::schale) ){
      if(mKinVector[i]->IsName(m_targetCName)){
        count++;
      }
    }
  }
  return count;
}

// ターゲットCがクリア条件の捕獲数を満たしていれば真を返す
bool KinManager::_IsClearTargetC() const
{
  if( m_targetCNum <= GetNumberOfTargetCInSchale() ){
    return true;
  }
  return false;
}

