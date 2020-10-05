#pragma once
#include <sqlite3.h>
#include <string>
#include <vector>

class Database
{
private:
	sqlite3* m_db;

public:
	void OnInit();
	void CreateScoreTable();
	void InsertToScoreTable(std::string username, int score);
	int GetMaxScoreID();
	std::vector<std::pair<std::string, int>> GetScoreList();
};

