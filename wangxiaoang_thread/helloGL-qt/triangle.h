#ifndef TRIANGLE_H
#define TRIANGLE_H
class Triangle
{
public:
    Triangle();
    int p[3];//�����˵�
    double value;//Ȩֵ
    int tode[2];//��СȨֵ�ı�
    bool operator >   (const Triangle& rhs )   const //��������ʱ����д�ĺ���
    {
    return value > rhs.value;
    }
};

#endif // TRIANGLE_H
