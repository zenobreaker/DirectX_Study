#include "Framework.h"
#include "String.h"

#include <locale>
#include <codecvt>

#pragma warning(disable : 4996)

//////////////////////////////////////////////////////////////////////////
///@brief ���ڿ� �ڸ���
///@param orgin : ���� ���ڿ�
///@param InToken : �ڸ� ������ �Ǵ� ���ڿ�
///@return �Ϸ�� ���ڿ� �迭
//////////////////////////////////////////////////////////////////////////
void CString::SplitString(vector<string>* InResult, string InOrigin, string InToken)
{
	InResult->clear();

	int cutAt = 0; //�ڸ� ��ġs
	while ((cutAt = (int)InOrigin.find_first_of(InToken)) != InOrigin.npos)
	{
		if (cutAt > 0) //�ڸ��� ��ġ�� 0����ũ��
			InResult->push_back(InOrigin.substr(0, cutAt));

		InOrigin = InOrigin.substr(cutAt + 1);
	}

	if (InOrigin.length() > 0) //�ڸ��� ���� ���� �ִٸ�
		InResult->push_back(InOrigin.substr(0, cutAt));
}

void CString::SplitString(vector<wstring>* InResult, wstring InOrigin, wstring InToken)
{
	InResult->clear();

	int cutAt = 0; //�ڸ� ��ġs
	while ((cutAt = (int)InOrigin.find_first_of(InToken)) != InOrigin.npos)
	{
		if (cutAt > 0) //�ڸ��� ��ġ�� 0����ũ��
			InResult->push_back(InOrigin.substr(0, cutAt));

		InOrigin = InOrigin.substr(cutAt + 1);
	}

	if (InOrigin.length() > 0) //�ڸ��� ���� ���� �ִٸ�
		InResult->push_back(InOrigin.substr(0, cutAt));
}


//////////////////////////////////////////////////////////////////////////
///@brief ���� ���ڿ��� ������ üũ
///@param InValue : üũ�Ϸ��� ���ڿ�
///@param InCompare : ���� �񱳹��ڿ�
//////////////////////////////////////////////////////////////////////////
bool CString::StartsWith(string InValue, string InCompare)
{
	wstring::size_type index = InValue.find(InCompare);
	if (index != wstring::npos && (int)index == 0)
		return true;

	return false;
}

bool CString::StartsWith(wstring InValue, wstring InCompare)
{
	wstring::size_type index = InValue.find(InCompare);
	if (index != wstring::npos && (int)index == 0)
		return true;

	return false;
}

//////////////////////////////////////////////////////////////////////////
///@brief �ش� ���ڿ��� ���ԵǾ� �ִ���
///@param InValue : üũ�Ϸ��� ���ڿ�
///@param InCompare : �񱳹��ڿ�
//////////////////////////////////////////////////////////////////////////
bool CString::Contain(string InValue, string InCompare)
{
	size_t found = InValue.find(InCompare);

	return found != wstring::npos;
}

bool CString::Contain(wstring InValue, wstring InCompare)
{
	size_t found = InValue.find(InCompare);

	return found != wstring::npos;
}


//////////////////////////////////////////////////////////////////////////
///@brief �ش� ���ڿ����� InCompare ���ڸ� InReplace�� ����
///@param InValue : üũ�Ϸ��� ���ڿ�
///@param InCompare : �񱳹��ڿ�
///@param InReplace : �ٲܹ��ڿ�
//////////////////////////////////////////////////////////////////////////
void CString::Replace(string * InValue, string InCompare, string InReplace)
{
	string temp = *InValue;

	size_t start_pos = 0;
	while ((start_pos = temp.find(InCompare, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, InCompare.length(), InReplace);
		start_pos += InReplace.length();
	}

	*InValue = temp;
}

void CString::Replace(wstring* InValue, wstring InCompare, wstring InReplace)
{
	wstring temp = *InValue;

	size_t start_pos = 0;
	while ((start_pos = temp.find(InCompare, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, InCompare.length(), InReplace);
		start_pos += InReplace.length();
	}

	*InValue = temp;
}

//////////////////////////////////////////////////////////////////////////
///@brief string���� wstring������ ����
///@param value : ��ȯ�� ���ڿ�
///@return ��ȯ �Ϸ� ���ڿ�
//////////////////////////////////////////////////////////////////////////
wstring CString::ToWString(string value)
{
	wstring temp = L"";
	temp.assign(value.begin(), value.end());

	return temp;
}

//////////////////////////////////////////////////////////////////////////
///@brief wstring���� string������ ����
///@param value : ��ȯ�� ���ڿ�
///@return ��ȯ �Ϸ� ���ڿ�
//////////////////////////////////////////////////////////////////////////
string CString::ToString(wstring value)
{
	wstring_convert<codecvt_utf8<wchar_t>> converter;

	return converter.to_bytes(value);
}
string CString::Format(const string format, ...)
{
	va_list args;

	va_start(args, format);
	size_t len = vsnprintf(NULL, 0, format.c_str(), args);
	va_end(args);

	vector<char> vec(len + 1);

	va_start(args, format);
	vsnprintf(&vec[0], len + 1, format.c_str(), args);
	va_end(args);

	return &vec[0];
}

wstring CString::Format(const wstring format, ...)
{
	va_list args;

	va_start(args, format);
	size_t len = _vsnwprintf(NULL, 0, format.c_str(), args);
	va_end(args);

	vector<WCHAR> vec(len + 1);

	va_start(args, format);
	_vsnwprintf(&vec[0], len + 1, format.c_str(), args);
	va_end(args);

	return &vec[0];
}

string CString::ToColor(const FColor& InValue)
{
	return Format("%f,%f,%f,%f", InValue.R, InValue.G, InValue.B, InValue.A);
}

FColor CString::FromColor(const string& InValue)
{
	vector<string> v;
	SplitString(&v, InValue, ",");

	return FColor(stof(v[0]), stof(v[1]), stof(v[2]), stof(v[3]));
}

//////////////////////////////////////////////////////////////////////////