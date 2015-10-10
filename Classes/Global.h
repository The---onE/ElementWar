#pragma once

#include "cocos2d.h"
USING_NS_CC;

using namespace std;

//#include "XMX_Vibrator.h" //震动器

//#include "cocostudio/CocoStudio.h"
//#include "ui/CocosGUI.h"
//#include "SimpleAudioEngine.h"
//using namespace CocosDenshion;

const int VIBRATE_TIME = 48; //震动时间

// extern Size visibleSize;
// extern Point origin; //应在AppDelegate.cpp中定义全局变量，并在applicationDidFinishLaunching()中初始化
// //visibleSize = Director::getInstance()->getVisibleSize();
// //origin = Director::getInstance()->getVisibleOrigin();

const int WIDTH = 1280; //屏幕宽度
const int HEIGHT = 720; //屏幕高度

const Size visibleSize = Size(WIDTH, HEIGHT); 
const Point origin = Point(0, 0);

const float DATUM = HEIGHT; //长度基准
const float DEFAULT_WIDTH = 1280; //默认屏幕宽度
const float PARAM = (DATUM / DEFAULT_WIDTH); //速度标准化参数

//#define SETSIZE(SPRITE,SIZE) ((SPRITE)->setScale(DATUM*(SIZE)/(SPRITE)->getContentSize().height)) //为Sprite等设置相对于长度基准的大小
void setSize(Node* s, float size);

int randNum(int size, int probability[]);

/*#define KEYBOARD_FUNCTION void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);\
void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

#define KEYBOARD_LISTENER(CLASS) EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();\
keyboardListener->onKeyPressed = CC_CALLBACK_2(CLASS::onKeyPressed, this); \
keyboardListener->onKeyReleased = CC_CALLBACK_2(CLASS::onKeyReleased, this); \
Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);*/
