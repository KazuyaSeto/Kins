/**************************************************************************//**
	@file		Application.cpp
	@brief		openFramworksアプリケーションクラス　実装ファイル
	@author		K.Seto
	@date		2011-10-29
	@par		[説明]
				ofBaseAppを継承してopenFrameworksのアプリケーションクラスを作成する。
				アプリケーションの初期化、更新、描画を行う。
				またマウスやキー入力のイベントはこのクラスで受け取る。
*//***************************************************************************/

#include "Application.h"
#include "Sequence/Parent.h"
#include "Mouse.h"
#include "Materials.h"
#include "ColorDefinitions.h"
#include "Misc.h"

namespace {
	static int GAME_FRAME_RATE	= 60;
	static int WINDOW_WIDTH		= 640;
	static int WINDOW_HEIGHT	= 480;
}

//--------------------------------------------------------------
void Application::setup(){
    ofSetFrameRate(GAME_FRAME_RATE);

    m_pParent = new Sequence::Parent;

    m_pMouse = Mouse::Instance();
    m_pMaterials = Materials::Instance();
}

//--------------------------------------------------------------
void Application::update(){
    m_pParent->Update();
    m_pMouse->Update();
    m_pMaterials->Update();
    ofSetWindowShape(WINDOW_WIDTH, WINDOW_HEIGHT);
}

//--------------------------------------------------------------
void Application::draw(){
    ofBackground(GameColor::WHITE);
    ofEnableAlphaBlending();
	m_pParent->Draw();
    ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void Application::keyPressed (int key){
}

//--------------------------------------------------------------
void Application::keyReleased(int key){
}

//--------------------------------------------------------------
void Application::mouseMoved(int x, int y ){
  m_pMouse->SetPos(x,y);
}

//--------------------------------------------------------------
void Application::mouseDragged(int x, int y, int button){
  m_pMouse->SetDraggedPos(x,y,button);
}

//--------------------------------------------------------------
void Application::mousePressed(int x, int y, int button){
  m_pMouse->SetPressedPos(x,y,button);
}

//--------------------------------------------------------------
void Application::mouseReleased(int x, int y, int button){
  m_pMouse->SetReleasedPos(x,y, button);
}

//--------------------------------------------------------------
void Application::windowResized(int w, int h){
}

//--------------------------------------------------------------
void Application::exit(){
    Misc::SafeDelete(m_pParent);
	Mouse::Destroy();
	Materials::Destroy();
}