﻿#include "Database.h"
#include "Parsing.h"
#include "sha1.h"
#include <memory>

//'Ανθρωπος

int Database::searchUserByName(string username)
{
	auto uit = _usersMapByName.find(username);
	if (uit != _usersMapByName.end()) return uit->second;
  return -1;
}

vector<string> Database::getUserList() const
{
    vector<string> userList;
    for(auto& user : _usersMapByName)
    {
        userList.push_back(user.first);
    }
    return userList;
}

vector<string> Database::getUserListAvailiableForBlocking() const
{
    vector<string> userList;
    for(auto& user : _usersMapByName)
    {
        if(user.first != "admin")
            userList.push_back(user.first);
    }
    return userList;
}

vector<string> Database::getBlockedUserList() const
{
    vector<string> userList;
    for(auto& user : _blockedUsersMapByName)
    {
        userList.push_back(user.first);
    }
    return userList;
}

string Database::getUserName(int userId) const
{
  for (auto it = _usersMapByName.begin(); it != _usersMapByName.end(); ++it) {
    if (it->second == userId)
      return it->first;
  }
  return "";
}

Database::Database() : _users(), _messages()
{
}

int Database::addUser(string username, string password)
{
	if (!correctName(username)) return -1;
	auto uit = _usersMapByName.find(username);
	if (uit != _usersMapByName.end()) return -2;
	User newUser = User(username, sha1(password));
	_users.push_back(newUser);
  _usersMapByName.insert({ username, newUser.getUserID() });
	return newUser.getUserID();
}

int Database::deleteUser(string username)
{
    if (!correctName(username)) return -1;
    auto uit = _usersMapByName.find(username);
    if (uit != _usersMapByName.end())
    {
        _usersMapByName.erase(uit);
    }
    for (vector<User>::iterator it = _users.begin(); it != _users.end();)
    {
        if (it->getuserName() == username)
            it = _users.erase(it);
        else
            ++it;
    }
    return uit->second;
}

int Database::blockUser(string username)
{
    if (!correctName(username)) return -1;
    auto uit = _usersMapByName.find(username);
    if (uit == _usersMapByName.end()) return -2;
    _blockedUsersMapByName.insert(*uit);
    return uit->second;
}

int Database::unblockUser(string username)
{
    if (!correctName(username)) return -1;
    auto uit = _blockedUsersMapByName.find(username);
    if (uit == _blockedUsersMapByName.end()) return -2;
    _blockedUsersMapByName.erase(uit);
    return uit->second;
}

int Database::checkPassword(string username, string password)
{
	int result = -1;
	Hash passHash = sha1(password);
	for (const auto &u : _users)
	{
		result = u.checklogin(username, passHash);
		if (result != -1) return result;
	}
	return result;
}

void Database::addChatMessage(string sender, string text)
{
    auto uit = _usersMapByName.find(sender);
    if (uit != _usersMapByName.end())
    {
        auto uit = _blockedUsersMapByName.find(sender);
        if (uit == _blockedUsersMapByName.end())
        {
            _messages.push_back(Message(sender, text));
        }
    }
}

bool Database::addPrivateMessage(string sender, string target, string message)
{
	int targetUser = searchUserByName(target);
	if (targetUser < 0)
	{
		return false;
	}
    auto uit = _usersMapByName.find(sender);
    if (uit != _usersMapByName.end())
    {
        auto uit = _blockedUsersMapByName.find(sender);
        if (uit == _blockedUsersMapByName.end())
        {
            _messages.push_back(Message(sender, targetUser, message));
        }
    }
	return true;
}

vector<string> Database::getChatMessages()
{
	vector<string> strings;
	for (auto &m: _messages)
	{
		if (m.getDest() == -1)
		{
			strings.push_back("<" + m.getSender() + ">: " + m.getText());
		}
	}
	return strings;
}

vector<Message> Database::getPrivateMessage(int userID)
{
	vector<Message> strings;
	//int userID = searchUserByName(username);
	for (auto &m : _messages)
  {
    if(userID == -1 && m.getDest() != -1)
      strings.push_back(m);
    else if(userID != -1 && m.getDest() == userID)
      strings.push_back(m);
	}
	return strings;
}
