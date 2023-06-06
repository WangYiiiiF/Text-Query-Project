#include "QueryResult.h"

class TextQuery 
{

public:
	typedef std::vector<std::string>::size_type line_no;
	TextQuery(ifstream&);//���캯��
	QueryResult query(const string&) const;	//��ѯ����

private:
	shared_ptr<vector<string>> file;	//ʹ������ָ��shared_ptr��Ϊ��ͨ�� ���� �Ӷ����⿽��
	map<string, shared_ptr<set<line_no>>> wm;
};

TextQuery::TextQuery(ifstream &is): file(new vector<string>) //ʹ���˳�Ա��ʼ���б��ʼ��file
{	
	string text;
	while (getline(is, text))
	{
		file->push_back(text);
		int n = file->size() - 1;
		istringstream line(text);
		string word;
		while (line >> word)
		{
			auto& lines = wm[word];
			if (!lines)
				lines.reset(new set<line_no>);
			lines->insert(n);
		}
	}
}

QueryResult TextQuery::query(const string& sought) const
{
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = wm.find(sought);
	if (loc == wm.end())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
}