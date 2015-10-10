#pragma once

#include "cocos2d.h"
USING_NS_CC;

using namespace std;

//#include "XMX_Vibrator.h" //����

//#include "cocostudio/CocoStudio.h"
//#include "ui/CocosGUI.h"
//#include "SimpleAudioEngine.h"
//using namespace CocosDenshion;

const int VIBRATE_TIME = 48; //��ʱ��

// extern Size visibleSize;
// extern Point origin; //Ӧ��AppDelegate.cpp�ж���ȫ�ֱ���������applicationDidFinishLaunching()�г�ʼ��
// //visibleSize = Director::getInstance()->getVisibleSize();
// //origin = Director::getInstance()->getVisibleOrigin();

const int WIDTH = 1280; //��Ļ���
const int HEIGHT = 720; //��Ļ�߶�

const Size visibleSize = Size(WIDTH, HEIGHT); 
const Point origin = Point(0, 0);

const float DATUM = HEIGHT; //���Ȼ�׼
const float DEFAULT_WIDTH = 1280; //Ĭ����Ļ���
const float PARAM = (DATUM / DEFAULT_WIDTH); //�ٶȱ�׼������

//#define SETSIZE(SPRITE,SIZE) ((SPRITE)->setScale(DATUM*(SIZE)/(SPRITE)->getContentSize().height)) //ΪSprite����������ڳ��Ȼ�׼�Ĵ�С
void setSize(Node* s, float size);

int randNum(int size, int probability[]);

/*#define KEYBOARD_FUNCTION void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);\
void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

#define KEYBOARD_LISTENER(CLASS) EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();\
keyboardListener->onKeyPressed = CC_CALLBACK_2(CLASS::onKeyPressed, this); \
keyboardListener->onKeyReleased = CC_CALLBACK_2(CLASS::onKeyReleased, this); \
Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);*/
