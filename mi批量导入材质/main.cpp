#include <iostream>
#include <stdio.h>
#include<vector>
#include <Windows.h>
#include <fstream>  
#include <iterator>
#include <string>
#include <time.h>
#include <fstream>
#include <istream>
#include <stdlib.h>
#include <string.h>
using namespace std;

char filename[1000],projectname[1000],resourceflag[15], id[16],word = 0x22,noneflag;
ifstream infile;
string s;
int num,location,counter = 1, skinflag;
#define MAX_PATH 1024  //�·������

/*----------------------------
* ���� : �ݹ�����ļ��У��ҵ����а����������ļ�
*----------------------------
* ���� : find
* ���� : public
*
* ���� : lpPath [in]      ��������ļ���Ŀ¼
* ���� : fileList [in]    ���ļ����Ƶ���ʽ�洢��������ļ�
*/
void find(char* lpPath, std::vector<std::string> &fileList)
{
	char szFind[MAX_PATH];
	WIN32_FIND_DATA FindFileData;

	strcpy(szFind, lpPath);
	strcat(szFind, "\\*.*");

	HANDLE hFind = ::FindFirstFile(szFind, &FindFileData);
	if (INVALID_HANDLE_VALUE == hFind)    return;

	while (true)
	{
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//����һ�ν���������ļ�,��ȡ�ļ����б�
		{
			if (FindFileData.cFileName[0] != '.')
			{
				char szFile[MAX_PATH];
				strcpy(szFile, lpPath);
				strcat(szFile, "\\");
				strcat(szFile, (char*)(FindFileData.cFileName));
				find(szFile, fileList);
			}
		}
		else
		{
			//std::cout << FindFileData.cFileName << std::endl; //����ļ����������ļ�������
			fileList.push_back(FindFileData.cFileName);
		}
		if (!FindNextFile(hFind, &FindFileData))    break;
	}
	FindClose(hFind);
}

int main()
{
	srand(time(0));
	cout << "��ӭʹ��Mine_imator��ͼ�������빤�ߣ��������ɿ��嶯���ṩ" << endl << endl;
	Sleep(2000);
	cout << "�ڵ���֮ǰ���뽫������ͼ����Mine_imator�����ļ���" << endl << endl;
	Sleep(2000);
	cout << "Ȼ���뽫����Ҫ����Ĳ��ʷ�����һ���ļ����У�Ȼ��������ļ��е�·�������س�����:" << endl << endl;
	cin.getline(filename,1000);
	cout << "�����빤���ļ�(.miproject)��·�������س�����:" << endl << endl;
	cin.getline(projectname, 1000);
	//cout << "�Ƿ���Ҫ��������Ƥ��skin����Ҫ������1������Ҫ������2" << endl << endl;
	//cin >> skinflag;
	std::vector<std::string> fileList;//����һ����Ž���ļ����Ƶ�����
	find(filename, fileList);//֮��ɶ��ļ��б��е��ļ�������Ӧ�Ĳ���
	infile.open(projectname, ios::in);
	//ofstream outfile(projectname, ios::out);
	infile.seekg(0, ios::end);
	long length = infile.tellg();
	infile.seekg(0);
	cout << "miproject���ȣ�" << length << endl;
	while (getline(infile, s)) {
		num++;
		if (s == "\t\"resources\": [")
		{
			cout << "����λ��������" << num << endl;
			location = infile.tellg();
			cout << "����λ���ֽ�����" << location << endl; \
			getline(infile, s);
			if (s == "\t]") {
				noneflag = 1;
			}
		}
	}
	//for (int i = 0; i < fileList.size(); i++)
	//{
	//	cout << fileList[i] << endl;//����ļ����������ļ�������
	//}
	cout << "��Ҫ����Ĳ�������" << fileList.size() << endl;
	infile.close();
	fstream filein(projectname, ios::binary | ios::out | ios::in);
	filein.seekp(location,ios::beg);
	for (int i = 0; i < fileList.size();i++) {
		for (int j = 0; j < 16; j++) {
			int kind = rand() % 2;
			if (kind == 0) {
				id[j] = 'A' + rand() % (('Z' + 1) - 'A');
			}
			else {
				id[j] = '0' + rand() % (('8' + 1) - '0');
			}
		}
		//if (noneflag == 1 ) {
		//	filein << endl << "\t";
		//	noneflag = 0;
		//}
		if (counter<fileList.size()) {
			filein << "\t\t{\n\t\t\t\"id\": " << word << id[0] << id[1] << id[2] << id[3] << id[4] << id[5] << id[6] << id[7] << id[8] << id[9] << id[10] << id[11] << id[12] << id[13] << id[14] << id[15] << word << ',' << endl << "\t\t\t\"type\": \"texture\", \n\t\t\t\"filename\": \"" << fileList[i] << "\"\n\t\t},\n";
			counter++;
		}
		else {
			filein << "\t\t{\n\t\t\t\"id\": " << word << id[0] << id[1] << id[2] << id[3] << id[4] << id[5] << id[6] << id[7] << id[8] << id[9] << id[10] << id[11] << id[12] << id[13] << id[14] << id[15] << word << ',' << endl << "\t\t\t\"type\": \"texture\", \n\t\t\t\"filename\": \"" << fileList[i] << "\"\n\t\t}";
		}
	}
	//if (skinflag == 1) {
	//	cout << "�ڵ���֮ǰ���뽫����Ƥ��skin����Mine_imator�����ļ���" << endl << endl;
	//	Sleep(2000);
	//	cout << "Ȼ���뽫����Ҫ�����Ƥ��skin������һ���ļ����У�Ȼ��������ļ��е�·�������س�����:" << endl << endl;
	//	cin.getline(filename, 1000);
	//	std::vector<std::string> fileList_skin;//����һ����Ž���ļ����Ƶ�����
	//	find(filename, fileList_skin);//֮��ɶ��ļ��б��е��ļ�������Ӧ�Ĳ���
	//	cout << "��Ҫ�����Ƥ��skin����" << fileList_skin.size() << endl;
	//	counter = 1;
	//	for (int i = 0; i < fileList_skin.size(); i++) {
	//		for (int j = 0; j < 16; j++) {
	//			int kind = rand() % 2;
	//			if (kind == 0) {
	//				id[j] = 'A' + rand() % (('Z' + 1) - 'A');
	//			}
	//			else {
	//				id[j] = '0' + rand() % (('8' + 1) - '0');
	//			}
	//		}
	//		if (counter<fileList_skin.size()) {
	//			filein << "\t\t{\n\t\t\t\"id\": " << word << id[0] << id[1] << id[2] << id[3] << id[4] << id[5] << id[6] << id[7] << id[8] << id[9] << id[10] << id[11] << id[12] << id[13] << id[14] << id[15] << word << ',' << endl << "\t\t\t\"type\": \"skin\", \n\t\t\t\"filename\": \"" << fileList_skin[i] << "\",\n\t\t\t\"player_skin\": true\n\t\t},\n";
	//			counter++;
	//		}
	//		else {
	//			filein << "\t\t{\n\t\t\t\"id\": " << word << id[0] << id[1] << id[2] << id[3] << id[4] << id[5] << id[6] << id[7] << id[8] << id[9] << id[10] << id[11] << id[12] << id[13] << id[14] << id[15] << word << ',' << endl << "\t\t\t\"type\": \"skin\", \n\t\t\t\"filename\": \"" << fileList_skin[i] << "\",\n\t\t\t\"player_skin\": true\n\t\t}";
	//		}
	//	}
	//}
	filein << "\n\t]\n}";
	filein.seekp(location, ios::beg);
	filein.close();
	system("cls");
	Sleep(1000);
	cout<< "���ڵ����С�����������" << endl << endl;
	Sleep(1000);
	cout << "�������������������嶯�����о��ʶ�������ϸ�̵̳�������~~~:" << endl << endl;
	Sleep(2000);
	cout << "�ѳɹ����룡����"  << endl << endl;
	Sleep(1000);
	system("pause");
	return 0;
}
