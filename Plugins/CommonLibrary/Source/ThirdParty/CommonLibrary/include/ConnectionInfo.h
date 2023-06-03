#pragma once

#ifdef _DEBUG
ADOConnectionInfo CommonAccountDatabaseInfoD(L"SQLOLEDB", L"APEIROGON", L"account_database", L"SSPI", L"NO", L"apeirogon", L"1248", EDBMSTypes::MSSQL);
ADOConnectionInfo CommonGameDatabaseInfoD(L"SQLOLEDB", L"APEIROGON", L"game_database", L"SSPI", L"NO", L"apeirogon", L"1248", EDBMSTypes::MSSQL);
ADOConnectionInfo CommonSharedDatabaseInfoD(L"SQLOLEDB", L"APEIROGON", L"game_database", L"SSPI", L"NO", L"apeirogon", L"1248", EDBMSTypes::MSSQL);
#else
std::wstring serverName = L"project-ld-database.csvni51jms4v.ap-northeast-2.rds.amazonaws.com,1433";
ADOConnectionInfo CommonAccountDatabaseInfo(L"SQLOLEDB", serverName.c_str(), L"account_database", L"SSPI", L"NO", L"admin", L"PRLD23!dev", EDBMSTypes::MSSQL);
ADOConnectionInfo CommonGameDatabaseInfo(L"SQLOLEDB", serverName.c_str(), L"game_database", L"SSPI", L"NO", L"apeirogon", L"PRLD23!dev", EDBMSTypes::MSSQL);
ADOConnectionInfo CommonSharedDatabaseInfo(L"SQLOLEDB", serverName.c_str(), L"shared_database", L"SSPI", L"NO", L"apeirogon", L"PRLD23!dev", EDBMSTypes::MSSQL);
#endif

