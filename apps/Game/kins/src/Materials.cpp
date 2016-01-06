/**************************************************************************//**
	@file		Materials.cpp
	@brief		画像やサウンドなどを一括で読み込んで素材として保持しているクラス 実装ファイル		
	@author		K.Seto
	@date		2011-10-23 
	@par		[説明]
				このゲームプレイ中に使われている素材は多くないので
				フォント、サウンド、画像は読み込んでこのクラスが保持している。
				メンバ関数を通して各素材クラスのポインタを取得してアクセスできる。
*//***************************************************************************/
#include "Materials.h"
#include "PairImages.h"
#include "Misc.h"
#include <cstdlib>

namespace{
	// フォント関連の定数
	static const char* FONT_FILENAME = "verdana.ttf";
	static const unsigned int FONT_SIZE_S = 12;
	static const unsigned int FONT_SIZE_M = 18;
	static const unsigned int FONT_SIZE_L = 48;

	// サウンド関連の定数
	static const char* SOUND_TITLE_FILENAME = "sound/title.ogg";
	static const char* SOUND_PLAY_FILENAME = "sound/play.ogg";
	static const char* SOUND_END_FILENAME = "sound/end.ogg";
	static const float SOUND_VOLUME = 0.5;

};

// inctance()内の条件式のために初期化
Materials *Materials::m_pInstance = 0; 

// インスタンスを返す
Materials* Materials::Instance(){
	// インスタンスがない場合はインスタンスを生成する
	if(!m_pInstance){
		m_pInstance = new Materials();
	}
	return m_pInstance;
}

// 更新関数
void Materials::Update(){
	// none
}

// フォントクラスを返す 
ofTrueTypeFont* Materials::GetSSizeFont(){ return &m_sSizeFont; }
ofTrueTypeFont* Materials::GetMSizeFont(){ return &m_mSizeFont; }
ofTrueTypeFont* Materials::GetLSizeFont(){ return &m_lSizeFont; }

// サウンドクラスを取得する
ofSoundPlayer* Materials::GetSoundTitle(){ return &soundTitle; };
ofSoundPlayer* Materials::GetSoundPlay(){ return &soundPlay; };
ofSoundPlayer* Materials::GetSoundEnd(){ return &soundEnd; };

// 菌の名前から対応した菌の画像ペアクラスを取得する
PairImages* Materials::GetKinPairImageByKey(const string& kinName){
	return m_kinImagesMap[kinName];
}

// コンストラクタ
Materials::Materials(){

	// フォントを初期化
	m_sSizeFont.loadFont(FONT_FILENAME,FONT_SIZE_S);
	m_mSizeFont.loadFont(FONT_FILENAME,FONT_SIZE_M);
	m_lSizeFont.loadFont(FONT_FILENAME,FONT_SIZE_L);
	// BGMを初期化
	soundTitle.loadSound(SOUND_TITLE_FILENAME);
	soundPlay.loadSound(SOUND_PLAY_FILENAME);
	soundEnd.loadSound(SOUND_END_FILENAME);
	soundTitle.setLoop(true);
	soundPlay.setLoop(true);
	soundEnd.setLoop(true);
	soundTitle.setVolume(SOUND_VOLUME);
	soundPlay.setVolume(SOUND_VOLUME);
	soundEnd.setVolume(SOUND_VOLUME);

	// 画像を読み込んで同じ種類の画像のペアをマップに登録する
	daruma1.loadImage("kin/daruma1.png");
	daruma2.loadImage("kin/daruma2.png");
	m_kinImagesMap.insert( map<string, PairImages*>::value_type( "daruma", new PairImages(&daruma1, &daruma2) ) );
	futago1.loadImage("kin/futago1.png");
	futago2.loadImage("kin/futago2.png");
	m_kinImagesMap.insert( map<string, PairImages*>::value_type( "futago", new PairImages(&futago1,&futago2) ) );
	gohonashi1.loadImage("kin/gohonashi1.png");
	gohonashi2.loadImage("kin/gohonashi2.png");
	m_kinImagesMap.insert( map<string, PairImages*>::value_type( "gohonashi", new PairImages(&gohonashi1,&gohonashi2) ) );
	hashibiro1.loadImage("kin/hashibiro1.png");
	hashibiro2.loadImage("kin/hashibiro2.png");
	m_kinImagesMap.insert( map<string, PairImages*>::value_type( "hashibiro", new PairImages(&hashibiro1,&hashibiro2) ) );
	kadosikaku1.loadImage("kin/kadosikaku1.png");
	kadosikaku2.loadImage("kin/kadosikaku2.png");
	m_kinImagesMap.insert( map<string, PairImages*>::value_type( "kadosikaku", new PairImages(&kadosikaku1,&kadosikaku2) ) );
	kuma1.loadImage("kin/kuma1.png");
	kuma2.loadImage("kin/kuma2.png");
	m_kinImagesMap.insert( map<string, PairImages*>::value_type( "kuma", new PairImages(&kuma1,&kuma2) ) );
	mitugo1.loadImage("kin/mitugo1.png");
	mitugo2.loadImage("kin/mitugo2.png");
	m_kinImagesMap.insert( map<string, PairImages*>::value_type( "mitugo", new PairImages(&mitugo1,&mitugo2) ) );
	rarmen1.loadImage("kin/rarmen1.png");
	rarmen2.loadImage("kin/rarmen2.png");
	m_kinImagesMap.insert( map<string, PairImages*>::value_type( "rarmen", new PairImages(&rarmen1,&rarmen2) ) );
	raten1.loadImage("kin/raten1.png");
	raten2.loadImage("kin/raten2.png");
	m_kinImagesMap.insert( map<string, PairImages*>::value_type( "raten", new PairImages(&raten1,&raten2) ) );
	sikaku1.loadImage("kin/sikaku1.png");
	sikaku2.loadImage("kin/sikaku2.png");
	m_kinImagesMap.insert( map<string, PairImages*>::value_type( "sikaku", new PairImages(&sikaku1,&sikaku2) ) );
	sippo1.loadImage("kin/sippo1.png");
	sippo2.loadImage("kin/sippo2.png");
	m_kinImagesMap.insert( map<string, PairImages*>::value_type( "sippo", new PairImages(&sippo1,&sippo2) ) );
	takoashi1.loadImage("kin/takoashi1.png");
	takoashi2.loadImage("kin/takoashi2.png");
	m_kinImagesMap.insert( map<string, PairImages*>::value_type( "takoashi", new PairImages(&takoashi1,&takoashi2) ) );

}

// デストラクタ
Materials::~Materials(){
	std::map<string, PairImages*>::iterator iter = m_kinImagesMap.begin();
	while( iter != m_kinImagesMap.end() )
	{
		Misc::SafeDelete( (*iter).second );
		++iter;
	}
}

// インスタンスを破棄
void Materials::Destroy(){
	if(m_pInstance != 0){
		delete m_pInstance;
	}
	m_pInstance = 0;
}
