#include "pch.h"
#include "LobbyTourRewardListPanel.h"
#include "HeroUtil.h"
#include "GameDataManager.h"
#include "GameStringDepot.h"


LobbyTourRewardListPanel::LobbyTourRewardListPanel()
{
	InitPanel();
}

LobbyTourRewardListPanel::~LobbyTourRewardListPanel()
{

}

void LobbyTourRewardListPanel::InitPanel()
{
	construct(getMxmlPath() + "dmy_tournament_round.mxml");
	mGameName = getLabel("txt_info1");
	mSeedMoney = getLabel("txt_seedmoney");
	mBasicMoney = getLabel("txt_basicmoney");


	CCPoint _pos = getDummy("dmy_tournament_round_slot1").origin;
	_pos.y = -_pos.y;
	mReward1 = new LobbyTourRewardContentPanel(); 
	addChild(mReward1);
	mReward1->release();
	mReward1->setPosition(_pos);
	mReward1->getImage("skel_icon")->setScale(0.5f);

	_pos = getDummy("dmy_tournament_round_slot2").origin;
	_pos.y = -_pos.y;
	mReward2 = new LobbyTourRewardContentPanel();
	addChild(mReward2);
	mReward2->release();
	mReward2->setPosition(_pos);
	mReward2->getImage("skel_icon")->setScale(0.5f);

	_pos = getDummy("dmy_tournament_round_slot3").origin;
	_pos.y = -_pos.y;
	mReward3 = new LobbyTourRewardContentPanel();
	addChild(mReward3);
	mReward3->release();
	mReward3->setPosition(_pos);
	mReward3->getImage("skel_icon")->setScale(0.5f);

	mRewards.push_back(mReward1);
	mRewards.push_back(mReward2);
	mRewards.push_back(mReward3);

}

void LobbyTourRewardListPanel::setTourStepInfo(W_TourStepInfo tourStepInfo)
{
	//시드 머니 출력
	string seedMoneyStr;
	seedMoneyStr = "[" + GameStringDepot::getSingletonPtr()->getString("TXT_SEED_MONEY_LABEL") + "]";
	seedMoneyStr += GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(tourStepInfo.seedmoney()), 1);
	
	mSeedMoney->setString(seedMoneyStr.c_str());
	
	string basicMoneyStr;
	basicMoneyStr = "[" + GameStringDepot::getSingletonPtr()->getString("TXT_STANDARD_MONEY_LABEL") + "]";
	basicMoneyStr += GameDataManager::getSingletonPtr()->GetKoreanLiteral(StringConverter::toString(tourStepInfo.startmoney()), 1);
	
	mBasicMoney->setString(basicMoneyStr.c_str());

	for (int i = 0; i < tourStepInfo.rewardinfo_size(); i++)
	{
		if (i < mRewards.size()) {
			W_RewardInfo rewardInfo = tourStepInfo.rewardinfo(i);
			int64 paymoney = 0;
			int trophy = 0;
			for (int j = 0; j < rewardInfo.rewardset_size(); j++)
			{
				if (rewardInfo.rewardset(j).type() == GAMEMONEY)
				{
					paymoney = rewardInfo.rewardset(j).amount();
				}
				else if (rewardInfo.rewardset(j).type() == REPUTE)
				{
					trophy = rewardInfo.rewardset(j).amount();
				}
			}
			mRewards[i]->setRewardData(i, paymoney, trophy);
		}
		
	}

	string underColor = "";
	string gameName = "";
	switch (GameDataManager::getSingletonPtr()->getGameKind())
	{
	case GameKind::GAMEKIND_7POKER:
		underColor = "5f0808";
		gameName = GameStringDepot::getSingletonPtr()->getString("TXT_SEVEN_POKER");
		break;
	case GameKind::GAMEKIND_HIGH_LOW:
		underColor = "08225F";
		gameName = GameStringDepot::getSingletonPtr()->getString("TXT_HIGHLOW");
		break;
	case GameKind::GAMEKIND_BADUKI:
		underColor = "1b510e";
		gameName = GameStringDepot::getSingletonPtr()->getString("TXT_BADUGI");
		break;
	case GameKind::GAMEKIND_HOLDEM:
		underColor = "085e55";
		gameName = GameStringDepot::getSingletonPtr()->getString("TXT_HOLDEM");
		break;
	}
	string gameNameStr;
	gameNameStr = "[" + gameName + "]";
	mGameName->setString(gameNameStr.c_str());
	mGameName->setStrokeColor((ccColor4B)StringConverter::parseColor3B(underColor));
	mSeedMoney->setStrokeColor((ccColor4B)StringConverter::parseColor3B(underColor));
	mBasicMoney->setStrokeColor((ccColor4B)StringConverter::parseColor3B(underColor));
}
