#include "Database.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Game.h"
#include <vector>

void Database::CreateScoreTable()
{
	std::string create_table_sql = "CREATE TABLE IF NOT EXISTS SCOREBOARD (ID integer PRIMARY KEY NOT NULL, NAME TEXT NOT NULL, points integer NOT NULL);";
	char* error_msg = NULL;

	int code = sqlite3_exec(m_db, create_table_sql.c_str(), NULL, 0, &error_msg);

	if (code != SQLITE_OK) {
		std::cerr << "[Error] Create SCOREBOARD Table Fail" << error_msg << std::endl;
		sqlite3_free(error_msg);
	}
	else
		std::cout << "[INFO] SCOREBOARD Table created successfully" << std::endl;
}

int Database::GetMaxScoreID()
{
	char* error_msg = NULL;
	sqlite3_stmt* stmt = NULL;
	const char* data = NULL;
	int max = 0;
	const char* sql = "Select max(ID) from SCOREBOARD;";
	sqlite3_prepare_v2(m_db, sql, -1, &stmt, 0);
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		max = sqlite3_column_int(stmt, 0);
	}
	return max;
}

std::vector<std::pair<std::string, int>> Database::GetScoreList()
{
	std::vector<std::pair<std::string, int>> score_list;
	char* error_msg = NULL;
	sqlite3_stmt* stmt = NULL;
	const char* name = NULL;
	const char* points = NULL;
	std::string row = "";
	const char* sql = "SELECT name, points FROM SCOREBOARD order by points desc LIMIT 10;";
	sqlite3_prepare_v2(m_db, sql, -1, &stmt, 0);
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		name = (const char*)sqlite3_column_text(stmt, 0);
		points = (const char*)sqlite3_column_text(stmt, 1);
		score_list.emplace_back(std::make_pair(name, atoi(points)));
	}
	return score_list;
}

void Database::InsertToScoreTable(std::string username, int score)
{
	char* error_msg = NULL;
	int maxID = GetMaxScoreID();
	std::string insert_sql = "INSERT INTO SCOREBOARD VALUES(" + std::to_string(maxID + 1) + ", '" + username + "', '" + std::to_string(score) + "');";
	int insert_operation = sqlite3_exec(m_db, insert_sql.c_str(), NULL, 0, &error_msg);
	if (insert_operation != SQLITE_OK) {
		std::cerr << "[ERROR] Insert to SCOREBOARD table unsuccessful" << error_msg << std::endl;
		sqlite3_free(error_msg);
	}
	else
		std::cout << "[INFO] Insert to SCOREBOARD table successful" << std::endl;
}

void Database::OnInit()
{
	/* Open database */
	int rc;
	rc = sqlite3_open("test.db", &m_db);
	if (rc) {
		fprintf(stderr, "[ERROR]Can't open database: %s\n", sqlite3_errmsg(m_db));
	}
	else {
		fprintf(stdout, "[INFO]Opened database successfully\n");
	}
}

