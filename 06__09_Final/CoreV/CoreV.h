// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
//��ı�׼�������� DLL �е������ļ��������������϶���� COREV_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
//�κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ 
// COREV_API ������Ϊ�ǴӴ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef COREV_EXPORTS
#define COREV_API __declspec(dllexport)
#else
#define COREV_API __declspec(dllimport)
#endif

// �����Ǵ� CoreV.dll ������
class COREV_API CCoreV {
public:
	CCoreV(void);
	// TODO: �ڴ�������ķ�����
};

extern COREV_API int nCoreV;

COREV_API int fnCoreV(void);
