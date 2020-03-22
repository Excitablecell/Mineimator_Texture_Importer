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
#define MAX_PATH 1024  //最长路径长度

/*----------------------------
* 功能 : 递归遍历文件夹，找到其中包含的所有文件
*----------------------------
* 函数 : find
* 访问 : public
*
* 参数 : lpPath [in]      需遍历的文件夹目录
* 参数 : fileList [in]    以文件名称的形式存储遍历后的文件
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
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//遍历一次结果的所有文件,获取文件名列表
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
			//std::cout << FindFileData.cFileName << std::endl; //输出文件夹下所有文件的名称
			fileList.push_back(FindFileData.cFileName);
		}
		if (!FindNextFile(hFind, &FindFileData))    break;
	}
	FindClose(hFind);
}

int main()
{
	srand(time(0));
	cout << "欢迎使用Mine_imator贴图批量导入工具，本工具由亢体动画提供" << endl << endl;
	Sleep(2000);
	cout << "在导入之前，请将所有贴图放入Mine_imator工程文件夹" << endl << endl;
	Sleep(2000);
	cout << "然后请将所有要导入的材质放入另一个文件夹中，然后输入该文件夹的路径，按回车结束:" << endl << endl;
	cin.getline(filename,1000);
	cout << "请输入工程文件(.miproject)的路径，按回车结束:" << endl << endl;
	cin.getline(projectname, 1000);
	//cout << "是否需要批量导入皮肤skin？需要请输入1，不需要请输入2" << endl << endl;
	//cin >> skinflag;
	std::vector<std::string> fileList;//定义一个存放结果文件名称的链表
	find(filename, fileList);//之后可对文件列表中的文件进行相应的操作
	infile.open(projectname, ios::in);
	//ofstream outfile(projectname, ios::out);
	infile.seekg(0, ios::end);
	long length = infile.tellg();
	infile.seekg(0);
	cout << "miproject长度：" << length << endl;
	while (getline(infile, s)) {
		num++;
		if (s == "\t\"resources\": [")
		{
			cout << "材质位置行数：" << num << endl;
			location = infile.tellg();
			cout << "材质位置字节数：" << location << endl; \
			getline(infile, s);
			if (s == "\t]") {
				noneflag = 1;
			}
		}
	}
	//for (int i = 0; i < fileList.size(); i++)
	//{
	//	cout << fileList[i] << endl;//输出文件夹下所有文件的名称
	//}
	cout << "需要导入的材质数：" << fileList.size() << endl;
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
	//	cout << "在导入之前，请将所有皮肤skin放入Mine_imator工程文件夹" << endl << endl;
	//	Sleep(2000);
	//	cout << "然后请将所有要导入的皮肤skin放入另一个文件夹中，然后输入该文件夹的路径，按回车结束:" << endl << endl;
	//	cin.getline(filename, 1000);
	//	std::vector<std::string> fileList_skin;//定义一个存放结果文件名称的链表
	//	find(filename, fileList_skin);//之后可对文件列表中的文件进行相应的操作
	//	cout << "需要导入的皮肤skin数：" << fileList_skin.size() << endl;
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
	cout<< "正在导入中………………" << endl << endl;
	Sleep(1000);
	cout << "上哔哩哔哩搜索：亢体动画，有精彩动画和详细教程等着你噢~~~:" << endl << endl;
	Sleep(2000);
	cout << "已成功导入！！！"  << endl << endl;
	Sleep(1000);
	system("pause");
	return 0;
}
