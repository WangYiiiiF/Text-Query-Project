#include "QueryResult.h"

class TextQuery 
{

public:
	typedef std::vector<std::string>::size_type line_no;
	TextQuery(ifstream&);//构造函数
	QueryResult query(const string&) const;	//查询函数

private:
	shared_ptr<vector<string>> file;	//使用智能指针shared_ptr是为了通过 共享 从而避免拷贝
	map<string, shared_ptr<set<line_no>>> wm;
};

TextQuery::TextQuery(ifstream &is): file(new vector<string>) //使用了成员初始化列表初始化file
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