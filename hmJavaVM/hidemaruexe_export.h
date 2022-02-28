/*
 * Copyright (c) 2017 Akitsugu Komiyama
 * under the Apache License Version 2.0
 */

#pragma once

#include <windows.h>
#include <string>

using namespace std;


// �ȉ��U�́Ahidemaruhandle(0)�ւ�SendMessage�Œl�𓾂�p�^�[��
#define WM_HIDEMARUINFO (WM_USER + 181)
#define HIDEMARUINFO_GETTABWIDTH 0
#define HIDEMARUINFO_GETSTARTCOLUMN 1
#define HIDEMARUINFO_GETSPACETAB 2
#define HIDEMARUINFO_GETMANUALTAB 3
#define HIDEMARUINFO_GETFILEFULLPATH 4

// �ȉ��́A�O���̘g�ł͂Ȃ������́uHM32CLIENT�v�̃E�B���h�E�ɑ���B
// �}�N�����s�����ǂ�����m�邽�߂ɁA�G�ۃ��[�_�[�p�Ƀ��[�U�[���b�Z�[�W������܂��B
#define WM_ISMACROEXECUTING (WM_USER + 167)
#define WM_REMOTE_EXECMACRO_FILE (WM_USER + 271)
#define WM_REMOTE_EXECMACRO_MEMORY (WM_USER + 272)

/*--------------------------------------------------------------------------------------------------------------------------
int WINAPI Hidemaru_GetDllFuncCalledType(int n);
�@ n�� - 1���w�肷��ƁAloaddll�̂������Ԃ��܂��B1�ȏ��loaddll�֐��̕Ԃ�l�Ɠ����ł��B
�@ - 1�̏ꍇ��loaddll���œǂݍ��܂ꂽDLL�ł��B

  �A n��0���w�肷��ƁAdllfunc / dllfuncw / dllfuncstr / dllfuncstrw�̂ǂ�ŌĂ΂ꂽ���ɂ���āAreturn�ŕԂ��ׂ��l�������܂��B
  �@ �ȉ��̒l�̂����ꂩ���Ԃ�܂��B
	--------------------------------------------------------------------------------------------------------------------------*/
#define DLLFUNCRETURN_NOTCALL   0       //�Ă΂�Ă��Ȃ�
#define DLLFUNCRETURN_INT       0x0001  //int��Ԃ��ׂ�(dllfunc�܂���dllfuncw)
#define DLLFUNCRETURN_CHAR_PTR  0x0002  //char*��Ԃ��ׂ�(dllfuncstr)
#define DLLFUNCRETURN_WCHAR_PTR 0x0003  //WCHAR*��Ԃ��ׂ�(dllfuncstrw)
#define DLLFUNCRETURN_DOUBLE    0x0004  //double��Ԃ��ׂ�(dllfunc�܂���dllfuncw�ŕ��������_�����L��)

/*--------------------------------------------------------------------------------------------------------------------------
�B n��1���琔�������Ԃ̒l���w�肷��ƁA1���琔�����p�����[�^�̎�ނ����l / ������ / Unicode������ / ���������_������Ԃ��܂��B
�@ �p�����[�^�̍ő��64�ł��B
  �ȉ��̒l�̂����ꂩ���Ԃ�܂��B
  --------------------------------------------------------------------------------------------------------------------------*/
#define DLLFUNCPARAM_NOPARAM    0       //�ȍ~�̃p�����[�^�Ȃ�
#define DLLFUNCPARAM_INT        0x0100  //int�̃p�����[�^
#define DLLFUNCPARAM_CHAR_PTR   0x0200  //char*�̃p�����[�^
#define DLLFUNCPARAM_WCHAR_PTR  0x0300  //WCHAR*�̃p�����[�^
#define DLLFUNCPARAM_DOUBLE     0x0400  //double�̃p�����[�^

/*--------------------------------------------------------------------------------------------------------------------------
dllfunc�����Ă�ł���ԁA�Ō��dllfunc�����Ă񂾓��e�̂ݎ擾�ł��܂��B
�Ⴆ��dllfunc�֐�����Hidemaru_EvalMacro�ł����dllfunc���Ăяo���ꍇ�A�擾�ł�����͈̂�ԐV�����Ă񂾂��݂̂̂ł��B
--------------------------------------------------------------------------------------------------------------------------*/


class CHidemaruExeExport {
private:

	static HMODULE hHideExeHandle;
	static TCHAR szHidemaruFullPath[MAX_PATH];

public:
	//========================================================================
	// �G�ۖ{�̂̃o�[�W�����B
	//-------------------------------------------------------------------------
	// 8.66��3�Ȃ�A�u866.03�v�݂����Ȋ����ɂȂ�B
	//========================================================================
	static double hm_version;
private:
	static double QueryFileVersion(TCHAR* path);

public:
	//========================================================================
	/// �G�ۖ{�̂���Export����Ă��邢�����̊֐��Q
	//========================================================================
	using PFNGetCurrentWindowHandle = HWND(WINAPI *)(void);
	static PFNGetCurrentWindowHandle Hidemaru_GetCurrentWindowHandle;

	//-------------------------------------------------------------------------
	// ���ݕҏW���̑S�Ẵe�L�X�g�𓾂�
	using PFNGetTotalTextUnicode = HGLOBAL(WINAPI *)(void);
	static PFNGetTotalTextUnicode Hidemaru_GetTotalTextUnicode;

	//-------------------------------------------------------------------------
	// ���ݕҏW���̑I���e�L�X�g�𓾂�(�P���I���̂�)
	using PFNGetSelectedTextUnicode = HGLOBAL(WINAPI *)(void);
	static PFNGetSelectedTextUnicode Hidemaru_GetSelectedTextUnicode;

	//-------------------------------------------------------------------------
	// ���ݕҏW���̃e�L�X�g�̃J�[�\��������s�̃e�L�X�g�𓾂�
	using PFNGetLineTextUnicode = HGLOBAL(WINAPI *)(int nLineNo);
	static PFNGetLineTextUnicode Hidemaru_GetLineTextUnicode;

	//-------------------------------------------------------------------------
	// �w��Ώۂ̃t�@�C���̏G��encode�𓾂�B�G�ێ��̂́u������v-�u�t�@�C���v�[�u�G���R�[�h1�v�̐ݒ�ɏ]���̂Œ��ӁB
	// �ėp�̃G���R�[�h�擾�@�\�ł͂Ȃ��A�g�p�҂��g���Ă���G�ۂ̐ݒ�̌��A���̊Y���̏G�ۂŃt�@�C�����J�����Ƃ�����A
	// ���̃G���R�[�h�ŊJ�����̂����擾����@�\�ƂȂ�B
	using PFNAnalyzeEncoding = int(WINAPI *)(const WCHAR* pwszFileName, DWORD_PTR lParam1, DWORD_PTR lParam2);
	static PFNAnalyzeEncoding Hidemaru_AnalyzeEncoding;

	//-------------------------------------------------------------------------
	// �w��̏G�ۂ�encode���w�肵�āA�t�@�C�����e��ǂݍ���
	using PFNLoadFileUnicode = HGLOBAL(WINAPI *)(const WCHAR* pwszFileName, int nEncode, UINT* pcwchOut, DWORD_PTR lParam1, DWORD_PTR lParam2);
	static PFNLoadFileUnicode Hidemaru_LoadFileUnicode;

	//-------------------------------------------------------------------------
	// ���ݕҏW���̃e�L�X�g�̃J�[�\���̈ʒu���擾����B�}�N����column��lineno����
	using PFNGetCursorPosUnicode = BOOL(WINAPI *)(int* pnLineNo, int* pnColumn);
	static PFNGetCursorPosUnicode Hidemaru_GetCursorPosUnicode;

	using PFNGetCursorPosUnicodeFromMousePos = BOOL(WINAPI *)(POINT* ppt, int* pnLineNo, int* pnColumn);
	static PFNGetCursorPosUnicodeFromMousePos Hidemaru_GetCursorPosUnicodeFromMousePos;

	//-------------------------------------------------------------------------
	// dll�̒�����G�ۃ}�N�������s����
	using PFNEvalMacro = BOOL(WINAPI *)(const wchar_t* pwsz);
	static PFNEvalMacro Hidemaru_EvalMacro;

	//-------------------------------------------------------------------------
	// dll�̌Ă΂ꂩ���A�֐��̌Ă΂��(�Ԃ�l�̗v���^������̗v���^�𔻒�ł���֐�)�B����
	//-------------------------------------------------------------------------
	// dllfunc�����Ă�ł���ԁA�Ō��dllfunc�����Ă񂾓��e�̂ݎ擾�ł��܂��B
	// �Ⴆ��dllfunc�֐�����Hidemaru_EvalMacro�ł����dllfunc���Ăяo���ꍇ�A�擾�ł�����͈̂�ԐV�����Ă񂾂��݂̂̂ł��B
	//-------------------------------------------------------------------------
	using PFNGetDllFuncCalledType = int(WINAPI *)(int n);
	static PFNGetDllFuncCalledType Hidemaru_GetDllFuncCalledType;

	//-------------------------------------------------------------------------
	// n�� - 1���w�肷��ƁAloaddll�̂������Ԃ��܂��B1�ȏ��loaddll�֐��̕Ԃ�l�Ɠ����ł��B - 1�̏ꍇ��loaddll���œǂݍ��܂ꂽDLL�ł��B

	//-------------------------------------------------------------------------
	// n��0���w�肷��ƁAdllfunc / dllfuncw / dllfuncstr / dllfuncstrw�̂ǂ�ŌĂ΂ꂽ���ɂ���āAreturn�ŕԂ��ׂ��l�������܂��B
	// �ȉ��̒l�̂����ꂩ���Ԃ�܂��B
	// dllfunc�����Ă΂�Ă���Ƃ��A�ǂ̂悤�ȌĂ΂�������Ă��邩���擾���܂��B
	enum class DLLFUNCRETURN {
		NOTCALL   = 0,       //�Ă΂�Ă��Ȃ�
		INT       = 0x0001,  //int��Ԃ��ׂ�(dllfunc�܂���dllfuncw)
		CHAR_PTR  = 0x0002,  //char*��Ԃ��ׂ�(dllfuncstr)
		WCHAR_PTR = 0x0003,  //WCHAR*��Ԃ��ׂ�(dllfuncstrw)
		DOUBLE    = 0x0004  //double��Ԃ��ׂ�(dllfunc�܂���dllfuncw�ŕ��������_�����L��)
	};

	//-------------------------------------------------------------------------
	//n��1���琔�������Ԃ̒l���w�肷��ƁA1���琔�����p�����[�^�̎�ނ����l / ������ / Unicode������ / ���������_������Ԃ��܂��B
	// �p�����[�^�̍ő��64�ł��B
	// �ȉ��̒l�̂����ꂩ���Ԃ�܂��B
	enum class DLLFUNCPARAM {
		NOPARAM   = 0,       //�ȍ~�̃p�����[�^�Ȃ�
		INT       = 0x0100,  //int�̃p�����[�^
		CHAR_PTR  = 0x0200,  //char*�̃p�����[�^
		WCHAR_PTR = 0x0300,  //WCHAR*�̃p�����[�^
		DOUBLE    = 0x0400   //double�̃p�����[�^
	};


public:

	//========================================================================
	/// ������
	//========================================================================
	static BOOL init();


	//========================================================================
	/// ���b�v�֐��S
	//========================================================================
private:
	static HWND hCurWndHidemaru;
public:
	static HWND GetCurWndHidemaru();

	static wstring GetFileFullPath();

	//-------------------------------------------------------------------------
	// Hidemaru_GetTotalTextUnicode�֐��̃��b�v��������
	//-------------------------------------------------------------------------
	static wstring GetTotalText();

	//-------------------------------------------------------------------------
	// Hidemaru_GetSelectedTextUnicode�֐��̃��b�v��������
	//-------------------------------------------------------------------------
	static wstring GetSelectedText();

	//-------------------------------------------------------------------------
	// Hidemaru_GetLineTextUnicode�֐��̃��b�v��������
	//-------------------------------------------------------------------------
	static wstring GetLineText(int lineno = 0);

	//-------------------------------------------------------------------------
	// Hidemaru_AnalyzeEncoding�֐��̃��b�v��������
	//-------------------------------------------------------------------------
	static int AnalyzeEncoding(wstring filename);

	//-------------------------------------------------------------------------
	// Hidemaru_LoadFileUnicode�֐��̃��b�v��������
	//-------------------------------------------------------------------------
	static wstring LoadFileUnicode(wstring filename, int nHmEncode, UINT* pcwchOut, DWORD_PTR lParam1, DWORD_PTR lParam2, bool* success);

	//-------------------------------------------------------------------------
	// Hidemaru_GetCursorPosUnicode�֐��̃��b�v��������
	//-------------------------------------------------------------------------
	// ���W�^�BPoint�^�ł́ASystem.Drawing��ǂݍ��܂Ȃ��ƃ_���Ȃ̂ŕ��ׂ�����B�܂��Ax, y�͏G�ۂɕʒl�Ƃ��đ��݂���̂ŁA
	// �����܂ł��A�}�N����column��lineno�ƈ�v���Ă���Ƃ����咣�B
	// column��lineno�̓G�f�B�^�I�ȍ��W�ł���B
	struct HmCursurPos
	{
	public:
		int lineno;
		int column;
		HmCursurPos(int _lineno, int _column)
		{
			this->lineno = _lineno;
			this->column = _column;
		}
	};
	static HmCursurPos GetCursorPos();


	//-------------------------------------------------------------------------
	// Hidemaru_GetCursorPosUnicodeFromMousePos�֐��̃��b�v��������
	// (�G��8.73�ȏ�)
	//-------------------------------------------------------------------------
	struct HmMousePos
	{
	public:
		int x;
		int y;
		int lineno;
		int column;
		HmMousePos(int _x, int _y, int _lineno, int _column)
		{
			this->x = _x;
			this->y = _y;
			this->lineno = _lineno;
			this->column = _column;
		}
	};
	static HmMousePos GetCursorPosFromMousePos();

	//-------------------------------------------------------------------------
	// Hidemaru_EvalMacro�֐��̃��b�v��������
	//-------------------------------------------------------------------------
	static BOOL EvalMacro(wstring);

	// �}�N�������s�����ǂ���
	static bool IsMacroExecuting();

	// �}�N���̃t�@�C�������s����
	static wstring ExecMacroFromFile(wstring szMacroFileName);

	static wstring ExecMacroFromString(wstring cmd);


	//-------------------------------------------------------------------------
	// �A�E�g�v�b�g�p�l��
	//-------------------------------------------------------------------------
	using PFNHmOutputPane_Output = int(_cdecl*)(HWND hwnd, BYTE *);
	static PFNHmOutputPane_Output HmOutputPane_Output;
	using PFNHmOutputPane_OutputW = int(_cdecl*)(HWND hwnd, wchar_t *);
	static PFNHmOutputPane_OutputW HmOutputPane_OutputW;
	using PFNHmOutputPane_Push = int(_cdecl*)(HWND hwnd);
	static PFNHmOutputPane_Push HmOutputPane_Push;
	using PFNHmOutputPane_Pop = int(_cdecl*)(HWND hwnd);
	static PFNHmOutputPane_Pop HmOutputPane_Pop;
	using PFNHmOutputPane_GetWindowHandle = HWND(_cdecl*)(HWND hwnd);
	static PFNHmOutputPane_GetWindowHandle HmOutputPane_GetWindowHandle;
	using PFNHmOutputPane_SetBaseDir = int(_cdecl*)(HWND hwnd, BYTE *);
	static PFNHmOutputPane_SetBaseDir HmOutputPane_SetBaseDir;

};

