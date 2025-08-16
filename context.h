#pragma once

#include <map>
#include <deque>
#include "common/nndef.h"
#include "context/user.h"
#include "third.pb.h"
#include "common/macros.h"
#include "utils/tarslog.h"
//
using namespace nndef;
using namespace nnuser;
namespace game
{
    class GameRoot;

    namespace context
    {
#define MAX_RECORD_COUNT 50    //最大保存的游戏记录数

        //行为记录
        struct ActRecord
        {
            E_NN_ACT act;
            long betNum;
        };

        //玩家记录
        struct RecordUser
        {
            std::string url;
            std::string name;
            guid_t uid;
            cid_t cid;
            vecc_t vComCard;
            vecc_t vHdCard;
            E_NN_TYPE eCardType;
            long change;
            bool fold;
            int callCount;
            int raiseCount;
            int betCount;//下注数
            std::map<E_NN_STATE, ActRecord> mActRecord;
            long squidChange;//鱿鱼积分
            long  clubjackpot;
            long mushChange;
        };

        //游戏记录
        struct Record
        {
            cid_t bankercid;
            cid_t bigblindcid;
            cid_t smallblindcid;
            bool complete;
            long jackpot;  //游戏奖池
            int time;
            std::map<cid_t, RecordUser> vRecordUser;

        };

        struct RobotComParam
        {
            int round; //轮数
            bool isBet;//是否有人下注
            int allAddNum;//本轮所有玩家累积加注次数
            void clear()
            {
                round = 0;
                isBet = false;
                allAddNum = 0;
            }
        };

        // 保险反超者
        struct InsureUser
        {
            long lUid;                // 玩家UID
            std::string sNickname;    // 昵称
            int iOutsCount;           // 总数量
            std::vector<int> vHand;   // 手牌
            std::vector<int> vOut;    // outs牌
            InsureUser()
            {
                lUid = 0;
                sNickname = "";
                iOutsCount = 0;
                vHand.clear();
                vOut.clear();
            }
        };

        // 保险数据
        struct InsureData
        {
            long lUid;                       // 玩家UID
            std::string sNickname;           // 昵称
            int iFlag;                       // 圈 1 转牌圈 2 河牌圈
            int iIndex;                      // 池子下标
            long lPool;                      // 池子额度
            long lBuy;                       // 购买额度
            long lPay;                       // 赔付额度
            long lMinAmount;                 // 最小购买值
            long lTime;                      // 时间戳
            int iCardCount;                  // 牌盒余数
            int iOutsCount;                  // outs总数量
            int iOdds;                       // 总赔率
            std::vector<int> vHand;          // 手牌
            std::vector<int> vOut;           // 总outs牌
            std::vector<InsureUser> vUser;   // 反超者
            bool bMust;                      // 必买
            int lPreBuy;                     // 转牌时未中保险(只在河牌圏出现)
            bool bSysBuy;                    // 系统强制买的(玩家取消后的强制也算)
            InsureData()
            {
                lUid = 0;
                sNickname = "";
                iFlag = 0;
                iIndex = 0;
                lPool = 0;
                lBuy = 0;
                lPay = 0;
                lMinAmount = 0;
                lTime = 0;
                iCardCount = 0;
                iOutsCount = 0;
                iOdds = 0;
                bMust = false;
                bSysBuy = false;
                lPreBuy = 0;
                vHand.clear();
                vOut.clear();
                vUser.clear();
            } 
        };
        //
        class Context
        {
            DISALLOW_COPY_AND_ASSIGN(Context)

        private:
            Context();
            explicit Context(GameRoot *root);

        public:
            //
            static Context *Create(GameRoot *root)
            {
                return new Context(root);
            }
            //
            void gameInit();
            //
            void roundInit();
            //
            void resetUserPart();
            //
            void updateUserMapByTail();
            //
            inline GameRoot const *getRoot()
            {
                return _root;
            }

        public:
            //
            void addUser(guid_t uid, cid_t cid, bool robot = false);
            //
            void addUserTail(guid_t uid, cid_t cid, bool robot = false);
            //
            void delUser(guid_t uid);
            //
            void delUserTail(guid_t uid);
            //
            bool isAllDone();
            //
            void setAllDone(bool done);
            //
            bool isAllIn();
            //
            int AllInCount();
            //
            bool isAllFold();
            //
            bool isCompareCards();
            //
            void setAllRobot(bool value)
            {
                _allrobot = value;
            }
            //
            bool isAllRobot()
            {
                return _allrobot;
            }
            //
            int getWinCardType()
            {
                return _win_card_type;
            }
            //
            void setWinCardType(int value)
            {
                _win_card_type = value;
            }
            //
            guid_t getWinUid()
            {
                return _win_uid;
            }
            //
            void setWinUid(guid_t uid)
            {
                _win_uid = uid;
            }
            //
            int userCount();
            //
            inline std::map<cid_t, User> const &getUserMap() const
            {
                return _cid_user_map;
            }
            //
            inline std::map<cid_t, User> &refUserMap()
            {
                return _cid_user_map;
            }
            //
            inline std::vector<User> const &getUserVecTail() const
            {
                return _cid_user_vec_tail;
            }
            //
            inline  std::vector<User> &refUserVecTail()
            {
                return _cid_user_vec_tail;
            }
            //
            inline vecc_t const &getVecWallCard() const
            {
                return _wallcards;
            }
            //
            inline vecc_t &refVecWallCard()
            {
                return _wallcards;
            }
            //配牌器手牌
            inline vecc_t const &getVecHdCard() const
            {
                return _hdcards;
            }
            //
            inline vecc_t &refVecHdCard()
            {
                return _hdcards;
            }
            //配牌器公牌
            inline vecc_t const &getVecCommCard() const
            {
                return _commcards;
            }
            //
            inline vecc_t &refVecCommCard()
            {
                return _commcards;
            }
            //保险outs牌
            inline vecc_t const &getVecOutsCard() const
            {
                return _outscards;
            }
            //
            inline vecc_t &refVecOutsCard()
            {
                return _outscards;
            }
            // 常量配置表
            inline RoomSo::TGAME_ConstConfig const &getConstConfig() const
            {
                return _constConfig;
            }
            inline void setConstConfig(const RoomSo::TGAME_ConstConfig &config)
            {
                _constConfig = config;
            }
            //增值服务配置
            inline RoomSo::BaseServiceConfig const &getBaseServiceConfig() const
            {
                return _baseserviceconfig;
            }
            //
            inline void setBaseServiceConfig(const RoomSo::BaseServiceConfig &config)
            {
                _baseserviceconfig = config;
            }
            //
            inline vecc_t const &getVecComCard() const
            {
                return _comcards;
            }
            //
            inline vecc_t &refVecComCard()
            {
                return _comcards;
            }
            //
            inline vecc_t const &getVecShowComCard() const
            {
                return _showcomcards;
            }
            //
            inline vecc_t &refVecShowComCard()
            {
                return _showcomcards;
            }
            inline vecc_t  &getVecOpenComCard()
            {
                return _opencomcards;
            }
            inline std::vector<vecc_t>  &getVecPaomaCard()
            {
                return _paomacards;
            }
            //
            inline void setBankerCid(cid_t cid)
            {
                _bankercid = cid;
            }
            //
            inline cid_t getBankerCid()
            {
                return _bankercid;
            }
             //
            inline void setSmallBlindCid(cid_t cid)
            {
                _smallblindcid = cid;
            }
            //
            inline cid_t getSmallBlindCid()
            {
                return _smallblindcid;
            }
             //
            inline void setBigBlindCid(cid_t cid)
            {
                _bigblindcid = cid;
            }
            //
            inline cid_t getBigBlindCid()
            {
                return _bigblindcid;
            }
            //
            inline void setTokenCid(cid_t cid)
            {
                _tokencid = cid;
            }
            //
            inline cid_t getTokenCid()
            {
                return _tokencid;
            }

            inline long getSysJackpotWealth() const
            {
                return _sysjackpotwealth;
            }
            //
            inline void setSysJackpotWealth(long sysjackpotwealth)
            {
                _sysjackpotwealth = sysjackpotwealth;
            }
            //
            inline long getRewardJackpotWealth() const
            {
                return _rewardjackpotwealth;
            }
            //
            inline void setRewardJackpotWealth(long rewardjackpotwealth)
            {
                _rewardjackpotwealth = rewardjackpotwealth;
            }
            //
            inline void setMinBetNum(long minbetnum)
            {
                _minbetnum = minbetnum;
            }
            //
            inline long getMinBetNum()
            {
                return _minbetnum;
            }
            //
            inline std::map<cid_t, long> const &getBetMap() const
            {
                return _cid_bet_map;
            }
            //
            inline std::map<cid_t, long> &refBetMap()
            {
                return _cid_bet_map;
            }
            //
            void setUserBet(cid_t cid, long num);
            //
            long getUserBetNum(cid_t cid);
            //
            long getUserTotalBetNum(cid_t cid);
            //
            void clearCidStepBet();
            //
            long getCidStepMaxBet();
            //
            long getUserBetNumNew(cid_t cid);
            //
            void addCidPools(cid_t cid, int pid, long change);
            //
            set<cid_t> getPoolCids(std::map<cid_t, long>& mapCidPool);
            //
            void fixBetPools(map<cid_t, long>& mapBackPool);
            //
            void addPoolCids(int pid, cid_t cid, long bet, bool isRobot);
            //
            void calCidPoolsChange(int raio, int limit, long lSmallBlind, bool bFeeDynamic);
            //
            inline std::map<cid_t, std::map<int, long>> const &getCidPools()
            {
                return _cid_pools;
            }
            //
            inline std::map<cid_t, std::map<int, long>> const &getCidPoolsChange()
            {
                return _cid_pools_change;
            }
            //
            inline std::map<cid_t, long> const &getCidPoolsProfit()
            {
                return _cid_pools_profit;
            }
             inline std::map<cid_t, long> const &getCidPoolsRobotProfit()
            {
                return _cid_pools_robot_profit;
            }
            //
            inline std::vector<std::map<cid_t, long> > const &getVecBetPool() const
            {
                return _betpool;
            }
            //
            inline std::vector<std::map<cid_t, long> > &refVecBetPool()
            {
                return _betpool;
            }
            //
            std::vector<long> getVecBetPoolNum();
            //
            inline void setTotalBetnum(long totalbetnum)
            {
                _totalbetnum = totalbetnum;
            }
            //
            inline long getTotalBetnum()
            {
                return _totalbetnum;
            }
            //
            inline std::vector<std::vector<cid_t> > const &getVecWinPool() const
            {
                return _winpool;
            }
            //
            inline std::vector<std::vector<cid_t> > &refVecWinPool()
            {
                return _winpool;
            }
            //
            inline void setInAllIn(bool inallin)
            {
                _inallin = inallin;
            }
            //
            inline bool isInAllIn()
            {
                return _inallin;
            }
            //
            cid_t getNextCid(cid_t cid, int count, int direction);
            //
            cid_t getNextActCid(cid_t cid, int count, int direction);
            //
            cid_t getNextTCid(cid_t cid, int count, int direction);
            //
            cid_t randomCid(cid_t cid, int count);
            //
            inline std::vector<Record> const &getVecRecord() const
            {
                return _record;
            }
            //
            inline std::vector<Record> &refVecRecord()
            {
                return _record;
            }
            inline void cleanVecRecord()
            {
                _record.clear();
            }

            inline void setLastAct(E_NN_ACT last_act)
            {
                _last_act = last_act;
            }
            inline E_NN_ACT getLastAct()
            {
                return _last_act;
            }

            inline void setLastBet(long last_bet)
            {
                _last_bet = last_bet;
            }
            inline long getLastBet()
            {
                return _last_bet;
            }
            inline void setCurBet(long last_bet)
            {
                _cur_bet = last_bet;
            }
            inline long getCurBet()
            {
                return _cur_bet;
            }

            inline void setFirstOption(bool first_option)
            {
                _first_option = first_option;
            }
            inline bool isFirstOption()
            {
                return _first_option;
            }

            inline void setBbLessSb(bool bb_less_sb)
            {
                _bb_less_sb = bb_less_sb;
            }
            inline bool isBbLessSb()
            {
                return _bb_less_sb;
            }

            inline void setStartOpTime(long start_time)
            {
                _start_op_time = start_time;
            }
            inline long getStartOpTime()
            {
                return _start_op_time;
            }

            inline void setGamePause(bool bPause)
            {
                _bPause = bPause;
            }
            inline long getGamePause()
            {
                return _bPause;
            }

            inline void setDismiss(int iDismiss)
            {
                _iDismiss = iDismiss;
            }
            inline int getDismiss()
            {
                return _iDismiss;
            }

            inline void setZombieBet(long zombie_bet)
            {
                _zombie_bet = zombie_bet;
            }

            inline void setCal(bool is_cal)
            {
                _iscal = is_cal;
            }
            inline bool isCal()
            {
                return _iscal;
            }

            inline void setRoundFirstOption(bool value)
            {
                _round_first_option = value;
            }
            inline bool getRoundFirstOption()
            {
                return _round_first_option;
            }
            inline std::vector<cid_t> &refRoundActCid()
            {
                return _vRoundActCid;
            }

        private:
            //
            int nnrand(int max, int min = 0);

        public:
            //
            cid_t getCidByUid(guid_t uid);
            //
            guid_t getUidByCid(cid_t cid);
            //
            User *getUserByUid(guid_t uid);
            //
            User *getUserByUidTail(guid_t uid);
            //
            User *getUserByCid(cid_t cid);
            //
            void setRoundMaxBet(long value)
            {
                _round_max_bet = value;
            }
            //
            long getRoundMaxBet()
            {
                return _round_max_bet;
            }
            //
            void setMinRaiseNum(long value)
            {
                _min_raise_num = value;
            }
            //
            long getMinRaiseNum()
            {
                return _min_raise_num;
            }
            void setPauseTime(long value)
            {
                _lPauseTime = value;
            }
            long getPauseTime()
            {
                return _lPauseTime;
            }


            string tranCard(short card);

            void addRobotPlayNum()
            {
                _iRobotPlayNum++;
            }
            void setRobotPlayNum(int Num)
            {
                _iRobotPlayNum = Num;
            }
            void setRobotPlayNumLimit(int Num)
            {
                _iRobotPlayNumLimit = Num;
            }
            bool isRobotPlayNumLimit()
            {
                return _iRobotPlayNumLimit >= _iRobotPlayNum && _iRobotPlayNum > 0;
            }
            vector<long> checkRobotExit(const string &roomid);
            long getGameMaxChip();

            void setRobotWinNum(long value)
            {
                _lRobotWinNum = value;
            }
            void addRobotWinNum(long value)
            {
                _lRobotWinNum += value;
            }
            long getRobotWinNum()
            {
                return _lRobotWinNum;
            }
            void setRobotWinId(guid_t uid)
            {
                _lRobotWinId = uid;
            }
            guid_t getRobotWinId()
            {
                return _lRobotWinId;
            }
            void setRoundOpNum(int Num)
            {
                _iRoundOpNum = Num;
            }
            int getRoundOpNum()
            {
                return _iRoundOpNum;
            }
            cid_t getWinCid()
            {
                return _wincid;
            }
            void checkWinCid(bool include = true);

            void setBeginTime(long value){
                _lBeginTime = value;
            }

            long getBeginTime(){
                return _lBeginTime;
            }
            int getRoundRaiseCount()
            {
                return _iRoundRaiseCount;
            }
            void setRoundRaiseCount(int value)
            {
                _iRoundRaiseCount = value;
            }
            guid_t getRobotUid()
            {
                return _lRobotUid;
            }
            void setRobotUid(guid_t robot_id)
            {
                _lRobotUid = robot_id;
            }
            void setUpdatePool(bool value)
            {
                _bUpdatePool = value;
            }
            bool getUpdatePool()
            {
                return _bUpdatePool;
            }

            long getPrifitNum()
            {
                return _prifitNum;
            }

            void setAiThinkTime(long totalWeight, std::vector<std::vector<int> > &thinkTime)
            {
                _totalWeight = totalWeight;
                _thinkTime = thinkTime;
            }

            int getAiThinkTime();

            void setAiBetAction(std::vector<long> &aiBetAction)
            {
                _vAiBetAction.clear();
                _vAiBetAction = aiBetAction;
            }
            std::vector<long>& getAiBetAction()
            {
                return _vAiBetAction;
            }
            void setTokenOpTime(long op_time)
            {
                _tokenOpTime = op_time;
            }
            long getTokenOpTime()
            {
                return _tokenOpTime;
            }
            long getUserPorfitByCid(cid_t cid);
            long getUserRobotPorfitByCid(cid_t cid);
            void addActionList(int action, int process)
            {
                auto it = _mActionList.find(process);
                if(it == _mActionList.end())
                {
                    _mActionList.insert(std::make_pair(process, std::vector<int>(1, action)));
                }
                else
                {
                    it->second.push_back(action);
                }
            }
            std::map<int, std::vector<int>>& getActionList()
            {
                return _mActionList;
            }

            int getActionNum()
            {
                return _iActionNum;
            }
            void addActionNum(){
                _iActionNum += 1;
            }

            void setFlopPoolNum(long value)
            {
                _lFlopPoolNum = value;
            }

            long getFlopPoolNum()
            {
                return _lFlopPoolNum;
            }

            bool getInsure()
            {
                return _bInsure;
            }
            void setInsure(bool value)
            {
                _bInsure = value;
            }
            long getOutsID()
            {
                return _lOutsID;
            }
            void setOutsID(long value)
            {
                _lOutsID = value;
            }
            long getInsureID()
            {
                return _lInsureID;
            }
            void setInsureID(long value)
            {
                _lInsureID = value;
            }
            long getInsurePool()
            {
                return _lInsurePool;
            }
            void setInsurePool(long value)
            {
                _lInsurePool = value;
            }
            long getInsureMinAmount()
            {
                return _lInsureMinAmount;
            }
            void setInsureMinAmount(long value)
            {
                _lInsureMinAmount = value;
            }
            long getInsureTime()
            {
                return _lInsureTime;
            }
            void setInsureTime(long value)
            {
                _lInsureTime = value;
            }
            long getInsureTurnUID()
            {
                return _lInsureTurnUID;
            }
            void setInsureTurnUID(long value)
            {
                _lInsureTurnUID = value;
            }
            long getInsureTurnTime()
            {
                return _lInsureTurnTime;
            }
            void setInsureTurnTime(long value)
            {
                _lInsureTurnTime = value;
            }
            long getInsureTurnBuy()
            {
                return _lInsureTurnBuy;
            }
            void setInsureTurnBuy(long value)
            {
                _lInsureTurnBuy = value;
            }
            long getInsureTurnPay()
            {
                return _lInsureTurnPay;
            }
            void setInsureTurnPay(long value)
            {
                _lInsureTurnPay = value;
            }
            int getInsureTurnOuts()
            {
                return _iInsureTurnOuts;
            }
            void setInsureTurnOuts(int value)
            {
                _iInsureTurnOuts = value;
            }
            int getInsureTurnOdds()
            {
                return _iInsureTurnOdds;
            }
            void setInsureTurnOdds(int value)
            {
                _iInsureTurnOdds = value;
            }
            long getInsureRiverUID()
            {
                return _lInsureRiverUID;
            }
            void setInsureRiverUID(long value)
            {
                _lInsureRiverUID = value;
            }
            long getInsureRiverTime()
            {
                return _lInsureRiverTime;
            }
            void setInsureRiverTime(long value)
            {
                _lInsureRiverTime = value;
            }
            long getInsureRiverBuy()
            {
                return _lInsureRiverBuy;
            }
            void setInsureRiverBuy(long value)
            {
                _lInsureRiverBuy = value;
            }
            long getInsureRiverPay()
            {
                return _lInsureRiverPay;
            }
            void setInsureRiverPay(long value)
            {
                _lInsureRiverPay = value;
            }
            int getInsureRiverOuts()
            {
                return _iInsureRiverOuts;
            }
            void setInsureRiverOuts(int value)
            {
                _iInsureRiverOuts = value;
            }
            int getInsureRiverOdds()
            {
                return _iInsureRiverOdds;
            }
            void setInsureRiverOdds(int value)
            {
                _iInsureRiverOdds = value;
            }
            int getInsureOutsCount()
            {
                return _iInsurOutsCount;
            }
            void setInsureOutsCount(int value)
            {
                _iInsurOutsCount = value;
            }
            int getQueueSize()
            {
                return _vWaitQueue.size();
            }

            std::vector<guid_t> getQueueList()
            {
                return _vWaitQueue;
            }

            guid_t getWaitQueue();

            int addWaitQueue(guid_t uid);

            int delWaitQueue(guid_t uid);

            int getWaitQueueIndexByUid(guid_t uid);

            long getPaomaTime()
            {
                return _lPaomaTime;
            }
            void setPaomaTime(long value)
            {
                _lPaomaTime = value;
            }
            long getPaomaApplyUID()
            {
                return _lPaomaApplyUID;
            }
            void setPaomaApplyUID(long value)
            {
                _lPaomaApplyUID = value;
            }
            long getPaomaAnswerUID()
            {
                return _lPaomaAnswerUID;
            }
            void setPaomaAnswerUID(long value)
            {
                _lPaomaAnswerUID = value;
            }
            int getPaomaCount()
            {
                return _iPaomaCount;
            }
            void setPaomaCount(int value)
            {
                _iPaomaCount = value;
            }
            std::string getPaomaNickname()
            {
                return _sPaomaNickname;
            }
            void setPaomaNickname(std::string value)
            {
                _sPaomaNickname = value;
            }
            void setPaomaPreProcess(E_NN_STATE value)
            {
                _iPaomaPreProcess = value;
            }
            E_NN_STATE getPaomaPreProcess()
            {
                return _iPaomaPreProcess;
            }
            bool getPaoma()
            {
                return _bPaoma;
            }
            void setPaoma(bool value)
            {
                _bPaoma = value;
            }
            bool getPaomaAgree()
            {
                return _bPaomaAgree;
            }
            void setPaomaAgree(bool value)
            {
                _bPaomaAgree = value;
            }
            std::vector<std::map<int, long>> &getPaomaCidPools()
            {
                return _vPaoma_cid_pools;
            }
            int getProlongTimes(long uId)
            {
                auto it = _mProlangTimes.find(uId);
                if (it != _mProlangTimes.end())
                {
                    return it->second;
                }

                return 0;
            }
            void addProlongTimes(long uId)
            {
                auto it = _mProlangTimes.find(uId);
                if(it == _mProlangTimes.end())
                {
                    _mProlangTimes.insert(std::make_pair(uId, 1));
                }
                else
                {
                    it->second += 1;
                }
            }
            void clearProlongTimes()
            {
                _mProlangTimes.clear();
            }
            void addShowCommCardTimes(long uId)
            {
                auto it = _mShowCommCardTimes.find(uId);
                if(it == _mShowCommCardTimes.end())
                {
                    _mShowCommCardTimes.insert(std::make_pair(uId, 1));
                }
                else
                {
                    it->second += 1;
                }
            }
            int getShowCommCardTimes(long uId)
            {
                auto it = _mShowCommCardTimes.find(uId);
                if (it != _mShowCommCardTimes.end())
                {
                    return it->second;
                }

                return 0;
            }
            void clearShowCommCardTimes()
            {
                _mShowCommCardTimes.clear();
            }

            bool getShowInsure(long uId)
            {
                auto it = _mShowInsure.find(uId);
                if (it != _mShowInsure.end())
                {
                    return it->second;
                }
                return true;
            }

            void addShowInsure(long uId, bool insure)
            {
                auto it = _mShowInsure.find(uId);
                if(it == _mShowInsure.end())
                {
                    _mShowInsure.insert(std::make_pair(uId, insure));
                }
                else
                {
                    it->second = insure;
                }
            }
            void clearShowInsure()
            {
                _mShowInsure.clear();
            }
            void setShowComCard()
            {
                _bShowComCard = true;
            }
            bool isShowComCard()
            {
                return _bShowComCard;
            }

            //
            void setCidSeatName(map<cid_t, Pb::E_SEAT_NAME>& mapCidName);
            //
            void initGameDetailUserInfo();
            //中途加入的玩家
            void addGameDetailUserInfo(long uid,string url,string nick,int gender);
            //
            void initGameDetailRoomInfo(Pb::RoomInfo& roomInfo);
            //
            void initGameDetailCalInfo(Pb::CalInfoClub& calInfo, const bool bPaoma = false);
            //
            void updateDealyRoundStep(Pb::E_ROUND round);
            //
            void updateBackGoldStep(Pb::E_ROUND round,const map<cid_t, long> &mapBackGold);
            //
            void addGameDetailStepInfo(Pb::StepInfoClub& stepInfo);
            //
            std::vector<Pb::GameDetail>& getGameDetails()
            {
                return gameDetails;
            }

            void clearGameDetails()
            {
                gameDetails.clear();
                mapUserGameDetail.clear();
            }

            Pb::GameDetail& getGameDetail()
            {
                DLOG_TRACE ("gameDetail:" << logPb(gameDetail));
                return gameDetail;
            }

            void clearGameDetail()
            {
                gameDetail.clear_userinfos();
                gameDetail.clear_roominfo();
                gameDetail.clear_calinfo();
                gameDetail.clear_stepinfos();
                gameDetail.clear_showdowninfo();
            }

            void setUserCollectGame(long uid, map<string, vector<int>>& mapCollectGame);

            int addUserCollectGame(long uid, string sBriefID, int round);

            int delUserCollectGame(long uid, string sBriefID, int round);

            int getUserCollectGameCount(long uid);

            bool isUserCollectGame(long uid, string sBriefID, int round);

            void setGameUids(vector<long> uids);

            void setUserGameDetail();

            void getGameDetailRound(const long uid, const int index, vector<int> &vecResult);

            int getUserGameDetailCount(const long uid);

            void setEndRound(int round)
            {
                iEndRound = round;
            }

            int getEndRound()
            {
                return iEndRound;
            }

            int getTableRound()
            {
                return _iTableRound;
            }

            void addTableRound()
            {
                _iTableRound += 1;
            }

            void addSneakCount(long uid)
            {
                auto it = _mapSneakCount.find(uid);
                if(it == _mapSneakCount.end())
                {
                    _mapSneakCount.insert(std::make_pair(uid, 1));
                }
                else
                {
                    it->second += 1;
                    //it->second = it->second > 5 ? 5 : it->second;
                }
            }
            int getSneakCount(long uid)
            {
                int count = 0;
                auto it = _mapSneakCount.find(uid);
                if(it != _mapSneakCount.end())
                {
                    count = it->second;
                }
                count += 1;
                //count = count > 5 ? 5 : count;
                return count;
            }

            void addHoldSeat(long uid, long lEndTime)
            {
                DLOG_TRACE("addHoldSeat uid:"<<uid);
                auto it = _mapHoldSeat.find(uid);
                if(it == _mapHoldSeat.end())
                {
                    _mapHoldSeat.insert(std::make_pair(uid, lEndTime));
                }
            }

            void delHoldSeat(long uid)
            {
                 DLOG_TRACE("delHoldSeat uid:"<<uid);
                auto it = _mapHoldSeat.find(uid);
                if(it != _mapHoldSeat.end())
                {
                    _mapHoldSeat.erase(it);
                }
            }

            long getHoldSeatTimeByUid(long uid)
            {
                auto it = _mapHoldSeat.find(uid);
                if(it != _mapHoldSeat.end())
                {
                    return it->second;
                }
                return 0;
            }

            void setMimiCid(cid_t cid)
            {
                _mimiCid = cid;
            }

            cid_t getMimiCid()
            {
                return _mimiCid;
            }
        public:
            std::map<int, std::vector<InsureData>> &getInsureInfo()
            {
                return _mInsureInfo;
            }

            void pushInsureInfo(InsureData data)
            {
                auto iter = _mInsureInfo.find(data.iFlag);
                if (iter != _mInsureInfo.end())
                {
                    iter->second.push_back(data);
                }
                else
                {
                    _mInsureInfo.insert(std::make_pair(data.iFlag, std::vector<InsureData>(1,data)));
                }
            }

            bool isInsureInfo(long uId, int iFlag, int iIndex)
            {
                auto iter = _mInsureInfo.find(iFlag);
                if (iter != _mInsureInfo.end())
                {
                    for (auto item : iter->second)
                    {
                        if (item.lUid == uId && item.iIndex == iIndex)
                        {
                            return true;
                        }
                    }
                }
                
                return false;
            }

            InsureData getInsureInfoData(int iFlag, int iIndex)
            {
                InsureData data;
                data.lUid = 0;
                auto iter = _mInsureInfo.find(iFlag);
                if (iter != _mInsureInfo.end())
                {
                    for (auto item : iter->second)
                    {
                        if (item.iIndex == iIndex)
                        {
                            return item;
                        }
                    }
                }
                
                return data;   
            }

            long getInsureInfoUid(int iFlag, int iIndex)
            {
                auto iter = _mInsureInfo.find(iFlag);
                if (iter != _mInsureInfo.end())
                {
                    for (auto item : iter->second)
                    {
                        if (item.iIndex == iIndex)
                        {
                            return item.lUid;
                        }
                    }
                }
                
                return 0;
            }

            long getInsureInfoBuy(int iFlag, int iIndex)
            {
                auto iter = _mInsureInfo.find(iFlag);
                if (iter != _mInsureInfo.end())
                {
                    for (auto item : iter->second)
                    {
                        if (item.iIndex == iIndex)
                        {
                            return item.lBuy;
                        }
                    }
                }
                
                return 0;
            }

            long getInsureInfoBuyTwo(long lUid, int iFlag, int iIndex)
            {
                auto iter = _mInsureInfo.find(iFlag);
                if (iter != _mInsureInfo.end())
                {
                    for (auto item : iter->second)
                    {
                        if (item.iIndex == iIndex && item.lUid == lUid)
                        {
                            return item.lBuy;
                        }
                    }
                }
                
                return 0;
            }

            int getInsureInfoOdds(int iFlag, int iIndex)
            {
                auto iter = _mInsureInfo.find(iFlag);
                if (iter != _mInsureInfo.end())
                {
                    for (auto item : iter->second)
                    {
                        if (item.iIndex == iIndex)
                        {
                            return item.iOdds;
                        }
                    }
                }
                
                return 0;
            }

            void setInsurePoolCount(int value)
            {
                _iInsurePoolCount = value;
            }
            int getInsurePoolCount()
            {
                return _iInsurePoolCount;
            }

            void setInsurePoolIndex(int value)
            {
                _iInsurePoolIndex = value;
            }
            void addInsurePoolIndex()
            {
                _iInsurePoolIndex += 1;
            }
            int getInsurePoolIndex()
            {
                return _iInsurePoolIndex;
            }

            void setInsureData(InsureData value)
            {
                _dInsureData = value;
            }
            InsureData& getInsureData()
            {
                return _dInsureData;
            }

            std::vector<InsureData> &refInsureData()
            {
                return _vInsureData;
            }
            void pushInsureData(InsureData data)
            {
                _vInsureData.push_back(data);
            }
            void clearInsureData()
            {
                _vInsureData.clear();
            }

            void setInsureDataIndex(int value)
            {
                _iInsureDataIndex = value;
            } 
            int getInsureDataIndex()
            {
                return _iInsureDataIndex;
            }

            bool isInsureNoticeAll()
            {
                int iCount = (int)_vInsureData.size();
                if (_iInsureDataIndex >= iCount)
                {
                    return true;
                }

                return false;
            }

            void setRoundFirstBet(bool value)
            {
                _bRoundFirstBet = value;
            }

            bool isRoundFirstBet()
            {
                return _bRoundFirstBet;
            }
            int getProlongCost(int times);
            int getshowCommCardCost(int times);
            map<cid_t,int> getCidSquidNum();
            map<cid_t,int> &refCidSquidNum(){
                return _cid_squid_num;
            }
            void clearSquid(cid_t cid,bool all);
            map<cid_t,long> &refSquidScore()
            {
                return _cid_squid_score;
            }
            void setSquidStatus(int status)
            {
                _squid_status = status;
            }
            int getSquidStatus()
            {
                return  _squid_status;
            }
           int getSquidMax(int type,int maxseat,int squidnum);
            int getSquidLeft(int type,int maxseat,int squidnum);
          long  getCritTime()
          {
            return lCritTime;
          }
           void setCritTime(long time)
           {
            lCritTime = time;
           }
           void addCritCount()
           {
            iCritCount++;
           }
           int getCritCount()
           {
             return iCritCount;
           }
           void setIsCritRound(bool value)
           {
                bCritRound = value;
           }
           bool IsCritRound()
           {
            return bCritRound;
           }
           long getMushPool()
           {
                return lMushPool;//蘑菇奖池数量
           }
           void addMushPool(cid_t cid,long value,long uid)
           {
            //蘑菇池子增加 玩家扣除
                lMushPool+=value;
                _cid_mush_change[cid] = -value;
                _uid_mush_push[uid] += value;
           }
            void setMushPool(long value)
           {
                lMushPool=value;
           }
           
           void setMushStatus(int status)
           {
             iMushStatus = status;
           }
           int getMushStatus()
           {
             return iMushStatus;
           }
           int getMushCid()
           {
             return iMushCid;
           }
           void setMushCid(cid_t cid)
           {
              iMushCid=cid;
           }
            map<cid_t,long> &refMushChange()
            {
                return _cid_mush_change;
            }
            map<long,long> &refMushPush()
            {
               return _uid_mush_push;
            }
            void clearMushChange()
            {
                _cid_mush_change.clear();
                _uid_mush_push.clear();
                  DLOG_TRACE("clearMushChange, _uid_mush_push.clear()");
            }
       
            long getClubJackpotPool()
            {
                return lClubJackpotPool;
            }
            void setClubjackpotPool(long pool)
            {
                lClubJackpotPool=pool;
            }
            int getJackpotRatio(int cardtype)
            {
                return mJackpotRatio[cardtype];
            }
            map<int,int> getJackpotRatios()
            {
                return mJackpotRatio;
            }
            void setJackpotRatio(map<int,int> ratio)
            {
                mJackpotRatio=ratio;
            }
            bool isJackpotOpen()
            {
                return mJackpotRatio.size()>0;
            }
            inline std::map<cid_t, long> &getCidJackpotChange()
            {
                return _cid_club_jackpot_change;
            }
     

            void addCidJackpotChange(cid_t cid, long change);//奖励获取记录
                  //机器人行为逻辑
            template<typename T>
            void setRobotComParam(const string varName, const string opType, T value)
            {
                if(varName == "round")
                {
                    _robotComParam.round = value;
                }
                else if(varName == "isBet")
                {
                    _robotComParam.isBet = value;
                }
                else if(varName == "allAddNum")
                {
                    if(opType == "set")
                    {
                        _robotComParam.allAddNum = value;
                    }
                    else if(opType == "add")
                    {
                        _robotComParam.allAddNum += value;
                    }
                    else
                    {

                    }
                }
                return ;
            }

            template<typename T>
            T getRobotComParam(const string varName)
            {
                if(varName == "round")
                {
                    return _robotComParam.round;
                }
                else if(varName == "isBet")
                {
                    return _robotComParam.isBet;
                }
                else if(varName == "allAddNum")
                {
                    return _robotComParam.allAddNum;
                }
                return 0;
            }
            bool getRobotComParamIsBet()
            {
                return _robotComParam.isBet;
            }
            void addCidPoolsRobotProfit(cid_t,long);
   
        protected:
            //
            GameRoot *const _root;

        protected:
            std::map<cid_t, User> _cid_user_map;
            std::vector<User> _cid_user_vec_tail;
            std::map<cid_t, long> _cid_bet_map;
            std::vector<std::map<cid_t, long> > _betpool;
            vecc_t                 _wallcards;
            vecc_t                 _hdcards;   //配牌器手牌
            vecc_t                 _commcards; //配牌器公牌
            vecc_t                 _outscards; //保险outs牌
            RoomSo::BaseServiceConfig _baseserviceconfig;  //增值服务配置
            RoomSo::TGAME_ConstConfig _constConfig;  // 常量表配置
            cid_t                  _bankercid;
            cid_t                  _smallblindcid;
            cid_t                  _bigblindcid;
            cid_t                  _tokencid;
            long                   _rewardjackpotwealth;
            long                   _sysjackpotwealth;
            vecc_t                 _comcards;       //公牌
            vecc_t                 _showcomcards;   //查看公牌
            vecc_t                 _opencomcards;   //翻开的公牌
            std::vector<vecc_t>    _paomacards;     //跑马的牌
            long                   _minbetnum;
            long                   _totalbetnum;
            std::vector<std::vector<cid_t> > _winpool;
            bool                   _inallin;
            std::vector<Record>    _record;
            E_NN_ACT               _last_act;
            long                   _last_bet;
            long                   _cur_bet;
            bool                   _allrobot;
            int                    _win_card_type; //1：真人  2：机器人
            guid_t                 _win_uid;
            bool                   _first_option;//第一次操作
            long                   _start_op_time; //开始操作时间
            bool                   _bb_less_sb;//大盲下注小于小盲下注
            std::map<cid_t, long>  _cid_bet;
            std::map<cid_t, long>  _cid_step_bet;
            bool                   _bPause;//游戏暂停
            std::map<cid_t, std::map<int, long>> _cid_pools;  //每个玩家奖池的分配情况
            std::map<cid_t, std::map<int, long>> _cid_pools_change;  //每个玩家奖池的获取情况（扣除抽水)
            std::map<cid_t, long> _cid_pools_profit;  //每个玩家服务费情况（扣除抽水）
            std::map<cid_t, long> _cid_pools_robot_profit;  //机器人赢代理分红

            std::map<int, std::map<cid_t, long >> _pool_cids; //每个池子玩家压注情况
            long                   _zombie_bet; //僵尸筹码
            bool                   _iscal;  //是否结算
            bool                   _round_first_option; //每轮第一个人操作
            long                   _round_max_bet;//本轮最大下注
            long                   _min_raise_num;//最小加注
            int                   _iDismiss;
            long                  _lPauseTime;
            RobotComParam         _robotComParam;
            long                  _prifitNum;
            long                  _totalWeight;
            std::vector<std::vector<int> > _thinkTime;
            std::vector<long> _vAiBetAction;
            long                  _tokenOpTime;
            bool                  _bInsure;             // 保险状态  是否已走完保险(可以直接发牌)
            long                  _lOutsID;             // 反超者ID
            long                  _lInsureID;           // 购买保险的人的ID
            long                  _lInsurePool;         // 保险最大保池额度
            long                  _lInsureMinAmount;    // 最小购买值
            long                  _lInsureTime;         // 保险结束时间戳(为了重连用)
            long                  _lInsureTurnUID;      // 转牌圏购买保险人的ID
            long                  _lInsureTurnTime;     // 转牌圏购买保险时间戳
            long                  _lInsureTurnBuy;      // 转牌圏购买保险人的购买额度
            long                  _lInsureTurnPay;      // 转牌圏购买保险人的赔付额度
            int                   _iInsureTurnOuts;     // 转牌圏outs
            int                   _iInsureTurnOdds;     // 转牌圏赔率
            long                  _lInsureRiverUID;     // 河牌圏购买保险人的ID
            long                  _lInsureRiverTime;    // 河牌圏购买保险时间戳
            long                  _lInsureRiverBuy;     // 河牌圏购买保险人的购买额度
            long                  _lInsureRiverPay;     // 河牌圏购买保险人的赔付额度
            int                   _iInsureRiverOuts;    // 河牌圏outs
            int                   _iInsureRiverOdds;    // 河牌圏赔率
            int                   _iInsurOutsCount;     // outs牌数量(用来river中outs=0时，做必买的)

            bool                  _bPaoma;          // 跑马状态,是否已走完跑马(直接下一步)
            bool                  _bPaomaAgree;     // 是否同意了(重连时就可以发牌)
            long                  _lPaomaTime;      // 跑马结束时间戳(为了重连用)
            long                  _lPaomaApplyUID;  // 跑马申请人的ID
            long                  _lPaomaAnswerUID; // 跑马应答人的ID
            int                   _iPaomaCount;     // 跑马次数
            std::string           _sPaomaNickname;  // 申请人的名字
            E_NN_STATE            _iPaomaPreProcess; // 进入跑马时的阶段
            std::vector<std::map<int, long>> _vPaoma_cid_pools; // 跑马时每轮的输赢
            std::map<long, int> _mProlangTimes;   // 每人的加时次数
            std::map<long, bool> _mShowInsure;    // 每个人的是否提示保险
            std::map<long, int> _mShowCommCardTimes;   // 每人的查看公共牌次数
 
            bool                  _bShowComCard;  // 是否放入过兔子牌

            std::map<int, std::vector<InsureData>> _mInsureInfo;   // 保险数据
            int                                    _iInsurePoolCount;   // 总池子数量
            int                                    _iInsurePoolIndex;   // 当前购买保险的池子下标
            InsureData                             _dInsureData;        // 当前轮的保险数据(下轮前会push到_mInsureInfo)
            std::vector<InsureData>                _vInsureData;        // 当前轮的保险数据(下轮前会push到_mInsureInfo)
            int                                    _iInsureDataIndex;   // 当前轮保险通知队列中的下标 
        public:
            int                   _iRobotPlayNum;//纯粹机器人玩的局数
            int                   _iRobotPlayNumLimit;
            long                  _lRobotWinNum; //牌桌机器人盈利值
            guid_t                _lRobotWinId; //必胜机器人ID
            int                   _iRoundOpNum; //本轮第几个出手
            cid_t                 _wincid;
            long                  _lBeginTime;
            int                   _iRoundRaiseCount;
            guid_t                _lRobotUid;
            bool                  _bUpdatePool;// 是否是翻拍阶段， 避免重复处理决策

            std::map<int, std::vector<int>> _mActionList;

            int                   _iActionNum;

            std::vector<cid_t> _vRoundActCid;//参与本轮的玩家

            long               _lFlopPoolNum;// 翻拍底池数

            vector<guid_t> _vWaitQueue;//等待坐桌队列

            //牌谱
            Pb::GameDetail gameDetail;
            std::vector<Pb::GameDetail> gameDetails;

            map<long, map<string, vector<int>>> mapUserCollectGame; //{uid: briefid:[rounid]}
            set<long> sGameUids;//本局玩家 包含观战
            map<long, vector<int>> mapUserGameDetail;//玩家参与的牌局（用于查看牌谱）

            //牌局结束轮数
            int iEndRound;

            int _iTableRound;  // 当前局数

            map<long, int> _mapSneakCount;  //偷偷看次数

            map<long, long> _mapHoldSeat;   //占座玩家信息

            cid_t _mimiCid;                 //眯牌座位

            bool _bRoundFirstBet;              //本轮首次操作
            std::map<cid_t, int>  _cid_squid_num;//鱿鱼数量
            std::map<cid_t, long>  _cid_squid_score;//鱿鱼分数
            int _squid_status;///鱿鱼状态 0未开启 1开启中 2结算
            //暴击模式玩法
            long lCritTime;//暴击开始时间
            int iCritCount;//暴击次数
            bool bCritRound;//本局是否暴击
            //蘑菇玩法
            long lMushPool;//蘑菇奖池数量
            int iMushStatus;//蘑菇状态 0未开启 1开启中 2结算
            cid_t iMushCid;//蘑菇位玩家
            map<cid_t, long> _cid_mush_change;//蘑菇结算分
            map<long, long> _uid_mush_push;//蘑菇贡献
            map<cid_t, long> _cid_club_jackpot_change;       //每个玩家牌型奖池获取
            long lClubJackpotPool;//jackpot奖池金额
            map<int,int> mJackpotRatio;//牌型获奖奖励
            
        };
    };
};

