/************************************************************************
*
* vapor3D Server � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#include "Editor/API.h"

#ifdef ENABLE_PLUGIN_SERVER

#include "Protocol/UserMessages.h"
#include "Protocol/ReplicaMessages.h"
#include "Plugins/Networking/ServerPlugin.h"
#include "Network/Host.h"
#include "Network/Session.h"
#include "Editor.h"

NAMESPACE_EDITOR_BEGIN

//-----------------------------------//

class UserMessagesClient : UserMessageHandler
{
	void handleUserAuthStatus(const SessionPtr&, const UserAuthStatusMessage&) OVERRIDE;
	void handleUserJoin(const SessionPtr&, const UserJoinMessage&) OVERRIDE;
	void handleUserLeave(const SessionPtr&, const UserLeaveMessage&) OVERRIDE;
};

REFLECT_CHILD_CLASS(UserMessagesClient, UserMessageHandler)
REFLECT_CLASS_END()

//-----------------------------------//

void UserMessagesClient::handleUserAuthStatus(const SessionPtr& session, const UserAuthStatusMessage&)
{
	ReplicaContextRequestMessage ask;
	
	MessagePtr m_ask = MessageCreate(ReplicaMessageIds::ReplicaContextRequest);
	m_ask->write(&ask);

	ServerPlugin* serverPlugin = GetPlugin<ServerPlugin>();
	serverPlugin->host->getPeer()->queueMessage(m_ask, 0);
}

//-----------------------------------//

void UserMessagesClient::handleUserJoin(const SessionPtr& session, const UserJoinMessage& join)
{
	LogInfo("User '%s' joined network session", join.name.c_str());
	
	User user;
	user.id = join.user;
	user.name = join.name;
	user.session = session;

	users.addUser(user);
}

//-----------------------------------//

void UserMessagesClient::handleUserLeave(const SessionPtr&, const UserLeaveMessage& leave)
{
	User* user = users.getUserFromId(leave.user);
	LogInfo("User '%s' left network session", user->name.c_str());
	users.removeUser(*user);
}

//-----------------------------------//

NAMESPACE_EDITOR_END

#endif