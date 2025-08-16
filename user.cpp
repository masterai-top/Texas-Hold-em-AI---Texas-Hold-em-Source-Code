#include "context/user.h"
#include "utils/tarslog.h"

namespace game
{
    namespace context
    {
        User::User()
        //: _state(NN_USER_STATE_NORMAL)
        //,_addmultiply(0)
            : _uid(nil_uid)
            , _cid(nil_cid)
            ,_robot(false)
            , _nick("")
            , _url("")
            , _country("")
            , _netbroken(false)
            , _left(false)
            , _pause(false)
            , _gender(0)
              // ,_wealthtype(0)
            , _wealth(0)
            , _diamond(0)
              // ,_ready(false)
              // ,_tpoint(0)
              // ,_delegate(false)
              // ,_notready(0)
              // ,_hasready(false)
            , _timeout(0)
            , _roundtimeout(0)
            , _tuoguan_round(0)
            , _last_play_game(false)
            , _last_join_game(true)
            , _roundoption(false)
            , _tuoguan(false)
            , _prestandup(false)
            , _dzwealth(0)
            , _dzbuychip(0)
            , _dzbuychipclubid(0)
            , _guessnum(0)
            , _guesstype(0)
            , ltakeCoin(0)
            , bAutoSupplement(false)
            , _bApplyed(false)
            , _bSecondApplyed(false)
            , _bIsApplyedBuy(false)
            , _bApplyedExpire(0)
            , _prolongtimes(1)
            , _prolongflag(0)
            , _play_time(0)
            , _robot_take_in(0)
            , _round_bet(0)
            , _bNextStandUp(false)
            , _bPlayGame(false)
            ,_iAiGameRound(0)
            ,_iAiGamePoint(0)
            ,_lRountInitChip(0)
            ,_bShowAchievement(false)
            ,_bAuthBB(false)
            ,_iLeagueLevel(0)
            ,_iSneak(0)
        {
            // _round_point.clear();
            this->_boxinfo.set_allboxnum(30);
            this->_boxinfo.set_allround(8);
            this->_boxinfo.set_curspeed(100);
            this->_vPauseEffectTime.clear();
            roundInit();
        }

        User::User(guid_t uid, cid_t cid, bool robot)
            : _uid(uid)
            , _cid(cid)
            , _robot(robot)
            , _nick("")
            , _url("")
            , _country("")
            , _netbroken(false)
            , _left(false)
            , _pause(false)
            , _gender(0)
            , _wealth(0)
            , _diamond(0)
            , _timeout(0)
            , _roundtimeout(0)
            , _tuoguan_round(0)
            , _last_play_game(false)
            , _last_join_game(true)
            , _roundoption(false)
            , _tuoguan(false)
            , _prestandup(false)
            , _dzwealth(0)
            , _dzbuychip(0)
            , _dzbuychipclubid(0)
            , _guessnum(0)
            , _guesstype(0)
            , ltakeCoin(0)
            , bAutoSupplement(false)
            , _bApplyed(false)
            , _bSecondApplyed(false)
            , _bIsApplyedBuy(false)
            , _bApplyedExpire(0)
            , _prolongtimes(1)
            , _prolongflag(0)
            , _showComCard(false)
            , _freeze(false)
            , _play_time(0)
            , _robot_take_in(0)
            , _round_bet(0)
            , _bNextStandUp(false)
            , _bPlayGame(false)
            ,_lBuyInNum(0)
            ,_lBuyInCount(0)
            ,_lStartTakenIn(0)
            ,_iAiGameRound(0)
            ,_iAiGamePoint(0)
            ,_lRountInitChip(0)
            ,_bShowAchievement(false)
            ,_bAuthBB(false)
            ,_iLeagueLevel(0)
            ,_lPauseStartTime(0)
            ,_lPauseLastTime(0)
            ,_lRoundTakenIn(0)
            ,_iSneak(0)
        {
            // _round_point.clear();
            this->_boxinfo.set_allboxnum(30);
            this->_boxinfo.set_allround(8);
            this->_boxinfo.set_curspeed(100);
            this->_vPauseEffectTime.clear();
            roundInit();
        }


        void User::roundInit()
        {
            // DLOG_TRACE("User::roundInit");
            this->_cards.clear();
            this->_done             = false;
            this->_midsit           = false;
            this->_active           = false;
            this->_fpoint           = 0;
            this->_fold             = false;
            this->_allin            = false;
            this->_showcard.clear();
            this->_act              = nil_act;
            this->_option           = nil_act;
            this->_simple_act       = nil_act;
            this->_max_raise_num    = 0;
            this->_changenum        = 0;
            this->_cardtype         = nil_nntype;
            this->_prolongtimes     = 1;
            this->_prolongflag      = 0;
            this->_showComCard      = false;
            this->_freeze           = false;
            this->_wincards.clear();
            this->_hd_point         = 0;
            this->_freeNum          = 0;
            this->_delaycal        = false;
            this->_round_bet       = 0;
            this->_robotUserParam.clear();
            this->_iRoundRaiseCount = 0;
            this->_diff = 0;
/*            this->_lRountInitChip = 0;*/
            this->_lSelfBetTo = 0;
            this->_lSeltStreeBetTo = 0;
            this->_vBetType.clear();
            this->_mActionData.clear();
            this->_prestandup = false;
            this->_lInsureBuy = 0;
            this->_lInsureWin = 0;
            this->_iSneak = 0;
            this->_vecSneakCard2U.clear();
            this->_cur_bet = 0;
          
        }

        // int User::getWinCount() const
        // {
        //     int count = 0;

        //     for(std::map<int, int>::const_iterator it = _round_point.begin();
        //         it != _round_point.end();
        //         it++)
        //     {
        //         if(it->second > 0)
        //         {
        //             count++;
        //         }
        //     }

        //     return count;
        // }

        // int User::getMaxWin() const
        // {
        //     int max = 0;

        //     for(std::map<int, int>::const_iterator it = _round_point.begin();
        //         it != _round_point.end();
        //         it++)
        //     {
        //         if(it->second > max)
        //         {
        //             max = it->second;
        //         }
        //     }

        //     return max;
        // }

        User::~User()
        {
        }
    };
};
