// ----------------------- notepad -------------------------------------------------------------------------------------------------------

release, 5000, fullscreen - ~270 fps after some time

«Помогавший забеременеть» Оксане Федоровой целитель искалечил москвичкуэ


// Шейдер теперь принимает на вход массив текстур
// Доступ к разным текстурам осуществляется посредством третьего параметра, передаваемого в семплер
//  Пример:
// float4 textureColor1 = myTextureArray.Sample(SampleType, float3(input.tex.x, input.tex.y, 0));
// float4 textureColor2 = myTextureArray.Sample(SampleType, float3(input.tex.x, input.tex.y, 1));

Texture2DArray myTextureArray;
SamplerState   SampleType;

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex		: TEXCOORD0;
    uint   material : BLENDINDICES0;
};

// Pixel Shader
float4 TexturePixelShader(PixelInputType input) : SV_TARGET
{
    float4 textureColor;

    // **********************************************************************************

    // http://dallinwellington.com/rendering/sprite-atlas-rendering-with-dx-hlsl/

    float texX;
    float texY;
    float texZ;

    myTextureArray.GetDimensions(X, Y, X);

    // эти три параметра нам известны, мы их получим снаружи
    int index = 5;                              // номер кусочка, который хотим отрисовать
    int sliceSizeX = 20;                        // ширина одного кусочка
    int sliceSizeY = 20;                        // высота одного кусочка

    int slicesCntX = texX / sliceSizeX;         // число кусочков, которое вмещается в текстуру по ширине

    int vIndex = index / slicesCntX;            // ряд с нужным кусочком

    int hIndex = index - (slicesCntX * vIndex); // столбец с нужным кусочком

    input.tex = float2((input.tex.x / slicesX) + (((textureWidth / slicesX) * float(hIndex)) / textureWidth),
        (input.tex.y / slicesY) + (((textureHeight / slicesY) * float(vIndex)) / textureHeight));

    // **********************************************************************************

    textureColor = myTextureArray.Sample(SampleType, float3(input.tex.x, input.tex.y, input.material));

    return textureColor;
}
