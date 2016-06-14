#ifndef TRIANGLE_H
#define TRIANGLE_H
class Triangle
{
public:
    Triangle();
    int p[3];//三个端点
    double value;//权值
    int tode[2];//最小权值的边
    bool operator >   (const Triangle& rhs )   const //升序排序时必须写的函数
    {
    return value > rhs.value;
    }
};

#endif // TRIANGLE_H
