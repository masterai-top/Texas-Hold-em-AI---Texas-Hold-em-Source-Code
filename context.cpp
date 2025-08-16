#include "common/macros.h"
#include "utils/tarslog.h"
#include "context/context.h"


namespace game
{
    namespace context
    {
        map<int, string> mSuitTran =
        {
            { 0, "d"}, { 16, "c"}, { 32, "h"}, { 48, "s"},
        };

        map<int, vector<int>> mSeatName =
        {
            { 2, {0, 1}},
            { 3, {0, 1, 2}},
            { 4, {0, 1, 2, 3}},
            { 5, {0, 1, 2, 3, 5}},
            { 6, {0, 1, 2, 3, 5, 8}},
            { 7, {0, 1, 2, 3, 5, 7, 8}},
            { 8, {0, 1, 2, 3, 4, 5, 7, 8}},
            { 9, {0, 1, 2, 3, 4, 5, 6, 7, 8}},
        };

        Context::Context() : _root(NULL)
        {
            LOG_FATAL("creator Context without root.");
        }

        Context::Context(GameRoot *root) : _root(root)
        {
            gameInit();
        }

        void Context::gameInit()
        {
            _cid_user_map.clear();
            _cid_user_vec_tail.clear();
            _sysjackpotwealth = 0;
            _rewardjackpotwealth = 0;
            _allrobot = false;
            _win_card_type = 0;
            _win_uid = 0;
            _record.clear();
            _bPause = false;
            _lPauseTime = 0;
            _iRobotPlayNum = 0;
            _iRobotPlayNumLimit = 0;
            _lRobotWinNum = 0;
            _totalWeight = 0;
            _thinkTime.clear();
            _vWaitQueue.clear();
            _bankercid = nil_cid;
            _smallblindcid = nil_cid;
            _bigblindcid = nil_cid;
            _iTableRound = 0;

            _iInsurePoolCount = 0;
            _iInsurePoolIndex = 0;
            _mInsureInfo.clear();

            _vInsureData.clear();
            _iInsureDataIndex = 0;

            mapUserCollectGame.clear();
            _mapSneakCount.clear();
            _mapHoldSeat.clear();
            clearGameDetails();
            clearProlongTimes();
            clearShowInsure();
            clearShowCommCardTimes();
            _cid_squid_num.clear();
            _cid_squid_score.clear();
            _squid_status=0;
            lMushPool=0;
         
            iMushStatus=0;//蘑菇状态 0未开启 1开启中 2结算
            iMushCid=-1;//蘑菇位玩家
            _cid_mush_change.clear();//蘑菇结算分
 _uid_mush_push.clear();
   DLOG_TRACE("before round init, _uid_mush_push.clear()");
              lCritTime=0;//暴击开始时间
             iCritCount=0;//暴击次数
             bCritRound=false;//本局是否暴击
            roundInit();
        }

        void Context::roundInit()
        {
            _betpool.clear();
            _winpool.clear();
            _cid_bet_map.clear();
            _wallcards.clear();
            _comcards.clear();
            _opencomcards.clear();

            _tokencid = nil_cid;
            _minbetnum = 0;
            _totalbetnum = 0;
            _inallin = false;
            _wincid = nil_cid;

            _last_act = nil_act;
            _last_bet = 0;
            _cur_bet = 0;
            _allrobot = false;
            _first_option = false;
            _bb_less_sb = false;

            _cid_bet.clear();
            _cid_step_bet.clear();
            _cid_pools.clear();
            _cid_pools_change.clear();
            _cid_pools_profit.clear();
            _cid_pools_robot_profit.clear();
            _pool_cids.clear();
            _zombie_bet = 0;
            _iscal = false;
            _round_max_bet = 0;
            _min_raise_num = 0;
            _start_op_time = 0;
            _iDismiss = -1;
            _robotComParam.clear();
            _lRobotWinId = 0;
            _iRoundOpNum = 0;
            _lBeginTime = 0;
            _iRoundRaiseCount = 0;
            _lRobotUid = 0;
            _bUpdatePool = false;
            _prifitNum = 0;
            _vAiBetAction.clear();
            _tokenOpTime = 0;
            _mActionList.clear();

            _iActionNum = 0;
            _lFlopPoolNum = 0;

            _lInsureID = 0;
            _lInsurePool = 0;
            _lInsureTime = 0;
            _lInsureTurnUID = 0;
            _lInsureTurnBuy = 0;
            _lInsureTurnPay = 0;
            _iInsureTurnOuts = 0;
            _iInsureTurnOdds = 0;
            _lInsureRiverUID = 0;
            _lInsureRiverBuy = 0;
            _lInsureRiverPay = 0;
            _iInsureRiverOuts = 0;
            _iInsureRiverOdds = 0;

            _bShowComCard = false;

            _iInsurePoolCount = 0;
            _iInsurePoolIndex = 0;
            _mInsureInfo.clear();

            _dInsureData.lUid = 0;

            _vInsureData.clear();
            _iInsureDataIndex = 0;

            clearGameDetail();

            iEndRound = 0;

            _mimiCid = nil_cid;

            _bRoundFirstBet = false;
            _cid_squid_score.clear();
            _cid_mush_change.clear();
            // _uid_mush_push.clear();
            // DLOG_TRACE("before round init, _uid_mush_push.clear()");
            _cid_club_jackpot_change.clear();
              bCritRound=false;//本局是否暴击
            //for test
            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); ++it)
            {
                DLOG_TRACE("before round init, cid = " << it->first << ", uid: " << it->second.getUid() << ", left: " << it->second.isLeft()<<", isMid:"<< it->second.isMidSit());
            }

            //
            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); )
            {
                if (it->second.isLeft())
                {
                    DLOG_TRACE("del left user, cid = " << it->first << ", uid: " << it->second.getUid());
                    _cid_user_map.erase(it++);
                }
                else
                {
                    it->second.roundInit();
                    ++it;
                }
            }

            updateUserMapByTail();
      

            //for test
            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); ++it)
            {
                DLOG_TRACE("after round init, cid = " << it->first << ", uid: " << it->second.getUid() << ", isfold: " << it->second.isFold()<<", isMid:"<< it->second.isMidSit());
            }
            
        }
    void Context::addCidJackpotChange(cid_t cid, long change)
        {
            auto it = _cid_club_jackpot_change.find(cid);
            if (it == _cid_club_jackpot_change.end())
            {
                _cid_club_jackpot_change.insert(std::make_pair(cid, change));
            }
            else
            {
                it->second += change;
            }
        }
        // 重置玩家部分数据
        void Context::resetUserPart()
        {
            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); ++it)
            {
                it->second.setProlongFlag(0);
            }
        }

        void Context::updateUserMapByTail()
        {
            std::vector<User> vTUser;
            vTUser.insert(vTUser.begin(), _cid_user_vec_tail.begin(), _cid_user_vec_tail.end());
            for(auto tuser : vTUser)
            {
                cid_t cid= tuser.getCid();
                if( cid != nil_cid && !getUserByCid(cid))
                {
                    _cid_user_map.insert(std::make_pair(cid, tuser));
                    delUserTail(tuser.getUid());
                    DLOG_TRACE("del user tail, cid = " << cid<< ", uid: " << tuser.getUid() << ", pause: "<< tuser.isPause());
                }
            }
        }

        void Context::addUser(guid_t uid, cid_t cid, bool robot)
        {
            auto it = _cid_user_map.find(cid);
            if (it != _cid_user_map.end())
            {
                // DLOG_TRACE("user exist, uid = " << uid);
            }

            _cid_user_map.insert(std::make_pair(cid, User(uid, cid, robot)));
           
        }

        void Context::addUserTail(guid_t uid, cid_t cid, bool robot)
        {
            auto tuser = User(uid, cid, robot);
            User* user = getUserByUid(uid);
            if(user)
            {
                tuser.setNick(user->getNick());
                tuser.setUrl(user->getUrl());
                tuser.setCountry(user->getCountry());
                tuser.setGender(user->getGender());
                tuser.setShowAchievement(user->isShowAchievement());
                tuser.setLeagueLevel(user->getLeagueLevel());
                tuser.setPauseLastTime(0);
            }

            _cid_user_vec_tail.push_back(tuser);
        }

        void Context::delUser(guid_t uid)
        {
            cid_t cid = getCidByUid(uid);
            auto it = _cid_user_map.find(cid);
            if (it != _cid_user_map.end())
            {
                _cid_user_map.erase(it);
            }
            else
            {
                // DLOG_TRACE("user isn't exist, uid = " << uid);
            }
        }

        void Context::delUserTail(guid_t uid)
        {
            auto it = std::find_if(_cid_user_vec_tail.begin(),_cid_user_vec_tail.end(), [uid](User user)->bool{
                return uid == user.getUid();
            });
            if(it != _cid_user_vec_tail.end())
            {
                _cid_user_vec_tail.erase(it);
            }
        }

        bool Context::isAllDone()
        {
            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); it++)
            {
                //DLOG_TRACE("cid:" << it->first<<"|"<< it->second._midsit << "|"<< it->second._allin << "|"<< it->second._fold << "|"<<  it->second._done);
                if (!it->second._midsit && !it->second._allin && !it->second._fold)
                {
                    if (not it->second._done)
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        bool Context::isAllFold()
        {
            int count = 0;

            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); it++)
            {
                DLOG_TRACE("cid:" << it->first<<"|"<< it->second._midsit  << "|"<< it->second._fold);
                if (!it->second._midsit && !it->second._fold)
                {
                    count++;
                }
            }

            return count <= 1;
        }

        bool Context::isCompareCards()
        {
            int count = 0;

            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); it++)
            {
                // DLOG_TRACE("cid:" << it->first<<"|"<< it->second._midsit  << "|"<< it->second._fold);
                if (!it->second._midsit && !it->second._fold)
                {
                    count++;
                }
            }

            return count >= 2;
        }

        void Context::checkWinCid(bool include)
        {
            if(_wincid == nil_cid)
            {
                std::vector<cid_t> v;
                for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); it++)
                {
                    if(include)
                    {
                        if (!it->second._midsit && !it->second._fold && !it->second._left)
                        {
                            v.push_back(it->first);
                        }
                    }
                    else
                    {
                        if (!it->second._midsit && !it->second._left)
                        {
                            v.push_back(it->first);
                        }
                    }
                }
                if(v.size() == 1)
                {
                    _wincid = v.front();
                }
                else
                {   
                    _wincid = nil_cid;  
                }
            }
            DLOG_TRACE("_wincid  = " << _wincid);
        }

        int Context::userCount()
        {
            int count = 0;

            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); it++)
            {
                if (!it->second._midsit)
                {
                    count++;
                }
            }

            return count;
        }

        void Context::setAllDone(bool done)
        {
            for (auto it = _cid_user_map.begin();  it != _cid_user_map.end(); it++)
            {
                if (!it->second._midsit && !it->second._allin && !it->second._fold)
                {
                    it->second.setDone(done);
                }
            }
        }

        cid_t Context::getCidByUid(guid_t uid)
        {
            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); it++)
            {
                if (it->second._uid == uid)
                {
                    return it->second._cid;
                }
            }

            return nil_cid;
        }

        guid_t Context::getUidByCid(cid_t cid)
        {
            auto it = _cid_user_map.find(cid);
            if (it != _cid_user_map.end())
            {
                return it->second._uid;
            }

            return nil_uid;
        }

        User *Context::getUserByUid(guid_t uid)
        {
            auto it = _cid_user_map.find(getCidByUid(uid));
            if (it != _cid_user_map.end())
            {
                return &(it->second);
            }

            return NULL;
        }

        User *Context::getUserByCid(cid_t cid)
        {
            auto it = _cid_user_map.find(cid);
            if (it != _cid_user_map.end())
            {
                return &(it->second);
            }

            return NULL;
        }

        User *Context::getUserByUidTail(guid_t uid)
        {
            auto it = std::find_if(_cid_user_vec_tail.begin(),_cid_user_vec_tail.end(), [uid](User user)->bool{
                return uid == user.getUid();
            }); 
            if(it != _cid_user_vec_tail.end())
            {
                return &(*it);
            }
            return NULL;
        }

        cid_t Context::getNextCid(cid_t cid, int count, int direction)
        {
            for (int i = 1; i < count; i++)
            {
                cid_t temp = (count + cid + i * direction) % count;
                User *user = getUserByCid(temp);
                if (user != NULL && !user->_midsit && !user->_fold && !user->_allin)
                {
                    return temp;
                }
            }

            return cid;
        }

        cid_t Context::getNextActCid(cid_t cid, int count, int direction)
        {
            for (int i = 1; i < count; i++)
            {
                cid_t temp = (count + cid + i * direction) % count;
                User *user = getUserByCid(temp);
                if (user != NULL && !user->_midsit && !user->_fold)
                {
                    return temp;
                }
            }

            return cid;
        }

        cid_t Context::getNextTCid(cid_t cid, int count, int direction)
        {
            for (int i = 1; i < count; i++)
            {
                cid_t temp = (count + cid + i * direction) % count;
                User *user = getUserByCid(temp);
                if (user != NULL && !user->_midsit)
                {
                    return temp;
                }
            }

            return cid;
        }

        int Context::nnrand(int max, int min)
        {
            std::random_device rd;
            srand(rd());
            return min + rand() % (max - min + 1);
        }

        cid_t Context::randomCid(cid_t cid, int count)
        {
            vector<int> cids;

            //
            for (int i = 1; i < count; i++)
            {
                User *user = getUserByCid(i);
                if (user != NULL && !user->_midsit && !user->_fold && !user->_allin)
                {
                    cids.push_back(i);
                }
            }

            //
            if (cids.size() > 0)
            {
                int randCid = nnrand(cids.size() - 1, 0);
                return cids[randCid];
            }

            return cid;
        }

        bool Context::isAllIn()
        {
            int count1 = 0;
            int count2 = 0;
            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); it++)
            {
                if (!it->second._midsit && !it->second._fold)
                {
                    count1++;
                    if (it->second._allin)
                    {
                        count2++;
                    }
                }
            }

            return count1 - count2 <= 1;
        }
        	int Context::AllInCount()
		{
			int count = 0;
			for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); it++)
			{
				if (!it->second._midsit && !it->second._fold)
				{
					count++;
				}
			}

			return count;
		}

        void Context::setUserBet(cid_t cid, long num)
        {
            //DLOG_TRACE("set user bet, cid : " << cid << ", num : " << num);

            auto it = _cid_bet_map.find(cid);
            if (it != _cid_bet_map.end())
            {
                it->second += num;
            }
            else
            {
                _cid_bet_map.insert(make_pair(cid, num));
            }

            auto it1 = _cid_bet.find(cid);
            if (it1 != _cid_bet.end())
            {
                it1->second += num;
            }
            else
            {
                _cid_bet.insert(make_pair(cid, num));
            }

            _totalbetnum += num;

            auto it2 = _cid_step_bet.find(cid);
            if (it2 != _cid_step_bet.end())
            {
                it2->second = num;
            }
            else
            {
                _cid_step_bet.insert(make_pair(cid, num));
            }
        }

        void Context::clearCidStepBet()
        {
            _cid_step_bet.clear();
        }

        long Context::getCidStepMaxBet()
        {
            long max_bet_num = 0;
            cid_t max_bet_cid = nil_cid;
            for(auto item : _cid_step_bet)
            {
                if(item.second > max_bet_num)
                {
                   max_bet_num = item.second;
                   max_bet_cid = item.first;
                }
            }
            if(_tokencid == max_bet_cid)
            {
                clearCidStepBet();
                max_bet_num = 0;
            }
            return max_bet_num;
        }

        long Context::getUserBetNumNew(cid_t cid)
        {
            auto it = _cid_bet.find(cid);
            if (it != _cid_bet.end())
            {
                return it->second;
            }
            else
            {
                return 0;
            }
        }

        long Context::getUserBetNum(cid_t cid)
        {
            auto it = _cid_bet_map.find(cid);
            if (it != _cid_bet_map.end())
            {
                return it->second;
            }
            else
            {
                return 0;
            }
        }

        long Context::getUserTotalBetNum(cid_t cid)
        {
            long sum = 0;

            for (auto it1 = _betpool.begin(); it1 != _betpool.end(); it1++)
            {
                for (auto it2 = it1->begin(); it2 != it1->end(); it2++)
                {
                    if (cid == it2->first)
                    {
                        sum += it2->second;
                    }
                }
            }

            return sum;
        }

        std::vector<long> Context::getVecBetPoolNum()
        {
            std::vector<long> temp;

            long temp_total_bet = 0;
            for (auto it1 = _betpool.begin(); it1 != _betpool.end(); it1++)
            {
                long sum = 0;
                for (auto it2 = it1->begin(); it2 != it1->end(); it2++)
                {
                    sum += it2->second;
                }
                if(sum > 0)
                {
                    temp_total_bet += sum;
                    temp.push_back(sum);
                }
            }

            //僵尸筹码归于大赢家
            if (temp_total_bet < getTotalBetnum() && temp.size() > 0)
            {
                temp[0] += getTotalBetnum() - temp_total_bet;
            }

            return std::move(temp);
        }

        set<cid_t> Context::getPoolCids(std::map<cid_t, long>& mapCidPool)
        {
            set<cid_t> setCids;
            for(auto item : mapCidPool)
            {
                User* user = getUserByCid(item.first);
                if(!user || user->isFold())
                {
                    continue;
                }
                setCids.insert(item.first);
            }
            return std::move(setCids);
        }

        //矫正分池
        void Context::fixBetPools(map<cid_t, long>& mapBackPool)
        {
            if(_betpool.size() <= 1)
            {
                return;
            }

            //合并分池
            vector<int> vecDelIndex;
            auto setLastCids = getPoolCids(_betpool[0]);
            int lastIndex = 0;
            for(unsigned int i = 1; i < _betpool.size(); i++)
            {
                if(_betpool[i].size() <= 0)
                {
                    vecDelIndex.push_back(i);
                }

                auto setCurCids = getPoolCids(_betpool[i]);
                vector<int> r;
                set_difference(setLastCids.begin(), setLastCids.end(), setCurCids.begin(), setCurCids.end(), inserter(r, r.begin()));

                if(r.size() == 0)//需要合并
                {
                    for(auto item : _betpool[i])
                    {
                        auto it = _betpool[lastIndex].find(item.first);
                        if(it == _betpool[lastIndex].end())
                        {
                            _betpool[lastIndex].insert(std::make_pair(item.first, item.second));
                        }
                        else
                        {
                            it->second += item.second;
                        }
                    }
                    vecDelIndex.push_back(i);
                }
                else
                {
                    setLastCids.clear();
                    for(auto item : setCurCids)
                    {
                        setLastCids.insert(item);
                    }
                    lastIndex = i;
                }
            }

            //删除分池
            map<int, map<cid_t, long>> mapBetPool;
            for(unsigned int i = 0; i < _betpool.size(); i++)
            {
                mapBetPool.insert(std::make_pair(i, _betpool[i]));
            }

            for(auto index : vecDelIndex)
            {
                auto it = mapBetPool.find(index);
                if(it != mapBetPool.end())
                {
                    mapBetPool.erase(it);
                }
            }

            _betpool.clear();
            for(auto betpool : mapBetPool)
            {
                if(betpool.second.size() == 1)//退还的分池
                {
                    auto item = betpool.second;
                    mapBackPool.insert(std::make_pair(item.begin()->first, item.begin()->second));

                    auto it1 = _cid_bet.find(item.begin()->first);
                    if (it1 != _cid_bet.end())
                    {
                        it1->second -= item.begin()->second;
                    }
                    _totalbetnum -= item.begin()->second;

                    User *user = getUserByCid(item.begin()->first);
                    if(user)
                    {
                        user->setDZWealth(user->getDZWealth() + item.begin()->second);
                    }
                }
                else
                {
                    _betpool.push_back(betpool.second);
                }
            }
        }

        //每个奖池中的玩家
        void Context::addPoolCids(int pid, cid_t cid, long bet, bool isRobot)
        {
            auto it = _pool_cids.find(pid);
            if (it == _pool_cids.end())
            {
                std::map<cid_t, long > Item;
                Item.insert(std::make_pair(cid, bet));
                _pool_cids.insert(std::make_pair(pid, Item));
            }
            else
            {
                auto it1 =  it->second.find(cid);
                if (it1 ==  it->second.end())
                {
                    it->second.insert(std::make_pair(cid, bet));
                }
                else
                {
                    it1->second += bet;
                }
            }
        }

        //每个奖池玩家win的筹码
        void Context::addCidPools(cid_t cid, int pid, long change)
        {
            auto it = _cid_pools.find(cid);
            if (it == _cid_pools.end())
            {
                std::map<int, long> subpool;
                subpool.insert(std::make_pair(pid, change));
                //_cid_pools[cid] = subpool;
                _cid_pools.insert(std::make_pair(cid, subpool));
            }
            else
            {
                auto it1 = it->second.find(pid);
                if (it1 == it->second.end())
                {
                    it->second.insert(std::make_pair(pid, change));
                }
                else
                {
                    it1->second += change;
                }
            }
        }

        //每个奖池玩家抽水后获得的筹码
        void Context::calCidPoolsChange(int raio, int limit, long lSmallBlind, bool bFeeDynamic)
        {
            for (auto it : _cid_pools)
            {
                for (auto item : it.second)
                {
                    User *user = getUserByCid(it.first);
                    if (user != NULL)
                    {
                        user->setChangeNum(user->getChangeNum() + item.second);
                    }

                    auto pit = _cid_pools_change.find(it.first);
                    if (pit == _cid_pools_change.end())
                    {
                        std::map<int, long> subpool;
                        subpool.insert(std::make_pair(item.first, item.second));
                        _cid_pools_change.insert(std::make_pair(it.first, subpool));
                    }
                    else
                    {
                        pit->second.insert(std::make_pair(item.first, item.second));
                    }
                }
            }

            if(raio == 0 || getTotalBetnum() <= 3 * lSmallBlind)// 不需要抽水 只有大小盲注时
            {
                return ;
            }

            int player_num = 0;
            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); it++)
            {
                if (it->second._midsit)
                {
                    continue;
                }
                player_num++;
            }

            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); it++)
            {
                long win_change = it->second.getChangeNum() - getUserBetNumNew(it->first);
                if (it->second._midsit || it->second._fold || win_change <= 0)
                {
                    continue;
                }

                //抽水
                long porfie_change = (win_change * raio * 0.001 > limit && limit > 0) ? limit : win_change * raio * 0.001;
                /*if(bFeeDynamic)//2人抽水五折，3，4人 7.5折
                {
                    porfie_change = porfie_change * (player_num == 2 ? 50 : (player_num >= 5 ? 100 : 75)) / 100.00;
                }*/
                if(getTotalBetnum() >= 10000)//如果底池>= 100时,抽水四舍五入
                {
                    int remain_num = porfie_change % 100;
                    if(remain_num != 0)
                    {
                        porfie_change += (remain_num >= 50 ? 100 : 0) - remain_num;
                    }
                }

                DLOG_TRACE("cid: " << it->first<<", winnum: "<< win_change <<", porfie_change: "<< porfie_change << ", player_num: "<< player_num << ", limit: "<< limit << ", bFeeDynamic: "<< bFeeDynamic << ", total:"<< getTotalBetnum()<<",raio:"<<raio<<endl);

                it->second.setChangeNum(it->second.getChangeNum() - porfie_change);
                _cid_pools_profit.insert(std::make_pair(it->first, porfie_change));
            }
        }

        long Context::getUserPorfitByCid(cid_t cid)
        {
            auto it = _cid_pools_profit.find(cid);
            if(it != _cid_pools_profit.end())
            {
                return it->second;
            }
            return 0;
        }
        long Context::getUserRobotPorfitByCid(cid_t cid)
        {
            auto it = _cid_pools_robot_profit.find(cid);
            if(it != _cid_pools_robot_profit.end())
            {
                return it->second;
            }
            return 0;
        }
        void Context::addCidPoolsRobotProfit(cid_t cid, long change)
        {
            auto it = _cid_pools_robot_profit.find(cid);
            if (it == _cid_pools_robot_profit.end())
            {
                _cid_pools_robot_profit.insert(std::make_pair(cid, change));
            }
            else
            {
                it->second +=change;
            }
        }
        string Context::tranCard(short card)
        {
            int suit = card & 0x00f0;
            int face = card & 0x000f;
            auto it = mSuitTran.find(suit);
            if(it == mSuitTran.end())
            {
                return "";
            }

            ostringstream os;
            if(face == 14)
            {
                os << "A";
            }
            else if(face == 13)
            {
                os << "K";
            }
            else if(face == 12)
            {
                os << "Q";
            }
            else if(face == 11)
            {
                os << "J";
            }
            else
            {
                os << face;
            }
            os << it->second;
            return os.str();
        }

        vector<long> Context::checkRobotExit(const string &roomid)
        {
            //检查携带货币
            std::vector<guid_t> robotUid;
            bool isAllRobot = true;
            std::map<cid_t, User> &usermap = refUserMap();
            for (auto it = usermap.begin(); it != usermap.end(); it++)
            {
                if(!it->second.isRobot())
                {
                    isAllRobot = false;
                }
                robotUid.push_back(it->second.getUid());
            }
            // DLOG_TRACE("roomid:" << roomid << ", robot size: " << robotUid.size() << ", iRobotPlayNumLimit:" << _iRobotPlayNumLimit << ", _iRobotPlayNum:" << _iRobotPlayNum);
            if(isAllRobot && ((isRobotPlayNumLimit() && robotUid.size() > 0) ||  robotUid.size() == 1 ))
            {
                setRobotPlayNumLimit(rand() % 5 + 1);
                setRobotPlayNum(0);
                return robotUid;
            }
            robotUid.clear();
            return robotUid;
        }
        long Context::getGameMaxChip()//最大筹码
        {
            long maxChip = 0;
            std::map<cid_t, User> &usermap = refUserMap();
            for (auto it = usermap.begin(); it != usermap.end(); it++)
            {
                if(it->second.getDZWealth() > maxChip)
                {
                    maxChip = it->second.getDZWealth();
                }
            }
            return maxChip;
        }
        int Context::getAiThinkTime()
        {
            if(_totalWeight <= 0) return 0;
            long randNum = rand() % _totalWeight;
            int baseNum = 0;
            for(auto item : _thinkTime){
                baseNum += item[2];
                if(baseNum >= randNum && item.size() == 3 && item[1] > 0){
                    return rand() % (item[1] - item[0]) + item[0];
                }
            }
            return rand() % 8 + 10;
        }

        guid_t Context::getWaitQueue()
        {
            if(_vWaitQueue.size() > 0)
            {
                return _vWaitQueue[0];
            }
            return nil_uid;
        }

        int Context::addWaitQueue(guid_t uid)
        {
            User* user = getUserByUidTail(uid);
            if(!user)
            {
                return -1;
            }
            auto it = std::find(_vWaitQueue.begin(), _vWaitQueue.end(), uid);
            if (it != _vWaitQueue.end())
            {
                return -2;
            }
            _vWaitQueue.push_back(uid);
            return 0;
        }

        int Context::delWaitQueue(guid_t uid)
        {
            auto it = std::find(_vWaitQueue.begin(), _vWaitQueue.end(), uid);
            if (it != _vWaitQueue.end())
            {
                _vWaitQueue.erase(it);
                return 0;
            }
            return -1;
        }

        int Context::getWaitQueueIndexByUid(guid_t uid)
        {
            auto it = std::find(_vWaitQueue.begin(), _vWaitQueue.end(), uid);
            if (it != _vWaitQueue.end())
            {
                return it - _vWaitQueue.begin();
            }
            return -1;
        }

        /*********************牌谱*********************/
        void Context::setCidSeatName(map<cid_t, Pb::E_SEAT_NAME>& mapCidName)
        {
            vector<cid_t> vecCids;
            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); it++)
            {
                if(it->second.isMidSit())
                {
                    continue;
                }
                vecCids.push_back(it->first);
            }

            auto itSeat = mSeatName.find(vecCids.size());
            //大盲位置
            auto itBigBlind = std::find_if(vecCids.begin(), vecCids.end(), [this](int cid)->bool{
                return this->_bigblindcid == cid;
            });
            if(itBigBlind == vecCids.end() || itSeat == mSeatName.end())
            {
                return;
            }

            mapCidName.insert(std::make_pair(this->_smallblindcid, Pb::E_SEAT_NAME(1)));
            mapCidName.insert(std::make_pair(this->_bigblindcid, Pb::E_SEAT_NAME(2)));

            cid_t cur_cid = this->_bigblindcid;
            for(auto iSeatName : itSeat->second)
            {
                if(iSeatName <= 2)
                {
                    continue;
                }
                cur_cid = getNextCid(cur_cid, 9, 1);
                auto it = mapCidName.find(cur_cid);
                if(it != mapCidName.end())
                {
                    continue;
                }
                mapCidName.insert(std::make_pair(cur_cid, Pb::E_SEAT_NAME(iSeatName)));
            }

            for(auto item : mapCidName)
            {
                DLOG_TRACE("cid: " << item.first << ", seat_name: "<< item.second );
            }

           /* unsigned int base_index = std::distance(vecCids.begin(), itBigBlind);
            for(unsigned int i = 0; i< vecCids.size(); i++)
            {
                int index = i > base_index ? i - base_index : i - base_index + vecCids.size();
                mapCidName.insert(std::make_pair(vecCids[i], Pb::E_SEAT_NAME(itSeat->second[index])));
            }
            if(vecCids.size() == 2)
            {
                auto it = mapCidName.find(_bigblindcid);
                if(it != mapCidName.end())
                {
                    it->second = Pb::E_SEAT_NAME(2);
                }
            }*/
        }

        void Context::initGameDetailUserInfo()
        {
            gameDetail.clear_userinfos();
            map<cid_t, Pb::E_SEAT_NAME> mapCidName;
            setCidSeatName(mapCidName);

            for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); it++)
            {
                if (it->second._midsit)
                {
                    continue;
                }
                auto prt = gameDetail.add_userinfos();
                prt->set_lplayerid(it->second._uid);
                prt->set_snickname(it->second._nick);
                prt->set_sheadstr(it->second._url);
                prt->set_iplayergender(it->second._gender);

                for(auto card : it->second._cards)
                {
                    prt->add_hdcards(card);
                }

                auto iter = mapCidName.find(it->first);
                if(iter != mapCidName.end())
                {
                    prt->set_eseatname(iter->second);
                }
            }

            DLOG_TRACE("initGameDetailUserInfo gameDetail: " << logPb(gameDetail) );
            return;
        }
      void Context::addGameDetailUserInfo(long uid,string url,string nick,int gender)  
        {  
            for (auto& userinfo : gameDetail.userinfos()) {  
                if (userinfo.lplayerid() == uid) {  
                    DLOG_TRACE("addGameDetailUserInfo user already exists");
                    return;  
                }  
            }  
            // 添加用户信息到 gameDetail  
            auto prt = gameDetail.add_userinfos();  
            prt->set_lplayerid( uid);  
            prt->set_snickname(nick);  
            prt->set_sheadstr(url);  
            prt->set_iplayergender(gender);  

            // 输出日志  
            DLOG_TRACE("addGameDetailUserInfo uid: " << uid<< ", gameDetail: " << logPb(gameDetail));  
        }  
        void Context::initGameDetailRoomInfo(Pb::RoomInfo& roomInfo)
        {
            gameDetail.mutable_roominfo()->CopyFrom(roomInfo);
        }
        void Context::initGameDetailCalInfo(Pb::CalInfoClub& calInfo, const bool bPaoma)
        {
            Pb::CalInfoClub showDownInfo;
            // 如果是跑马 把跑马数量整合
            if (bPaoma)
            {
                set<long> vIds;
                for(auto& item : calInfo.veccalitem())
                {
                    if(item.isfold() || item.lwincount() <= 0)
                    {
                        continue;
                    }

                    vIds.insert(item.lplayerid());
                }

                for (auto lUid : vIds)
                {
                    // 这个玩家最终赢的钱
                    long lWins = 0;
                    User* user = getUserByUid(lUid);
                    if(user)
                    {
                        lWins = user->getChangeNum() - getUserBetNumNew(user->getCid());
                    }
                    if (lWins <= 0)
                    {
                        continue;
                    }
                    bool bCopy = false;
                    auto ptr = showDownInfo.add_veccalitem();
                    for(auto & item : calInfo.veccalitem())
                    {
                        if(item.isfold() || item.lwincount() <= 0 || item.lplayerid() != lUid)
                        {
                            continue;
                        }

                        if (!bCopy)
                        {
                            ptr->CopyFrom(item);
                            ptr->set_lwincount(lWins);
                        }
                        else
                        {
                            if (item.icardtype() > ptr->icardtype())
                            {
                                ptr->CopyFrom(item);
                                ptr->set_lwincount(lWins);
                            }
                        }
                    }
                }
            }
            else
            {
                // 原来的逻辑
                for(auto& item : calInfo.veccalitem())
                {
                    if(item.isfold() || item.lwincount() <= 0)
                    {
                        continue;
                    }
                    auto ptr = showDownInfo.add_veccalitem();
                    ptr->CopyFrom(item);
                }
            }

            for(auto item : calInfo.vcomcard())
            {
                showDownInfo.add_vcomcard(item);
            }

            showDownInfo.set_lpoolcount(calInfo.lpoolcount());
            showDownInfo.set_ihand(calInfo.ihand());

            showDownInfo.set_linsurecount(calInfo.linsurecount());
            showDownInfo.set_iplayercount(showDownInfo.veccalitem_size());

            gameDetail.mutable_showdowninfo()->CopyFrom(showDownInfo);
            gameDetail.mutable_calinfo()->CopyFrom(calInfo);

            updateDealyRoundStep(Pb::E_ROUND(iEndRound - 3));

            gameDetails.push_back(gameDetail);

            DLOG_TRACE("gameDetail size: " << gameDetails.size() );
        }

        void Context::updateDealyRoundStep(Pb::E_ROUND round)
        {
            if(round == Pb::E_ROUND::E_PREFLOP)//更新preflop底池
            {
                int betCount = 0;
                for(auto& step : gameDetail.stepinfos())
                {
                    if(step.eround() != round || step.iinfotype() == 0)
                    {
                        continue;
                    }
                    betCount += step.ibetcount();
                    betCount -= step.ibackcount();
                }

                for(auto& step : gameDetail.stepinfos())
                {
                    if(step.eround() == round && step.iinfotype() == 0)
                    {
                        const_cast<Pb::StepInfoClub &>(step).set_lpoolcount(betCount);
                    }
                }
            }
            else//更新上轮人数
            {
                int count = 0;
                for (auto it = _cid_user_map.begin(); it != _cid_user_map.end(); it++)
                {
                    if (!it->second._midsit && !it->second._fold)
                    {
                        count++;
                    }
                }

                for(auto& step : gameDetail.stepinfos())
                {
                    if(step.eround() == round && step.iinfotype() == 0)
                    {
                        const_cast<Pb::StepInfoClub &>(step).set_iplayercount(count);
                    }
                }
            }
        }

        //返还多余分池金币
   void Context::updateBackGoldStep(Pb::E_ROUND round, const map<cid_t, long>& mapBackGold)  
    {  
        // 准备倒序遍历游戏步骤  
        for (auto& item : mapBackGold)  
        {  
            for (int index = gameDetail.stepinfos_size() - 1; index >= 0; --index)  
            {  
                Pb::StepInfoClub* step = gameDetail.mutable_stepinfos(index);  

                // 判断步骤是否匹配指定回合  
                if (step->eround() != round) {  
                    continue;  
                }  

                // 根据步骤中的玩家 ID 获取用户对象并检查是否匹配  
                User* user = getUserByUid(step->lplayerid());  
                if (user && user->getCid() == item.first)  
                {  
                    // 更新回退金币数  
                    step->set_ibackcount(item.second);  
                    break;  // 匹配成功后无需继续此玩家的其他步骤  
                }  
            }  
        }  
    }

        void Context::addGameDetailStepInfo(Pb::StepInfoClub& stepInfo)
        {
            auto prt = gameDetail.add_stepinfos();
            prt->CopyFrom(stepInfo);

            if(stepInfo.iinfotype() == 0 && stepInfo.eround() >= Pb::E_ROUND::E_FLOP)
            {
                updateDealyRoundStep(Pb::E_ROUND(stepInfo.eround() - 1));
                DLOG_TRACE("gameDetail: " << logPb(gameDetail) );
            }
        }

        void Context::setUserCollectGame(long uid, map<string, vector<int>>& mapCollectGame)
        {
            auto it = mapUserCollectGame.find(uid);
            if(it != mapUserCollectGame.end())
            {
                it->second = mapCollectGame;
            }
            else
            {
                mapUserCollectGame.insert(std::make_pair(uid, mapCollectGame));
            }
        }

        int Context::addUserCollectGame(long uid, string sBriefID, int round)
        {
            auto it = mapUserCollectGame.find(uid);
            if(it != mapUserCollectGame.end())
            {
                auto subit = it->second.find(sBriefID);
                if(subit != it->second.end())
                {
                    auto iter = std::find(subit->second.begin(), subit->second.end(), round);
                    if(iter == subit->second.end())
                    {
                        subit->second.push_back(round);
                    }
                    else
                    {
                        return -1;
                    }
                }
                else
                {
                    it->second.insert(std::make_pair(sBriefID, vector<int>(1, round)));
                }
            }
            else
            {
                map<string, vector<int>> mapCollectGame;
                mapCollectGame.insert(std::make_pair(sBriefID, vector<int>(1, round)));
                mapUserCollectGame.insert(std::make_pair(uid, mapCollectGame));
            }
            return 0;
        }

        int Context::delUserCollectGame(long uid, string sBriefID, int round)
        {
            auto it = mapUserCollectGame.find(uid);
            if(it != mapUserCollectGame.end())
            {
                auto subit = it->second.find(sBriefID);
                if(subit != it->second.end())
                {
                    auto iter = std::find(subit->second.begin(), subit->second.end(), round);
                    if(iter != subit->second.end())
                    {
                        subit->second.erase(iter);
                        return 0;
                    }
                }
            }
            return -1;
        }

        int Context::getUserCollectGameCount(long uid)
        {
            int count = 0;
            auto it = mapUserCollectGame.find(uid);
            if(it != mapUserCollectGame.end())
            {
                for(auto item : it->second)
                {
                    count += item.second.size();
                }
            }
            return count;
        }

        bool Context::isUserCollectGame(long uid, string sBriefID, int round)
        {
            auto it = mapUserCollectGame.find(uid);
            if(it != mapUserCollectGame.end())
            {
                auto subit = it->second.find(sBriefID);
                if(subit != it->second.end())
                {
                    auto iter = std::find(subit->second.begin(), subit->second.end(), round);
                    return iter != subit->second.end();
                }
            }
            return false;
        }

        void Context::setGameUids(vector<long> uids)
        {
            sGameUids.clear();
            for(auto uid : uids)
            {
                sGameUids.insert(uid);
            }
            DLOG_TRACE("sGameUids size: " << sGameUids.size());
        }

        void Context::setUserGameDetail()
        {
            DLOG_TRACE("sGameUids size: " << sGameUids.size());
            for(auto uid : sGameUids)
            {
                DLOG_TRACE("sGameUids uid: " << uid);
                auto it = mapUserGameDetail.find(uid);
                if(it == mapUserGameDetail.end())
                {
                    mapUserGameDetail.insert(std::make_pair(uid, vector<int>(1, int(gameDetails.size()))));
                }
                else
                {
                    it->second.push_back(int(gameDetails.size()));
                }
            }
        }

        void Context::getGameDetailRound(const long uid, const int index, vector<int> &vecResult)
        {
            auto it = mapUserGameDetail.find(uid);
            if(it != mapUserGameDetail.end())
            {
                if(index == 0)//默认返回最后一把
                {
                    vecResult = {int(it->second.size()) - 1, it->second[int(it->second.size()) - 1]};
                }
                else if(int(it->second.size()) >= index)
                {
                    vecResult = {index - 1, it->second[index - 1]};
                }
            }
            return ;
        }

        int Context::getUserGameDetailCount(const long uid)
        {
            auto it = mapUserGameDetail.find(uid);
            if(it == mapUserGameDetail.end())
            {
                return 0;
            }
            else
            {
                return it->second.size();
            }
        }
        int Context::getProlongCost(int times)
        {
            int cost = 0;
            int freetimes = 0;
            const RoomSo::TGAME_ConstConfig &constCfg = getConstConfig();
            auto it = constCfg.constCfg.find("table_prolangTimes");
            if (it == constCfg.constCfg.end())
            {
                freetimes = it->second;
            }
            if (times>freetimes)
            {
                //拼接字符串 获取次数配置
                stringstream ss;
                ss<<"table_prolangPrice_"<<times;
                DLOG_TRACE("ss.str():"<<ss.str());
                auto it = constCfg.constCfg.find(ss.str());
                if (it == constCfg.constCfg.end())
                {
                    DLOG_TRACE("ss.str()  end :"<<ss.str());
                    auto it_max = constCfg.constCfg.find("table_prolangPrice_max");
                    if (it_max != constCfg.constCfg.end())
                    {
                        cost = it_max->second;
                    }
                }
                else{
                    
                    cost = it->second;
                    DLOG_TRACE("ss.str()  find :"<<ss.str()<<",cost:"<<cost);
                }
            }
            return cost;
        }
        int Context::getshowCommCardCost(int times)
        {
            int cost = 0;
             int freetimes = 0;
            const RoomSo::TGAME_ConstConfig &constCfg = getConstConfig();
            auto it = constCfg.constCfg.find("table_showCommCardTimes");
            if (it != constCfg.constCfg.end())
            {
                freetimes = it->second;
            }
            if (times>=freetimes)
            {
                auto it_max = constCfg.constCfg.find("table_showCommCard");
                if (it_max != constCfg.constCfg.end())
                {
                    cost = it_max->second;
                }
            }
            return cost;
        }
        
        map<cid_t,int> Context::getCidSquidNum()
        {
            return _cid_squid_num;
        }
        void Context::clearSquid(cid_t cid,bool all)
        {
            if (all)
            {
               _cid_squid_num.clear();
               _cid_squid_score.clear();
            }
            else{
                _cid_squid_num.erase(cid);
                _cid_squid_score.erase(cid);
            }
        }
        int Context::getSquidMax(int type,int maxseat,int squidnum)
        {
            //人数+额外数
            if (type == 1)
            {
                return squidnum + maxseat;
            }
            else
            {
                int playerNum = 0;
                std::map<cid_t, User> const &usermap = getUserMap();
                for (auto it = usermap.begin(); it != usermap.end(); it++)
                { 
                    User *tuser = getUserByCid(it->first);
                    if(!tuser || tuser->isMidSit())
                    {
                        continue;
                    }
                    playerNum += 1;
                }
                return playerNum;
            }
            return 0;
        }
        int Context::getSquidLeft(int type,int maxseat,int squidnum)
        {
            int maxSquid = getSquidMax(type,maxseat,squidnum);
            int hasSquid = 0;
            auto &mapCidSquidNum = refCidSquidNum();
            for (auto it:mapCidSquidNum)
            {
                hasSquid += it.second;
            }
            return  maxSquid - hasSquid;
        }
    };
};
