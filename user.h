#pragma once

#include <string>
#include <map>

#include "common/nndef.h"
#include "utils/tarslog.h"
#include "dz_club.pb.h"

using namespace nndef;
using namespace nnuser;
using namespace nncard;
using namespace nninvalid;

namespace game
{
    namespace context
    {
        class User
        {
            //
            friend class Context;

        public:
            //机器人配置
            struct RobotUserParam
            {
                float wRate; //随机胜率
                bool isBB;  //是否大盲位
                bool isSelfAdd;//本轮自己是否加注
                bool isSelfBet;//本轮自己是否下注

                void clear()
                {
                    wRate = 0;
                    isBB = false;
                    isSelfAdd = false;
                    isSelfBet = false;
                }
            };

        private:
            User();

        public:
            explicit User(guid_t uid, cid_t cid, bool robot = false);
            ~User();

        public:
            void roundInit();

        public:
            guid_t getUid() const
            {
                return _uid;
            }
            cid_t getCid() const
            {
                return _cid;
            }
            void setCid(cid_t cid)
            {
                _cid = cid;
            }
            bool isRobot() const
            {
                return _robot;
            }
            void setRobot(bool robot, long robotid = 0)
            {
                _robot = robot;
                if(robot){
                    _robotID= robotid;
                }
            }

            long getRobotID() const
            {
                return _robotID;
            }

            inline vecc_t const &getVecCards() const
            {
                return _cards;
            }
            inline vecc_t &refVecCards()
            {
                return _cards;
            }

            void setDone(bool done)
            {
                _done = done;
            }
            bool isDone() const
            {
                return _done;
            }

            void setNetBroken(bool netbroken)
            {
                _netbroken = netbroken;
            }
            bool isNetBroken() const
            {
                return _netbroken;
            }

            void setLeft(bool left)
            {
                _left = left;
            }
            bool isLeft() const
            {
                return _left;
            }

            void setPause(bool pause)
            {
                _pause = pause;
            }
            bool isPause() const
            {
                return _pause;
            }

            void setGender(int gender)
            {
                _gender = gender;
            }
            int getGender() const
            {
                return _gender;
            }

            // void setWealthType(int wealthtype) { _wealthtype = wealthtype; }
            // int getWealthType() const { return _wealthtype; }

            void setWealth(long wealth)
            {
                _wealth = (wealth < 0 ? 0 : wealth);
            }
            long getWealth() const
            {
                return _wealth;
            }

            void setDiamond(long diamond)
            {
                _diamond = (diamond < 0 ? 0 : diamond);
            }
            long getDiamond() const
            {
                return _diamond;
            }

            void setClubCoin(long value)
            {
                _clubCoin = (value < 0 ? 0 : value);
            }
            long getClubCoin() const
            {
                return _clubCoin;
            }

            void setNick(std::string nick)
            {
                _nick = nick;
            }
            std::string getNick() const
            {
                return _nick;
            }

            void setUrl(std::string url)
            {
                _url = url;
            }
            std::string getCountry() const
            {
                return _country;
            }

            void setCountry(std::string country)
            {
                _country = country;
            }
            std::string getUrl() const
            {
                return _url;
            }

            void setProfitChange(int fpoint)
            {
                _fpoint = fpoint;
            }
            int getProfitChange() const
            {
                return _fpoint;
            }

            void setMidSit(bool midsit)
            {
                _midsit = midsit;
            }
            bool isMidSit() const
            {
                return _midsit;
            }

            void setActive(bool active)
            {
                _active = active;
            }

            bool isActive() const
            {
                return _active;
            }

            void setDZWealth(long dzwealth)
            {
                _dzwealth = dzwealth;
                // DLOG_TRACE("set dzwealth : " << dzwealth);
            }
            void addDZWealth(long dzwealth)
            {
                _dzwealth += dzwealth;
                // DLOG_TRACE("add dzwealth : " << dzwealth);
            }
            long getDZWealth() const
            {
                return _dzwealth;
            }

            void setBuyChip(long buychip)
            {
                _dzbuychip = buychip;
            }
            long getBuyChip() const
            {
                return _dzbuychip;
            }

            void setBuyChipClubId(long cid)
            {
                _dzbuychipclubid = cid;
            }
            long getBuyChipClubId() const
            {
                return _dzbuychipclubid;
            }

            void setAllIn(bool allin)
            {
                _allin = allin;
            }
            bool isAllIn() const
            {
                return _allin;
            }

            void setFold(bool fold)
            {
                _fold = fold;
            }
            bool isFold() const
            {
                return _fold;
            }

            void updateShowCard(card_t hdcard, bool bEnd)
            {
                auto it = std::find_if(_showcard.begin(), _showcard.end(), [hdcard](card_t card)->bool{
                    return hdcard == card;
                });
                if(it != _showcard.end())
                {
                    if(!bEnd)//结算后不能取消了
                    {
                       _showcard.erase(it);
                    }
                }
                else
                {
                    _showcard.push_back(hdcard);
                }
                
            }
            bool checkShowCard(card_t hdcard) const
            {
                return _showcard.end() != std::find_if(_showcard.begin(), _showcard.end(), [hdcard](card_t card)->bool{
                    return hdcard == card;
                });
            }

            bool isShowCard() const
            {
                return _showcard.size() > 0;
            }

            void setAct(E_NN_ACT act)
            {
                _act = act;
            }
            E_NN_ACT getAct() const
            {
                return _act;
            }

            void setOption(E_NN_ACT option)
            {
                _option = option;
            }
            E_NN_ACT getOption() const
            {
                return _option;
            }

            void setSimpleAct(E_NN_ACT act)
            {
                _simple_act = act;
            }
            E_NN_ACT getSimpleAct() const
            {
                return _simple_act;
            }

            void setMinRaiseNum(long num)
            {
                _min_raise_num = num;
            }
            long getMinRaiseNum() const
            {
                return _min_raise_num;
            }
            void setMaxRaiseNum(long num)
            {
                _max_raise_num = num;
            }
            long getMaxRaiseNum() const
            {
                return _max_raise_num;
            }

            void setTimeOut(int timeout)
            {
                _timeout = timeout;
            }
            int getTimeOut() const
            {
                return _timeout;
            }

            bool isRoundUOp()
            {
                return _roundoption;
            }
            void setRoundUOp(bool flag)
            {
                _roundoption = flag;
            }
            bool isTuoGuan() const
            {
                return _tuoguan;
            }
            void setTuoGuan(bool flag)
            {
                _tuoguan = flag;
            }
            bool isPreStandUp()
            {
                return _prestandup;
            }
            void setPreStandUp(bool flag)
            {
                _prestandup = flag;
            }
            int getTuoGuanRound() const
            {
                return _tuoguan_round;
            }
            void setTuoGuanRound(int round)
            {
                _tuoguan_round = round;
            }

            void setRoundTimeOut(int roundtimeout)
            {
                _roundtimeout = roundtimeout;
            }
            int getRoundTimeOut() const
            {
                return _roundtimeout;
            }

            bool isLastPlayGame()
            {
                return _last_play_game;
            }
            void setLastPlayGame(bool flag)
            {
                _last_play_game = flag;
            }

            bool isLastJoinGame()
            {
                return _last_join_game;
            }
            void setLastJoinGame(bool flag)
            {
                _last_join_game = flag;
            }

            void setChangeNum(long changenum)
            {
                _changenum = changenum;
            }
            long getChangeNum() const
            {
                return _changenum;
            }

            void setCardType(E_NN_TYPE cardtype)
            {
                _cardtype = cardtype;
            }
            E_NN_TYPE getCardType() const
            {
                return _cardtype;
            }

            inline vecc_t const &getVecWinCards() const
            {
                return _wincards;
            }
            inline vecc_t &refVecWinCards()
            {
                return _wincards;
            }

            void setGuessNum(int guessnum)
            {
                _guessnum = guessnum;
            }
            int getGuessNum() const
            {
                return _guessnum;
            }

            void setGuessType(int guesstype)
            {
                _guesstype = guesstype;
            }
            int getGuessType() const
            {
                return _guesstype;
            }

            void setTakeCoin(long coin)
            {
                ltakeCoin = coin;
            }
            long getTakeCoin() const
            {
                return ltakeCoin;
            }

            void setMinTakeCoin(long coin)
            {
                lminTakeCoin = coin;
            }
            long getMinTakeCoin() const
            {
                return lminTakeCoin;
            }

            void setMaxTakeCoin(long coin)
            {
                lmaxTakeCoin = coin;
            }
            long getMaxTakeCoin() const
            {
                return lmaxTakeCoin;
            }

            void setAutoSupplement(bool bauto)
            {
                bAutoSupplement = bauto;
            }
            bool getAutoSupplement()
            {
                return bAutoSupplement;
            }

            void setAutoAlignment(bool bauto)
            {
                bAutoAlignment = bauto;
            }
            bool getAutoAlignment()
            {
                return bAutoAlignment;
            }

            void setProlongTimes(int times)
            {
                _prolongtimes = times;
            }
            void incProlongTimes()
            {
                ++_prolongtimes;
            }
            void doubleProlongTimes()
            {
                _prolongtimes += 15;
            }
            int getProlongTimes()
            {
                return _prolongtimes;
            }

            void setProlongFlag(int flag)
            {
                _prolongflag = flag;
            }
            int getProlongFlag()
            {
                return _prolongflag;
            }
            void setShowComCard()
            {
                _showComCard = true;
            }
            bool isShowComCard()
            {
                return _showComCard;
            }
            
            void setFreeze(bool value)
            {
                _freeze = value;
            }
            bool isFreeze()
            {
                return _freeze;
            }
            void setTokenTime(int time)
            {
                _tokentime = time;
            }
            int getTokenTime()
            {
                return _tokentime;
            }

            void addPlayTimes()
            {
                _play_time += 1;
            }
            int getPlayTimes() const
            {
                return _play_time;
            }

            void setRobotTakeIn(long value)
            {
                _robot_take_in = value;
            }
            long getRobotTakenIn()
            {
                return _robot_take_in;
            }

            void setHDPoint(int value)
            {
                _hd_point = value;
            }
            int getHDPoint()
            {
                return _hd_point;
            }

            void setFreeNum(long value)
            {
                _freeNum = value;
            }
            long getFreeNum()
            {
                return _freeNum;
            }

            bool isDelayCal()
            {
                return _delaycal;
            }
            void setDelayCal(bool delaycal)
            {
                _delaycal = delaycal;
            }

            void setRoundBet(long value)
            {
                _round_bet = value;
            }
            void addRoundBet(long value)
            {
                _round_bet += value;
            }
            long getRoundBet()
            {
                return _round_bet;
            }

            void setCurBet(long value)
            {
                _cur_bet = value;
            }

            long getCurBet()
            {
                return _cur_bet;
            }

            template<typename T>
            void setRobotUserParam(const string varName, const string opType, T value)
            {
                if(varName == "wRate")
                {
                    _robotUserParam.wRate = value;
                }
                else if(varName == "isBB")
                {
                    _robotUserParam.isBB = value;
                }
                else if(varName == "isSelfAdd")
                {
                    _robotUserParam.isSelfAdd = value;
                }
                else if(varName == "isSelfBet")
                {
                    _robotUserParam.isSelfBet = value;
                }
                return;
            }

            template<typename T>
            T getRobotUserParam(const string varName)
            {
                if(varName == "wRate")
                {
                    return _robotUserParam.wRate;
                }
                else if(varName == "isBB")
                {
                    return _robotUserParam.isBB;
                }
                else if(varName == "isSelfAdd")
                {
                    return _robotUserParam.isSelfAdd;
                }
                else if(varName == "isSelfBet")
                {
                    return _robotUserParam.isSelfBet;
                }
                return 0;
            }

            RobotUserParam &getRobotUserParam()
            {
                return _robotUserParam;
            }
            void setNextStandUp(bool flag)
            {
                _bNextStandUp = flag;
            }
            bool getNextStandUp()
            {
                return _bNextStandUp;
            }
            void setPlayGameFlag(bool flag)
            {
                _bPlayGame = flag;
            }
            bool getPlayGameFlag()
            {
                return _bPlayGame;
            }
            void setBuyInNum(long value)
            {
                _lBuyInNum = value;
                _lBuyInCount++;
            }
            long getBuyInNum()
            {
                return _lBuyInNum;
            }
            long getBuyInCount()
            {
                return _lBuyInCount;
            }
            long getStartTakenIn()
            {
                return _lStartTakenIn;
            }
            void setStartTakenIn(long value)
            {
                _lStartTakenIn = value;
            }
            void setAiGameRound(int value){
                _iAiGameRound = value;
            }
            int getAiGameRound(){
                return _iAiGameRound;
            }
            void setAiGamePoint(int value){
                _iAiGamePoint = value;
            }
            int getAiGamePoint(){
                return _iAiGamePoint;
            }
            int getRoundRaiseCount()
            {
                return _iRoundRaiseCount;
            }
            void setRoundRaiseCount(int value)
            {
                _iRoundRaiseCount = value;
            }
            void setDiff(int value)
            {
                _diff = value;
            }
            int getDiff()
            {
                return _diff;
            }

            void setRoundInitChip(long value)
            {
                _lRountInitChip = value;
            }
            long getRoundInitChip()
            {
                return _lRountInitChip;
            }
            void setSelfBetTo(long value)
            {
                _lSelfBetTo = value;
            }
            long getSelfBetTo()
            {
                return _lSelfBetTo;
            }
            void setSeltStreeBetTo(long value)
            {
                _lSeltStreeBetTo = value;
            }
            long getSeltStreeBetTo()
            {
                return _lSeltStreeBetTo;
            }
            void addUserBetType(int type)
            {
                _vBetType.push_back(type);
            }
            std::vector<int>& getBetType()
            {
                return _vBetType;
            }

            void addActionData(int process, int action)
            {
                auto it = _mActionData.find(process);
                if(it != _mActionData.end())
                {
                    auto itt = it->second.find(action);
                    if(itt != it->second.end())
                    {
                        itt->second++;
                    }
                    else
                    {
                        it->second.insert(std::make_pair(action, 1));
                    }
                }
                else
                {
                    std::map<int, int> sub;
                    sub.insert(std::make_pair(action, 1));
                    _mActionData.insert(std::make_pair(process, sub));
                }
            }

            std::map<int, std::map<int, int>>& getActionData()
            {
                return _mActionData;
            }

            void setShowAchievement(bool flag)
            {
                _bShowAchievement = flag;
            }
            bool isShowAchievement()
            {
                return _bShowAchievement;
            }

            void setAuthBB(bool flag)
            {
                _bAuthBB = flag;
            }
            bool istAuthBB()
            {
                return _bAuthBB;
            }

            void setLeagueLevel(int level)
            {
                _iLeagueLevel = level;
            }
            int getLeagueLevel()
            {
                return _iLeagueLevel;
            }

            void setBoxInfo(XGameDZProtoClub::NN_sBoxInfo const &info)
            {
                _boxinfo.CopyFrom(info);
            }
            XGameDZProtoClub::NN_sBoxInfo const &getBoxInfo() const
            {
                return _boxinfo;
            }

            int getRound() const
            {
                return _boxinfo.curround();
            }

            long getInsureBuy()
            {
                return _lInsureBuy;
            }
            void setInsureBuy(long value)
            {
                _lInsureBuy = value;
            }
            long getInsureWin()
            {
                return _lInsureWin;
            }
            void setInsureWin(long value)
            {
                _lInsureWin = value;
            }
            inline vecc_t const &getInsureCards() const
            {
                return _insurecards;
            }
            inline vecc_t &refInsureCards()
            {
                return _insurecards;
            }

            void clearPauseEffectTime()
            {
                _lPauseStartTime = 0;
                _vPauseEffectTime.clear();
            }

            void setPauseStartTime()
            {
                _lPauseStartTime = TNOW;
                _lPauseLastTime = _lPauseStartTime;
            }

            long getPauseStartTime()
            {
                return _lPauseStartTime;
            }

            void setPauseLastTime()
            {
                _lPauseLastTime = TNOW;
            }

            void setPauseLastTime(long value)
            {
                _lPauseLastTime = value;
            }

            long getPauseLastTime()
            {
                return _lPauseLastTime;
            }

            void setPauseEffectTime(int base_value, int extra_value, int extra_id)
            {
                _vPauseEffectTime.clear();
                _vPauseEffectTime.push_back(base_value);
                _vPauseEffectTime.push_back(extra_value);
                _vPauseEffectTime.push_back(extra_id);
            }

            std::vector<int> getVecPauseEffectTime()
            {
                return _vPauseEffectTime;
            }

            long getPauseEndTime()
            {
                long last_time = _lPauseStartTime;
                for(auto subTime :_vPauseEffectTime) 
                {
                    last_time += subTime;
                }
                return last_time;
            }

            long remianPauseBaseTime()
            {
                if(_vPauseEffectTime.size() != 3)
                {
                    return 0;
                }
                long cost_time = TNOW - _lPauseStartTime;
                if(cost_time > _vPauseEffectTime[0])
                {
                    return 0;
                }
                return _vPauseEffectTime[0] - cost_time;
            }

            long remianPauseExtraTime()
            {
                if(_vPauseEffectTime.size() != 3)
                {
                    return 0;
                }
                long cost_time = TNOW - _lPauseStartTime;
                if(cost_time > _vPauseEffectTime[0] + _vPauseEffectTime[1])
                {
                    return 0;
                }
                if(cost_time < _vPauseEffectTime[0])
                {
                    return _vPauseEffectTime[1];
                }
                if(cost_time > _vPauseEffectTime[0])
                {
                    return _vPauseEffectTime[0] + _vPauseEffectTime[1] - cost_time;
                }
                return 0;
            }

            int getPauseExtraTimeID()
            {
                if(_vPauseEffectTime.size() != 3)
                {
                    return 0;
                }

                return _vPauseEffectTime[2];
            }

            void setRoundTakenIn(long value)
            {
                _lRoundTakenIn = value;
            }

            long getRoundTakenIn()
            {
                return _lRoundTakenIn;
            }

            void setSneak(int value)
            {
                _iSneak = value;
            }

            int getSneak()
            {
                return _iSneak;
            }

            void addSneakCard2U(long uid)
            {
                auto it = std::find(_vecSneakCard2U.begin(), _vecSneakCard2U.end(), uid);
                if(it == _vecSneakCard2U.end())
                {
                    _vecSneakCard2U.push_back(uid);
                }
            }

            vector<long>& getSneakCard2U()
            {
                return _vecSneakCard2U;
            }

            void setApplyed(bool value)
            {
                _bApplyed = value;
            }

            bool getApplyed()
            {
                return _bApplyed;
            }

            void setSecondApplyed(bool value)
            {
                _bSecondApplyed = value;
            }

            bool getSecondApplyed()
            {
                return _bSecondApplyed;
            }

            void setIsApplyedBuy(bool value)
            {
                _bIsApplyedBuy = value;
            }

            bool isApplyedBuy()
            {
                return _bIsApplyedBuy;
            }

            void setApplyedExpire(int value)
            {
                _bApplyedExpire = value;
            }
            int getApplyedExpire()
            {
                return _bApplyedExpire;
            }

            // 跑马
            inline std::vector<E_NN_TYPE> const &getVecPaomaCardTypes() const
            {
                return _paomaCardTypes;
            }
            inline std::vector<E_NN_TYPE> &refVecPaomaCardTypes()
            {
                return _paomaCardTypes;
            }
            inline std::vector<vecc_t> const &getVecPaomaWinCards() const
            {
                return _paomaWinCards;
            }
            inline std::vector<vecc_t> &refVecPaomaWinCards()
            {
                return _paomaWinCards;
            }
            inline std::vector<long> const &getVecPaomaWins() const
            {
                return _paomaWins;
            }
            inline std::vector<long> &refVecPaomaWins()
            {
                return _paomaWins;
            }
            inline void pushPaomaWin(long value)
            {
                _paomaWins.push_back(value);
            }
        protected:
            // E_NN_USER_STATE _state;

            vecc_t  _cards;     //手牌
            // vecc_t  _tempcards;

            bool    _done;
            bool    _midsit;
            bool    _active;//是否活跃此局

            // int     _bankermultiply;
            // int     _betmultiply;
            // int     _addmultiply;
            // int     _minmultiply;

            // int     _cpoint; //每局输赢变化
            // cid_t   _raisecid;
            // int     _raisemultiply;
            // int     _epoint; //输赢变化
            int     _fpoint; //抽成
            bool    _fold;   //弃牌
            bool    _allin;        //allin标记
            vecc_t    _showcard;     //显示手牌
            long    _changenum;    //
            E_NN_TYPE _cardtype;   //牌型
            vecc_t  _wincards;     //牌面

        protected:
            guid_t          _uid;   //uid
            cid_t           _cid;   //位置id
            bool            _robot; //是否机器人
            long            _robotID;
            std::string     _nick;  //玩家昵称
            std::string     _url;   //玩家头像url
            std::string     _country;//国籍
            bool            _netbroken; //掉线标记
            bool            _left;      //离开
            bool            _pause;     //挂机
            int             _gender;    //性别
            //int             _wealthtype;      //玩家财富类型 2-钻石，3-俱乐部币，4-金币
            long            _wealth;            //玩家财富(金币)
            long            _diamond;           //玩家财富(钻石)
            long            _clubCoin;          //玩家财富(俱乐部币B币)

        protected:
            // bool            _ready;
            // int             _tpoint;   //总分
            // bool            _delegate; //玩家财富
            // int             _notready;
            // bool            _hasready; //是否准备过
            int             _timeout;  //超时次数
            int             _roundtimeout; //整局超时次数
            int             _tuoguan_round; //托管局数
            bool            _last_play_game; //是否参与上局游戏
            bool            _last_join_game; //是否上一局加入游戏
            bool            _roundoption;
            bool            _tuoguan;
            bool            _prestandup;// 即将退出

            E_NN_ACT        _act;
            E_NN_ACT        _option;
            E_NN_ACT        _simple_act; //简介的下注行为
            long            _max_raise_num;// 最大加注数
            long            _min_raise_num;// 最小加注数(奥马哈有限注用)


        protected:
            // std::map<int, int> _round_point;    //每局输赢记录
            long            _dzwealth;          //玩家财富
            long            _dzbuychip;         //买入金币
            long            _dzbuychipclubid;   //买入时用的俱乐部ID
            int             _guessnum;
            int             _guesstype;

        protected:
            long ltakeCoin;        // 买入金额
            bool bAutoSupplement;  // 自动补充
            bool bAutoAlignment;   // 自动补齐
            long lminTakeCoin;     // 最少买入
            long lmaxTakeCoin;     // 最大买入
            bool _bApplyed;        // 是否在审核期
            bool _bSecondApplyed;  // 补充筹码中
            bool _bIsApplyedBuy;   // 是否是审核的被充
            int _bApplyedExpire;   // 审核时间戳

        protected:
            int _prolongtimes;     // 行动延长次数
            int _prolongflag;      // 行动延长标记，0--不延长，1--延长
            bool _showComCard;     // 是否查看过兔子牌
            bool _freeze;          // 是否冻结

        protected:
            int _tokentime;       //行动时间
            int _diff;

        protected:
            std::vector<int> vec_res;
            int _play_time;
            long _robot_take_in;// 机器人带入
            int _hd_point;      //牌力
            long _freeNum;  //无需抽水部分
            bool _delaycal; //延迟返还金币
            long _round_bet; //玩家本轮下注
            RobotUserParam _robotUserParam;
            bool _bNextStandUp;
            bool _bPlayGame; //是否参与过游戏
            long _lBuyInNum;//买入数量
            long _lBuyInCount;//买入次数
            long _lStartTakenIn; //初始带入
            long _iAiGameRound; //ai 挑战次数
            long _iAiGamePoint; //ai 挑战积分
            int _iRoundRaiseCount; //本轮下注次数
            long _lRountInitChip; //小局初始筹码
            long _lSelfBetTo;   //累计下注
            long _lSeltStreeBetTo;// 本轮累计下注

            bool _bShowAchievement; //是否显示成就
            bool _bAuthBB;//是否强制下大盲

            int _iLeagueLevel;

            std::vector<int> _vBetType; // 下注操作

            std::map<int, std::map<int, int>> _mActionData; // 下注行为统计

            long _lPauseStartTime;//暂停开始时间
            long _lPauseLastTime;//上次暂停时间
            std::vector<int> _vPauseEffectTime;//有效时间

            long _lRoundTakenIn;             //本轮带入

            int _iSneak;                    //查看偷偷牌 0：初始状态  1:最后两人  2：触发

            std::vector<long> _vecSneakCard2U;//亮牌玩家映射

            long _cur_bet;//玩家当前下注
            
        protected:
            XGameDZProtoClub::NN_sBoxInfo _boxinfo;
        protected:
            long _lInsureBuy;       // 保险购买金额
            long _lInsureWin;       // 保险输赢金额
            vecc_t  _insurecards;   // 投保选择的outs牌
        protected:
            std::vector<E_NN_TYPE> _paomaCardTypes;  // 跑马牌型
            std::vector<vecc_t> _paomaWinCards;      // 跑马牌面
            std::vector<long> _paomaWins;            // 跑马输赢
        };
    };
};

