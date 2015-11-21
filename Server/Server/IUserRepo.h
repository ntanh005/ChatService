#pragma once
class IUserRepo
{
public:
	IUserRepo();
	~IUserRepo();
	virtual void getUsers() = 0;
	virtual void getFriends(const char *user) = 0;
	virtual int checkUserPass(const char* user, const char* pass) = 0;
	virtual int searchUser(const char* user) = 0;
};

