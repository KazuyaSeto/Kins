/**************************************************************************//**
	@file		main.cpp
	@brief		�A�v���P�[�V�������쐬���ăX�^�[�g����B		
	@author		K.Seto
	@date		2011-10-24 
	@par		[����]
				openFrameworks�̃A�v���[�P�[�V������ݒ�A�������Q�[�����J�n����B
*//***************************************************************************/
#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>

#include "ofMain.h"
#include "Application.h"
#include "ofAppGlutWindow.h"

namespace {
	static int WINDOW_WIDTH = 640;
	static int WINDOW_HEIGHT = 480;
}

//========================================================================
int main( ){
	// ���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ofAppGlutWindow window;
	ofSetupOpenGL(&window, WINDOW_WIDTH, WINDOW_HEIGHT, OF_WINDOW); // <-------- setup the GL context
	ofSetWindowTitle("kins");

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:

	ofRunApp( new Application());

}
