/**
 * # JHMysql Ver, 1.0
 * 
 * Author: Juhoon Kim (kimjuhoon@gmail.com)
 *
 */

#ifndef _JHMYSQL_C_
#define _JHMYSQL_C_

//-------------------------------------------------------------------------------------------//

#include "../mysql/mysql.h"

class JHMysql
{
public:
	MYSQL*			m_pMysql;
	MYSQL_RES*		m_pMyres;
	MYSQL_ROW		m_pMyrow;
	MYSQL_FIELD*	m_pMyfld;
	BOOL			m_bConnected;

public:
	JHMysql();
	virtual ~JHMysql();

public:
	BOOL	connect(char*, char*, char*, char*, int nPort = 3306);
	BOOL	query(char*);
	int		cols();
	int		rows();
	void	fetchRow();
	void	fetchField();
	void	freeResult();
	void	close();
};

//-------------------------------------------------------------------------------------------//

JHMysql::JHMysql()
{
	m_pMyres = NULL;
	m_pMysql = NULL;
	m_pMyfld = NULL;

	m_bConnected = false;
}

JHMysql::~JHMysql()
{

}

BOOL JHMysql::connect(char* pHost, char* pUser, char* pPassword, char* pDatabase, int nPort)
{	
	m_pMysql = mysql_init(NULL);

	if (m_pMysql == NULL)
	{
		return false;
	}

	if (mysql_real_connect(m_pMysql, pHost, pUser, pPassword, pDatabase, nPort, NULL, 0))
	{
		m_bConnected = true;
	}
	else
	{
		return false;
	}
	
	return true;
}

BOOL JHMysql::query(char* pQuery)
{
	if (!mysql_query(m_pMysql, pQuery))
	{
		m_pMyres = mysql_store_result(m_pMysql);
	}
	else
	{
		return false;
	}

	return true;
}

void JHMysql::fetchField()
{
	m_pMyfld = NULL;
	m_pMyfld = mysql_fetch_fields(m_pMyres);
}

void JHMysql::fetchRow()
{
	m_pMyrow = NULL;
	m_pMyrow = mysql_fetch_row(m_pMyres);
}

int JHMysql::cols()
{
	return mysql_num_fields(m_pMyres);
}

int	JHMysql::rows()
{
	return mysql_num_rows(m_pMyres);
}

void JHMysql::freeResult()
{
	mysql_free_result(m_pMyres);
	m_pMyres = NULL;
}

void JHMysql::close()
{
	if (m_bConnected)
	{
		mysql_close(m_pMysql);
		m_bConnected = FALSE;
	}
}

//-------------------------------------------------------------------------------------------//

#endif
