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

bool Math::Intersect(XMFLOAT3 start, XMFLOAT3 dir, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, XMFLOAT3* s1, XMFLOAT3* s2, float* length, XMFLOAT3* pos)
{
    //1•Ó‚Ì’·‚³‚ğ‹‚ß‚é
    XMFLOAT3 e01 = XMFLOAT3{ v1.x - v0.x,v1.y - v0.y, v1.z - v0.z };
    XMFLOAT3 e02 = XMFLOAT3{ v2.x - v0.x,v2.y - v0.y, v2.z - v0.z };
    XMFLOAT3 d = XMFLOAT3(start.x - v0.x, start.y - v0.y, start.z - v0.z);
    dir = XMFLOAT3(-dir.x, -dir.y, -dir.z);
    //start.x = start.x - v0.x;
    //start.y = start.y - v0.y;
    //start.z = start.z - v0.z;
    //dir = XMFLOAT3(-dir.x, -dir.y, -dir.z);
    //u,v,l‚Ì“š‚¦‚ğ‹‚ß‚é
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
        *pos = XMFLOAT3{u,l,v};
        return true;
    }
    //u‚Ì“š‚¦‚ª0‚æ‚è‘å‚«‚­1‚æ‚è¬‚³‚¢‚©
    //if (0 <= result.x  && result.x <= 1);
    //{
    //    //v‚Ì“š‚¦‚ª0‚æ‚è‘å‚«‚­1‚æ‚è¬‚³‚¢‚©
    //    if (0 <= result.y && result.y <= 1)
    //    {
    //        //u+v‚Ì“š‚¦‚ª0‚æ‚è‘å‚«‚­1‚æ‚è¬‚³‚¢‚©
    //        if (result.x + result.y <= 1)
    //        {
    //            //l‚Í0‚æ‚è‘å‚«‚¢‚©
    //            if (0 <= result.z)
    //            {
    //                return true;
    //            }
    //        }
    //    }
    //}
    return false;
}

XMFLOAT3 Math::FacingConversion(XMFLOAT3 myDir,XMFLOAT3 pairDir)
{
    XMVECTOR dir = XMVector3Normalize(XMLoadFloat3(&myDir)) + XMVector3Normalize(XMLoadFloat3(&pairDir));
    XMStoreFloat3(&myDir, dir);
    return myDir;
}

bool Math::SegmentToPlane(XMFLOAT3 segstart, XMFLOAT3 segend, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, XMFLOAT3* s1, XMFLOAT3* s2, float* length, XMFLOAT3* pos)
{
    XMFLOAT3 a = XMFLOAT3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
    XMFLOAT3 b = XMFLOAT3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
    XMFLOAT3 d = XMFLOAT3(segstart.x - v0.x, segstart.y - v0.y, segstart.z - v0.z);

    XMFLOAT3 dir = XMFLOAT3(segend.x - segstart.x, segend.y - segstart.y, segend.z - segstart.z);
    float Dist;
    Dist = (float)sqrt(pow(dir.x, 2.0) + pow(dir.y, 2.0) + pow(dir.z, 2.0));

    XMVECTOR vDir = XMLoadFloat3(&dir);
    vDir = XMVector3Normalize(vDir);
    XMStoreFloat3(&dir, vDir);

    dir = XMFLOAT3(-dir.x, -dir.y, -dir.z);

    float u, v, l;
    u = Det(d, b, dir) / Det(a, b, dir);
    v = Det(a, d, dir) / Det(a, b, dir);
    l = Det(a, b, d) / Det(a, b, dir);
    if (u + v <= 1 && l >= 0 && u >= 0 && v >= 0 && l <= Dist)
    {
        *length = l;
        *s1 = a;
        *s2 = b;
        *pos = XMFLOAT3{ u,l,v };
        return true;
    }
    return false;
}

XMFLOAT3 Math::AddXMFLOAT3(XMFLOAT3 f1, XMFLOAT3 f2)
{
    return XMFLOAT3(f1.x + f2.x, f1.y + f2.y, f1.z + f2.z);
}

XMFLOAT3 Math::AddXMFLOAT3(XMFLOAT3 f1, float f2)
{
    return XMFLOAT3(f1.x + f2, f1.y + f2, f1.z + f2);
}

XMFLOAT3 Math::SubtractionXMFLOAT3(XMFLOAT3 f1, XMFLOAT3 f2)
{
    return XMFLOAT3(f1.x - f2.x, f1.y - f2.y, f1.z - f2.z);
}

XMFLOAT3 Math::SubtractionXMFLOAT3(XMFLOAT3 f1, float f2)
{
    return XMFLOAT3(f1.x - f2, f1.y - f2, f1.z - f2);
}

XMFLOAT3 Math::MultiplicationXMFLOAT3(XMFLOAT3 f1, XMFLOAT3 f2)
{
    return XMFLOAT3(f1.x * f2.x, f1.y * f2.y, f1.z * f2.z);
}

XMFLOAT3 Math::MultiplicationXMFLOAT3(XMFLOAT3 f1, float f2)
{
    return XMFLOAT3(f1.x * f2, f1.y * f2, f1.z * f2);
}

XMFLOAT3 Math::DivisionXMFLOAT3(XMFLOAT3 f1, XMFLOAT3 f2)
{
    return XMFLOAT3(f1.x / f2.x, f1.y / f2.y, f1.z / f2.z);
}

XMFLOAT3 Math::DivisionXMFLOAT3(XMFLOAT3 f1, float f2)
{
    return XMFLOAT3(f1.x / f2, f1.y / f2, f1.z / f2);
}

XMFLOAT3 Math::GetDisplacement(XMFLOAT3 f1, XMFLOAT3 f2)
{
    XMFLOAT3 f3 = SubtractionXMFLOAT3(f1, f2);
    f1 = DivisionXMFLOAT3(AddXMFLOAT3(f1, f3),2.0f);
    return f1;
  /*  XMVECTOR v1 = XMLoadFloat3(&f1);
    XMVECTOR v2 = XMLoadFloat3(&f2);
    float dis = XMVectorGetX(XMVector3Length(v1 - v2));

    int a = 0;
    return dis;*/
}
