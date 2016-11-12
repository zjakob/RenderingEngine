#version 430

uniform struct LightInfo {
    vec4 Position;
    vec3 Intensity;
} Light;

uniform struct MaterialInfo {
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    float Shininess;
} Material;

uniform sampler2DShadow ShadowMap;

in vec3 Position;
in vec3 Normal;
in vec4 ShadowCoord;

layout ( location = 0 ) out vec4 FragColor;

vec3 phongModelDiffAndSpec()
{
    vec3 s = normalize(vec3(Light.Position) - Position);
    vec3 v = normalize(-Position.xyz);
    vec3 r = reflect( -s, Normal );
    float sDotN = max( dot(s,Normal), 0.0 );
    vec3 diffuse = Light.Intensity * Material.Kd * sDotN;
    vec3 spec = vec3(0.0);
    if( sDotN > 0.0 )
        spec = Light.Intensity * Material.Ks *
            pow( max( dot(r,v), 0.0 ), Material.Shininess );

    return diffuse + spec;
}

void main()
{
    vec3 ambient = Light.Intensity * Material.Ka;
    vec3 diffAndSpec = phongModelDiffAndSpec();
	
	ivec2 ts = textureSize(ShadowMap, 0);
	float startstop = 2; // 1 = 9x, 2 = 25x, 3 = 49x, ...

	float sum = 0, count = 0;
	float x, y;
	for (y = -startstop; y <= startstop; y += 1.0)
	for (x = -startstop; x <= startstop; x += 1.0) {
		// Can't use texture(Proj)Offset directly since it expects the offset to be a constant value,
		// i.e. no loops, so instead we calculate the offset manually (given the texture size)
		vec2 texmapscale = vec2(1.0/ts.x, 1.0/ts.y);
		vec2 offset = vec2(x, y);
		sum += textureProj(ShadowMap, vec4(ShadowCoord.xy + offset * texmapscale * ShadowCoord.w, ShadowCoord.z, ShadowCoord.w));
		count++;
	}

	float shadow = sum / count;
	
    // If the fragment is in shadow, use ambient light only.
    FragColor = vec4(diffAndSpec * shadow + ambient, 1.0);

    // Gamma correct
    FragColor = pow( FragColor, vec4(1.0 / 2.2) );
}
