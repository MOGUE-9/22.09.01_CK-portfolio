#include "framework.h"


//Light::Light()
//{
//    for (int i = 0; i < 10; i++)
//    {
//        //화면상의 좌표
//        light.elem[i].screenPos = Vector2(app.GetHalfWidth(), app.GetHalfHeight());
//        //조명 반지름
//        light.elem[i].radius = 0.0f;
//        //light.elem[i].lightColor = Color(0.5f, 0.5f, 0.5f, 0.5f); // 안에 섞을 색
//    }
//    light.select.x = 1.0f;
//    light.inColor = Color(0.5f, 0.5f, 0.5f, 0.5f); // 안에 섞을 색
//    light.outColor = Color(0.1f, 0.1f, 0.1f, 0.5f);
//
//    light.elem[0].radius = 2000.0f;
//
//    //light.elem[1].screenPos = Vector2(app.GetHalfWidth() + 100, app.GetHalfHeight() + 100);
//    //light.elem[1].radius = 100.0f;
//
//
//    //CreateConstantBuffer
//    {
//        D3D11_BUFFER_DESC desc = { 0 };
//        desc.ByteWidth = sizeof(LightBuffer); //PointLight 크기로
//        desc.Usage = D3D11_USAGE_DYNAMIC;
//        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; //상수버퍼
//        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//        desc.MiscFlags = 0;
//        desc.StructureByteStride = 0;
//        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &lightBuffer);
//        assert(SUCCEEDED(hr));
//    }
//
//    D3D->GetDC()->PSSetConstantBuffers(0, 1, &lightBuffer);
//}
//
//Light::~Light()
//{
//    SafeRelease(lightBuffer);
//}
//
//void Light::Set()
//{
//    D3D11_MAPPED_SUBRESOURCE mappedResource;
//    D3D->GetDC()->Map(lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
//    memcpy_s(mappedResource.pData, sizeof(LightBuffer), &light, sizeof(LightBuffer));
//    D3D->GetDC()->Unmap(lightBuffer, 0);
//}
//
//void Light::LightBuffer::SetLight(Vector2 WPos, int i)
//{
//    //World To Screen
//    WPos -= CAM->position;
//    WPos.y *= -1.0f;
//    WPos += Vector2(app.GetHalfWidth(), app.GetHalfHeight());
//    elem->screenPos = WPos;
//}

Light::Light()
{
    //화면상의 좌표
    light.screenPos = Vector2(app.GetHalfWidth(), app.GetHalfHeight());
    //조명 반지름
    light.radius = 2000.0f;
    //조명색
    light.lightColor = Color(0.5f, 0.5f, 0.5f, 0.5f); // 안에 섞을 색
    //경계밖 색
    light.outColor = Color(0.0f, 0.0f, 0.0f, 0.8f); //밖에 섞을 색
    light.select = 0;

    //CreateConstantBuffer
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.ByteWidth = sizeof(PointLight); //PointLight 크기로
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; //상수버퍼
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &lightBuffer);
        assert(SUCCEEDED(hr));
    }

    D3D->GetDC()->PSSetConstantBuffers(0, 1, &lightBuffer);
}

Light::~Light()
{
    SafeRelease(lightBuffer);
}

void Light::Set()
{
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    D3D->GetDC()->Map(lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    memcpy_s(mappedResource.pData, sizeof(PointLight), &light, sizeof(PointLight));
    D3D->GetDC()->Unmap(lightBuffer, 0);
}

void Light::SetLightPos(Vector2 WPos)
{
    //World To Screen
    WPos -= CAM->position;
    WPos.y *= -1.0f;
    WPos += Vector2(app.GetHalfWidth(), app.GetHalfHeight());
    light.screenPos = WPos;
}

