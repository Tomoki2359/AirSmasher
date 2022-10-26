#include "Math.h"

float Math::Det(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c)
{
    return a.x * b.y * c.z +
           a.z * b.x * c.y +
           a.y * b.z * c.x -
           a.z * b.y * c.x -
           a.y * b.x * c.z -
           a.x * b.z * c.y;
}

bool Math::Intersect(XMFLOAT3 start, XMFLOAT3 dir, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, XMFLOAT3* s1, XMFLOAT3* s2, float* length)
{
    //1�ӂ̒��������߂�
    XMFLOAT3 e01 = XMFLOAT3{ v1.x - v0.x,v1.y - v0.y, v1.z - v0.z };
    XMFLOAT3 e02 = XMFLOAT3{ v2.x - v0.x,v2.y - v0.y, v2.z - v0.z };
    XMFLOAT3 d = XMFLOAT3(start.x - v0.x, start.y - v0.y, start.z - v0.z);
    dir = XMFLOAT3(-dir.x, -dir.y, -dir.z);
    //start.x = start.x - v0.x;
    //start.y = start.y - v0.y;
    //start.z = start.z - v0.z;
    //dir = XMFLOAT3(-dir.x, -dir.y, -dir.z);
    //u,v,l�̓��������߂�
    //XMFLOAT3 result = XMFLOAT3{Det(start,e02,dir)/Det(e01,e02,dir),Det(e01,start,dir) / Det(e01,e02,dir),Det(e01,e02,start) / Det(e01,e02,dir) };
    float u = Math::Det(d, e02, dir) / Math::Det(e01, e02, dir);
    float v = Math::Det(e01, d, dir) / Math::Det(e01, e02, dir);
    float l = Math::Det(e01, e02, d) / Math::Det(e01, e02, dir);
    //*length = l;
    if (u >= 0 && u <= 1 && v >= 0 && v <= 1 && (u + v) <= 1 && l >= 0)
    {
            *length = l;
            *s1 = e01;
            *s2 = e02;
        
        return true;
    }
    //u�̓�����0���傫��1��菬������
    //if (0 <= result.x  && result.x <= 1);
    //{
    //    //v�̓�����0���傫��1��菬������
    //    if (0 <= result.y && result.y <= 1)
    //    {
    //        //u+v�̓�����0���傫��1��菬������
    //        if (result.x + result.y <= 1)
    //        {
    //            //l��0���傫����
    //            if (0 <= result.z)
    //            {
    //                return true;
    //            }
    //        }
    //    }
    //}
    return false;
}
