#ifndef _MATRIX_H
#define _MATRIX_H

//�������ݽṹ
//��ά����
class _Matrix{
private:
public:
	int m;
	int n;
	float *arr;
	
	_Matrix(int mm = 0,int nn = 0);

	void free_matrix();
	//��ȡi,j���������
	//ʧ�ܷ���-31415,�ɹ�����ֵ
	float read(int i,int j);
	//д��i,j���������
	//ʧ�ܷ���-1,�ɹ�����1
	int write(int i,int j,float val);

	void display();

};

#endif