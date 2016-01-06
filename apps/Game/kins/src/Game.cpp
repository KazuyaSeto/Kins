/**************************************************************************//**
	@file		Game.cpp
	@brief		ゲームプレイを管理するクラス　実装ファイル
	@author		K.Seto
	@date		2011-10-24
	@par		[説明]
				ゲームプレイを制御するクラス。
				ゲームステージのスタートからクリアまでの表現する。
				ステージは外部ファイルから初期設定を読み込んで構成する。
*//***************************************************************************/
#include "Game.h"

#include "StageData.h"
#include "Materials.h"
#include "Mouse.h"
#include "ToolBox.h"
#include "kin.h"
#include "kinManager.h"
#include "ClickButton.h"
#include "Misc.h"
#include "ColorDefinitions.h"

#include <algorithm>
// ゲームクラスの各種設定、初期化する。

namespace {
	static const int DISPLAY_WIDTH = 640;
	static const int DISPLAY_HEIGHT = 480;

	static const char* SCHALE_IMAGAE_FILE_NAME = "schale.png";

	// Returnボタンの設定
	static const char* RETURN_TO_TITLE_BUTTON_LABEL = "Return to Title";
	static const int RETURN_BUTTON_WIDTH = 150;
	static const int RETURN_BUTTON_HEIGHT = 30;
	
	// Pauseボタンの設定
	static const char* PAUSE_BUTTOM_LABEL = "Pause";
	static const int PAUSE_BUTTOM_WIDTH = 160;
	static const int PAUSE_BUTTOM_HEIGHT = 82;
	static const int PAUSE_BUTTOM_POSX = 480;
	static const int PAUSE_BUTTOM_POSY = 238;

	static const int dx = 160;
	static const int dy = 160;
	static const int dw = 150;
	static const int dh = 30;

	// ターゲットイメージのファイルの設定
	static const string FILE_PATH = "kin/";
	static const string FILE_EXTENTION = "1.png";
	static const char* TARGET_A_KEY = "targetA";
	static const char* TARGET_B_KEY = "targetB";
	static const char* TARGET_C_KEY = "targetC";


	static const float LINE_WEIGHT = 0.3;	//<! 線の太さ

	static const int SECOND = 60;			//<! 秒
};

//////////////////////////////////////////////////////////////////////////
// Public Function

// コンストラクタ
Game::Game(const std::string& stage):m_frameCount(0)
{
	// 共通素材をシングルトンからセットアップする

	m_pButtonReturn = new ClickButton(	ofGetWidth()/2-dw/2,
										ofGetHeight()/2-dh/2,
										RETURN_BUTTON_WIDTH,
										RETURN_BUTTON_HEIGHT,
										RETURN_TO_TITLE_BUTTON_LABEL );

	m_pButtonPause = new ClickButton(	PAUSE_BUTTOM_POSX,
										PAUSE_BUTTOM_POSY,
										PAUSE_BUTTOM_WIDTH,
										PAUSE_BUTTOM_HEIGHT,
										PAUSE_BUTTOM_LABEL );

	m_pMaterials = Materials::Instance();
	m_pMouse = Mouse::Instance();
	m_pLSizeFont = m_pMaterials->GetLSizeFont();
	m_pMSizeFont = m_pMaterials->GetMSizeFont();
	// 変数を初期化
	m_gameState = GAME_READY;
	m_windowWidth = ofGetWidth();
	m_windowHeight = ofGetHeight();
	// シャーレのイメージをロード
	m_schaleImage.loadImage( SCHALE_IMAGAE_FILE_NAME );


	// ターゲットの数によってイメージをロード
	if(m_targetNum >= 1){
		m_imageTargetA.loadImage( FILE_PATH + m_stageDataLoader.GetStringValue(TARGET_A_KEY) + FILE_EXTENTION);
	}
	if(m_targetNum >= 2){
		m_imageTargetB.loadImage( FILE_PATH + m_stageDataLoader.GetStringValue(TARGET_B_KEY) + FILE_EXTENTION);
	}
	if(m_targetNum == 3){
		m_imageTargetC.loadImage( FILE_PATH + m_stageDataLoader.GetStringValue(TARGET_C_KEY) + FILE_EXTENTION);
	}
	m_loupeTexture.allocate( 64, 64, GL_RGB);
	// ツールボックスを実体化
	m_pToolbox = new ToolBox(dx*3, dy*1, dx, dy);

	m_pKinManager = new KinManager(this, stage);
}

// デストラクタ
Game::~Game()
{

	Misc::SafeDelete(m_pButtonReturn);
	Misc::SafeDelete(m_pButtonPause);

	Misc::SafeDelete(m_pToolbox);
	Misc::SafeDelete(m_pKinManager);
}

// 更新関数
void Game::Update(){
	switch ( m_gameState ) {
	case GAME_READY :
		// READYは数字をカウントしてゲームスタートする。
		// 状態はPLAYに移行
		// GAME_PLAYに移行
		_UpdateGameReady();
		break;

	case GAME_PLAY :
		// PLAYのときはゲームの本体の処理を行う
		// ポーズボタンを押すとPAUSEへ移行
		if( _IsClearedGeme() ){ // TODO
			_SetGameState( GAME_CLEAR );
		}
		if( _IsPressedPauseButton() ){ // TODO
			_SetGameState( GAME_PAUSE );
		}
		_UpdateGamePlay();
		break;

	case GAME_PAUSE :
		// PAUSEのときは再びポーズボタンを押すとPLAYへ移行する
		// また、ポーズメニューの処理を行う
		// ポーズメニューから処理を行う
		if( _IsPressedTitleMenuButton() ){ // TODO
			_SetGameState( GAME_RETURN_TO_TITLE );
		}
		if( _IsPressedPauseButton() ){
			_SetGameState( GAME_PLAY );
		}
		_UpdateGamePause();
		break;

	case GAME_CLEAR :
		// CLEARのときはクリアーメニューの処理を行う
		_UpdateGameClear();
		break;

	case GAME_NONE :
		break;
	default :
		break;
	}
	m_pToolbox->Update();

}

// 描画関数
void Game::Draw(){
	switch ( m_gameState ) {
	case GAME_READY :
		_DrawGameReady();
		break;
	case GAME_PLAY : 
		_DrawGamePlay();
		break;
	case GAME_PAUSE : 
		_DrawGamePause();
		break;
	case GAME_CLEAR : 
		_DrawGameClear();
		break;
	case GAME_NONE :
		break;
	default :
		break;
	}
}

// ツールボックスの状態を取得する
ToolBox::TOOL_STATE Game::GetToolBoxState() const {
	return m_pToolbox->GetToolState();
}

// ゲームの状態を変更
void Game::_SetGameState(GameState InGameState){
	m_gameState = InGameState;
}

// 次のステージに移動するかどうか？
bool Game::IsNextStage() const{
	if(m_gameState == GAME_NEXT_STAGE){
		return true;
	}
	return false;
}

// 描画関数（Ready状態）
void Game::_DrawGameReady(){
	ofSetLineWidth( LINE_WEIGHT );

	_DrawTargetImages();
	_DrawToolBox();
	_DrawSchale();
	_DrawShowcase();
	_DrawCountDown();
}

// 描画関数（Play状態）
void Game::_DrawGamePlay(){
	ofSetLineWidth( LINE_WEIGHT );

	_DrawTargetImages();
	_DrawToolBox();
	_DrawSchale();
	_DrawShowcase();
	if( m_pToolbox->IsLoupe() ){ _DrawLoupe(); };
}

// 描画関数（Pause状態）
void Game::_DrawGamePause(){
	ofSetLineWidth( LINE_WEIGHT );

	_DrawTargetImages();
	_DrawToolBox();
	_DrawSchale();
	_DrawShowcase();
	_DrawPauseMenu();
}

// 描画関数（Clear状態）
void Game::_DrawGameClear(){
	ofSetLineWidth( LINE_WEIGHT );

	_DrawTargetImages();
	_DrawToolBox();
	_DrawSchale();
	_DrawShowcase();
	_DrawStringClear();
}

// 描画関数（Ready状態）
void Game::_UpdateGameReady(){
	const int sec = 60;
	// 五秒経過したらゲームプレイに移行
	if(m_frameCount > sec*5 ){ _SetGameState( GAME_PLAY ); }
	m_frameCount++;
}

// 更新関数（Play状態）
void Game::_UpdateGamePlay(){
	m_pKinManager->Update();
	m_pButtonPause->Update();
}

// 更新関数（Pause状態）
void Game::_UpdateGamePause(){
	m_pButtonReturn->Update();
	m_pButtonPause->Update();
}

// 更新関数（Clear）
void Game::_UpdateGameClear(){
	static int counter = 0;
	m_pKinManager->Update();
	if(counter > 360){
		_SetGameState( GAME_NEXT_STAGE );
		counter = 0;
	}
	counter++;
}

// クリアしたかどうか？
bool Game::_IsClearedGeme() const {
	if(m_pKinManager->IsStageClear()){
		return true;
	}
	return false;
}

// ReturnToTitleボタンが押されたかどうか？
bool Game::IsPressedReturnToTitleButton() const{
	if(m_gameState == GAME_RETURN_TO_TITLE){
		return true;
	}
	return false;
}

// Pauseボタンが押されたかどうか？
bool Game::_IsPressedPauseButton() const{
	if( m_pButtonPause->IsClicked() ){
		return true;
	}
	return false;
}

// タイトルメニュボタンが押されたかどうか？
bool Game::_IsPressedTitleMenuButton() const{
	if( m_pButtonReturn->IsClicked()){
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
// Private Function

// カウントダウンの数字を描画する
void Game::_DrawCountDown(){
	ofPushMatrix();
	ofPushStyle();

	ofSetHexColor(GameColor::BLACK);
	float center_x = m_windowWidth*0.5;
	float center_y = m_windowHeight*0.5;

	if(m_frameCount < SECOND){
		ofRectangle rect = m_pLSizeFont->getStringBoundingBox("Ready",center_x,center_y);
		m_pLSizeFont->drawString("Ready", rect.x - rect.width*0.5, rect.y + rect.height*0.5);
	}else if( m_frameCount < SECOND*2 ){
		ofRectangle rect = m_pLSizeFont->getStringBoundingBox("3",center_x,center_y);
		m_pLSizeFont->drawString("3", rect.x - rect.width*0.5, rect.y + rect.height*0.5);
	}else if( m_frameCount < SECOND*3){
		ofRectangle rect = m_pLSizeFont->getStringBoundingBox("2",center_x,center_y);
		m_pLSizeFont->drawString("2", rect.x - rect.width*0.5, rect.y + rect.height*0.5);
	}else if( m_frameCount < SECOND*4){
		ofRectangle rect = m_pLSizeFont->getStringBoundingBox("1",center_x,center_y);
		m_pLSizeFont->drawString("1", rect.x - rect.width*0.5, rect.y + rect.height*0.5);
	}else if( m_frameCount < SECOND*5){
		ofRectangle rect = m_pLSizeFont->getStringBoundingBox("Go",center_x,center_y);
		m_pLSizeFont->drawString("Go", rect.x - rect.width*0.5, rect.y + rect.height*0.5);
	}

	ofPopStyle();
	ofPopMatrix();
}

//
void Game::_DrawShowcase(){
	ofPushMatrix();
	ofPushStyle();

	m_pKinManager->Draw();

	ofPopStyle();
	ofPopMatrix();
}

// ターゲットの菌をそれおれ描画する
void Game::_DrawTargetImages(){
	ofPushMatrix();
	ofPushStyle();

	ofSetHexColor(GameColor::BLACK);
	ofTranslate(dx*3, 0, 0 );
	ofNoFill();
	ofRect(0,0,dx,dy);

	m_pMSizeFont->drawString("Target!",0,m_pMSizeFont->getLineHeight()*0.5+5.0);
	ofRect(0,0, dx, m_pMSizeFont->getLineHeight() );

	ofTranslate(20,50,0);
	m_pKinManager->GetPairImagesTargetA()->GetFirstImage()->draw(0,0);
	m_pMSizeFont->drawString(ofToString(m_pKinManager->GetNumberOfTargetA()),0, 50 );
	m_pMSizeFont->drawString(ofToString(m_pKinManager->GetNumberOfTargetAInSchale()),0, 100 );
	if(m_pKinManager->GetNumberOfTypesOfTarget() >= 2){
		m_pKinManager->GetPairImagesTargetB()->GetFirstImage()->draw(40,0);
		m_pMSizeFont->drawString(ofToString(m_pKinManager->GetNumberOfTargetB()),40, 50 );
		m_pMSizeFont->drawString(ofToString(m_pKinManager->GetNumberOfTargetBInSchale()),40, 100 );
	}
	if(m_pKinManager->GetNumberOfTypesOfTarget() >= 3){
		m_pKinManager->GetPairImagesTargetC()->GetFirstImage()->draw(80,0);
		m_pMSizeFont->drawString(ofToString(m_pKinManager->GetNumberOfTargetC()),80, 50 );
		m_pMSizeFont->drawString(ofToString(m_pKinManager->GetNumberOfTargetCInSchale()),80, 100 );
	}

	ofPopStyle();
	ofPopMatrix();
}
void Game::_DrawToolBox(){
	ofPushMatrix();
	ofPushStyle();

	m_pToolbox->Draw();
	m_pButtonPause->Draw();

	ofPopStyle();
	ofPopMatrix();
}

void Game::_DrawSchale(){
	ofPushMatrix();
	ofPushStyle();

	ofTranslate(dx*3, dy*2, 0 );
	m_schaleImage.draw(0, 0, dx, dy);
	ofNoFill();
	ofSetHexColor(GameColor::BLACK);
	ofRect(0, 0, dx, dy);
	m_pMSizeFont->drawString("Schale",0,m_pMSizeFont->getLineHeight()*0.5+5.0);
	ofRect(0, 0, dx, m_pMSizeFont->getLineHeight() );

	ofPopStyle();
	ofPopMatrix();
}

void Game::_DrawLoupe(){
	ofPushMatrix();
	ofPushStyle();
	const int load_size = 64;
	const int draw_size = 128;
	const int space_size = 4;

	m_loupeTexture.loadScreenData(m_pMouse->GetPosX()-load_size, m_pMouse->GetPosY()-load_size, load_size,load_size);
	ofSetHexColor(GameColor::BLACK);
	ofRect(m_pMouse->GetPosX(), m_pMouse->GetPosY()-load_size,draw_size,draw_size);
	ofSetHexColor(GameColor::WHITE);
	m_loupeTexture.draw(m_pMouse->GetPosX(), m_pMouse->GetPosY()-load_size,draw_size,draw_size);
	ofSetHexColor(GameColor::BLACK);
	ofNoFill();
	ofRect(m_pMouse->GetPosX()-load_size, m_pMouse->GetPosY()-load_size, load_size,load_size);
	ofRect(m_pMouse->GetPosX(), m_pMouse->GetPosY()-load_size,draw_size,draw_size);
	ofPopStyle();
	ofPopMatrix();
}

void Game::_DrawStringClear(){
	ofPushMatrix();
	ofPushStyle();

	ofSetHexColor(GameColor::BLACK);
	float center_x = m_windowWidth*0.5;
	float center_y = m_windowHeight*0.5;
	ofRectangle rect = m_pLSizeFont->getStringBoundingBox("StageClear",center_x,center_y);
	m_pLSizeFont->drawString("StageClear", rect.x - rect.width*0.5, rect.y + rect.height*0.5);
	ofPopStyle();
	ofPopMatrix();
}

void Game::_DrawPauseMenu(){
	ofPushMatrix();
	ofPushStyle();
	int dw = 150;
	int dh = 30;
	ofSetHexColor(GameColor::BLACK);
	ofRect(ofGetWidth()/2-2-dw/2,ofGetHeight()/2-2-dh/2,dw+4,dh+4);

	ofSetHexColor(GameColor::WHITE);
	ofRect(ofGetWidth()/2-dw/2,ofGetHeight()/2-dh/2,150,30);
	m_pButtonReturn->Draw();

	ofPopStyle();
	ofPopMatrix();
}