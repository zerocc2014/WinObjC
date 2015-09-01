//******************************************************************************
//
// Copyright (c) 2015 Microsoft Corporation. All rights reserved.
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
//******************************************************************************

#pragma once

#include <math.h>

#include <QuartzCore/CATransform3D.h>

typedef CATransform3D GLKMatrix4;
typedef CAPoint3D GLKVector3;

typedef struct _GLKVector4 {
    union {
        struct { float x, y, z, w; };
        struct { float r, g, b, a; };
        struct { float s, t, p, q; };
        float v[4];
    };
} GLKVector4;

typedef struct _GLKMatrix3 {
    union {
        struct {
            float m11, m12, m13;
            float m21, m22, m23;
            float m31, m32, m33;
        };
        float m[3][3];
    };
} GLKMatrix3;

// --------------------------------------------------------------------------------
// Matrices

GLKMatrix3 GLKMatrix3Identity();
GLKMatrix3 GLKMatrix3FromMatrix4(GLKMatrix4 m);
GLKMatrix4 GLKMatrix4Identity();
GLKMatrix4 GLKMatrix4Make(float m00, float m01, float m02, float m03,
                          float m10, float m11, float m12, float m13,
                          float m20, float m21, float m22, float m23,
                          float m30, float m31, float m32, float m33);
GLKMatrix3 GLKMatrix3Make(float m00, float m01, float m02,
                          float m10, float m11, float m12,
                          float m20, float m21, float m22);
GLKMatrix4 GLKMatrix3Transpose(GLKMatrix4 mat);
GLKMatrix4 GLKMatrix4Transpose(GLKMatrix4 mat);
GLKMatrix3 GLKMatrix3MakeAndTranspose(float m00, float m01, float m02,
                                      float m10, float m11, float m12,
                                      float m20, float m21, float m22);
GLKMatrix4 GLKMatrix4MakeAndTranspose(float m00, float m01, float m02, float m03,
                                      float m10, float m11, float m12, float m13,
                                      float m20, float m21, float m22, float m23,
                                      float m30, float m31, float m32, float m33);
GLKMatrix4 GLKMatrix4MakeWithArray(float* values);
GLKMatrix4 GLKMatrix4MakeWithArrayAndTranspose(float* values);
GLKMatrix4 GLKMatrix4MakeWithColumns(GLKVector4 r0, GLKVector4 r1, GLKVector4 r2, GLKVector4 r3);
GLKMatrix4 GLKMatrix4MakeWithRows(GLKVector4 r0, GLKVector4 r1, GLKVector4 r2, GLKVector4 r3);
GLKMatrix4 GLKMatrix4MakeOrthonormalXform(GLKVector3 right, GLKVector3 up, GLKVector3 forward, GLKVector3 pos);

GLKMatrix4 GLKMatrix4Invert(GLKMatrix4 m, bool* invertible);

inline GLKMatrix4 GLKMatrix4MakeRotation(float rad, float x, float y, float z)  { return CATransform3DMakeRotation(rad, x, y, z); }
inline GLKMatrix4 GLKMatrix4MakeXRotation(float rad)                            { return CATransform3DMakeRotation(rad, 1.f, 0.f, 0.f); }
inline GLKMatrix4 GLKMatrix4MakeYRotation(float rad)                            { return CATransform3DMakeRotation(rad, 0.f, 1.f, 0.f); }
inline GLKMatrix4 GLKMatrix4MakeZRotation(float rad)                            { return CATransform3DMakeRotation(rad, 0.f, 0.f, 1.f); }

inline GLKMatrix4 GLKMatrix4MakeTranslation(float x, float y, float z)          { return CATransform3DMakeTranslation(x, y, z); }
inline GLKMatrix4 GLKMatrix4MakeScale(float x, float y, float z)                { return CATransform3DMakeScale(x, y, z); }

GLKMatrix4 GLKMatrix4MakeLookAt(float eyeX, float eyeY, float eyeZ,
                                float lookX, float lookY, float lookZ,
                                float upX, float upY, float upZ);
GLKMatrix4 GLKMatrix4MakeOrtho(float left, float right, float bot, float top, float near, float far);
GLKMatrix4 GLKMatrix4MakePerspective(float yrad, float aspect, float near, float far);
GLKMatrix4 GLKMatrix4MakeFrustum(float left, float right, float bottom, float top, float near, float far);

GLKMatrix4 GLKMatrixMultiply(GLKMatrix4 m1, GLKMatrix4 m2);

// --------------------------------------------------------------------------------
// Vectors.

inline GLKVector3 GLKVector3Make(float x, float y, float z)
{
    GLKVector3 res;

    res.x = x;
    res.y = y;
    res.z = z;

    return res;
}

inline GLKVector4 GLKVector4Make(float x, float y, float z, float w)
{
    GLKVector4 res;

    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;

    return res;
}

inline GLKVector3 GLKVector3MakeWithArray(float* values)
{
    GLKVector3 res;

    res.x = values[0];
    res.y = values[1];
    res.z = values[2];

    return res;
}

inline GLKVector4 GLKVector4MakeWithArray(float* values)
{
    GLKVector4 res;

    res.x = values[0];
    res.y = values[1];
    res.z = values[2];
    res.w = values[3];

    return res;
}

inline GLKVector4 GLKVector4MakeWithVector3(GLKVector3 v, float w)
{
    GLKVector4 res;

    res.x = v.x;
    res.y = v.y;
    res.z = v.z;
    res.w = w;

    return res;
}

inline float GLKVector3DotProduct(GLKVector3 v1, GLKVector3 v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline float GLKVector4DotProduct(GLKVector4 v1, GLKVector4 v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

inline float GLKVector3Length(GLKVector3 v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline float GLKVector4Length(GLKVector4 v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

inline GLKVector3 GLKVector3Normalize(GLKVector3 v)
{
    float invlen = 1.f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    return GLKVector3Make(v.x * invlen, v.y * invlen, v.z * invlen);
}

inline GLKVector4 GLKVector4Normalize(GLKVector4 v)
{
    float invlen = 1.f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    return GLKVector4Make(v.x * invlen, v.y * invlen, v.z * invlen, v.w * invlen);
}

inline GLKVector3 GLKVector3Add(GLKVector3 v1, GLKVector3 v2)
{
    return GLKVector3Make(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline GLKVector4 GLKVector4Add(GLKVector4 v1, GLKVector4 v2)
{
    return GLKVector4Make(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

inline GLKVector3 GLKVector3AddScalar(GLKVector3 v1, float s)
{
    return GLKVector3Make(v1.x + s, v1.y + s, v1.z + s);
}

inline GLKVector4 GLKVector4AddScalar(GLKVector4 v1, float s)
{
    return GLKVector4Make(v1.x + s, v1.y + s, v1.z + s, v1.w + s);
}

inline GLKVector3 GLKVector3SubtractScalar(GLKVector3 v1, float s)
{
    return GLKVector3Make(v1.x - s, v1.y - s, v1.z - s);
}

inline GLKVector4 GLKVector4SubtractScalar(GLKVector4 v1, float s)
{
    return GLKVector4Make(v1.x - s, v1.y - s, v1.z - s, v1.w - s);
}

inline GLKVector3 GLKVector3MultiplyScalar(GLKVector3 v1, float s)
{
    return GLKVector3Make(v1.x * s, v1.y * s, v1.z * s);
}

inline GLKVector4 GLKVector4MultiplyScalar(GLKVector4 v1, float s)
{
    return GLKVector4Make(v1.x * s, v1.y * s, v1.z * s, v1.w * s);
}

inline GLKVector3 GLKVector3DivideScalar(GLKVector3 v1, float s)
{
    return GLKVector3Make(v1.x / s, v1.y / s, v1.z / s);
}

inline GLKVector4 GLKVector4DivideScalar(GLKVector4 v1, float s)
{
    return GLKVector4Make(v1.x / s, v1.y / s, v1.z / s, v1.w / s);
}

inline GLKVector3 GLKVector3Subtract(GLKVector3 v1, GLKVector3 v2)
{
    return GLKVector3Make(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline GLKVector4 GLKVector4Subtract(GLKVector4 v1, GLKVector4 v2)
{
    return GLKVector4Make(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

inline GLKVector3 GLKVector3Negate(GLKVector3 v)
{
    return GLKVector3Make(-v.x, -v.y, -v.z);
}

inline GLKVector4 GLKVector4Negate(GLKVector4 v)
{
    return GLKVector4Make(-v.x, -v.y, -v.z, -v.w);
}

inline float GLKVector3Distance(GLKVector3 v1, GLKVector3 v2)
{
    GLKVector3 v = GLKVector3Subtract(v1, v2);
    return GLKVector3Length(v);
}

inline float GLKVector4Distance(GLKVector4 v1, GLKVector4 v2)
{
    GLKVector4 v = GLKVector4Subtract(v1, v2);
    return GLKVector4Length(v);
}

inline GLKVector3 GLKVector3Divide(GLKVector3 v1, GLKVector3 v2)
{
    return GLKVector3Make(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

inline GLKVector4 GLKVector4Divide(GLKVector4 v1, GLKVector4 v2)
{
    return GLKVector4Make(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}

inline GLKVector3 GLKVector3Multiply(GLKVector3 v1, GLKVector3 v2)
{
    return GLKVector3Make(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

inline GLKVector4 GLKVector4Multiply(GLKVector4 v1, GLKVector4 v2)
{
    return GLKVector4Make(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

inline GLKVector4 GLKVector4CrossProduct(GLKVector4 l, GLKVector4 r)
{
    return GLKVector4Make(l.y * r.z - l.z * r.y,
                          l.z * r.x - l.x * r.z,
                          l.x * r.y - l.y * r.x,
                          1.f);
}

inline GLKVector3 GLKVector3CrossProduct(GLKVector3 l, GLKVector3 r)
{
    return GLKVector3Make(l.y * r.z - l.z * r.y,
                          l.z * r.x - l.x * r.z,
                          l.x * r.y - l.y * r.x);
}

inline GLKVector4 GLKVector4Lerp(GLKVector4 a, GLKVector4 b, float t)
{
    float it = (1.f - t);
    GLKVector4 res;

    res.x = t * b.x + it * a.x;
    res.y = t * b.y + it * a.y;
    res.z = t * b.z + it * a.z;
    res.w = t * b.w + it * a.w;
    
    return res;
}

inline GLKVector3 GLKVector3Lerp(GLKVector3 a, GLKVector3 b, float t)
{
    float it = (1.f - t);
    GLKVector3 res;

    res.x = t * b.x + it * a.x;
    res.y = t * b.y + it * a.y;
    res.z = t * b.z + it * a.z;
    
    return res;
}

// --------------------------------------------------------------------------------
// Utilities.

inline GLKVector3 GLKVector3Origin()    { return GLKVector3Make(0.f, 0.f, 0.f); }
inline GLKVector3 GLKVector3XAxis()     { return GLKVector3Make(1.f, 0.f, 0.f); }
inline GLKVector3 GLKVector3YAxis()     { return GLKVector3Make(0.f, 1.f, 0.f); }
inline GLKVector3 GLKVector3ZAxis()     { return GLKVector3Make(0.f, 0.f, 1.f); }

inline GLKVector4 GLKVector4Black()     { return GLKVector4Make(0.f, 0.f, 0.f, 1.f); }
inline GLKVector4 GLKVector4White()     { return GLKVector4Make(1.f, 1.f, 1.f, 1.f); }
