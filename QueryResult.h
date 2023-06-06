#include "Include.h"

class QueryResult {

friend ostream& print(ostream&, const QueryResult&);

public:
	typedef std::vector<std::string>::size_type line_no;
	QueryResult(string s, 
				shared_ptr<set<line_no>> p, 
				shared_ptr<vector<string>> f): 
		sought(s), lines(p), file(f) {}

private:
	string sought;	//��ѯ����
	shared_ptr<set<line_no>> lines;	//���ֵ��к�
	shared_ptr<vector<string>> file;			//�����ļ�
};

ostream& print(ostream& os, const QueryResult& qr)
{
	os << qr.sought << " occurs " << qr.lines->size() << " " << "time(s)" << endl;
	for (auto num : *qr.lines)
		os << "\t(line " << num + 1 << ") "<< *(qr.file->begin() + num) << endl;
	return os;
}