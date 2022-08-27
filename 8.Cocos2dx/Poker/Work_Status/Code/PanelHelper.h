/********************************************************************
	file name:	PanelHelper.h
	
	purpose:	Panel 관련 helper
*********************************************************************/
#pragma once
#include "W_RewardInfo.pb.h"
#include "NotiData.pb.h"
#include "W_NotiData.pb.h"
#include "ModelListPartPanel.h"

#define DynamicPush_Zorder 64
//#define NO_USE_CHECK

class PanelHelper
{
public:
	static int getUiState();		//현재 current UI 관련 해서 
	static void setLobbyTopUi();

	//패널 방침은 있으면 갱신 , 없으면 만들어서 갱신한다.
	static void pushShopPanel();	//상점 push(맴버쉽
	static void pushMissionPanel();	//기록실창 push
	static void pushEventMissionPanel();
	static void pushFriendPanel();	//친구추가 push
	static void pushRecordPanel();	// 기록창 push
	static void pushInventoryPanel();	//보관함 push

	//TopUI 패널
	static void pushMyHomePanel();	//마이룸 push
	static void pushBankPanel();	//은행 관련 push
	
	static void pushRubyShopPanel();	//루비 상점 ( 상점창 쓰는데 있는면 tab 만 바꾼다.
	static void pushMemberShipShopPanel();	//맴버쉽 상점 ( 상점창 쓰는데 있는면 tab 만 바꾼다.
	static void pushCharacterShopPanel();	//캐릭터 상점 ( 상점창 쓰는데 있는면 tab 만 바꾼다.

	//channel
	static void pushChannelListPanel();
	static void pushTournamentPanel();
	static void pushServivalPanel();
	static void pushReplayPanel();	//챔피언스tv

	static void pushLetterPanel();	//기존 편지가 인벤토리로 이동

	static void pushRankingTutorialPanel();	//??
	static void pushReplayBoxPanel();
	static Panel* pushGoldRefilPopupPanel();// 좌절 금지
	static void pushBigBonusPanel();	//빅팟보너스
	static void pushFreeMoviePanel();	//무료 충전소
	static Panel* pushAttendPopupPanel();	//7일 출석창

	static Panel* pushJackpotPanel();	//한정 상품 구매창 잭팟 
	static Panel* pushMadePanel();
	static Panel* pushMadePanelB();


	static void pushAllinPopupPanel();	//올인됐을때 나오는 창
	
	static Panel* pushSeasonResultPanel();
	static Panel* pushWeeklyResultPanel();
	static void pushVipInfoPanel();

	static Panel* pushNotiFocusPanel(NotiData_eNotiType type);		//lobbyScene 에서 나오는 팝업창
	static void pushNotiChannelListPanel(NotiData_eNotiType type);
	static Panel* pushRatingUpPanel();	//등급업할때 나오는 창

	//보상 확인창
	static void pushCommonRewardPanel(string title, string content, W_RewardInfo rewardInfo);
	static void pushCommonRewardPanel(string title, string content);
	static void pushLetterRewardPanel(W_RewardInfo rewardInfo);	//편지 보상
	static void pushEventRewardPanel(W_RewardInfo rewardInfo);	//이벵트  보상
	static void pushRubyRewardPanel(int rewardRuby, int rubyId , bool isFirstBuy);	
	static void pushReceiveAllPanel(W_RewardInfo rewardInfo);			//전체 보상
	static void pushBigPotRewardPanel(string desc, W_RewardInfo rewardInfo);
	static void pushLimitedAllRewardPanel(W_RewardInfo rewardInfo);
	static void pushFirstBuyRewardPanel(W_RewardInfo rewardInfo);
	static void pushTourRewardPanel(W_RewardInfo rewardInfo);


	static void pushConfirmCharacterPanel(int characterId);	//캐릭터 구매창
	static void pushModellsBackPopupPanel(int modelListIdx, MODEL_TYPE modelType, TAB_TYPE tapType); // 모델별 더 보기 리스트 창
	static void pushConfirmMemberShipPanel(int membershipId);	//맴버쉽 구매 확인창
	static void pushCharacterBuySucessPanel(int characterInfoId , int useRuby);	//캐릭터 구매 성공창
	static void pushMemberShipBuySucessPanel(int membetrShipId, W_RewardInfo rewardInfo);	//맴버쉽 구매 성공창
	
	static void pushSeasonRankInfoPanel();
	

	static void pushCouponPanel();
	static void pushModelShotPanel(int tIdx,int idx);
	static void pushGamePlayTimePanel();
	static void pushAnnounceNotiPanel(string str);

	//로딩페이지
	static Panel* pushLoadingPanel(string str);	
	static void popLoadingPanel(float delayTime = 0.f);

	//심플 팝업
	static void pushSimpleConfirmPopupPanel(string text, string title);

	static Panel* pushRoomListPanel();

	static void pushFirstBuyPanel();	//첫 구매

	static void pushConfirmSkinPanel(int skinId);
	static void pushSkinBuySucessPanel(int characterInfoId, int useRuby);	//캐릭터 구매 성공창
	
	static void pushSurvivalWindowMainPanel();
	static void pushBankInResultPanel(int64 changeMoney);
	static void pushBankOutResultPanel(int64 changeMoney);
	static void pushBuyMemberNoticePanel();

	static Panel* pushBuyMemberConfirmPanel(string message);	// 맴버쉽 알림

	static Panel* pushNotiPanel(W_NotiData notidata);

	//토너먼트 씨드 머니 상승창
	static void pushSeedMoneyUpPanel(int64 seedMoney, bool isMax);	//seed 값 , max 인가.
	//토너먼트 Rearrange 창
	static void pushRearrangePanel();	//정렬이 끝났다.
	static void pushRearrangeCompletePanel();	//정렬이 끝났다.
	static void pushTouramentRankPanel(int rank);	//토너먼트 랭크창

	static void setCompactImage(Widget* img, const CCRect& rtSize);
};