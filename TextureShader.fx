cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix lightViewMatrix;
	matrix lightProjectionMatrix;
};

cbuffer LightBuffer
{
	float4 ambientColor;
	float4 diffuseColor;
	float4 specularColor;
	float3 lightDirection;
	float specularPower;
	float3 cameraDirection;
	float padding;
};

struct VS_IN
{
	float4 pos : POSITION0;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float4 lightViewPosition : TEXCOORD1;
	float3 lightPos : TEXCOORD2;
};

Texture2D DiffuseMap	: register(t0);
Texture2D depthMapTexture : register(t1);

SamplerState Sampler	: register(s0);
SamplerState SampleTypeClamp : register(s1);


PS_IN VSMain(VS_IN input)
{
	PS_IN output = (PS_IN)0;

	float3 lightPos = lightDirection * -50.0;

	float4 worldPosition;

	output.pos = mul(float4(input.pos.xyz, 1.0f), worldMatrix);
	output.pos = mul(output.pos, viewMatrix);
	output.pos = mul(output.pos, projectionMatrix);
	output.tex = input.tex.xy;
	// Calculate the normal vector against the world matrix only.
	output.normal = mul(input.normal, (float3x3)worldMatrix);

	// Normalize the normal vector.
	output.normal = normalize(output.normal);

	// Calculate the position of the vertice as viewed by the light source.
	output.lightViewPosition = mul(input.pos, worldMatrix);
	output.lightViewPosition = mul(output.lightViewPosition, lightViewMatrix);
	output.lightViewPosition = mul(output.lightViewPosition, lightProjectionMatrix);

	worldPosition = mul(input.pos, worldMatrix);
	
	// Determine the light position based on the position of the light and the position of the vertex in the world.
	output.lightPos = lightPos.xyz - worldPosition.xyz;

	// Normalize the light position vector.
	output.lightPos = normalize(output.lightPos);

	return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
	float bias;
	float depthValue;
	float lightDepthValue;
	float2 projectTexCoord;
	float3 lightDir;
	float3 camDir;
	float4 difInt, ambInt, specInt;
	float cosTheta, cosPhi, rAngle;
	float3 r, nrAng;

	bias = 0.001f;

	// Calculate the projected texture coordinates.
	projectTexCoord.x = input.lightViewPosition.x / input.lightViewPosition.w / 2.0f + 0.5f;
	projectTexCoord.y = -input.lightViewPosition.y / input.lightViewPosition.w / 2.0f + 0.5f;

	camDir = -cameraDirection;
	lightDir = -lightDirection;

	float4 color = ambientColor;
	specInt.x = 0;
	specInt.y = 0;
	specInt.z = 0;
	specInt.w = 1.0;

	// Determine if the projected coordinates are in the 0 to 1 range.  If so then this pixel is in the view of the light.
	if ((saturate(projectTexCoord.x) == projectTexCoord.x) && (saturate(projectTexCoord.y) == projectTexCoord.y))
	{

		// Sample the shadow map depth value from the depth texture using the sampler at the projected texture coordinate location.
		depthValue = depthMapTexture.Sample(SampleTypeClamp, projectTexCoord).r;

		// Calculate the depth of the light.
		lightDepthValue = input.lightViewPosition.z / input.lightViewPosition.w;

		// Subtract the bias from the lightDepthValue.
		lightDepthValue = lightDepthValue - bias;

		// Compare the depth of the shadow map value and the depth of the light to determine whether to shadow or to light this pixel.
	   // If the light is in front of the object then light the pixel, if not then shadow this pixel since an object (occluder) is casting a shadow on it.
		if (lightDepthValue < depthValue)
		{

			cosTheta = saturate(dot(input.normal, lightDir));

			difInt = diffuseColor * cosTheta;

			rAngle = 2 * cosTheta;
			nrAng = rAngle * input.normal;
			r = nrAng - lightDir;
			cosPhi = saturate(dot(camDir, r));
			cosPhi = pow(cosPhi, specularPower);

			specInt = specularColor * cosPhi;

			color += 0.2;
			color += difInt * 4;
			color = saturate(color);
		}

	}

	float4 texColor = DiffuseMap.Sample(Sampler, input.tex.xy);
	color = color * texColor;
	color = saturate(specInt + color);
	return color;
}
