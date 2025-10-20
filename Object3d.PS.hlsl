#include "object3d.hlsli"

struct Material
{
    float32_t4 color;
};
ConstantBuffer<Material> gMaterial : register(b0);
Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);
struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);
    output.color = gMaterial.color * textureColor;
    
    input.normal = normalize(mul(input.normal, (float32_t3x3) gTransformationMatrix.World));
    
    return output;
    
    
};

ConstantBuffer<DirectionalLight>gDirectionalLight : register(b1);


struct vertexShaderOutput
{
    float32_t position : SV_Position;
    float32_t texcoord : TEXCOORDO;
    float32_t normal : NORMAL;
};