#include "../lib/generalHeader.h"

int main () {
	User admin;
	admin.active = admin.privilege = 1;
	admin.online = admin.gender = admin.charge = 0;
	strcpy(admin.username, "admin"); strcpy(admin.password, "admin");
	sprintf(admin.fname, "Sina"); sprintf(admin.lname, "Sahabi");
	convert_pass(admin.password);
	system("rm -rf data/log"); system("mkdir data/log");
	clearUserList(); clearSelfList(); clearFoodList(); clearPlanList();
	addUser(admin);
	return 0;
}