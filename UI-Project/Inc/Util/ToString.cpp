#include "ToString.h"
#include "../Containers/Str.h"
#include "../Math/Color.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Quaternion.h"
#include "../Math/Sphere.h"
#include "../Math/Rect.h"

namespace Pyro 
{
    String ToString::FromColor(const Color& color){
        String ret(color.r);
        ret += ',';
        ret += color.g;
        ret += ',';
        ret += color.b;
        ret += ',';
        ret += color.a;
        return ret;
    }

    String ToString::FromVector2(const Vector2& vec){
        String ret(vec.x);
        ret += ',';
        ret += vec.y;
        return ret;
    }

    String ToString::FromVector3(const Vector3& vec){
        String ret(vec.x);
        ret += ',';
        ret += vec.y;
        ret += ',';
        ret += vec.z;
        return ret;
    }
    String ToString::FromVector4(const Vector4& vec){
        String ret(vec.x);
        ret += ',';
        ret += vec.y;
        ret += ',';
        ret += vec.z;
        ret += ',';
        ret += vec.w;
        return ret;
    }

    String ToString::FromQuaternion(const Quaternion& quaternion){
        String ret(quaternion.x);
        ret += ',';
        ret += quaternion.y;
        ret += ',';
        ret += quaternion.z;
        ret += ',';
        ret += quaternion.w;
        return ret;
    }

    String ToString::FromSphere(const Sphere& sphere){
        String ret = FromVector3(sphere.Center());
        ret += ',';
        ret += "(" + String(sphere.Radius()) + ")";
        return ret;
    }

    String ToString::FromRect(const Rect& rect){
        String ret(rect.x);
        ret += ',';
        ret += rect.y;
        ret += ',';
        ret += rect.width;
        ret += ',';
        ret += rect.height;
        return ret;
    }
}