/* Project:		GSMPre
   File Name:	LevelChoose.c
   Author:		Xinrea
   Date:		2017-6-4
   Purpose:		LEVELCHOOSE */

#include "LevelChoose.h"
#include "stdio.h"
#include "GameStateList.h"
#include "GameStateManager.h"
#include "System.h"
#include "inc/AEEngine.h"
#include "Input.h"
#include "inc/fmod.h"
#pragma comment (lib, "lib/fmod_vc.lib")
#pragma comment (lib, "lib/Alpha_Engine.lib")
extern FILE* fp;
//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct postion {
	float pos_x;
	float pos_y;
};
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static AEGfxVertexList*	pBackground;
static AEGfxTexture *MainBackground;
static AEGfxVertexList* pMenue1;
static AEGfxVertexList* pMenue2;
static AEGfxTexture* MenueTexture;
static AEGfxTexture *help_Texture[3];
static AEGfxTexture *about_Texture[3];
static AEGfxTexture *choose_Texture[5];
static AEGfxVertexList* pMesh_reply;			//答题后选择界面
static AEGfxVertexList* pMesh_choice_s;
static AEGfxVertexList* pMesh_choice_l;
static AEGfxTexture *choice_s_Texture;
static int currentframe;
static FMOD_SYSTEM* mbgm;
static FMOD_SOUND* main;
static FMOD_CREATESOUNDEXINFO* smain;
static FMOD_CHANNELGROUP* channelgroup;
static FMOD_CHANNEL* channel;
static FMOD_RESULT result;
static void* extradriverdata;
static float volume;
static struct postion pos[5]; //开始，选关，帮助，退出，关于
static int pos_state;
static int help_choose;                         // 在帮助界面里的选择
static int help;								// 判断是否打开帮助页面
static int about;								// 判断是否打开关于页面
static int about_choose;						// 在关于界面里的选择
static int choose_level;
static int choose_level_c;
static float choice_l_X[4], choice_l_Y[4];       // 记录选关操作选择的位置
static float choice_s_X[4], choice_s_Y[4];       // 记录答题后操作选择的位置
static float choice_a_X[4], choice_a_Y[4];       // 关于界面内操作选择的位置
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------ ------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
void LoadC(void){
	AEGfxMeshStart();//添加背景图片
	AEGfxTriAdd(
		-800.0f, -450.0f, 0xFFFF0000, 0.0f, 1.0f,
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		800.0f, 450.0f, 0xFFFF0000, 1.0f, 0.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	pBackground = AEGfxMeshEnd();

	AEGfxMeshStart();//添加菜单效果1
	AEGfxTriAdd(
		-800.0f, -450.0f, 0xFFFF0000, 0.0f, 1.0f,
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		800.0f, 450.0f, 0xFFFF0000, 1.0f, 0.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	pMenue1 = AEGfxMeshEnd();

	AEGfxMeshStart();//添加菜单效果2
	AEGfxTriAdd(
		-800.0f, -450.0f, 0xFFFF0000, 0.0f, 1.0f,
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		800.0f, 450.0f, 0xFFFF0000, 1.0f, 0.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	pMenue2 = AEGfxMeshEnd();

	AEGfxMeshStart();
	AEGfxTriAdd(
		-800.0f, -450.0f, 0xFFFF0000, 0.0f, 1.0f,
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		800.0f, 450.0f, 0xFFFF0000, 1.0f, 0.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	pMesh_reply = AEGfxMeshEnd();

	AEGfxMeshStart();
	AEGfxTriAdd(
		-800.0f, -450.0f, 0xFFFF0000, 0.0f, 1.0f,
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		800.0f, 450.0f, 0xFFFF0000, 1.0f, 0.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	pMesh_choice_s = AEGfxMeshEnd();

	AEGfxMeshStart();
	AEGfxTriAdd(
		-800.0f, -450.0f, 0xFFFF0000, 0.0f, 1.0f,
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	AEGfxTriAdd(
		800.0f, -450.0f, 0xFFFF0000, 1.0f, 1.0f,
		800.0f, 450.0f, 0xFFFF0000, 1.0f, 0.0f,
		-800.0f, 450.0f, 0xFFFF0000, 0.0f, 0.0f);
	pMesh_choice_l = AEGfxMeshEnd();

	MainBackground = AEGfxTextureLoad("res\\main.png");
	MenueTexture = AEGfxTextureLoad("res\\highlight.png");
	help_Texture[0] = AEGfxTextureLoad("res\\help1.png");
	help_Texture[1] = AEGfxTextureLoad("res\\help2.png");
	help_Texture[2] = AEGfxTextureLoad("res\\help3.png");
	about_Texture[0] = AEGfxTextureLoad("res\\Member1.png");
	about_Texture[1] = AEGfxTextureLoad("res\\Member2.png");
	about_Texture[2] = AEGfxTextureLoad("res\\Member3.png");
	choose_Texture[0] = AEGfxTextureLoad("res\\Choose1.png");
	choose_Texture[1] = AEGfxTextureLoad("res\\Choose2.png");
	choose_Texture[2] = AEGfxTextureLoad("res\\Choose3.png");
	choose_Texture[3] = AEGfxTextureLoad("res\\Choose4.png");
	choose_Texture[4] = AEGfxTextureLoad("res\\Choose5.png");
	choice_s_Texture = AEGfxTextureLoad("res\\choice_s.png");
	FMOD_System_Create(&mbgm);
	FMOD_System_Init(mbgm, 32, FMOD_INIT_NORMAL, extradriverdata);
	FMOD_System_CreateSound(mbgm, "res\\mp3\\main.mp3", FMOD_LOOP_NORMAL, smain, &main);
    fprintf(fp, "Choose:Load\n");
}
void IniC(void){
	currentframe = 0;
	channel = 0;
	volume = 0.5f;
	pos_state = 0;
	help_choose = 0;                    // 在帮助界面里的选择
	help = 0;
	about_choose = 0;
	about = 0;
	choose_level = 0;
	choose_level_c = 0;

	pos[0].pos_x = 136.0f;
	pos[0].pos_y = -136.0f;
	pos[1].pos_x = 0.0f;
	pos[1].pos_y = 0.0f;
	pos[2].pos_x = 272.0f;
	pos[2].pos_y = 0.0f;
	pos[3].pos_x = 272.0f;
	pos[3].pos_y = -272.0f;
	pos[4].pos_x = 0.0f;
	pos[4].pos_y = -272.0f;

	// 小选择框位置
	choice_s_X[0] = 0.0f;
	choice_s_Y[0] = 0.0f;
	choice_s_X[1] = 180.0f;
	choice_s_Y[1] = 0.0f;
	choice_s_X[2] = 0.0f;
	choice_s_Y[2] = -155.0f;
	choice_s_X[3] = 180.0f;
	choice_s_Y[3] = -155.0f;

	// level小选择框位置
	choice_l_X[0] = 0.0f;
	choice_l_Y[0] = 0.0f;
	choice_l_X[1] = 180.0f;
	choice_l_Y[1] = 0.0f;
	choice_l_X[2] = 0.0f;
	choice_l_Y[2] = -155.0f;
	choice_l_X[3] = 180.0f;
	choice_l_Y[3] = -155.0f;

	// 关于界面里的选择框位置
	choice_a_X[0] = -106.0f;
	choice_a_Y[0] = -206.0f;
	choice_a_X[1] = 90.0f;
	choice_a_Y[1] = -206.0f;
	choice_a_X[2] = 290.0f;
	choice_a_Y[2] = -206.0f;

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	FMOD_System_PlaySound(mbgm, main, channelgroup, FALSE, &channel);
	FMOD_Channel_SetVolume(channel, volume);

    fprintf(fp, "Choose:Ini\n");
}
void UpdateC(void)
{
	if (KeyPressed[KeyESC]) {
		State.Next = State_Quit;
		GS = GS_Quit;
	}

	if(!choose_level&&!about&&!help&&KeyPressed[KeyReturn]){
		switch (pos_state)
		{
		case 0: State.Next = State_Level1; GS_L1; break;
		case 1: choose_level = 1; help = 0; about = 0; KeyPressed[KeyReturn] = 0; break;
		case 2: choose_level = 0; help = 1; about = 0; KeyPressed[KeyReturn] = 0; break;
		case 3: State.Next = State_Quit; GS = GS_Quit; break;
		case 4: choose_level = 0; help = 0; about = 1; KeyPressed[KeyReturn] = 0; break;
		default:break;
		}
	}

	if (!choose_level && !about && !help&&KeyPressed[KeyUp]) {
		if (pos_state == 0) pos_state = 1;
		if (pos_state == 3) pos_state = 0;
		if (pos_state == 4) pos_state = 0;
	}

	if (!choose_level && !about && !help&&KeyPressed[KeyDown]) {
		if (pos_state == 0) pos_state = 4;
		if (pos_state == 1) pos_state = 0;
		if (pos_state == 2) pos_state = 0;
	}

	if (!choose_level && !about && !help&&KeyPressed[KeyLeft]) {
		if (pos_state == 0) pos_state = 1;
		if (pos_state == 2) pos_state = 1;
		if (pos_state == 3) pos_state = 4;
	}

	if (!choose_level && !about && !help&&KeyPressed[KeyRight]) {
		if (pos_state == 0) pos_state = 2;
		if (pos_state == 1) pos_state = 2;
		if (pos_state == 4) pos_state = 3;
	}

	//小选择框选择切换
	if (!choose_level&&help&&!about) {
		if ((KeyPressed[KeyUp]) || (KeyPressed[KeyDown]))
		{
			help_choose = (help_choose + 2) % 4;
		}
		if ((KeyPressed[KeyLeft]) || (KeyPressed[KeyRight]))
		{
			switch (help_choose) {
			case 0: help_choose = 1; break;
			case 1: help_choose = 0; break;
			case 2: help_choose = 3; break;
			case 3: help_choose = 2; break;
			}
		}
	}

	if (choose_level&&!help && !about) {
		if ((KeyPressed[KeyUp]) || (KeyPressed[KeyDown]))
		{
			choose_level_c = (choose_level_c + 2) % 4;
		}
		if ((KeyPressed[KeyLeft]) || (KeyPressed[KeyRight]))
		{
			switch (choose_level_c) {
			case 0: choose_level_c = 1; break;
			case 1: choose_level_c = 0; break;
			case 2: choose_level_c = 3; break;
			case 3: choose_level_c = 2; break;
			}
		}
	}

	if (!choose_level&&help && !about&&KeyPressed[KeyReturn]) {
		if (help == 1) {				//处于第一张帮助界面
			switch (help_choose) {
			case 0: {

				break;
			}		//上一页（无效）
			case 1: {
				help = help + 1;
				break;
			}		//下一页
			case 2: {
				help = 0;
				about = 0;
				KeyPressed[KeyReturn] = 0;
				break;
			}		//返回
			case 3: {
				break;	//成员
			}
			}
		}
		else if (help == 2) {
			switch (help_choose) {
			case 0: {
				help = help - 1;
				break;
			}		//上一页
			case 1: {
				help = help + 1;
				break;
			}		//下一页
			case 2: {
				help = 0;
				about = 0;
				KeyPressed[KeyReturn] = 0;
				break;
			}		//返回
			case 3: {
				break;	//成员
			}
			}
		}
		else {
			switch (help_choose) {
			case 0: {
				help = help - 1;
				break;
			}		//上一页
			case 1: {

				break;
			}		//下一页（无效）
			case 2: {
				help = 0;
				about = 0;
				KeyPressed[KeyReturn] = 0;
				break;
			}		//返回
			case 3: {
				break;	//成员
			}
			}
		}
	}

	if (choose_level&&!help && !about&&KeyPressed[KeyReturn]) {
		if (choose_level == 1) {				//处于第一张选关界面
			switch (choose_level_c) {
			case 0: {

				break;
			}		//上一页（无效）
			case 1: {
				choose_level = choose_level + 1;
				break;
			}		//下一页
			case 2: {
				State.Next = State_Level1;
				GS_L1;
				break;
			}		
			case 3: {
				choose_level = 0;
				help = 0;
				about = 0;
				KeyPressed[KeyReturn] = 0;
				break;	
			}
			}
		}
		else if (choose_level == 2) {
			switch (choose_level_c) {
			case 0: {
				choose_level = choose_level - 1;
				break;
			}		//上一页
			case 1: {
				choose_level = choose_level + 1;
				break;
			}		//下一页
			case 2: {
				State.Next = State_Level2;
				GS_L2;
				break;
			}		
			case 3: {
				choose_level = 0;
				help = 0;
				about = 0;
				KeyPressed[KeyReturn] = 0;
				break;	
			}
			}
		}
		else if (choose_level == 3) {
			switch (choose_level_c) {
			case 0: {
				choose_level = choose_level - 1;
				break;
			}		//上一页
			case 1: {
				choose_level = choose_level + 1;
				break;
			}		//下一页
			case 2: {
				State.Next = State_Level3;
				GS_L3;
				break;
			}
			case 3: {
				choose_level = 0;
				help = 0;
				about = 0;
				KeyPressed[KeyReturn] = 0;
				break;
			}
			}
		}
		else if (choose_level == 4) {
			switch (choose_level_c) {
			case 0: {
				choose_level = choose_level - 1;
				break;
			}		//上一页
			case 1: {
				choose_level = choose_level + 1;
				break;
			}		//下一页
			case 2: {
				break;
			}
			case 3: {
				choose_level = 0;
				help = 0;
				about = 0;
				KeyPressed[KeyReturn] = 0;
				break;
			}
			}
		}
		else {
			switch (choose_level_c) {
			case 0: {
				choose_level = choose_level - 1;
				break;
			}		//上一页
			case 1: {

				break;
			}		//下一页（无效）
			case 2: {
				break;
			}		
			case 3: {
				choose_level = 0;
				help = 0;
				about = 0;
				KeyPressed[KeyReturn] = 0;
				break;	
			}
			}
		}
	}

	//在关于页面里的选项切换
	if (!choose_level&&about && !help) {
		if (KeyPressed[KeyLeft])
			about_choose = (about_choose + 2) % 3;
		if (KeyPressed[KeyRight])
			about_choose = (about_choose + 1) % 3;
	}

	//在关于页面里的选择
	if (!choose_level&&about && !help&&KeyPressed[KeyReturn])
	{
		if (about == 1) {				//关于第一页
			switch (about_choose) {
			case 0: {
				break;
			}	//上一页（无效）
			case 1: {
				help = 0;
				about = 0;
				KeyPressed[KeyReturn] = 0;
				break;
			}	//返回
			case 2: {
				about = about + 1;
				break;
			}	//下一页
			}
		}
		else if (about == 2) {
			switch (about_choose) {
			case 0: {
				about = about - 1;
				break;
			}	//上一页
			case 1: {
				help = 0;
				about = 0;
				KeyPressed[KeyReturn] = 0;
				break;
			}	//返回
			case 2: {
				about = about + 1;
				break;
			}	//下一页
			}
		}
		else {
			switch (about_choose) {
			case 0: {
				about = about - 1;
				break;
			}	//上一页
			case 1: {
				help = 0;
				about = 0;
				KeyPressed[KeyReturn] = 0;
				break;
			}	//返回
			case 2: {
				break;
			}	//下一页(无效)
			}
		}
	}
	// 输入重置
	Input_Initialize();

	// 签到
	fprintf(fp, "Choose:Update\n");
}
void DrawC(void){
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0.0f, 0.0f);
	AEGfxTextureSet(MainBackground, 0.0f, 0.0f);
	AEGfxSetTransparency(1);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	AEGfxMeshDraw(pBackground, AE_GFX_MDM_TRIANGLES);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(pos[pos_state].pos_x, pos[pos_state].pos_y);
	AEGfxTextureSet(MenueTexture, 0.0f, 0.0f);
	AEGfxSetTransparency(1.0f);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
	AEGfxMeshDraw(pMenue1, AE_GFX_MDM_TRIANGLES);

	if (choose_level) {
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(0.0f, 0.0f);
		AEGfxTextureSet(choose_Texture[choose_level - 1], 0.0f, 0.0f);
		AEGfxSetTransparency(1);
		AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
		AEGfxMeshDraw(pMesh_reply, AE_GFX_MDM_TRIANGLES);

		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(choice_l_X[choose_level_c], choice_l_Y[choose_level_c]);
		AEGfxTextureSet(choice_s_Texture, 0.0f, 0.0f);
		AEGfxSetTransparency(1);
		AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
		AEGfxMeshDraw(pMesh_choice_l, AE_GFX_MDM_TRIANGLES);
	}

	if (help) {
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(0.0f, 0.0f);
		AEGfxTextureSet(help_Texture[help - 1], 0.0f, 0.0f);
		AEGfxSetTransparency(1);
		AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
		AEGfxMeshDraw(pMesh_reply, AE_GFX_MDM_TRIANGLES);

		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(choice_s_X[help_choose], choice_s_Y[help_choose]);
		AEGfxTextureSet(choice_s_Texture, 0.0f, 0.0f);
		AEGfxSetTransparency(1);
		AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
		AEGfxMeshDraw(pMesh_choice_s, AE_GFX_MDM_TRIANGLES);
	}

	if (about) {
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(0.0f, 0.0f);
		AEGfxTextureSet(about_Texture[about - 1], 0.0f, 0.0f);
		AEGfxSetTransparency(1);
		AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
		AEGfxMeshDraw(pMesh_reply, AE_GFX_MDM_TRIANGLES);

		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetPosition(choice_a_X[about_choose], choice_a_Y[about_choose]);
		AEGfxTextureSet(choice_s_Texture, 0.0f, 0.0f);
		AEGfxSetTransparency(1);
		AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);
		AEGfxMeshDraw(pMesh_choice_s, AE_GFX_MDM_TRIANGLES);
	}

	currentframe++;
	currentframe = currentframe % 60;

    fprintf(fp, "Choose:Draw\n");
}
void FreeC(void){
	FMOD_Sound_Release(main);
	FMOD_System_Release(mbgm);
    fprintf(fp, "Choose:Free\n");
}
void UnloadC(void){
    AEGfxMeshFree(pBackground);
	AEGfxMeshFree(pMenue1);
	AEGfxMeshFree(pMenue2);
	AEGfxTextureUnload(MainBackground);
	AEGfxTextureUnload(MenueTexture);
	FMOD_System_Close(mbgm);
    fprintf(fp, "Choose:Unload\n");
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
