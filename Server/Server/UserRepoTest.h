#pragma once
#include "IUserRepo.h"
class UserRepoTest : public IUserRepo
{
public:
	UserRepoTest();
	~UserRepoTest();

	void getUsers() ;
	void getFriends(const char *user);
	int checkUserPass(const char* user, const char* pass) ;
	int searchUser(const char* user) ;
};

