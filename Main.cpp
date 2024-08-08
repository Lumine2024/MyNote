#include<bits/stdc++.h>
#include<Windows.h>
using namespace std;
fstream Note;
class note {
public:
	string title;
	string content;
	int id;
};
vector<note> notes;
bool load() {
	Note.open("notes.txt", ios::in);
	if (Note.is_open()) {
		string s, title, content;
		int id;
		while (getline(Note, s, '\n')) {
			Note >> id; 
			getline(Note, s, ' ');
			getline(Note, title, '$');
			getline(Note, content, '$');
			note n;
			n.id = id;
			n.title = title;
			n.content = content;
			notes.push_back(n);
		}
	}
	Note.close();
	return true;
}
bool save() {
	Note.open("notes.txt", ios::out);
	if (Note.is_open()) {
		for (auto n : notes) {
			Note <<"\n"<< n.id << " " << n.title << "$" << n.content << "$";
		}
	}
	Note.close();
	return true;
}
vector<note> search(vector<note>& sea, string key) {
	vector<note> res;
	for (auto s : sea) {
		if (s.title.find(key) != string::npos) {
			res.push_back(s);
		}
	}
	return res;
}
bool readnote(vector<note>& sea, int n) {
	system("cls");
	cout << "标题：" << sea[n].title << "\n内容：\n" << sea[n].content<<"\n";
	system("pause");
	return true;
}
bool modifynote(vector<note>& sea, int n) {
	system("cls");
	string title, content;
	cout << "原来的标题为："<<sea[n].title<<"\n"<<"请输入修改后的标题，输入“$”结束：";
	getline(cin, title, '$');
	title.erase(title.begin());//他妈的，不知道为什么getline的时候会在开头自动加个换行'\n'，我要疯掉了
	cout << "原来的内容为：\n" << sea[n].content << "\n请输入修改后的内容，输入“$”结束：\n";
	getline(cin, content, '$');
	content.erase(content.begin());
	cout << "修改成功！\n";
	sea[n].title = title;
	sea[n].content = content;
	system("pause");
	return true;
}
int main() {
	load();
	SYSTEMTIME t;
	int m;
	while (1) {
		system("cls");
		cout << "欢迎回来\n按1读取文档，按2添加文档，按3修改文档，按4删除文档，按0退出\n";
		GetLocalTime(&t);
		if (notes.size() != 0) {
			cout << "             " << notes[t.wMilliseconds % notes.size()].title << "\n";
		}
		cout << t.wYear << "/" << t.wMonth << "/" << t.wDay << "   ";
		if (t.wHour < 10) {
			cout << "0" << t.wMonth << ":";
		}
		else {
			cout << t.wHour << ":";
		}
		if (t.wMinute < 10) {
			cout << "0" << t.wMinute << "\n";
		}
		else {
			cout << t.wMinute << "\n";
		}
		if (t.wHour < 6 || t.wHour >= 23) {
			cout << "时间不早啦，注意休息！\n";
		}
		else if (t.wHour > 6 && t.wHour <= 12) {
			cout << "早上好，今天也是活力满满的一天！\n";

		}
		else if (t.wHour > 12 && t.wHour <= 18) {
			cout << "下午好，继续努力工作吧！\n";
		}
		else if (t.wHour > 18 && t.wHour <= 23) {
			cout << "晚上好，把今天的工作势头坚持下去吧！坚持就是胜利！\n";
		}
		cin >> m;
		if (notes.size() == 0 && m != 2) {
			cout << "当前没有文档，请先添加！\n";
			system("pause");
			continue;
		}
		switch (m) {
		case 1:
			system("cls");
			cout << "请输入需要读取的文档编号，输入0搜索\n";
			for (auto it : notes) {
				cout << it.id << ".    " << it.title << "\n";
			}
			cin >> m;
			if (m == 0) {
				string key;
				cout << "请输入搜索关键词\n";
				cin >> key;
				vector<note> result = search(notes, key);
				for (auto it : result) {
					cout << it.id << ".    " << it.title << "\n";
				}
				cin >> m;
			}
			if (m > notes.size()) {
				cout << "请输入正确的文档编号！\n";
				system("pause");
				break;
			}
			readnote(notes, m - 1);
			break;
		case 2: {
			system("cls");
			string Title, Content;
			cout << "请输入标题，输入“$”结束：";
			getline(cin, Title, '$');
			Title.erase(Title.begin());
			cout << "请输入内容，输入“$”结束：\n";
			getline(cin, Content, '$');
			Content.erase(Content.begin());
			note n;
			n.id = notes.size() + 1;
			n.title = Title;
			n.content = Content;
			notes.push_back(n);
			cout << "添加成功！\n";
			system("pause");
			save();
			break;
		}
		case 3:
			system("cls");
			cout << "请输入需要修改的文档编号，输入0搜索\n";
			for (auto it : notes) {
				cout << it.id << ".    " << it.title << "\n";
			}
			cin >> m;
			if (m == 0) {
				string key;
				cout << "请输入搜索关键词\n";
				cin >> key;
				vector<note> result = search(notes, key);
				for (auto it : result) {
					cout << it.id << ".    " << it.title << "\n";
				}
				cin >> m;
			}
			if (m > notes.size()) {
				cout << "请输入正确的文档编号！\n";
				system("pause");
				break;
			}
			modifynote(notes, m - 1);
			save();
			break;
		case 4:
			system("cls");
			cout << "请输入需要删除的文档编号，输入0搜索\n";
			for (auto it : notes) {
				cout << it.id << ".    " << it.title << "\n";
			}
			cin >> m;
			if (m == 0) {
				string key;
				cout << "请输入搜索关键词\n";
				cin >> key;
				vector<note> result = search(notes, key);
				cout << "请输入需要删除的文档编号";
				for (auto it : result) {
					cout << it.id << ".    " << it.title << "\n";
				}
				cin >> m;
			}
			if (m > notes.size()) {
				cout << "请输入正确的文档编号！\n";
				system("pause");
				break;
			}
			int k;
			cout << "确认要删除" << m << "号文档吗？\n输入1表示确认，输入0表示取消";
			cin >> k;
			if (k) {
				notes.erase(notes.begin() + m - 1);
				for (int i = m - 1; i < notes.size(); i++) {
					notes[i].id--;
				}
				cout << "删除成功！\n";
				system("pause");
			}
			else {
				cout << "已取消删除\n";
				system("pause");
			}
			save();
			break;
		case 0:
			save();
			return 0;
		}
	}
	save();
	return 0;
}
