#pragma once
#include <vector>
using namespace std;

class CFileUtil
{
public:
	CFileUtil(void);
	~CFileUtil(void);
public:
	struct FILE_STRUCT
	{		
		CDuiString fileName;
		CDuiString name;
		CDuiString exName;
		int        size;
	};

	//�򿪶Ի��� lpstrFilter�������ַ���   hwndOwner��������  fileNames�������ļ�·��
	static BOOL OpenFile(LPCWSTR lpstrFilter, HWND hwndOwner,vector<CDuiString> &fileNames, bool IsMulti = true);

	//����ļ��� path��·��  hwndOwner:������  tile:���ڱ���
	static BOOL BrowseDir(CDuiString &path,HWND hwndOwner,CDuiString title);

	//�����ļ����ڵ������ļ� path��·��  lpstrFilter�������ַ���   files���ļ�
	static BOOL BrowseAllFile(CDuiString path,LPCWSTR lpstrFilter,vector<FILE_STRUCT> &files);

	//��һ��·����ѡ��һ���ļ�
	static void OpenDir(HWND hwndOwner,CDuiString path,CDuiString fileName);

	//��һ�������ļ�����ֳɣ��ļ�������չ��
	static void SplitFileName(CDuiString fileName,CDuiString &name,CDuiString &exName);

	//����ļ��Ƿ����
	static BOOL CheckFileExist(CDuiString pathFileName);

	//����ļ���׺�� pstrPath���ļ�·�� pstrExtFilter�������б�
	static bool FindFileExt(LPCTSTR pstrPath, LPCTSTR pstrExtFilter);

	//�ݹ������ǰĿ¼���ļ��ļ�
	static void EnumerateFiles(vector<CDuiString> &vctString);

	//�õ��ļ��Ĵ�С
	static DWORD GetFileSize(LPCTSTR fileName);

	//�ļ���Сת��Ϊ�ַ����� xx.xxM
	static LPCTSTR FileSizeToString(DWORD dwSize);

};

