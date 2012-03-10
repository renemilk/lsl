#ifndef LSL_TASSERVER_H
#define LSL_TASSERVER_H

#include "iserver.h"

#include <lslutils/type_forwards.h>
#include <boost/format/format_fwd.hpp>

namespace LSL {

class CommandDictionary;
class Server;

class ServerImpl
{
    friend class Server;
private:
    ServerImpl( Server* serv );


	void AcceptAgreement();
	void RequestChannels();
	/*** these are only in this class */
	void Login(const std::string& user, const std::string& password);
	std::string GetPasswordHash(const std::string& pass) const;
	bool IsPasswordHash(const std::string& pass) const;
    int Register(const std::string& addr, const int port, const std::string& nick, const std::string& password, std::string& reason);
	void GetLastUserIP(const std::string& user);
	void GetUserIP(const std::string& user);
	void GetLastLoginTime(const std::string& user);
	void Rename(const std::string& newnick);
	void GetMD5(const std::string& text, const std::string& newpassword);
	void ChangePassword(const std::string& oldpassword, const std::string& newpassword);
	void GetChannelMutelist(const std::string& channel);
	void GetIP(const std::string& user);
	void SendChannelMessage(const std::string& channel, const std::string& message);
	void SetChannelTopic(const std::string& channel, const std::string& topic);
	void GetBanList();
	void UnBanUser(const std::string& user);
	void BanUser(const std::string& user);
	void KickUser(const std::string& user);
	void GetInGameTime(const std::string& user);
	/*** **************************** */

	void ModeratorSetChannelTopic(const std::string &channel, const std::string &topic);
	void ModeratorSetChannelKey(const std::string &channel, const std::string &key);
	void ModeratorMute(const std::string &channel, const std::string &nick, int duration, bool byip);
	void ModeratorUnmute(const std::string &channel, const std::string &nick);
	void ModeratorKick(const std::string &channel, const std::string &reason);
	void ModeratorBan(const std::string &, bool);
	void ModeratorUnban(const std::string &);
	void ModeratorGetIP(const std::string &nick);
	void ModeratorGetLastLogin(const std::string &nick);
	void ModeratorGetLastIP(const std::string &nick);
	void ModeratorFindByIP(const std::string &ipadress);
	void AdminGetAccountAccess(const std::string &);
	void AdminChangeAccountAccess(const std::string &, const std::string &);
	void AdminSetBotMode(const std::string &nick, bool isbot);

	void SendPing();

    void LeaveBattle( const int& battle_id );
    void StartHostedBattle();
    ChannelPtr GetCreatePrivateChannel(const UserPtr user);
    void RemoveUser( const UserPtr user );
    void RemoveChannel( const ChannelPtr chan );
    void RemoveBattle( const IBattlePtr battle );

	void SendMyUserStatus();
	void RequestSpringUpdate(std::string &currentspringversion);
	int GetNewUserId();

	std::string GetBattleChannelName(const BattlePtr battle);

private:
	void ExecuteCommand( const std::string& cmd, std::string& inparams );
	void ExecuteCommand( const std::string& cmd, std::string& inparams, int replyid );

	void OnNewUser( const std::string& nick, const std::string& country, int cpu, int id );


	void SendCmd( const std::string& command, const std::string& param = "" );
	void SendCmd( const std::string& command, const boost::format& param );
	void SendRaw(const std::string &raw);
	void RequestInGameTime(const std::string &nick);

    void JoinChannel( const std::string& channel, const std::string& key );
    void PartChannel( const std::string& channel );

    void DoActionChannel( const std::string& channel, const std::string& msg );
    void SayChannel( const std::string& channel, const std::string& msg );

    void SayPrivate( const std::string& user, const std::string& msg );
    void DoActionPrivate( const std::string& user, const std::string& msg );

    void SayBattle( const int battle_id, const std::string& msg );
    void DoActionBattle( const int battle_id, const std::string& msg );

    void Ring(const ConstUserPtr user );
    void _Disconnect(const std::string& reason);
    void _Ping();
    void _JoinChannel( const std::string& channel, const std::string& key );
    void _JoinBattle( const IBattlePtr battle, const std::string& password, const std::string& scriptpassword );
    void _HostBattle( Battle::BattleOptions bo );
    void _StartHostedBattle();
    void _LeaveBattle( const IBattlePtr battle);

    friend class CommandDictionary;
    CommandDictionary* m_cmd_dict;

	MutexWrapper<unsigned int> m_last_id;
	unsigned int& GetLastID()
	{
		ScopedLocker<unsigned int> l_last_id(m_last_id);
		return l_last_id.Get();
	}

    std::string m_delayed_open_command;
    std::string m_agreement;
    unsigned int m_account_id_count;
    MuteList m_mutelist;
    std::string m_mutelist_current_channelname;

private:
	//! command handlers
    void OnConnected( const std::string&, const int, const std::string&, const int);
    void OnMotd( const std::string& msg );
    void OnLoginInfoComplete();
    void OnChannelListEnd();
    void OnServerMessage( const std::string& message );
    void OnServerMessageBox( const std::string& message );
    void OnJoinBattleFailed( const std::string& msg );
    void OnOpenBattleFailed( const std::string& msg );
    void OnLoginFailed( const std::string& reason );
    void OnServerBroadcast( const std::string& message );
    void OnRedirect( const std::string& address, int port );
	void OnBattleOpened(int id, Enum::BattleType type, Enum::NatType nat, const std::string &nick, const std::string &host, int port, int maxplayers, bool haspass, int rank, const std::string &maphash, const std::string &map, const std::string &title, const std::string &mod);
	void OnUserStatusChanged(const std::string &nick, int intstatus);
	void OnHostedBattle(int battleid);
	void OnUserQuit(const std::string &nick);
	void OnSelfJoinedBattle(int battleid, const std::string &hash);
	void OnStartHostedBattle();
	void OnClientBattleStatus(const std::string &nick, int intstatus, int colorint);
	void OnUserJoinedBattle(int battleid, const std::string &nick, const std::string &userScriptPassword);
	void OnUserLeftBattle(int battleid, const std::string &nick);
    void OnBattleInfoUpdated(int battleid, int spectators, bool locked, const std::string &maphash, const std::string &mapname);
    void OnSetBattleOption(std::string key, const std::string &value);
    void OnSetBattleInfo(std::string infos);
	void OnAcceptAgreement();
	void OnBattleClosed(int battleid);
	void OnBattleDisableUnits(const std::string &unitlist);
	void OnBattleDisableUnit(const std::string &unitname, int count);
	void OnBattleEnableUnits(const std::string &unitnames);
	void OnBattleEnableAllUnits();
	void OnJoinChannel(const std::string &channel, const std::string& rest);
	void OnJoinChannelFailed(const std::string &channel, const std::string &reason);
	void OnChannelJoin(const std::string &name, const std::string &who);
	void OnChannelJoinUserList(const std::string &channel, const std::string &usernames);
	void OnJoinedBattle(const int battleid, const std::string msg);
	void OnGetHandle();
	void OnLogin(const std::string& msg);
	void OnUserJoinedChannel(const std::string &channel_name, const std::string &who);
	void OnChannelSaid(const std::string &channel, const std::string &who, const std::string &message);
	void OnChannelPart(const std::string &channel, const std::string &who, const std::string &message);
	void OnChannelTopic(const std::string &channel, const std::string &who, int, const std::string &message);
	void OnChannelAction(const std::string &channel, const std::string &who, const std::string &action);
	void OnSayPrivateMessageEx(const std::string &user, const std::string &action);
	void OnSaidPrivateMessageEx(const std::string &user, const std::string &action);
	void OnSayPrivateMessage(const std::string &user, const std::string &message);
	void OnSaidPrivateMessage(const std::string &user, const std::string &message);
	void OnSaidBattle(const std::string &nick, const std::string &msg);
	void OnBattleAction(const std::string &nick, const std::string &msg);
	void OnBattleStartRectAdd(int allyno, int left, int top, int right, int bottom);
	void OnBattleStartRectRemove(int allyno);
	void OnScriptStart();
	void OnScriptLine(const std::string &line);
	void OnScriptEnd();
	void OnMutelistBegin(const std::string &channel);
    void OnMutelistItem(const std::string &mutee, const std::string &message);
	void OnMutelistEnd();
	void OnChannelMessage(const std::string &channel, const std::string &msg);
	void OnRing(const std::string &from);
	void OnKickedFromBattle();
    void OnKickedFromChannel(const std::string &channel, const std::string &fromWho, const std::string &message);
	void OnMyInternalUdpSourcePort(const unsigned int udpport);
	void OnMyExternalUdpSourcePort(const unsigned int udpport);
	void OnClientIPPort(const std::string &username, const std::string &ip, unsigned int udpport);
	void OnHostExternalUdpPort(const int udpport);
	void OnChannelListEntry(const std::string &channel, const int &numusers, const std::string &topic);
	void OnAgreenmentLine(const std::string &line);
	void OnRequestBattleStatus();
	void OnBattleAddBot(int battleid, const std::string &nick, const std::string &owner, int intstatus, int intcolor, const std::string &aidll);
	void OnBattleUpdateBot(int battleid, const std::string &nick, int intstatus, int intcolor);
	void OnBattleRemoveBot(int battleid, const std::string &nick);
	void OnFileDownload(int intdata, const std::string &FileName, const std::string &url, const std::string &description);

    void RelayCmd( const std::string& command, const std::string& param = "" );
    void RelayCmd( const std::string& command, const boost::format& param );
    void SendHostInfo(Enum::HostInfo update);
    void SendHostInfo(int type, const std::string &key);
    void SendHostInfo(const std::string& tag );

private:
    std::map<std::string,std::string> m_channel_pw;  /// channel name -> password, filled on channel join

    int m_keepalive; //! in seconds
    int m_ping_timeout; //! in seconds
    int m_ping_interval; //! in seconds
    int m_server_rate_limit; //! in bytes/sec
    std::string m_min_required_spring_ver;
    std::string m_last_denied_connection_reason;
    std::string m_server_name;
    std::string m_server_ver;
    std::string m_last_relay_host_password;
    PingThread* m_ping_thread;
    std::string m_buffer;
    std::string m_addr;
    std::string m_last_denied;
    bool m_redirecting;
    bool m_connected;
    bool m_online;
    int m_udp_private_port;
    int m_nat_helper_port;
    int m_udp_reply_timeout;
    time_t m_last_udp_ping;

    MutexWrapper<unsigned int> m_last_ping_id;
    unsigned int& GetLastPingID()
    {
        ScopedLocker<unsigned int> l_last_ping_id(m_last_ping_id);
        return l_last_ping_id.Get();
    }
    MutexWrapper<PingList> m_pinglist;
    PingList& GetPingList()
    {
        ScopedLocker<PingList> l_pinglist(m_pinglist);
        return l_pinglist.Get();
    }

    UserPtr m_relay_host_manager;



    UserVector m_relay_masters;
    Socket* m_sock;
    void HandlePong( int replyid );
    CRC m_crc;
    IBattlePtr m_current_battle;
    UserPtr m_relay_host_bot;
    int m_message_size_limit; //! in bytes
    UserPtr m_me;
    Battle::BattleList m_battles;
    UserList m_users;
    ChannelList m_channels;
    Server* m_iface;
};

} //namespace LSL

/**
 * \file tasserver.h
 * \section LICENSE
Copyright 2012 by The libSpringLobby team. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

#endif // LSL_TASSERVER_H
